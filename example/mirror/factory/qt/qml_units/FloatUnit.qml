import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import "qrc:///qml_units"

RowLayout {
    id: floatUnit
    property variant model: null

	Label {
		Layout.preferredWidth: 150
		text: floatUnit.model.name
	}

	TextField {
		Layout.fillWidth: true
		validator: DoubleValidator { }
		text: floatUnit.model.nested.value
		onEditingFinished: {
			floatUnit.model.nested.value = text
		}
	}
}
