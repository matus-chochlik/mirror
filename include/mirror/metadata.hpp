/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_METADATA_HPP
#define MIRROR_METADATA_HPP

#include "hash.hpp"
#include "operations.hpp"
#include "registry_fwd.hpp"
#include "traits.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include <vector>

namespace mirror {
//------------------------------------------------------------------------------
class metadata_not_found : public std::runtime_error {
public:
    metadata_not_found() noexcept
      : std::runtime_error{"metadata not found"} {}
};
//------------------------------------------------------------------------------
class metadata_iterator {
private:
    using base_iter_t = std::vector<const metadata*>::const_iterator;
    base_iter_t _iter{};

public:
    using value_type = const metadata;
    using pointer = const metadata*;
    using reference = const metadata&;
    using difference_type = base_iter_t::difference_type;
    using iterator_category = base_iter_t::iterator_category;

    metadata_iterator(base_iter_t iter) noexcept
      : _iter{iter} {}

    friend auto
    operator==(const metadata_iterator& l, const metadata_iterator& r) noexcept
      -> bool {
        return l._iter == r._iter;
    }

    friend auto
    operator!=(const metadata_iterator& l, const metadata_iterator& r) noexcept
      -> bool {
        return l._iter != r._iter;
    }

    friend auto
    operator<(const metadata_iterator& l, const metadata_iterator& r) noexcept
      -> bool {
        return l._iter < r._iter;
    }

    friend auto
    operator-(const metadata_iterator& l, const metadata_iterator& r) noexcept
      -> difference_type {
        return l._iter - r._iter;
    }

    friend auto
    operator+(const metadata_iterator& i, difference_type ofs) noexcept
      -> metadata_iterator {
        return {i._iter + ofs};
    }

    friend auto
    operator-(const metadata_iterator& i, difference_type ofs) noexcept
      -> metadata_iterator {
        return {i._iter - ofs};
    }

    auto operator++() noexcept -> auto& {
        ++_iter;
        return *this;
    }

    auto operator++(int) noexcept -> auto {
        auto copy{*this};
        ++_iter;
        return copy;
    }

    auto operator+=(difference_type ofs) noexcept -> auto& {
        _iter += ofs;
        return *this;
    }

    auto operator--() noexcept -> auto& {
        --_iter;
        return *this;
    }

    auto operator--(int) noexcept -> auto {
        auto copy{*this};
        --_iter;
        return copy;
    }

    auto operator-=(difference_type ofs) noexcept -> auto& {
        _iter -= ofs;
        return *this;
    }

    auto operator*() noexcept -> const metadata& {
        return **_iter;
    }
};
//------------------------------------------------------------------------------
class metadata_sequence {
private:
    std::vector<const metadata*> _elements;

protected:
    metadata_sequence() noexcept = default;

    metadata_sequence(std::vector<const metadata*> elements) noexcept
      : _elements{elements} {}

    friend class metadata_registry;

    auto _emplace_elements(std::vector<const metadata*> elements) noexcept
      -> auto& {
        _elements = std::move(elements);
        return _elements;
    }

public:
    friend auto operator+(const metadata_sequence& l, const metadata_sequence& r)
      -> metadata_sequence {
        std::vector<const metadata*> elements;
        elements.reserve(l._elements.size() + r._elements.size());
        elements.insert(elements.end(), l._elements.begin(), l._elements.end());
        elements.insert(elements.end(), r._elements.begin(), r._elements.end());
        return {elements};
    }

    auto element(size_t index) const noexcept -> const metadata& {
        return *_elements[index];
    }

    auto count() const noexcept -> size_t {
        return _elements.size();
    }

    auto begin() const noexcept -> metadata_iterator {
        return {_elements.begin()};
    }

    auto end() const noexcept -> metadata_iterator {
        return {_elements.end()};
    }

    auto contains(const metadata& md) const noexcept;

    template <typename F>
    auto filtered(F predicate) const -> metadata_sequence;

    auto intersecting(const metadata_sequence& s) const -> metadata_sequence;

    auto excluding(const metadata_sequence& s) const -> metadata_sequence;

