import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import QtQuick.Controls 1.4 as Control_1_4
import QtQuick.Controls.Styles 1.4 as Control_styles_1_4

Window {
    modality:Qt.ApplicationModal
    flags: Qt.FramelessWindowHint
    width: 334
    height: 220

    color: "transparent"

    property var g_strText:"正在登录中..."

    Rectangle
    {
        id:rect
        anchors.fill: parent
        radius: 10

        Control_1_4.BusyIndicator
        {
            width: 110
            height: 110
            anchors.top:parent.top
            anchors.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter
            style: Control_styles_1_4.BusyIndicatorStyle
            {
                indicator: RCBusyIndicatorType{}
            }

            Rectangle
            {
                anchors.centerIn: parent
                width: 60
                height: 60
                Image
                {
                    anchors.fill:parent
                    source: "qrc:/Item/Robot.png"
                }
            }
        }

        Text {
            anchors.bottom:parent.bottom
            anchors.bottomMargin: 15
            anchors.horizontalCenter: parent.horizontalCenter
            text: g_strText
            font.pointSize: 13
            font.family: "微软雅黑"
        }
    }


}
