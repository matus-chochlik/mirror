import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import "qrc:///qml_units"

ColumnLayout {
    id: builderUnit
    property variant model: null

	Label {
		Layout.fillWidth: true
		text: qsTr("Select factory")
	}

	ComboBox {
		id: factorySelector
		Layout.fillWidth: true
		model: builderUnit.model.factoryLabels
		onActivated: builderUnit.model.selectFactory(currentIndex)
	}

	FactoryUnit {
		Layout.fillWidth: true
		Layout.fillHeight: true
		model: builderUnit.model.selectedFactory
	}
}
