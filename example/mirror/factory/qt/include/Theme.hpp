///
/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///

#ifndef MIRROR_FACTORY_BUILDER_QT_THEME_HPP
#define MIRROR_FACTORY_BUILDER_QT_THEME_HPP

#include <QObject>

//------------------------------------------------------------------------------
class Theme : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool light READ getLight WRITE setLight NOTIFY lightChanged)

public:
    Theme();

    void setLight(bool);
    auto getLight() const -> bool;

signals:
    void lightChanged();
public slots:
private:
    bool _light{false};
};
//------------------------------------------------------------------------------
#endif
