import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import "qrc:///qml_units"

ColumnLayout {
    id: factoryUnit
    property variant model: null

	Repeater {
		model: factoryUnit.model.parameters
		delegate: Loader {
			id: unitLoader
			Layout.fillWidth: true
			source: modelData.unitUrl
			onLoaded: {
				unitLoader.item.model = modelData
			}
		}
	}

	Item {
		Layout.fillWidth: true
		Layout.fillHeight: true
	}
}
