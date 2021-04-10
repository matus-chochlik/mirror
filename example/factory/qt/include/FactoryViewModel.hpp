/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_FACTORY_VIEW_MODEL_HPP
#define MIRROR_FACTORY_BUILDER_QT_FACTORY_VIEW_MODEL_HPP

#include <QtCore>

class ConstructorViewModel;
//------------------------------------------------------------------------------
class FactoryViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString label READ getLabel() CONSTANT)
    Q_PROPERTY(QStringList constructorLabels READ getConstructorLabels NOTIFY
                 constructorsChanged)
    Q_PROPERTY(ConstructorViewModel* selectedConstructor READ
                 getSelectedConstructor NOTIFY constructorSelected)
public:
    FactoryViewModel(QString label);

    auto getLabel() -> QString;

    void addConstructor(ConstructorViewModel& viewModel);
    auto getConstructorLabels() -> QStringList;
    auto getSelectedConstructor() -> ConstructorViewModel*;
    auto getSelectedIndex() -> size_t;
signals:
    void constructorsChanged();
    void constructorSelected();
public slots:
    void selectConstructor(int index);

private:
    QString _label;
    std::vector<ConstructorViewModel*> _constructorViewModels;
    int _selectedIndex{0};
};
//------------------------------------------------------------------------------
#endif
