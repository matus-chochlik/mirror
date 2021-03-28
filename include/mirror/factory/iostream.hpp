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
    template <typename Product>
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

    template <typename Product>
    struct builder_unit {
        builder_unit(std::istream& i, std::ostream& o)
          : in{i}
          , out{o} {}

        std::istream& in;
        std::ostream& out;
    };

    template <typename Product>
    struct factory_unit {
        factory_unit(const builder_unit<Product>& parent)
          : in{parent.in}
          , out{parent.out} {}

        factory_unit(const composite_unit<Product>& parent)
          : in{parent.in}
          , out{parent.out} {}

        auto select_constructor(const factory& fac) -> size_t {
            size_t pick = 0U;
            auto bad_pick = [](const auto& ctr) {
                return ctr.is_copy_constructor() || ctr.is_move_constructor();
            };

            while(true) {
                out << "select constructor:" << std::endl;
                const auto ctr_count = fac.constructor_count();
                for(size_t c = 0; c < ctr_count; ++c) {
                    const auto& ctr = fac.constructor(c);
                    if(!bad_pick(ctr)) {
                        out << "  " << c << ": " << fac.product_type_name()
                            << "(";
                        const auto param_count = ctr.parameter_count();
                        for(size_t p = 0; p < param_count; ++p) {
                            if(p) {
                                out << ", ";
                            }
                            out << ctr.parameter(p).type_name();
                            out << " ";
                            out << ctr.parameter(p).name();
                        }
                        out << ")" << std::endl;
                    }
                }
                in >> pick;
                if(pick < ctr_count) {
                    if(!bad_pick(fac.constructor(pick))) {
                        break;
                    }
                }
            }
            return pick;
        }

        std::istream& in;
        std::ostream& out;
    };

    template <typename Product>
    struct constructor_unit {
        constructor_unit(const factory_unit<Product>& parent)
          : in{parent.in}
          , out{parent.out} {}

        std::istream& in;
        std::ostream& out;
    };

    template <typename T>
    static constexpr bool is_atomic =
      std::is_floating_point_v<T> || std::is_integral_v<T> ||
      std::is_same_v<T, std::string>;

    static auto make_path_of(const factory_constructor_parameter& param) {
        auto path = std::string(param.name());
        auto* pparam = &param;
        while(true) {
            pparam = pparam->parent_constructor()
                       .parent_factory()
                       .parent_builder()
                       .as_parameter();
            if(!pparam) {
                break;
            }
            path = std::string(pparam->name()) + "." + path;
        }
        return path;
    }

    template <typename T>
    struct atomic_unit {
        template <typename P>
        atomic_unit(const constructor_unit<P>& parent, const object_builder&)
          : in{parent.in}
          , out{parent.out} {}

        auto get(const factory_constructor_parameter& p) {
            std::remove_reference_t<T> result{};
            const auto path = make_path_of(p);
            while(true) {
                out << "get " << path << " (" << p.type_name()
                    << "): " << std::flush;
                if(in >> result) {
                    break;
                }
            }
            return result;
        }

        std::istream& in;
        std::ostream& out;
    };

    template <typename T>
    struct composite_unit {
        template <typename P>
        composite_unit(
          const constructor_unit<P>& parent,
          const object_builder& builder)
          : in{parent.in}
          , out{parent.out}
          , factory{*this, builder} {}

        auto get(const factory_constructor_parameter&) {
            return factory.construct();
        }

        std::istream& in;
        std::ostream& out;
        built_factory_type<iostream_factory_traits, T> factory;
    };

    template <typename T>
    struct copy_unit {
        template <typename P>
        copy_unit(const constructor_unit<P>&, const object_builder&) {}

        auto get(const factory_constructor_parameter&) -> T {
            return T{};
        }
    };
};
//------------------------------------------------------------------------------
} // namespace mirror

#endif // MIRROR_FACTORY_IOSTREAM_HPP

