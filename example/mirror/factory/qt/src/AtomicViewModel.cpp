/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "AtomicViewModel.hpp"
//------------------------------------------------------------------------------
// AtomicViewModel
//------------------------------------------------------------------------------
AtomicViewModel::AtomicViewModel(QString unit)
  : QObject{}
  , _unit{std::move(unit)} {}
//------------------------------------------------------------------------------
auto AtomicViewModel::getUnitName() -> QString {
    return _unit;
}
//------------------------------------------------------------------------------
// StringBackedViewModel
//------------------------------------------------------------------------------
StringBackedViewModel::StringBackedViewModel(QString unit)
  : AtomicViewModel{std::move(unit)} {}
//------------------------------------------------------------------------------
void StringBackedViewModel::setValue(QString str) {
    _value = str;
}
//------------------------------------------------------------------------------
auto StringBackedViewModel::getValue() -> const QString& {
    return _value;
}
//------------------------------------------------------------------------------
// StringViewModel
//------------------------------------------------------------------------------
StringViewModel::StringViewModel()
  : StringBackedViewModel{"String"} {}
//------------------------------------------------------------------------------
auto StringViewModel::get(std::string*) -> std::string {
    return getValue().toStdString();
}
//------------------------------------------------------------------------------
// FloatViewModel
//------------------------------------------------------------------------------
FloatViewModel::FloatViewModel()
  : StringBackedViewModel{"Float"} {}
//------------------------------------------------------------------------------
auto FloatViewModel::get(float*) -> float {
    return getValue().toFloat();
}
//------------------------------------------------------------------------------
auto FloatViewModel::get(double*) -> double {
    return getValue().toDouble();
}
//------------------------------------------------------------------------------
// BoolViewModel
//------------------------------------------------------------------------------
BoolViewModel::BoolViewModel()
  : AtomicViewModel("Bool") {}
//------------------------------------------------------------------------------
