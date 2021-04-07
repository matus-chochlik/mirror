/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_BUILDER_VIEW_MODEL_HPP
#define MIRROR_FACTORY_BUILDER_QT_BUILDER_VIEW_MODEL_HPP

#include <QStringList>
#include <QtCore>
#include <vector>

class FactoryViewModel;
//------------------------------------------------------------------------------
class BuilderViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(
      QStringList factoryLabels READ getFactoryLabels NOTIFY factoriesChanged)
    Q_PROPERTY(FactoryViewModel* selectedFactory READ getSelectedFactory NOTIFY
                 factorySelected)
public:
    BuilderViewModel();

    void addFactory(FactoryViewModel& viewModel);
    auto getFactoryLabels() -> QStringList;
    auto getSelectedFactory() -> FactoryViewModel*;
signals:
    void factoriesChanged();
    void factorySelected();
public slots:
    void selectFactory(int index);

private:
    std::vector<FactoryViewModel*> _factoryViewModels;
    int _selectedIndex{0};
};
//------------------------------------------------------------------------------
#endif
