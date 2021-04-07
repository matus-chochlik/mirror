/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "BuilderViewModel.hpp"
#include "FactoryViewModel.hpp"
//------------------------------------------------------------------------------
// BuilderViewModel
//------------------------------------------------------------------------------
BuilderViewModel::BuilderViewModel()
  : QObject{} {
    emit factoriesChanged();
}
//------------------------------------------------------------------------------
void BuilderViewModel::addFactory(FactoryViewModel& viewModel) {
    _factoryViewModels.push_back(&viewModel);
}
//------------------------------------------------------------------------------
auto BuilderViewModel::getFactoryLabels() -> QStringList {
    QStringList labels;
    for(auto* viewModel : _factoryViewModels) {
        labels.push_back(viewModel->getLabel());
    }
    return labels;
}
//------------------------------------------------------------------------------
auto BuilderViewModel::getSelectedFactory() -> FactoryViewModel* {
    if(_selectedIndex >= 0) {
        if(_selectedIndex < int(_factoryViewModels.size())) {
            return _factoryViewModels[static_cast<std::size_t>(_selectedIndex)];
        }
    }
    return nullptr;
}
//------------------------------------------------------------------------------
void BuilderViewModel::selectFactory(int index) {
    if(_selectedIndex != index) {
        _selectedIndex = index;
        emit factorySelected();
    }
}
//------------------------------------------------------------------------------
