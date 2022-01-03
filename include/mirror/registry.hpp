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
#include "init_list.hpp"
#include "operations.hpp"
#include "placeholder.hpp"
#include "registry_fwd.hpp"
#include "traits.hpp"
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

namespace mirror {

class metadata_not_found : public std::runtime_error {
public:
    metadata_not_found() noexcept
      : std::runtime_error{"metadata not found"} {}
};

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

class metadata {
private:
    size_t _id{0U};
    metaobject_traits _traits{};

    unary_ops_boolean _op_boolean_results{};
    unary_ops_boolean _op_boolean_applicable{};
    unary_ops_metaobject _op_metaobject_applicable{};
    unary_ops_integer _op_integer_applicable{};
    unary_ops_string _op_string_applicable{};

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

protected:
    metadata() noexcept = default;

    metadata(
      size_t id,
      metaobject_traits traits,
      unary_ops_boolean op_boolean_results,
      unary_ops_boolean op_boolean_applicable,
      unary_ops_metaobject op_metaobject_applicable,
      unary_ops_integer op_integer_applicable,
      unary_ops_string op_string_applicable,
      size_t source_column,
      size_t source_line,
      std::string_view name,
      std::string_view display_name,
      const metadata& scope,
      const metadata& type,
      const metadata& underlying_type,
      const metadata& aliased,
      const metadata& class_,
      const metadata& base_classes,
      const metadata& captures,
      const metadata& constructors,
      const metadata& data_members,
      const metadata& destructors,
      const metadata& enumerators,
      const metadata& member_functions,
      const metadata& member_types,
      const metadata& operators,
      const metadata& parameters,
      std::vector<const metadata*> elements) noexcept
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
      , _scope{scope}
      , _type{type}
      , _underlying_type{underlying_type}
      , _aliased{aliased}
      , _class{class_}
      , _base_classes{base_classes}
      , _captures{captures}
      , _constructors{constructors}
      , _data_members{data_members}
      , _destructors{destructors}
      , _enumerators{enumerators}
      , _member_functions{member_functions}
      , _member_types{member_types}
      , _operators{operators}
      , _parameters{parameters}
      , _elements{std::move(elements)} {}

public:
    metadata(metadata&&) = delete;
    auto operator=(metadata&&) = delete;
    metadata(const metadata&) = delete;
    auto operator=(const metadata&) = delete;
    ~metadata() noexcept = default;

