import QtQuick 2.11
import QtQuick.Window 2.11
import lograt 1.0

Window {
    visible: true
    width: 640
    height: 480
    visibility: Window.Maximized
    title: qsTr("Lograt")
    color: "black"

    Flickable {
        id: __flickable

        anchors.fill: parent
        contentWidth: contentItem.childrenRect.width
        contentHeight: contentItem.childrenRect.height
        flickableDirection: Flickable.VerticalFlick

        Column{
            Repeater {
                id: __repeater
                model: LogLinesModel {
                    id: __model
                }

                Text {
                    color: "white"
                    text: model.display ? model.display : ""
                }
            }
        }
    }

    DropArea {
        anchors.fill: parent
        onDropped: {
            var fileScheme = "file://"
            var filepath = drop.text
            console.log("dropped file " + filepath)
            if(filepath.indexOf(fileScheme) === -1) {
                console.log("file scheme not present. rejecting drop.")
                return
            }

            __model.filename = filepath.substring(fileScheme.length, filepath.length)
        }
    }

    Component.onCompleted: {
        // filename is a RootContext property
        if(filename.length === 0)
            return

        __model.filename = filename
    }
}
