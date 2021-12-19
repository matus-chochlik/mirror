/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_BACKEND_HPP
#define MIRROR_FACTORY_BUILDER_QT_BACKEND_HPP

#include "../../testdecl/tetrahedron.hpp"
#include "factory_traits.hpp"
#include <QtCore>

class BuilderViewModel;
//------------------------------------------------------------------------------
class Backend : public QObject {
    Q_OBJECT

    Q_PROPERTY(BuilderViewModel* builder READ getBuilder CONSTANT)
public:
    Backend();

    auto getBuilder() -> BuilderViewModel*;
public slots:
private:
    mirror::factory_builder<mirror::qt5_factory_traits> _builder;
    std::unique_ptr<mirror::qt5_product_factory<example::point>> _pointFactory;
    std::unique_ptr<mirror::qt5_product_factory<example::triangle>>
      _triangleFactory;
    std::unique_ptr<mirror::qt5_product_factory<example::tetrahedron>>
      _tetrahedronFactory;
};
//------------------------------------------------------------------------------
#endif
