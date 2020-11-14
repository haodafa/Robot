import QtQuick 2.5
import QtQuick.Controls 2.5

MenuItem {
    id: menuItem

    property color g_textColor:"white"
    property color g_selectTextColor:"white"
    
    property color g_selectItemColor:"#024F7A"

    implicitWidth: 220
    implicitHeight: 55

    leftPadding: 20

    font: Qt.font({
                  family: "微软雅黑",
                  pointSize: 11,
                  })

    contentItem: Text
    {
         text: menuItem.text
         font: menuItem.font
         color: menuItem.highlighted ? g_selectTextColor : g_textColor
         horizontalAlignment: Text.AlignLeft
         verticalAlignment: Text.AlignVCenter
         elide: Text.ElideRight
     }

    background: Rectangle
    {
        anchors.centerIn: menuItem
        implicitWidth: 200
        implicitHeight: parent.height
        opacity: enabled ? 1 : 0.3
        color: menuItem.highlighted ? g_selectItemColor : "transparent"
    }
}
