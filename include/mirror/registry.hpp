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
#include <map>

namespace mirror {

class stored_metadata;

auto get_no_metadata(metadata_registry&) noexcept -> const metadata&;

template <__metaobject_id M>
auto get_metadata(wrapped_metaobject<M>, metadata_registry&) noexcept
  -> stored_metadata&;

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

    template <typename R, typename T>
    static constexpr auto
    _do_get_referenced_type(std::type_identity<T>, R& r) noexcept
      -> const metadata& {
        if constexpr(std::is_pointer_v<T>) {
            using P =
              std::remove_cv_t<typename std::pointer_traits<T>::value_type>;
            return get_metadata(get_aliased(mirror(P)), r);
        } else if constexpr(std::is_reference_v<T>) {
            using P = std::remove_cv_t<std::remove_reference_t<T>>;
            return get_metadata(get_aliased(mirror(P)), r);
        } else {
            return r.get_none();
        }
    }

    static constexpr auto _get_referenced_type(auto mo, auto& r) noexcept
      -> const metadata& {
        if constexpr(reflects_type(mo)) {
            return _do_get_referenced_type(get_reflected_type(mo), r);
        } else {
            return r.get_none();
        }
    }

    template <__metaobject_id... M>
    static auto
    _expand(unpacked_metaobject_sequence<M...>, metadata_registry& r) noexcept
      -> std::vector<const metadata*> {
        return {&get_metadata(wrapped_metaobject<M>{}, r)...};
    }

    static void _init(
      unpacked_metaobject_sequence<>,
      const metadata_registry&,
      const std::vector<const metadata*>&,
      size_t = 0Z) noexcept {}

    template <__metaobject_id M, __metaobject_id... Ms>
    static void _init(
      unpacked_metaobject_sequence<M, Ms...>,
      metadata_registry& r,
      std::vector<const metadata*>& md,
      size_t idx = 0Z) noexcept {
        static_cast<stored_metadata*>(const_cast<metadata*>(md[idx]))
          ->init(wrapped_metaobject<M>{}, r);
        _init(unpacked_metaobject_sequence<Ms...>{}, r, md, idx + 1Z);
    }

    template <unary_op_metaobject O, __metaobject_id M>
    static auto _try_init(
      wrapped_metaobject<M> mo,
      metadata_registry& r,
      const metadata*& pmd) -> const metadata* {
        if(pmd->is_none()) {
            if constexpr(mirror::is_applicable<O>(mo)) {
                const auto ms = mirror::try_apply<O>(mo);
                auto& md = get_metadata(ms, r);
                pmd = &md;
                if constexpr(!reflects_type(ms)) {
                    md.init(ms, r);
                }
            }
        }
        return pmd;
    }

public:
    stored_metadata() noexcept = default;

    stored_metadata(auto mo, metadata_registry& r) noexcept
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
          get_no_metadata(r)} {}

    void init(auto mo, metadata_registry& r) {
        if constexpr(reflects_object_sequence(mo)) {
            if(_needs_elements()) {
                const auto ms{unpack(mo)};
                _init(ms, r, _emplace_elements(_expand(ms, r)));
            }
        } else if constexpr(reflects_object(mo)) {
            using O = unary_op_metaobject;
            _try_init<O::get_scope>(mo, r, _scope);
            _try_init<O::get_type>(mo, r, _type);
            _try_init<O::get_underlying_type>(mo, r, _underlying_type);
            _try_init<O::get_aliased>(mo, r, _aliased);
            _try_init<O::get_class>(mo, r, _class);

            _try_init<O::get_base_classes>(mo, r, _base_classes);
            _try_init<O::get_captures>(mo, r, _captures);
            _try_init<O::get_constructors>(mo, r, _constructors);
            _try_init<O::get_data_members>(mo, r, _data_members);
            _try_init<O::get_destructors>(mo, r, _destructors);
            _try_init<O::get_enumerators>(mo, r, _enumerators);
            _try_init<O::get_member_functions>(mo, r, _member_functions);
            _try_init<O::get_member_types>(mo, r, _member_types);
            _try_init<O::get_operators>(mo, r, _operators);
            _try_init<O::get_parameters>(mo, r, _parameters);
        }
    }
};

class metadata_registry_iterator {
private:
    using base_iter_t =
      std::map<hash_t, std::unique_ptr<stored_metadata>>::const_iterator;
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
    std::map<hash_t, std::unique_ptr<stored_metadata>> _metadata;

    friend auto get_no_metadata(metadata_registry& r) noexcept
      -> const metadata& {
        return r.get_none();
    }

    template <__metaobject_id M>
    auto _get(wrapped_metaobject<M> mo) noexcept -> stored_metadata& {
        const auto id = get_hash(mo);
        auto pos = _metadata.find(id);
        if(pos == _metadata.end()) {
            pos = _metadata
                    .emplace(id, std::make_unique<stored_metadata>(mo, *this))
                    .first;
        }
        return *pos->second;
    }

    template <__metaobject_id M>
    friend auto
    get_metadata(wrapped_metaobject<M> mo, metadata_registry& r) noexcept
      -> stored_metadata& {
        return r._get(mo);
    }

    auto _find(metaobject auto mo) -> stored_metadata& {
        const auto id = get_hash(mo);
        auto pos = _metadata.find(id);
        if(pos == _metadata.end()) {
            throw metadata_not_found();
        }
        return *pos->second;
    }

    template <__metaobject_id M>
    auto _add(wrapped_metaobject<M> mo) noexcept -> stored_metadata& {
        auto& md = _get(mo);
        md.init(mo, *this);
        return md;
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

    auto get_none() noexcept -> const metadata& {
        return *_metadata[get_hash(no_metaobject)];
    }

    auto add(metaobject auto mo) noexcept -> const metadata& {
        return _add(mo);
    }

    auto find(metaobject auto mo) -> const metadata& {
        return _find(mo);
    }

    auto all() const -> metadata_sequence {
        std::vector<const metadata*> elements;
        elements.reserve(_metadata.size());
        for(const auto& p : _metadata) {
            elements.push_back(std::get<1>(p).get());
        }
        return {elements};
    }
};

} // namespace mirror

#endif

