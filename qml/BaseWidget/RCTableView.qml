import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TableView{
    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
    verticalScrollBarPolicy:Qt.ScrollBarAlwaysOff   //隐藏横向和竖向滚动条
    id:tableView
    clip: true
    backgroundVisible: true;
    frameVisible: true

    style:TableViewStyle{
        backgroundColor: "#990E4269"

        frame: Rectangle {
            color: "#990E4269"
            radius: 6
            border {
                color: "#047BB4"
                width: 1
            }
        }

        rowDelegate: Rectangle {
            radius: 5
            height: 72
            color : styleData.selected ? "#024F7A": "transparent"//#99184860

            Rectangle
            {
                width: parent.width
                height: 1
                anchors.bottom: parent.bottom
                color: "#29628E"
                visible: (styleData.row < rowCount)? true : false
            }
         }

        headerDelegate:Rectangle{
            color: "#176AA8"
            height: 77
            anchors.top: parent.top
            anchors.topMargin: 1.5
            radius: (styleData.column === 0 || styleData.column === columnCount - 1 ) ? 6 : 0
            Rectangle
            {
                width: 10
                height: parent.height
                anchors.right:parent.right
                color:"#176AA8"
                visible: (styleData.column === 0) ? true : false
            }

            Rectangle
            {
                width: parent.width
                height: 5
                anchors.bottom:parent.bottom
                color:"#176AA8"
                visible: (styleData.column === 0 || styleData.column === columnCount - 1 ) ? true : false
            }

            Rectangle
            {
                width: 10
                height: parent.height
                anchors.left:parent.left
                color:"#176AA8"
                visible: (styleData.column === columnCount - 1) ? true : false
            }
            Text {
                color: "white"
                anchors.fill: parent
                horizontalAlignment:(styleData.column === 0) ? Text.AlignHCenter:Text.AlignLeft
                verticalAlignment:Text.AlignVCenter
                text: styleData.value
                font.pointSize: 12
                font.family: "微软雅黑"
            }
        }

        itemDelegate:Rectangle{
            color: "transparent"
            Text {
                anchors.fill: parent
                color: "white"
                verticalAlignment:Text.AlignVCenter
                horizontalAlignment:(styleData.column === 0) ? Text.AlignHCenter:Text.AlignLeft
                text: (styleData.column === 0) ? styleData.row+1 : (styleData.column !== columnCount - 1) ? styleData.value:""
                font.pointSize: 12
                font.family: "微软雅黑"
            }
        }
     }
}
