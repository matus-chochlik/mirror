/// @file
///
/// Copyright Matus Chochlik.
/// Distributed under the Boost Software License, Version 1.0.
/// See accompanying file LICENSE_1_0.txt or copy at
///  http://www.boost.org/LICENSE_1_0.txt
///

#ifndef MIRROR_PUML_HPP
#define MIRROR_PUML_HPP

#include "metadata.hpp"
#include <ostream>
#include <set>

namespace mirror {

/// @brief Class that can generate PlantUML code for entities reflected by metaobjects
/// @ingroup utilities
class puml_class_diagram {
private:
    void _add_access_marker(std::ostream& out, const metadata& md) const {
        if(md.has(trait::is_private)) {
            out << "-";
        } else if(md.has(trait::is_protected)) {
            out << "#";
        } else {
            out << "+";
        }
    }

    void _add_parameter_list(std::ostream& out, const metadata& md) {
        out << "(";
        bool first = true;
        for(const auto& mp : md.parameters()) {
            if(first) {
                first = false;
            } else {
                out << ", ";
            }
            out << mp.type().name_();
        }
        out << ")";
    }

    void _gen_enum_decl(std::ostream& out, const metadata& md) {
        out << "enum ";
        out << md.name_() << " {\n";
        for(const auto& me : md.enumerators()) {
            out << "  " << me.name_() << '\n';
        }
        out << "}\n";
    }

    void _gen_record_decl(std::ostream& out, const metadata& md) {
        if(md.has(trait::uses_class_key)) {
            out << "class ";
        } else if(md.has(trait::uses_struct_key)) {
            out << "class ";
        } else {
            out << "union ";
        }
        out << md.name_() << " {\n";
        bool separate_members = false;
        for(const auto& mm : md.data_members()) {
            if(mm.has(trait::is_public)) {
                out << "  ";
                _add_access_marker(out, mm);
                if(mm.has(trait::is_static)) {
                    out << "{static}";
                }
                out << mm.name_();
                out << ": ";
                out << mm.type().name_();
                out << "\n";
                separate_members = true;
            }
        }
        bool separate_constructors = false;
        for(const auto& mc : md.constructors()) {
            if(mc.has_none(
                 trait::is_copy_constructor | trait::is_move_constructor)) {
                if(separate_members) {
                    out << "  __\n";
                    separate_members = false;
                }
                out << "  ";
                _add_access_marker(out, mc);
                out << mc.name_();
                _add_parameter_list(out, mc);
                out << "\n";
                separate_constructors = true;
            }
        }
        for(const auto& mf : md.member_functions().with_name()) {
            if(separate_members) {
                out << "  __\n";
                separate_members = false;
            }
            if(separate_constructors) {
                out << "  ..\n";
                separate_constructors = false;
            }
            out << "  ";
            _add_access_marker(out, mf);
            if(mf.has(trait::is_pure_virtual)) {
                out << "{abstract}";
            }
            out << mf.type().name_() << " ";
            out << mf.name_();
            _add_parameter_list(out, mf);
            out << "\n";
        }
        out << "}\n";
    }

    void _gen_decl(std::ostream& out, const metadata& md) {
        if(md.has(trait::reflects_enum)) {
            _gen_enum_decl(out, md);
        } else if(md.has(trait::reflects_record)) {
            _gen_record_decl(out, md);
        }
    }

    void _gen_rel(
      std::ostream& out,
      const metadata& md,
      const metadata_sequence& ms) {
        if(md.has(trait::reflects_class)) {
            for(const auto& mb : md.base_classes()) {
                if(ms.contains(mb.class_())) {
                    out << mb.class_().name_();
                    if(mb.has(trait::is_virtual)) {
                        out << " <|.. ";
                    } else {
                        out << " <|-- ";
                    }
                    out << md.name_() << '\n';
                }
            }
        }
        if(md.has(trait::reflects_record)) {
            std::set<metadata_value> owns;
            std::set<metadata_value> refs;
            std::set<metadata_value> uses;

            for(const auto& mm : md.data_members()) {
                if(mm.base_type().element_type()) {
                    const auto& mt = mm.base_type().element_type().base_type();
                    if(ms.contains(mt)) {
                        if(mt.has(trait::is_pointer | trait::is_reference)) {
                            refs.emplace(mt);
                        } else {
                            owns.emplace(mt);
                        }
                    }
                } else {
                    const auto& mt = mm.base_type();
                    if(ms.contains(mt)) {
                        if(mt.has(trait::is_pointer | trait::is_reference)) {
                            refs.emplace(mt);
                        } else {
                            uses.emplace(mt);
                        }
                    }
                }
            }
            for(const auto& mf : md.constructors() + md.member_functions()) {
                if(ms.contains(mf.base_type())) {
                    uses.emplace(mf.base_type());
                }
                for(const auto& mp : mf.parameters()) {
                    if(ms.contains(mp.base_type())) {
                        uses.emplace(mp.base_type());
                    }
                }
            }
            for(const auto& mv : uses) {
                if(
                  (mv != md) && !owns.contains(mv) && !refs.contains(mv) &&
                  mv->has_none(trait::is_fundamental)) {
                    out << md.name_() << " --> " << mv->name_() << '\n';
                }
            }
            for(const auto& mv : owns) {
                if((mv != md) && mv->has_none(trait::is_fundamental)) {
                    out << md.name_() << " *-- " << mv->name_() << '\n';
                }
            }
            for(const auto& mv : refs) {
                if(mv->has_none(trait::is_fundamental)) {
                    out << md.name_() << " o-- " << mv->name_() << '\n';
                }
            }
        }
    }

public:
    /// @brief Generate PUML for metadata instances in the specified sequence
    std::ostream& generate(std::ostream& out, const metadata_sequence& ms) {
        const auto named = ms.with_name().not_having(
          type_trait::is_const | type_trait::is_volatile | trait::is_pointer |
          trait::is_reference);

        out << "@startuml\n";
        for(const auto& md : named) {
            _gen_decl(out, md);
        }
        out << '\n';
        for(const auto& md : named) {
            _gen_rel(out, md, named);
        }
        out << "@enduml\n";
        return out;
    }
};

} // namespace mirror

#endif
