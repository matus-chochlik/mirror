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
// BoolViewModel
//------------------------------------------------------------------------------
BoolViewModel::BoolViewModel()
  : AtomicViewModel("Bool") {}
//------------------------------------------------------------------------------
// StringViewModel
//------------------------------------------------------------------------------
StringViewModel::StringViewModel()
  : AtomicViewModel("String") {}
//------------------------------------------------------------------------------
