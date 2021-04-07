/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "ConstructorViewModel.hpp"
//------------------------------------------------------------------------------
// ConstructorViewModel
//------------------------------------------------------------------------------
ConstructorViewModel::ConstructorViewModel(QObject* parent)
  : QObject{parent} {}
//------------------------------------------------------------------------------
auto ConstructorViewModel::getParameters() -> QList<ParameterViewModel*> {
    return {};
}
//------------------------------------------------------------------------------
