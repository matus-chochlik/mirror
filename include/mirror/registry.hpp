/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_REGISTRY_HPP
#define MIRROR_REGISTRY_HPP

#include "extract.hpp"
#include "hash.hpp"
#include "operations.hpp"
#include "traits.hpp"
#include <map>
#include <vector>

namespace mirror {

class metadata;
class metadata_registry;

template <__metaobject_id M>
auto get_metadata(metadata_registry&, wrapped_metaobject<M>) -> const metadata&;

template <__metaobject_id M>
auto get_metadata(
  metadata_registry&,
  const metadata& scope,
  wrapped_metaobject<M>) -> const metadata&;

template <__metaobject_id M>
auto get_metadata(
  metadata_registry&,
  const metadata& scope,
  const metadata& type,
  wrapped_metaobject<M>) -> const metadata&;

class metadata {
private:
    size_t _id{0U};
    metaobject_traits _traits{};

    bitfield<unary_op_boolean> _op_boolean_results{};
    bitfield<unary_op_boolean> _op_boolean_applicable{};
    bitfield<unary_op_metaobject> _op_metaobject_applicable{};
    bitfield<unary_op_integer> _op_integer_applicable{};
    bitfield<unary_op_string> _op_string_applicable{};

    size_t _source_column{0U};
    size_t _source_line{0U};

    std::string_view _name{};
    std::string_view _display_name{};

    const metadata& _scope{*this};
    const metadata& _type{*this};
    const metadata& _underlying_type{*this};
    const metadata& _aliased{*this};
    const metadata& _class{*this};

    const metadata& _base_classes{*this};
    const metadata& _captures{*this};
    const metadata& _constructors{*this};
    const metadata& _data_members{*this};
    const metadata& _destructors{*this};
    const metadata& _enumerators{*this};
    const metadata& _member_functions{*this};
    const metadata& _member_types{*this};
    const metadata& _operators{*this};
    const metadata& _parameters{*this};

    std::vector<const metadata*> _elements;

    template <__metaobject_id... M>
    static auto _unpack(
      metadata_registry& r,
      const metadata& scope,
      const metadata& type,
      unpacked_metaobject_sequence<M...>) noexcept
      -> std::vector<const metadata*> {
        return {&get_metadata(r, scope, type, wrapped_metaobject<M>{})...};
    }

    template <__metaobject_id M>
    static auto _unpack(
      metadata_registry& r,
      const metadata& scope,
      const metadata& type,
      wrapped_metaobject<M> mo) noexcept -> std::vector<const metadata*> {
        if constexpr(reflects_object_sequence(mo)) {
            return _unpack(r, scope, type, unpack(mo));
        }
        return {};
    }

    template <__metaobject_id M>
    static auto _get_name(wrapped_metaobject<M> mo) noexcept
      -> std::string_view {
        if constexpr(reflects_named(mo)) {
            return get_name(mo);
        }
        return {};
    }

    template <__metaobject_id M>
    static auto _get_display_name(wrapped_metaobject<M> mo) noexcept
      -> std::string_view {
        if constexpr(reflects_named(mo)) {
            return get_display_name(mo);
        }
        return {};
    }

    metadata() noexcept = default;

