import QtQuick 2.2
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.2
import "qrc:///common"

ApplicationWindow {
    id: root
    visible: true
    width: 300
    height: 700
    Material.theme: Material.Dark
	Material.accent: Material.Orange

    Action {
        id: quitAction
        text: qsTr("&Quit")
        shortcut: StandardKey.Quit
        onTriggered: {
            Qt.callLater(Qt.quit)
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                action: quitAction
            }
        }
    }

    contentData: BuilderUnit {
        anchors.fill: parent
        model: backend.builder
    }
}
