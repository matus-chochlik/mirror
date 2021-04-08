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
  , _pointFactory{_builder.build<test::point>()}
  , _triangleFactory{_builder.build<test::triangle>()}
  , _tetrahedronFactory{_builder.build<test::tetrahedron>()} {}
//------------------------------------------------------------------------------
auto Backend::getBuilder() -> BuilderViewModel* {
    return &_builder.base_unit().view_model();
}
//------------------------------------------------------------------------------
