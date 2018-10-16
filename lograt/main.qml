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

        model: LogLinesModel {
            id: __model
            onRowsInserted: __tableview.updateColumns()
        }

        style: TableViewStyle {
            backgroundColor: "black";
            alternateBackgroundColor: "black"
            textColor: "white"
            headerDelegate: Rectangle {
                height: textItem.implicitHeight * 1.2
                width: textItem.implicitWidth
                color: "black"
                Text {
                    id: textItem
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.leftMargin: 12
                    text: styleData.value
                    elide: Text.ElideRight
                    font.bold: true
                    color: "gray"
                    renderType: Text.NativeRendering
                }
            }
        }

        Component {
            id: columnComponent
            TableViewColumn {}
        }

        function updateColumns() {
            while(columnCount != 0) { // Remove existing columns first
                removeColumn(0);
            }

            for(var i = 0; i < __model.columnCount(0); i++)
            {
                var col  = __model.columnName(i);
                var newCol = columnComponent.createObject(__tableview, { "role": col, "title": col})
                __tableview.addColumn(newCol);
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
