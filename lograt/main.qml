import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import lograt 1.0
import QtQml 2.11

Window {
    visible: true
    visibility: Window.Maximized
    title: qsTr("Lograt")
    color: "black"


    TableView {
        id: __tableview

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: __rockscroll.left

        frameVisible: false
        sortIndicatorVisible: true

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

        itemDelegate: Item {
            clip: true
            TextEdit {
                readOnly: true
                anchors.verticalCenter: parent.verticalCenter
                color: __tableview.getColorForStr(styleData.column, styleData.value)
                text: styleData.value
                selectByMouse: true
            }
        }

        Component {
            id: columnComponent
            TableViewColumn {}
        }

        function getColorForStr(columnIndex, string) {
            var config = __model.columnConfig(columnIndex)
            return config.colorForString(string)
        }

        function updateColumns() {
            while(columnCount != 0) { // Remove existing columns first
                removeColumn(0);
            }

            for(var i = 0; i < __model.columnCount(0); i++)
            {
                var colConfig = __model.columnConfig(i)
                var newCol = columnComponent.createObject(__tableview, {
                                                              role: colConfig.name,
                                                              title: colConfig.name,
                                                              width: colConfig.width
                                                          })
                __tableview.addColumn(newCol)
            }
        }
    }

    RockScroll {
        id: __rockscroll
        width: 50
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
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

    property real golden_ratio_conjugate:0.618033988749895
    property real h: Math.random()
    function randomColor() {
        h += golden_ratio_conjugate
        h %= 1
        return Qt.hsva(h, 0.5, 0.95, 1)
    }
}
