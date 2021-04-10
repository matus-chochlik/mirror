import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2
import "qrc:///qml_units"

ColumnLayout {
    id: builderUnit
    property variant model: null

	Label {
		Layout.fillWidth: true
		text: qsTr("Select product type")
	}

	ComboBox {
		id: factorySelector
		Layout.fillWidth: true
		model: builderUnit.model.factoryLabels
		onActivated: builderUnit.model.selectFactory(currentIndex)
	}

	ScrollView {
		Layout.fillWidth: true
		Layout.fillHeight: true
		clip: true
		ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
		ColumnLayout {
			FactoryUnit {
				Layout.preferredWidth: builderUnit.width
				Layout.fillHeight: true
				model: builderUnit.model.selectedFactory
			}
		}
	}

	Button {
		Layout.fillWidth: true
		text: qsTr("construct")
		onClicked: {
			message.text = builderUnit.model.selectedFactory.test()
		}
	}

	TextArea {
		id: message
		text: ""
		readOnly: true
	}
}
