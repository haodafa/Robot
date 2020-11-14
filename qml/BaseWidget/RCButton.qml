import QtQuick.Controls 2.12
import QtQuick 2.12


Button{
    property color hoveredBackgroundColor:"transparent"
    property color pressedBackgroundColor:"transparent"
    property color normalBackgroundColor:"transparent"

    property color hoveredBorderColor:"transparent"
    property color pressedBorderColor:"transparent"
    property color normalBorderColor:"transparent"

    property color textColor:"white"

    property var g_fontSize:13

    property var g_btnText:""

    property var g_radius:4

    id:buttonId
    background:Rectangle
    {
        radius: g_radius
        color:(buttonId.pressed)?pressedBackgroundColor
                                :(buttonId.hovered)?hoveredBackgroundColor:normalBackgroundColor

        border.width:1
        border.color:(buttonId.pressed)?pressedBorderColor
                                       :(buttonId.hovered)?hoveredBorderColor:normalBorderColor
    }

    contentItem: Text
    {
        font.family: "微软雅黑"
        horizontalAlignment:Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: g_fontSize
        text: g_btnText
        color:textColor
    }
}
