import QtQuick.Controls 2.2
import QtQuick 2.12

TextField{
    property var g_width:300
    property var g_height:45

    property var g_textSize:12

    property color g_backgroundColor:"white"
    property color g_selectBackgroundColor:"#0078D7"

    property color g_borderColor:"#0078D8"

    property color g_textColor:"#303133"
    property color g_selectTextColor:"white"

    property var g_regExp: "[a-zA-Z0-9\u4e00-\u9fa5][a-zA-Z0-9\u4e00-\u9fa5]+"

    id:control
    width:g_width
    height:g_height
    selectByMouse:true
    selectionColor:g_selectBackgroundColor
    selectedTextColor:g_selectTextColor
    color: g_textColor
    font.pointSize: g_textSize
    font.family: "微软雅黑"
    leftPadding: 20
    focus: true
    background:Rectangle
    {
        color: enabled ? g_backgroundColor : "#E3E6EA"
        implicitHeight: g_height
        implicitWidth: g_width
        border.color: g_borderColor
        border.width: 1
        radius:4
    }

    validator: RegExpValidator
    {
        regExp:new RegExp(g_regExp)
    }
}
