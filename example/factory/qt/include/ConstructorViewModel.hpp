/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_CONSTRUCTOR_VIEW_MODEL_HPP
#define MIRROR_FACTORY_BUILDER_QT_CONSTRUCTOR_VIEW_MODEL_HPP

#include <QList>
#include <QtCore>

class ParameterViewModel;
//------------------------------------------------------------------------------
class ConstructorViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString label READ getLabel() NOTIFY parametersChanged)
    Q_PROPERTY(QList<ParameterViewModel*> constructors READ getParameters NOTIFY
                 parametersChanged)
public:
    ConstructorViewModel();

    auto getLabel() -> QString;

    void addParameter(ParameterViewModel& viewModel);
    auto getParameters() -> QList<ParameterViewModel*>;
signals:
    void parametersChanged();
public slots:
private:
    std::vector<ParameterViewModel*> _parameterViewModels;
};
//------------------------------------------------------------------------------
#endif