/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_BUILDER_VIEW_MODEL_HPP
#define MIRROR_FACTORY_BUILDER_QT_BUILDER_VIEW_MODEL_HPP

#include <QList>
#include <QtCore>

class FactoryViewModel;
//------------------------------------------------------------------------------
class BuilderViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QList<FactoryViewModel*> factories READ getFactories NOTIFY
                 factoriesChanged)
public:
    BuilderViewModel(QObject* parent);

    auto getFactories() -> QList<FactoryViewModel*>;
signals:
    void factoriesChanged();
public slots:
private:
};
//------------------------------------------------------------------------------
#endif