    auto having_all(meta_traits t) const -> metadata_sequence;
    auto having(meta_traits t) const -> metadata_sequence;
    auto not_having(meta_traits t) const -> metadata_sequence;

    auto having_all(type_traits t) const -> metadata_sequence;
    auto having(type_traits t) const -> metadata_sequence;
    auto not_having(type_traits t) const -> metadata_sequence;

    auto having_all(object_traits t) const -> metadata_sequence;
    auto having(object_traits t) const -> metadata_sequence;
    auto not_having(object_traits t) const -> metadata_sequence;

    auto supporting(operations_boolean op) const -> metadata_sequence;

    auto supporting(operations_integer op) const -> metadata_sequence;

    auto supporting(operations_string op) const -> metadata_sequence;

    auto supporting(operations_metaobject op) const -> metadata_sequence;

    auto with_name() const -> metadata_sequence {
        return supporting(operation::get_name);
    }
};
//------------------------------------------------------------------------------
class metadata : public metadata_sequence {
private:
    hash_t _id{0U};
    meta_traits _meta_traits{};
    type_traits _type_traits{};

    operations_boolean _op_boolean_results{};
    operations_boolean _op_boolean_applicable{};
    operations_metaobject _op_metaobject_applicable{};
    operations_integer _op_integer_applicable{};
    operations_string _op_string_applicable{};

    size_t _source_column{0U};
    size_t _source_line{0U};

    std::string_view _name{};
    std::string_view _display_name{};
    std::string _full_name{};

protected:
    const metadata& _none{*this};
    const metadata* _scope{&_none};
    const metadata* _type{&_none};
    const metadata* _base_type{&_none};
    const metadata* _element_type{&_none};
    const metadata* _underlying_type{&_none};
    const metadata* _aliased{&_none};
    const metadata* _class{&_none};

    const metadata* _base_classes{&_none};
    const metadata* _captures{&_none};
    const metadata* _constructors{&_none};
    const metadata* _data_members{&_none};
    const metadata* _destructors{&_none};
    const metadata* _enumerators{&_none};
    const metadata* _member_functions{&_none};
    const metadata* _member_types{&_none};
    const metadata* _operators{&_none};
    const metadata* _parameters{&_none};

    auto _needs_elements() const noexcept -> bool {
        return _op_boolean_applicable.has(trait::is_empty) &&
               !_op_boolean_results.has(trait::is_empty) && (count() == 0Z);
    }

    metadata() noexcept = default;

    metadata(
      hash_t id,
      meta_traits meta_tr,
      type_traits type_tr,
      operations_boolean op_boolean_results,
      operations_boolean op_boolean_applicable,
      operations_metaobject op_metaobject_applicable,
      operations_integer op_integer_applicable,
      operations_string op_string_applicable,
      size_t source_column,
      size_t source_line,
      std::string_view name,
      std::string_view display_name,
      std::string full_name,
      const metadata& none)
      : _id{id}
      , _meta_traits{meta_tr}
      , _type_traits{type_tr}
      , _op_boolean_results{op_boolean_results}
      , _op_boolean_applicable{op_boolean_applicable}
      , _op_metaobject_applicable{op_metaobject_applicable}
      , _op_integer_applicable{op_integer_applicable}
      , _op_string_applicable{op_string_applicable}
      , _source_column{source_column}
      , _source_line{source_line}
      , _name{name}
      , _display_name{display_name}
      , _full_name{std::move(full_name)}
      , _none{none} {}

public:
    metadata(metadata&&) = delete;
    auto operator=(metadata&&) = delete;
    metadata(const metadata&) = delete;
    auto operator=(const metadata&) = delete;
    ~metadata() noexcept = default;

    auto is_none() const noexcept {
        return !_meta_traits.has(trait::reflects_object);
    }

    explicit operator bool() const noexcept {
        return _meta_traits.has(trait::reflects_object);
    }

    friend bool operator==(const metadata& l, const metadata& r) noexcept {
        return l._id == r._id;
    }

