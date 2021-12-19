/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "Backend.hpp"
#include "BuilderViewModel.hpp"
//------------------------------------------------------------------------------
// Backend
//------------------------------------------------------------------------------
Backend::Backend()
  : QObject{nullptr}
  , _builder{"qt5"}
  , _pointFactory{_builder.build<example::point>()}
  , _triangleFactory{_builder.build<example::triangle>()}
  , _tetrahedronFactory{_builder.build<example::tetrahedron>()} {

    _pointFactory.base_unit().view_model().testFunc([this] {
        const auto p = _pointFactory.construct({});
        return QString("Distance of constructed point from origin: %1")
          .arg(QString::number(double(p.direction().length())));
    });

    _triangleFactory.base_unit().view_model().testFunc([this] {
        const auto t = _triangleFactory.construct({});
        return QString("Area of constructed triangle: %1")
          .arg(QString::number(double(t.area())));
    });

    _tetrahedronFactory.base_unit().view_model().testFunc([this] {
        const auto t = _tetrahedronFactory.construct({});
        return QString("Volume of constructed tetrahedron: %1")
          .arg(QString::number(double(t.volume())));
    });
}
//------------------------------------------------------------------------------
auto Backend::getBuilder() -> BuilderViewModel* {
    return &_builder.base_unit().view_model();
}
//------------------------------------------------------------------------------