    template <__metaobject_id M>
    metadata(
      metadata_registry& r,
      const metadata& scope,
      const metadata& type,
      wrapped_metaobject<M> mo) noexcept
      : _id{get_id(mo)}
      , _traits{get_traits(mo)}
      , _source_column{get_source_column(mo)}
      , _source_line{get_source_line(mo)}
      , _name{_get_name(mo)}
      , _display_name{_get_display_name(mo)}
      , _scope{scope}
      , _type{type}
      , _underlying_type{get_metadata(
          r,
          try_apply<unary_op_metaobject::get_underlying_type>(mo))}
      , _aliased{get_metadata(
          r,
          try_apply<unary_op_metaobject::get_aliased>(mo))}
      , _class{get_metadata(r, try_apply<unary_op_metaobject::get_class>(mo))}
      , _base_classes{get_metadata(
          r,
          *this,
          try_apply<unary_op_metaobject::get_base_classes>(mo))}
      , _captures{get_metadata(
          r,
          *this,
          try_apply<unary_op_metaobject::get_captures>(mo))}
      , _constructors{get_metadata(
          r,
          *this,
          try_apply<unary_op_metaobject::get_constructors>(mo))}
      , _data_members{get_metadata(
          r,
          *this,
          try_apply<unary_op_metaobject::get_data_members>(mo))}
      , _destructors{get_metadata(
          r,
          *this,
          try_apply<unary_op_metaobject::get_destructors>(mo))}
      , _enumerators{get_metadata(
          r,
          *this,
          *this,
          try_apply<unary_op_metaobject::get_enumerators>(mo))}
      , _member_functions{get_metadata(
          r,
          *this,
          try_apply<unary_op_metaobject::get_member_functions>(mo))}
      , _member_types{get_metadata(
          r,
          *this,
          try_apply<unary_op_metaobject::get_member_types>(mo))}
      , _operators{get_metadata(
          r,
          *this,
          try_apply<unary_op_metaobject::get_operators>(mo))}
      , _parameters{get_metadata(
          r,
          *this,
          try_apply<unary_op_metaobject::get_parameters>(mo))}
      , _elements{_unpack(r, _scope, _type, mo)} {
        for_each(get_enumerators(mirror(unary_op_boolean)), [&](auto me) {
            const auto result = try_apply<get_constant(me)>(mo);
            if(has_value(result)) {
                if(extract(result)) {
                    _op_boolean_results |= get_constant(me);
                }
                _op_boolean_applicable |= get_constant(me);
            }
        });
        for_each(get_enumerators(mirror(unary_op_metaobject)), [&](auto me) {
            if(is_applicable<get_constant(me)>(mo)) {
                _op_metaobject_applicable |= get_constant(me);
            }
        });
        for_each(get_enumerators(mirror(unary_op_integer)), [&](auto me) {
            if(is_applicable<get_constant(me)>(mo)) {
                _op_integer_applicable |= get_constant(me);
            }
        });
        for_each(get_enumerators(mirror(unary_op_string)), [&](auto me) {
            if(is_applicable<get_constant(me)>(mo)) {
                _op_string_applicable |= get_constant(me);
            }
        });
    }

    template <__metaobject_id M>
    metadata(
      metadata_registry& r,
      const metadata& scope,
      wrapped_metaobject<M> mo) noexcept
      : metadata{
          r,
          scope,
          get_metadata(r, try_apply<unary_op_metaobject::get_type>(mo)),
          mo} {}

    template <__metaobject_id M>
    metadata(metadata_registry& r, wrapped_metaobject<M> mo) noexcept
      : metadata{
          r,
          get_metadata(r, try_apply<unary_op_metaobject::get_scope>(mo)),
          mo} {}

