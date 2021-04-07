/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_FACTORY_VIEW_MODEL_HPP
#define MIRROR_FACTORY_BUILDER_QT_FACTORY_VIEW_MODEL_HPP

#include <QList>
#include <QtCore>

class ConstructorViewModel;
//------------------------------------------------------------------------------
class FactoryViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QList<ConstructorViewModel*> constructors READ getConstructors
                 NOTIFY constructorsChanged)
public:
    FactoryViewModel(QObject* parent);

    auto getConstructors() -> QList<ConstructorViewModel*>;
signals:
    void constructorsChanged();
public slots:
private:
};
//------------------------------------------------------------------------------
#endif
