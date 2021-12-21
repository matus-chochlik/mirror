///
/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///

#include "Theme.hpp"
//------------------------------------------------------------------------------
Theme::Theme()
  : QObject{nullptr} {
    setLight(false);
}
//------------------------------------------------------------------------------
void Theme::setLight(bool value) {
    _light = value;
    emit lightChanged();
}
//------------------------------------------------------------------------------
auto Theme::getLight() const -> bool {
    return _light;
}
//------------------------------------------------------------------------------
