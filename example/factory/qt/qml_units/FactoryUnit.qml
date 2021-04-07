import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import "qrc:///qml_units"

ColumnLayout {
    id: factoryUnit
    property variant model: null

	Label {
		Layout.fillWidth: true
		text: model ? model.label : qsTr("N/A")
	}
	ComboBox {
		id: constructorSelector
		Layout.fillWidth: true
		model: factoryUnit.model.constructorLabels
		onActivated: factoryUnit.model.selectConstructor(currentIndex)
	}
	ConstructorUnit {
		Layout.fillWidth: true
		Layout.fillHeight: true
		model: factoryUnit.model.selectedConstructor
	}
}
