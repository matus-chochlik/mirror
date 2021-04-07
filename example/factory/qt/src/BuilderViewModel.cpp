/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "BuilderViewModel.hpp"
//------------------------------------------------------------------------------
// BuilderViewModel
//------------------------------------------------------------------------------
BuilderViewModel::BuilderViewModel(QObject* parent)
  : QObject{parent} {}
//------------------------------------------------------------------------------
auto BuilderViewModel::getFactories() -> QList<FactoryViewModel*> {
    return {};
}
//------------------------------------------------------------------------------
