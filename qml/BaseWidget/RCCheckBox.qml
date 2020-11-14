import QtQuick.Controls 2.12
import QtQuick 2.12


CheckBox{
    property color g_textColor:"white"

    property var rectangleWidth:18
    property var rectangleHeight:18

    property var g_checkBoxName

    property var imagePath:"qrc:/Item/unChecked.png"
    id:checkBox

    indicator:Rectangle
    {
        id:rememberRectangle
        anchors.verticalCenter:checkBox.verticalCenter
        anchors.left: checkBox.left
        implicitWidth:rectangleWidth
        implicitHeight:rectangleHeight
        radius: 4

        Image
        {
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            source: (checkBox.checked)?imagePath = "qrc:/Item/Checked.png"
                                      :imagePath = "qrc:/Item/unChecked.png"
        }

    }
    contentItem: Text
    {
        font.family: "微软雅黑"
        font.pointSize: 10
        text: g_checkBoxName
        color:g_textColor
        anchors.verticalCenter:rememberRectangle.verticalCenter
        anchors.left: rememberRectangle.right
        anchors.leftMargin: 10
    }
}