    explicit operator bool() const noexcept {
        return _traits.has(metaobject_trait::reflects_object);
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

    auto count() const noexcept -> size_t {
        return _elements.size();
    }

    auto begin() const noexcept -> metadata_iterator {
        return {_elements.begin()};
    }

    auto end() const noexcept -> metadata_iterator {
        return {_elements.end()};
    }

    auto name() const noexcept -> std::optional<std::string_view> {
        if(is_applicable(unary_op_string::get_name)) {
            return {_name};
        }
        return {};
    }

    auto display_name() const noexcept -> std::optional<std::string_view> {
        if(is_applicable(unary_op_string::get_display_name)) {
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

    auto data_members() const noexcept -> const metadata& {
        return _data_members;
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

template <__metaobject_id M>
auto get_metadata(metadata_registry&, wrapped_metaobject<M>) noexcept
  -> const metadata&;

template <__metaobject_id M>
auto get_metadata(
  metadata_registry&,
  const metadata& scope,
  wrapped_metaobject<M>) noexcept -> const metadata&;

template <__metaobject_id M>
auto get_metadata(
  metadata_registry&,
  const metadata& scope,
  const metadata& type,
  wrapped_metaobject<M>) noexcept -> const metadata&;

class stored_metadata : public metadata {
private:
    static auto _get_op_boolean_results(auto mo) noexcept {
        return fold_init_list_of<unary_op_boolean>(
          filter(
            get_enumerators(mirror(unary_op_boolean)),
            mirror::try_apply(_1, mo)),
          get_constant(_1),
          [](auto il) { return unary_ops_boolean{il}; });
    }

    static auto _get_op_boolean_applicable(auto mo) noexcept {
        return fold_init_list_of<unary_op_boolean>(
          filter(
            get_enumerators(mirror(unary_op_boolean)),
            mirror::is_applicable(_1, mo)),
          get_constant(_1),
          [](auto il) { return unary_ops_boolean{il}; });
    }

    static auto _get_op_metaobject_applicable(auto mo) noexcept {
        return fold_init_list_of<unary_op_metaobject>(
          filter(
            get_enumerators(mirror(unary_op_metaobject)),
            mirror::is_applicable(_1, mo)),
          get_constant(_1),
          [](auto il) { return unary_ops_metaobject{il}; });
    }

    static auto _get_op_integer_applicable(auto mo) noexcept {
        return fold_init_list_of<unary_op_integer>(
          filter(
            get_enumerators(mirror(unary_op_integer)),
            mirror::is_applicable(_1, mo)),
          get_constant(_1),
          [](auto il) { return unary_ops_integer{il}; });
    }

    static auto _get_op_string_applicable(auto mo) noexcept {
        return fold_init_list_of<unary_op_string>(
          filter(
            get_enumerators(mirror(unary_op_string)),
            mirror::is_applicable(_1, mo)),
          get_constant(_1),
          [](auto il) { return unary_ops_string{il}; });
    }

    static auto _get_name(auto mo) noexcept -> std::string_view {
        if constexpr(reflects_named(mo)) {
            return get_name(mo);
        }
        return {};
    }

    static auto _get_display_name(auto mo) noexcept -> std::string_view {
        if constexpr(reflects_named(mo)) {
            return get_display_name(mo);
        }
        return {};
    }

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

public:
    stored_metadata() noexcept = default;

    stored_metadata(
      metadata_registry& r,
      const metadata& scope,
      const metadata& type,
      auto mo) noexcept
      : metadata{
          get_id(mo),
          get_traits(mo),
          _get_op_boolean_results(mo),
          _get_op_boolean_applicable(mo),
          _get_op_metaobject_applicable(mo),
          _get_op_integer_applicable(mo),
          _get_op_string_applicable(mo),
          get_source_column(mo),
          get_source_line(mo),
          _get_name(mo),
          _get_display_name(mo),
          scope,
          type,
          get_metadata(
            r,
            try_apply<unary_op_metaobject::get_underlying_type>(mo)),
          get_metadata(r, try_apply<unary_op_metaobject::get_aliased>(mo)),
          get_metadata(r, try_apply<unary_op_metaobject::get_class>(mo)),
          get_metadata(
            r,
            *this,
            try_apply<unary_op_metaobject::get_base_classes>(mo)),
          get_metadata(
            r,
            *this,
            try_apply<unary_op_metaobject::get_captures>(mo)),
          get_metadata(
            r,
            *this,
            try_apply<unary_op_metaobject::get_constructors>(mo)),
          get_metadata(
            r,
            *this,
            try_apply<unary_op_metaobject::get_data_members>(mo)),
          get_metadata(
            r,
            *this,
            try_apply<unary_op_metaobject::get_destructors>(mo)),
          get_metadata(
            r,
            *this,
            *this,
            try_apply<unary_op_metaobject::get_enumerators>(mo)),
          get_metadata(
            r,
            *this,
            try_apply<unary_op_metaobject::get_member_functions>(mo)),
          get_metadata(
            r,
            *this,
            try_apply<unary_op_metaobject::get_member_types>(mo)),
          get_metadata(
            r,
            *this,
            try_apply<unary_op_metaobject::get_operators>(mo)),
          get_metadata(
            r,
            *this,
            try_apply<unary_op_metaobject::get_parameters>(mo)),
          _unpack(r, scope, type, mo)} {}

    stored_metadata(metadata_registry& r, const metadata& scope, auto mo) noexcept
      : stored_metadata{
          r,
          scope,
          get_metadata(r, try_apply<unary_op_metaobject::get_type>(mo)),
          mo} {}

    stored_metadata(metadata_registry& r, auto mo) noexcept
      : stored_metadata{
          r,
          get_metadata(r, try_apply<unary_op_metaobject::get_scope>(mo)),
          mo} {}
};

class metadata_registry_iterator {
private:
    using base_iter_t =
      std::map<hash_t, std::unique_ptr<const metadata>>::const_iterator;
    base_iter_t _iter{};

public:
    using value_type = const metadata;
    using pointer = const metadata*;
    using reference = const metadata&;
    using difference_type = base_iter_t::difference_type;
    using iterator_category = std::forward_iterator_tag;

    metadata_registry_iterator(base_iter_t iter) noexcept
      : _iter{iter} {}

    friend auto operator==(
      const metadata_registry_iterator& l,
      const metadata_registry_iterator& r) noexcept -> bool {
        return l._iter == r._iter;
    }

    friend auto operator!=(
      const metadata_registry_iterator& l,
      const metadata_registry_iterator& r) noexcept -> bool {
        return l._iter != r._iter;
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

    auto operator*() noexcept -> const metadata& {
        return *_iter->second;
    }
};

class metadata_registry {
private:
    std::map<hash_t, std::unique_ptr<const metadata>> _metadata;

    template <__metaobject_id M>
    auto _get(const metadata& scope, wrapped_metaobject<M> mo) noexcept
      -> const metadata& {
        const auto id = get_hash(mo);
        auto pos = _metadata.find(id);
        if(pos == _metadata.end()) {
            pos = _metadata
                    .emplace(
                      id, std::make_unique<stored_metadata>(*this, scope, mo))
                    .first;
        }
        return *pos->second;
    }

    template <__metaobject_id M>
    auto _get(
      const metadata& scope,
      const metadata& type,
      wrapped_metaobject<M> mo) noexcept -> const metadata& {
        const auto id = get_hash(mo);
        auto pos = _metadata.find(id);
        if(pos == _metadata.end()) {
            pos =
              _metadata
                .emplace(
                  id, std::make_unique<stored_metadata>(*this, scope, type, mo))
                .first;
        }
        return *pos->second;
    }

    template <__metaobject_id M>
    friend auto
    get_metadata(metadata_registry& r, wrapped_metaobject<M> mo) noexcept
      -> const metadata& {
        return r.get(mo);
    }

    template <__metaobject_id M>
    friend auto get_metadata(
      metadata_registry& r,
      const metadata& scope,
      wrapped_metaobject<M> mo) noexcept -> const metadata& {
        return r._get(scope, mo);
    }

    template <__metaobject_id M>
    friend auto get_metadata(
      metadata_registry& r,
      const metadata& scope,
      const metadata& type,
      wrapped_metaobject<M> mo) noexcept -> const metadata& {
        return r._get(scope, type, mo);
    }

public:
    metadata_registry() noexcept {
        _metadata.emplace(
          get_hash(no_metaobject), std::make_unique<stored_metadata>());
    }

    auto size() const noexcept {
        return _metadata.size();
    }

    auto begin() const noexcept -> metadata_registry_iterator {
        return {_metadata.begin()};
    }

    auto end() const noexcept -> metadata_registry_iterator {
        return {_metadata.end()};
    }

    template <__metaobject_id M>
    auto get(wrapped_metaobject<M> mo) noexcept -> const metadata& {
        const auto id = get_hash(mo);
        auto pos = _metadata.find(id);
        if(pos == _metadata.end()) {
            pos = _metadata
                    .emplace(id, std::make_unique<stored_metadata>(*this, mo))
                    .first;
        }
        return *pos->second;
    }

    template <__metaobject_id M>
    auto add(wrapped_metaobject<M> mo) noexcept {
        (void)get(mo);
    }

    template <__metaobject_id M>
    auto find(wrapped_metaobject<M> mo) -> const metadata& {
        const auto id = get_hash(mo);
        auto pos = _metadata.find(id);
        if(pos == _metadata.end()) {
            throw metadata_not_found();
        }
        return *pos->second;
    }
};

} // namespace mirror

#endif

