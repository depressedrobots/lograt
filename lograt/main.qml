import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Lograt")

    Flickable {
        id: __flickable

        anchors.fill: parent
        contentWidth: contentItem.childrenRect.width
        contentHeight: contentItem.childrenRect.height
        flickableDirection: Flickable.VerticalFlick

        Column{
            Repeater {
                id: __repeater
                model: 10
                Rectangle {
                    height: 50
                    width: 100
                    border.color: "red"
                    color: "yellow"
                }
            }
        }
    }
}
