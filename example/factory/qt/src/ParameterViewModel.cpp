/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "ParameterViewModel.hpp"
#include "FactoryViewModel.hpp"
//------------------------------------------------------------------------------
// ParameterViewModel
//------------------------------------------------------------------------------
ParameterViewModel::ParameterViewModel(
  QString typeName,
  QString name,
  QString unit)
  : QObject{}
  , _typeName{std::move(typeName)}
  , _name{std::move(name)}
  , _unit{std::move(unit)} {}
//------------------------------------------------------------------------------
auto ParameterViewModel::getUnitUrl() -> QUrl {
    return {"qrc:///qml_units/" + _unit + "Unit.qml"};
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
