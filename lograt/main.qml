import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import lograt 1.0

Window {
    visible: true
    visibility: Window.Maximized
    title: qsTr("Lograt")
    color: "black"

    TableView {
        id: __tableview
        frameVisible: false
        sortIndicatorVisible: true
        anchors.fill: parent

        TableViewColumn {
            role: "index"
            title: "#"
            width: 50
        }

        TableViewColumn {
            role: "display"
            title: "text"
            width: 600
        }

        model: LogLinesModel {
            id: __model
        }

        style: TableViewStyle {
            backgroundColor: "black";
            alternateBackgroundColor: "black"
            textColor: "white"
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
