/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#include "ConstructorViewModel.hpp"
#include "ParameterViewModel.hpp"
//------------------------------------------------------------------------------
// ConstructorViewModel
//------------------------------------------------------------------------------
ConstructorViewModel::ConstructorViewModel(
  bool is_default,
  bool is_move,
  bool is_copy)
  : QObject{}
  , _is_default{is_default}
  , _is_move{is_move}
  , _is_copy{is_copy} {}
//------------------------------------------------------------------------------
auto ConstructorViewModel::getLabel() -> QString {
    QString label;
    if(_is_default) {
        return "<default>";
    }

    if(_is_move) {
        return "<move>";
    }

    if(_is_copy) {
        return "<copy>";
    }

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
    emit parametersChanged();
}
//------------------------------------------------------------------------------
auto ConstructorViewModel::getParameters() -> QList<QObject*> {
    QList<QObject*> result;
    for(auto* viewModel : _parameterViewModels) {
        result.push_back(viewModel);
    }
    return result;
}
//------------------------------------------------------------------------------
