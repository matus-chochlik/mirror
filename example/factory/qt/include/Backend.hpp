/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_BACKEND_HPP
#define MIRROR_FACTORY_BUILDER_QT_BACKEND_HPP

#include <QtCore>

class BuilderViewModel;
//------------------------------------------------------------------------------
class Backend : public QObject {
    Q_OBJECT

    Q_PROPERTY(BuilderViewModel* builder READ getBuilder NOTIFY builderChanged)
public:
    Backend(QObject* parent = 0);

    auto getBuilder() -> BuilderViewModel*;
signals:
    void builderChanged();
public slots:
private:
};
//------------------------------------------------------------------------------
#endif
