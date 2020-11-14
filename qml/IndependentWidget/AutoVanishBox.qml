import QtQuick 2.7
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

import BaseWidget 1.0

Window {
    id:root
    width: 280
    height: 65
    visible:true
    modality:Qt.ApplicationModal
    flags: Qt.FramelessWindowHint

    color: "transparent"

    signal signalClose();

    Rectangle
    {
        id:rect
        anchors.fill: parent
        color: "#FFFFFF"
        radius: 4

        Row
        {
            leftPadding: 20
            rightPadding: 10
            spacing: 15
            anchors.fill: parent
            Image
            {
                anchors.verticalCenter: parent.verticalCenter
                width: 34
                height: 34
                source: "qrc:/Item/IconTips.png"
            }

            Text
            {
                id:txtContent
                anchors.verticalCenter: parent.verticalCenter
                font.family: "微软雅黑"
                font.pointSize: 12
                color: "#303133"
            }
        }
    }

    Timer
    {
        id:timer
        repeat:false
        interval:3000
        onTriggered:
        {
            signalClose()
        }
    }

    Component.onCompleted:
    {
        timer.start()
    }

    function setTxtContent(strContent)
    {
        txtContent.text = strContent
        root.width = 80 + txtContent.width
    }
}
