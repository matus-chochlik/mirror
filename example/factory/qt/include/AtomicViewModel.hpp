/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_ATOMIC_VIEW_MODEL_HPP
#define MIRROR_FACTORY_BUILDER_QT_ATOMIC_VIEW_MODEL_HPP

#include <QtCore>

class FactoryViewModel;
//------------------------------------------------------------------------------
class AtomicViewModel : public QObject {
    Q_OBJECT

public:
    AtomicViewModel(QString unit);

    auto getUnitName() -> QString;
public slots:
private:
    QString _unit;
};
//------------------------------------------------------------------------------
class BoolViewModel : public AtomicViewModel {
public:
    BoolViewModel();
};
//------------------------------------------------------------------------------
class StringViewModel : public AtomicViewModel {
public:
    StringViewModel();
};
//------------------------------------------------------------------------------
#endif
