/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_BACKEND_HPP
#define MIRROR_FACTORY_BUILDER_QT_BACKEND_HPP

#include "factory_traits.hpp"
#include <QtCore>

class BuilderViewModel;
//------------------------------------------------------------------------------
class Backend : public QObject {
    Q_OBJECT

    Q_PROPERTY(BuilderViewModel* builder READ getBuilder NOTIFY builderChanged)
public:
    Backend();

    auto getBuilder() -> BuilderViewModel*;
signals:
    void builderChanged();
public slots:
private:
    mirror::factory_builder<mirror::qt5_factory_traits> _builder;
};
//------------------------------------------------------------------------------
#endif