    friend class metadata_registry;

public:
    explicit operator bool() const noexcept {
        return _traits.has(metaobject_trait::is_object);
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

    auto satisfies(metaobject_trait trait) const noexcept -> bool {
        return _traits.has(trait);
    }

    auto is_applicable(unary_op_boolean op) const noexcept -> bool {
        return _op_boolean_applicable.has(op);
    }

    auto is_applicable(unary_op_integer op) const noexcept -> bool {
        return _op_integer_applicable.has(op);
    }

    auto is_applicable(unary_op_string op) const noexcept -> bool {
        return _op_string_applicable.has(op);
    }

    auto is_applicable(unary_op_metaobject op) const noexcept -> bool {
        return _op_metaobject_applicable.has(op);
    }

    auto apply(unary_op_boolean op) const noexcept -> tribool {
        return {_op_boolean_results.has(op), !_op_boolean_applicable.has(op)};
    }

    auto is_empty() const noexcept -> tribool {
        return apply(unary_op_boolean::is_empty);
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

    auto size() const noexcept -> std::optional<size_t> {
        if(is_applicable(unary_op_integer::get_size)) {
            return {_elements.size()};
        }
        return {};
    }

    auto name() const noexcept -> std::optional<std::string_view> {
        if(_traits.has(metaobject_trait::is_named)) {
            return {_name};
        }
        return {};
    }

    auto display_name() const noexcept -> std::optional<std::string_view> {
        if(_traits.has(metaobject_trait::is_named)) {
            return {_display_name};
        }
        return {};
    }

    auto element(size_t index) const noexcept -> const metadata& {
        return *_elements[index];
    }

    auto scope() const noexcept -> const metadata& {
        return _scope;
    }

    auto type() const noexcept -> const metadata& {
        return _type;
    }

    auto underlying_type() const noexcept -> const metadata& {
        return _underlying_type;
    }

    auto aliased() const noexcept -> const metadata& {
        return _aliased;
    }

    auto class_() const noexcept -> const metadata& {
        return _class;
    }

    auto base_classes() const noexcept -> const metadata& {
        return _base_classes;
    }

    auto captures() const noexcept -> const metadata& {
        return _captures;
    }

    auto constructors() const noexcept -> const metadata& {
        return _constructors;
    }

    auto destructors() const noexcept -> const metadata& {
        return _destructors;
    }

    auto enumerators() const noexcept -> const metadata& {
        return _enumerators;
    }

    auto member_functions() const noexcept -> const metadata& {
        return _member_functions;
    }

    auto member_types() const noexcept -> const metadata& {
        return _member_types;
    }

    auto operators() const noexcept -> const metadata& {
        return _operators;
    }

    auto parameters() const noexcept -> const metadata& {
        return _parameters;
    }
};

class metadata_registry {
private:
    std::map<hash_t, const metadata> _metadata;

    template <__metaobject_id M>
    auto _get(const metadata& scope, wrapped_metaobject<M> mo)
      -> const metadata& {
        const auto id = get_hash(mo);
        auto pos = _metadata.find(id);
        if(pos == _metadata.end()) {
            pos = _metadata.emplace(id, metadata(*this, scope, mo)).first;
        }
        return pos->second;
    }

    template <__metaobject_id M>
    auto
    _get(const metadata& scope, const metadata& type, wrapped_metaobject<M> mo)
      -> const metadata& {
        const auto id = get_hash(mo);
        auto pos = _metadata.find(id);
        if(pos == _metadata.end()) {
            pos = _metadata.emplace(id, metadata(*this, scope, type, mo)).first;
        }
        return pos->second;
    }

public:
    metadata_registry() noexcept {
        _metadata.emplace(get_hash(no_metaobject), metadata{});
    }

    auto size() const noexcept {
        return _metadata.size();
    }

    template <__metaobject_id M>
    auto get(wrapped_metaobject<M> mo) -> const metadata& {
        const auto id = get_hash(mo);
        auto pos = _metadata.find(id);
        if(pos == _metadata.end()) {
            pos = _metadata.emplace(id, metadata(*this, mo)).first;
        }
        return pos->second;
    }

    template <__metaobject_id M>
    friend auto get_metadata(metadata_registry& r, wrapped_metaobject<M> mo)
      -> const metadata& {
        return r.get(mo);
    }

    template <__metaobject_id M>
    friend auto get_metadata(
      metadata_registry& r,
      const metadata& scope,
      wrapped_metaobject<M> mo) -> const metadata& {
        return r._get(scope, mo);
    }

    template <__metaobject_id M>
    friend auto get_metadata(
      metadata_registry& r,
      const metadata& scope,
      const metadata& type,
      wrapped_metaobject<M> mo) -> const metadata& {
        return r._get(scope, type, mo);
    }
};

} // namespace mirror

#endif