    friend bool operator!=(const metadata& l, const metadata& r) noexcept {
        return l._id != r._id;
    }

    friend bool operator<(const metadata& l, const metadata& r) noexcept {
        return l._id < r._id;
    }

    auto id() const noexcept -> hash_t {
        return _id;
    }

    auto is_applicable(operation_boolean op) const noexcept -> bool {
        return _op_boolean_applicable.has(op);
    }

    auto supports(operations_boolean op) const noexcept -> bool {
        return _op_boolean_applicable.has_all(op);
    }

    auto is_applicable(operation_integer op) const noexcept -> bool {
        return _op_integer_applicable.has(op);
    }

    auto supports(operations_integer op) const noexcept -> bool {
        return _op_integer_applicable.has_all(op);
    }

    auto is_applicable(operation_string op) const noexcept -> bool {
        return _op_string_applicable.has(op);
    }

    auto supports(operations_string op) const noexcept -> bool {
        return _op_string_applicable.has_all(op);
    }

    auto is_applicable(operation_metaobject op) const noexcept -> bool {
        return _op_metaobject_applicable.has(op);
    }

    auto supports(operations_metaobject op) const noexcept -> bool {
        return _op_metaobject_applicable.has_all(op);
    }

    auto has_all(meta_traits t) const noexcept -> bool {
        return _meta_traits.has_all(t);
    }

    auto has(meta_traits t) const noexcept -> bool {
        return _meta_traits.has_some(t);
    }

    auto has_none(meta_traits t) const noexcept -> bool {
        return _meta_traits.has_none(t);
    }

    auto has_all(type_traits t) const noexcept -> bool {
        return _type_traits.has_all(t);
    }

    auto has(type_traits t) const noexcept -> bool {
        return _type_traits.has_some(t);
    }

    auto has_none(type_traits t) const noexcept -> bool {
        return _type_traits.has_none(t);
    }

    auto has_all(object_traits t) const noexcept -> bool {
        return _op_boolean_results.has_all(t) &&
               _op_boolean_applicable.has_all(t);
    }

    auto has(object_traits t) const noexcept -> bool {
        return _op_boolean_results.has_some(t & _op_boolean_applicable);
    }

    auto has_none(object_traits t) const noexcept -> bool {
        return !has(t);
    }

    auto apply(operation_boolean op) const noexcept -> tribool {
        return {_op_boolean_results.has(op), !_op_boolean_applicable.has(op)};
    }

    auto is_empty() const noexcept -> tribool {
        return apply(trait::is_empty);
    }

    auto source_column() const noexcept -> std::optional<size_t> {
        if(_source_column) {
            return {_source_column};
        }
        return {};
    }

    auto source_line() const noexcept -> std::optional<size_t> {
        if(_source_line) {
            return {_source_line};
        }
        return {};
    }

    auto name() const noexcept -> std::optional<std::string_view> {
        if(is_applicable(operation::get_name)) {
            return {_name};
        }
        return {};
    }

    auto name_() const noexcept -> std::string_view {
        return _name;
    }

    auto display_name() const noexcept -> std::optional<std::string_view> {
        if(is_applicable(operation::get_display_name)) {
            return {_display_name};
        }
        return {};
    }

    auto full_name() const noexcept -> std::string_view {
        return _full_name;
    }

    auto scope() const noexcept -> const metadata& {
        return *_scope;
    }

    auto type() const noexcept -> const metadata& {
        return *_type;
    }

    auto base_type() const noexcept -> const metadata& {
        return *_base_type;
    }

    auto element_type() const noexcept -> const metadata& {
        return *_element_type;
    }

    auto underlying_type() const noexcept -> const metadata& {
        return *_underlying_type;
    }

    auto aliased() const noexcept -> const metadata& {
        return *_aliased;
    }

    auto class_() const noexcept -> const metadata& {
        return *_class;
    }

    auto base_classes() const noexcept -> const metadata& {
        return *_base_classes;
    }

    auto captures() const noexcept -> const metadata& {
        return *_captures;
    }

    auto constructors() const noexcept -> const metadata& {
        return *_constructors;
    }

