/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_REGISTRY_HPP
#define MIRROR_REGISTRY_HPP

#include "hash.hpp"
#include "init_list.hpp"
#include "metadata.hpp"
#include "placeholder.hpp"

namespace mirror {

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

