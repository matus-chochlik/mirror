/// Copyright Matus Chochlik.
/// Distributed under the GNU GENERAL PUBLIC LICENSE version 3.
/// See http://www.gnu.org/licenses/gpl-3.0.txt
///
#ifndef MIRROR_FACTORY_BUILDER_QT_PARAMETER_VIEW_MODEL_HPP
#define MIRROR_FACTORY_BUILDER_QT_PARAMETER_VIEW_MODEL_HPP

#include <QtCore>

//------------------------------------------------------------------------------
class ParameterViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QUrl unitUrl READ getUnitUrl() CONSTANT)
    Q_PROPERTY(QString typeName READ getTypeName() CONSTANT)
    Q_PROPERTY(QString name READ getName() CONSTANT)
public:
    ParameterViewModel(QString typeName, QString name, QString unit);

    auto getUnitUrl() -> QUrl;
    auto getTypeName() -> QString;
    auto getName() -> QString;
signals:
public slots:
private:
    QString _typeName;
    QString _name;
    QString _unit;
};
//------------------------------------------------------------------------------
#endif
