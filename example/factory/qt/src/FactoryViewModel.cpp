/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "FactoryViewModel.hpp"
//------------------------------------------------------------------------------
// FactoryViewModel
//------------------------------------------------------------------------------
FactoryViewModel::FactoryViewModel(QObject* parent)
  : QObject{parent} {}
//------------------------------------------------------------------------------
auto FactoryViewModel::getConstructors() -> QList<ConstructorViewModel*> {
    return {};
}
//------------------------------------------------------------------------------
