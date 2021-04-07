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
  , _builder{"qt5", this} {}
//------------------------------------------------------------------------------
auto Backend::getBuilder() -> BuilderViewModel* {
    return nullptr;
}
//------------------------------------------------------------------------------
