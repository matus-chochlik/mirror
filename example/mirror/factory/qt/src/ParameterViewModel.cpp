/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "ParameterViewModel.hpp"
#include "AtomicViewModel.hpp"
#include "FactoryViewModel.hpp"
//------------------------------------------------------------------------------
// ParameterViewModel
//------------------------------------------------------------------------------
ParameterViewModel::ParameterViewModel(
  QString typeName,
  QString name,
  QObject* nestedModel)
  : QObject{}
  , _typeName{std::move(typeName)}
  , _name{std::move(name)}
  , _nestedModel{nestedModel} {}
//------------------------------------------------------------------------------
auto ParameterViewModel::getUnitName() -> QString {
    if(auto* atomicViewModel{dynamic_cast<AtomicViewModel*>(_nestedModel)}) {
        return atomicViewModel->getUnitName();
    }
    return "Composite";
}
//------------------------------------------------------------------------------
auto ParameterViewModel::getUnitUrl() -> QUrl {
    return {"qrc:///qml_units/" + getUnitName() + "Unit.qml"};
}
//------------------------------------------------------------------------------
auto ParameterViewModel::getTypeName() -> QString {
    return _typeName;
}
//------------------------------------------------------------------------------
auto ParameterViewModel::getName() -> QString {
    return _name;
}
//------------------------------------------------------------------------------
auto ParameterViewModel::getNested() -> QObject* {
    return _nestedModel;
}
//------------------------------------------------------------------------------
void ParameterViewModel::addFactory(FactoryViewModel& viewModel) {
    _nestedModel = &viewModel;
    emit nestedModelAdded();
}
//------------------------------------------------------------------------------
