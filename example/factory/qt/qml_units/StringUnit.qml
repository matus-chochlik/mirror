import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import "qrc:///qml_units"

RowLayout {
    id: stringUnit
    property variant model: null

	Label {
		Layout.preferredWidth: 150
		text: stringUnit.model.name
	}

	TextField {
		Layout.fillWidth: true
	}
}
