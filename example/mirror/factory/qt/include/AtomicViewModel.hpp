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
class StringBackedViewModel : public AtomicViewModel {
    Q_OBJECT

    Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY valueChanged)
public:
    StringBackedViewModel(QString);

    void setValue(QString);
    auto getValue() -> const QString&;

signals:
    void valueChanged();

private:
    QString _value;
};
//------------------------------------------------------------------------------
class StringViewModel : public StringBackedViewModel {
public:
    StringViewModel();

    auto get(std::string*) -> std::string;
};
//------------------------------------------------------------------------------
class FloatViewModel : public StringBackedViewModel {
public:
    FloatViewModel();

    auto get(float*) -> float;
    auto get(double*) -> double;
};
//------------------------------------------------------------------------------
class BoolViewModel : public AtomicViewModel {
    Q_OBJECT

public:
    BoolViewModel();

    auto get(bool*) -> bool;

private:
    bool _value;
};
//------------------------------------------------------------------------------
#endif
