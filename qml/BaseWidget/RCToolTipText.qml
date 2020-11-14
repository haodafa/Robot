import QtQuick 2.0
import QtQuick.Controls 2.2


Text {
    id: name
    clip :true                  // 是否剪切掉超出显示范围的文字，默认false
    font.family: "微软雅黑"
    elide: Text.ElideRight      // 超出显示范围的用...代替
    color: "white"

    ToolTip {
        parent: name
        delay:100
        visible: mouseArea.isEntered
        text: name.text
        background:rect
        font.pointSize:12
        x:mouseArea.clickPos.x + 10
        y:name.height

        Rectangle
        {
            id:rect
            color: "white"
            radius: 4
            border.color: "#C0C4CC"
            border.width: 1
        }
    }

    MouseArea
    {
        id:mouseArea
        width: contentWidth
        height: name.height
        hoverEnabled:true
        property bool isEntered: false
        property point clickPos: "0,0"

        onEntered:{
            isEntered = true
            clickPos = Qt.point(mouseX,mouseY)
        }

        onExited:{
            isEntered = false
        }
    }
}