    auto data_members() const noexcept -> const metadata& {
        return *_data_members;
    }

    auto destructors() const noexcept -> const metadata& {
        return *_destructors;
    }

    auto enumerators() const noexcept -> const metadata& {
        return *_enumerators;
    }

    auto member_functions() const noexcept -> const metadata& {
        return *_member_functions;
    }

    auto member_types() const noexcept -> const metadata& {
        return *_member_types;
    }

    auto operators() const noexcept -> const metadata& {
        return *_operators;
    }

    auto parameters() const noexcept -> const metadata& {
        return *_parameters;
    }

    auto size() const noexcept -> std::optional<size_t> {
        if(is_applicable(operation::get_size)) {
            return {count()};
        }
        return {};
    }
};
//------------------------------------------------------------------------------
class metadata_value {
private:
    const metadata* _pmd{nullptr};

public:
    metadata_value() noexcept = default;
    explicit metadata_value(const metadata& md) noexcept
      : _pmd{&md} {}

    friend auto
    operator==(const metadata_value l, const metadata_value r) noexcept
      -> bool {
        if(l._pmd && r._pmd) {
            return *l._pmd == *r._pmd;
        } else if(!l._pmd && !r._pmd) {
            return true;
        }
        return false;
    }

    friend auto
    operator!=(const metadata_value l, const metadata_value r) noexcept
      -> bool {
        return !(l == r);
    }

    friend auto
    operator<(const metadata_value l, const metadata_value r) noexcept -> bool {
        if(l._pmd && r._pmd) {
            return *l._pmd < *r._pmd;
        } else if(l._pmd) {
            return false;
        } else if(r._pmd) {
            return true;
        }
        return true;
    }

    explicit operator bool() const noexcept {
        return bool(_pmd);
    }

    auto get() const noexcept -> const metadata& {
        assert(_pmd);
        return *_pmd;
    }

    operator const metadata&() const noexcept {
        return get();
    }

    auto operator->() const noexcept -> const metadata* {
        return _pmd;
    }
};

static inline auto has_value(const metadata_value& v) noexcept -> bool {
    return bool(v);
}

static inline auto extract(const metadata_value& v) noexcept
  -> const metadata& {
    return v.get();
}
//------------------------------------------------------------------------------
inline auto metadata_sequence::contains(const metadata& md) const noexcept {
    for(const auto* pmd : _elements) {
        if(*pmd == md) {
            return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------
template <typename F>
inline auto metadata_sequence::filtered(F predicate) const
  -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(predicate(*md)) {
            result.push_back(md);
        }
    }
    return {result};
}

inline auto metadata_sequence::intersecting(const metadata_sequence& s) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return s.contains(md); });
}

inline auto metadata_sequence::excluding(const metadata_sequence& s) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return !s.contains(md); });
}

inline auto metadata_sequence::having_all(meta_traits t) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.has_all(t); });
}

inline auto metadata_sequence::having(meta_traits t) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.has(t); });
}

inline auto metadata_sequence::not_having(meta_traits t) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return !md.has(t); });
}

inline auto metadata_sequence::having_all(type_traits t) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.has_all(t); });
}

inline auto metadata_sequence::having(type_traits t) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.has(t); });
}

inline auto metadata_sequence::not_having(type_traits t) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return !md.has(t); });
}

inline auto metadata_sequence::having_all(object_traits t) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.has_all(t); });
}

inline auto metadata_sequence::having(object_traits t) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.has(t); });
}

inline auto metadata_sequence::not_having(object_traits t) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return !md.has(t); });
}

inline auto metadata_sequence::supporting(operations_boolean op) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.supports(op); });
}

inline auto metadata_sequence::supporting(operations_integer op) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.supports(op); });
}

inline auto metadata_sequence::supporting(operations_string op) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.supports(op); });
}

inline auto metadata_sequence::supporting(operations_metaobject op) const
  -> metadata_sequence {
    return filtered([&](auto& md) { return md.supports(op); });
}
//------------------------------------------------------------------------------
} // namespace mirror

#endif

