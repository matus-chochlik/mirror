/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_FACTORY_IOSTREAM_HPP
#define MIRROR_FACTORY_IOSTREAM_HPP

#include <iostream>

namespace mirror {
//------------------------------------------------------------------------------
struct iostream_factory_traits {
    struct builder_unit;

    template <typename Product>
    struct factory_unit;

    template <typename Product>
    struct constructor_unit;

    template <typename T>
    struct atomic_unit;

    template <typename T>
    struct composite_unit;

    template <typename T>
    struct copy_unit;

    struct construction_context {
        std::istream& in;
        std::ostream& out;
    };

    struct builder_unit {};

    template <typename Product>
    struct factory_unit {
        factory_unit(const builder_unit&) {}
        factory_unit(const composite_unit<Product>&) {}

        auto select_constructor(construction_context& ctx, const factory& fac)
          -> size_t {
            size_t pick = 0U;
            auto bad_pick = [](const auto& ctr) {
                return ctr.is_copy_constructor() || ctr.is_move_constructor();
            };

            while(true) {
                ctx.out << "select constructor:" << std::endl;
                const auto ctr_count = fac.constructor_count();
                for(size_t c = 0; c < ctr_count; ++c) {
                    const auto& ctr = fac.constructor(c);
                    if(!bad_pick(ctr)) {
                        ctx.out << "  " << c << ": " << fac.product_type_name()
                                << "(";
                        const auto param_count = ctr.parameter_count();
                        for(size_t p = 0; p < param_count; ++p) {
                            if(p) {
                                ctx.out << ", ";
                            }
                            ctx.out << ctr.parameter(p).type_name();
                            ctx.out << " ";
                            ctx.out << ctr.parameter(p).name();
                        }
                        ctx.out << ")" << std::endl;
                    }
                }
                ctx.in >> pick;
                if(pick < ctr_count) {
                    if(!bad_pick(fac.constructor(pick))) {
                        break;
                    }
                }
            }
            return pick;
        }
    };

    template <typename Product>
    struct constructor_unit {
        constructor_unit(const factory_unit<Product>&) {}
    };

    template <typename T>
    static constexpr bool is_atomic =
      std::is_floating_point_v<T> || std::is_integral_v<T> ||
      std::is_same_v<T, std::string>;

    static auto make_path_of(const factory_constructor_parameter& param) {
        auto path = std::string(param.name());
        auto* pparam = &param;
        while(true) {
            if(!(pparam = pparam->parent_parameter())) {
                break;
            }
            path = std::string(pparam->name()) + "." + path;
        }
        return path;
    }

    template <typename T>
    struct atomic_unit {
        template <typename P>
        atomic_unit(
          const constructor_unit<P>&,
          const object_builder&,
          const factory_constructor&) {}

        auto
        get(construction_context& ctx, const factory_constructor_parameter& p) {
            std::remove_reference_t<T> result{};
            const auto path = make_path_of(p);
            while(true) {
                ctx.out << "get " << path << " (" << p.type_name()
                        << "): " << std::flush;
                if(ctx.in >> result) {
                    break;
                }
            }
            return result;
        }
    };

    template <typename T>
    struct composite_unit {
        template <typename P>
        composite_unit(
          const constructor_unit<P>&,
          const object_builder& builder,
          const factory_constructor&)
          : fac{*this, builder} {}

        auto
        get(construction_context& ctx, const factory_constructor_parameter&) {
            return fac.construct(ctx);
        }

        built_factory_type<iostream_factory_traits, T> fac;
    };

    template <typename T>
    struct copy_unit {
        template <typename P>
        copy_unit(
          const constructor_unit<P>&,
          const object_builder&,
          const factory_constructor&) {}

        auto get(construction_context&, const factory_constructor_parameter&)
          -> T {
            return T{};
        }
    };
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_FACTORY_IOSTREAM_HPP

