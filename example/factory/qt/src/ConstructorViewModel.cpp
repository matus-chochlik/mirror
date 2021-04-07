/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "ConstructorViewModel.hpp"
#include "ParameterViewModel.hpp"
//------------------------------------------------------------------------------
// ConstructorViewModel
//------------------------------------------------------------------------------
ConstructorViewModel::ConstructorViewModel()
  : QObject{} {}
//------------------------------------------------------------------------------
auto ConstructorViewModel::getLabel() -> QString {
    QString label;
    label.append("(");
    bool first = true;
    for(auto* viewModel : _parameterViewModels) {
        if(first) {
            first = false;
        } else {
            label.append(", ");
        }
        label.append(viewModel->getName());
        label.append(": ");
        label.append(viewModel->getTypeName());
    }
    label.append(")");
    return label;
}
//------------------------------------------------------------------------------
void ConstructorViewModel::addParameter(ParameterViewModel& viewModel) {
    _parameterViewModels.push_back(&viewModel);
}
//------------------------------------------------------------------------------
auto ConstructorViewModel::getParameters() -> QList<ParameterViewModel*> {
    return {};
}
//------------------------------------------------------------------------------
