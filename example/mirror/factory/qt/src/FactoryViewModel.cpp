/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "FactoryViewModel.hpp"
#include "ConstructorViewModel.hpp"
//------------------------------------------------------------------------------
// FactoryViewModel
//------------------------------------------------------------------------------
FactoryViewModel::FactoryViewModel(QString label)
  : QObject{}
  , _label{std::move(label)} {}
//------------------------------------------------------------------------------
auto FactoryViewModel::getLabel() -> QString {
    return _label;
}
//------------------------------------------------------------------------------
void FactoryViewModel::addConstructor(ConstructorViewModel& viewModel) {
    _constructorViewModels.push_back(&viewModel);
    emit constructorsChanged();
}
//------------------------------------------------------------------------------
auto FactoryViewModel::getConstructorLabels() -> QStringList {
    QStringList labels;
    for(auto* viewModel : _constructorViewModels) {
        labels.push_back(viewModel->getLabel());
    }
    return labels;
}
//------------------------------------------------------------------------------
auto FactoryViewModel::getSelectedConstructor() -> ConstructorViewModel* {
    if(_selectedIndex >= 0) {
        if(_selectedIndex < int(_constructorViewModels.size())) {
            return _constructorViewModels[static_cast<std::size_t>(
              _selectedIndex)];
        }
    }
    return nullptr;
}
//------------------------------------------------------------------------------
auto FactoryViewModel::getSelectedIndex() -> size_t {
    if(_selectedIndex >= 0) {
        if(_selectedIndex < int(_constructorViewModels.size())) {
            return static_cast<std::size_t>(_selectedIndex);
        }
    }
    return 0;
}
//------------------------------------------------------------------------------
void FactoryViewModel::selectConstructor(int index) {
    if(_selectedIndex != index) {
        _selectedIndex = index;
        emit constructorSelected();
    }
}
//------------------------------------------------------------------------------
void FactoryViewModel::testFunc(std::function<QString()> func) {
    _doTest = func;
}
//------------------------------------------------------------------------------
auto FactoryViewModel::test() -> QString {
    return _doTest ? _doTest() : QString("N/A");
}
//------------------------------------------------------------------------------
