/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "ParameterViewModel.hpp"
//------------------------------------------------------------------------------
// ParameterViewModel
//------------------------------------------------------------------------------
ParameterViewModel::ParameterViewModel(QString typeName, QString name)
  : QObject{}
  , _typeName{std::move(typeName)}
  , _name{std::move(name)} {}
//------------------------------------------------------------------------------
auto ParameterViewModel::getTypeName() -> QString {
    return _typeName;
}
//------------------------------------------------------------------------------
auto ParameterViewModel::getName() -> QString {
    return _name;
}
//------------------------------------------------------------------------------
