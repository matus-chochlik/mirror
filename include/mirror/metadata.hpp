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

    auto intersecting(const metadata_sequence& s) const -> metadata_sequence;

    auto excluding(const metadata_sequence& s) const -> metadata_sequence;

    auto satisfying(meta_traits all) const -> metadata_sequence;

    auto satisfying(meta_traits all, meta_traits none) const
      -> metadata_sequence;

    auto supporting(unary_ops_boolean all) const -> metadata_sequence;

    auto supporting(unary_ops_integer all) const -> metadata_sequence;

    auto supporting(unary_ops_string all) const -> metadata_sequence;

    auto supporting(unary_ops_metaobject all) const -> metadata_sequence;

    auto having(traits all) const -> metadata_sequence;

    auto with_name() const -> metadata_sequence {
        return supporting(unary_op_string::get_name);
    }
};
//------------------------------------------------------------------------------
class metadata : public metadata_sequence {
private:
    size_t _id{0U};
    meta_traits _traits{};

    unary_ops_boolean _op_boolean_results{};
    unary_ops_boolean _op_boolean_applicable{};
    unary_ops_metaobject _op_metaobject_applicable{};
    unary_ops_integer _op_integer_applicable{};
    unary_ops_string _op_string_applicable{};

    size_t _source_column{0U};
    size_t _source_line{0U};

    std::string_view _name{};
    std::string_view _display_name{};

protected:
    const metadata& _none{*this};
    const metadata* _scope{&_none};
    const metadata* _type{&_none};
    const metadata* _referenced_type{&_none};
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
      size_t id,
      meta_traits traits,
      unary_ops_boolean op_boolean_results,
      unary_ops_boolean op_boolean_applicable,
      unary_ops_metaobject op_metaobject_applicable,
      unary_ops_integer op_integer_applicable,
      unary_ops_string op_string_applicable,
      size_t source_column,
      size_t source_line,
      std::string_view name,
      std::string_view display_name,
      const metadata& none)
      : _id{id}
      , _traits{traits}
      , _op_boolean_results{op_boolean_results}
      , _op_boolean_applicable{op_boolean_applicable}
      , _op_metaobject_applicable{op_metaobject_applicable}
      , _op_integer_applicable{op_integer_applicable}
      , _op_string_applicable{op_string_applicable}
      , _source_column{source_column}
      , _source_line{source_line}
      , _name{name}
      , _display_name{display_name}
      , _none{none} {}

public:
    metadata(metadata&&) = delete;
    auto operator=(metadata&&) = delete;
    metadata(const metadata&) = delete;
    auto operator=(const metadata&) = delete;
    ~metadata() noexcept = default;

    auto is_none() const noexcept {
        return !_traits.has(meta_trait::reflects_object);
    }

    explicit operator bool() const noexcept {
        return _traits.has(meta_trait::reflects_object);
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

    auto satisfies(meta_traits all) const noexcept -> bool {
        return _traits.has_all(all);
    }

    auto satisfies(meta_traits all, meta_traits none) const noexcept -> bool {
        return _traits.has_all(all) && _traits.has_none(none);
    }

    auto is_applicable(unary_op_boolean op) const noexcept -> bool {
        return _op_boolean_applicable.has(op);
    }

    auto supports(unary_ops_boolean all) const noexcept -> bool {
        return _op_boolean_applicable.has_all(all);
    }

    auto is_applicable(unary_op_integer op) const noexcept -> bool {
        return _op_integer_applicable.has(op);
    }

    auto supports(unary_ops_integer all) const noexcept -> bool {
        return _op_integer_applicable.has_all(all);
    }

    auto is_applicable(unary_op_string op) const noexcept -> bool {
        return _op_string_applicable.has(op);
    }

    auto supports(unary_ops_string all) const noexcept -> bool {
        return _op_string_applicable.has_all(all);
    }

    auto is_applicable(unary_op_metaobject op) const noexcept -> bool {
        return _op_metaobject_applicable.has(op);
    }

    auto supports(unary_ops_metaobject all) const noexcept -> bool {
        return _op_metaobject_applicable.has_all(all);
    }

    auto has(traits all) const noexcept -> bool {
        return _op_boolean_results.has_all(all) &&
               _op_boolean_applicable.has_all(all);
    }

    auto has_some(traits all) const noexcept -> bool {
        return _op_boolean_results.has_some(all & _op_boolean_applicable);
    }

    auto apply(unary_op_boolean op) const noexcept -> tribool {
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
        if(is_applicable(unary_op_string::get_name)) {
            return {_name};
        }
        return {};
    }

    auto name_() const noexcept -> std::string_view {
        return _name;
    }

    auto display_name() const noexcept -> std::optional<std::string_view> {
        if(is_applicable(unary_op_string::get_display_name)) {
            return {_display_name};
        }
        return {};
    }

    auto scope() const noexcept -> const metadata& {
        return *_scope;
    }

    auto type() const noexcept -> const metadata& {
        return *_type;
    }

    auto referenced_type() const noexcept -> const metadata& {
        return *_referenced_type;
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
        if(is_applicable(unary_op_integer::get_size)) {
            return {count()};
        }
        return {};
    }
};
//------------------------------------------------------------------------------
inline auto metadata_sequence::contains(const metadata& md) const noexcept {
    for(const auto* pmd : _elements) {
        if(*pmd == md) {
            return true;
        }
    }
    return false;
}

inline auto metadata_sequence::intersecting(const metadata_sequence& s) const
  -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(s.contains(*md)) {
            result.push_back(md);
        }
    }
    return {result};
}

inline auto metadata_sequence::excluding(const metadata_sequence& s) const
  -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(!s.contains(*md)) {
            result.push_back(md);
        }
    }
    return {result};
}

inline auto metadata_sequence::satisfying(meta_traits all) const
  -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(md->satisfies(all)) {
            result.push_back(md);
        }
    }
    return {result};
}

inline auto
metadata_sequence::satisfying(meta_traits all, meta_traits none) const
  -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(md->satisfies(all, none)) {
            result.push_back(md);
        }
    }
    return {result};
}

inline auto metadata_sequence::supporting(unary_ops_boolean all) const
  -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(md->supports(all)) {
            result.push_back(md);
        }
    }
    return {result};
}

inline auto metadata_sequence::supporting(unary_ops_integer all) const
  -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(md->supports(all)) {
            result.push_back(md);
        }
    }
    return {result};
}

inline auto metadata_sequence::supporting(unary_ops_string all) const
  -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(md->supports(all)) {
            result.push_back(md);
        }
    }
    return {result};
}

inline auto metadata_sequence::supporting(unary_ops_metaobject all) const
  -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(md->supports(all)) {
            result.push_back(md);
        }
    }
    return {result};
}

inline auto metadata_sequence::having(traits all) const -> metadata_sequence {
    std::vector<const metadata*> result;
    for(const auto* md : _elements) {
        if(md->has(all)) {
            result.push_back(md);
        }
    }
    return {result};
}
//------------------------------------------------------------------------------
} // namespace mirror

#endif

