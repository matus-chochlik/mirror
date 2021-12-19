import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import "qrc:///qml_units"

RowLayout {
    id: compositeUnit
    property variant model: null

	Label {
		Layout.fillWidth: true
		text: compositeUnit.model.name
	}

	FactoryUnit {
		Layout.fillWidth: true
		Layout.fillHeight: true
		model: compositeUnit.model.nested
	}
}
