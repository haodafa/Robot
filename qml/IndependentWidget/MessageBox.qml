import QtQuick 2.7
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQuick.Window 2.12


import BaseWidget 1.0

Window {
    id:root
    modality:Qt.ApplicationModal
    flags: Qt.FramelessWindowHint
    width: 590
    height: 260

    color: "transparent"

    property int m_enumReturnResult:MessageBox.ReturnType.RESULT_NO

    enum ReturnType
    {
        RESULT_YES,
        RESULT_NO,
        RESULT_CLOSE
    }

    signal signalReturnResult(var enumReturn);

    Rectangle
    {
        id:rect
        width: parent.width - 20
        height: parent.height - 20
        anchors.centerIn: parent
        radius: 10

        Column
        {
            width: parent.width
            height: parent.height

            Rectangle
            {
                id:titeRect
                width: parent.width
                height: 72
                radius: 10

                MouseArea
                {
                    anchors.fill: parent  //整个区域都接受鼠标事件
                    property point clickPos: "0,0"
                    visible: true
                    onPressed:
                    {
                        clickPos = Qt.point(mouse.x,mouse.y)

                    }
                    onPositionChanged:
                    {
                        // 鼠标偏移量
                        var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                        // 如果mainwinodw继承自QWidget,用setPos
                        root.x = root.x+delta.x
                        root.y = root.y+delta.y
                    }
                }

                Text
                {
                    id: txtTiteName
                    anchors.left: parent.left
                    anchors.leftMargin: 24
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    text: qsTr("提示")
                    font.family: "微软雅黑"
                    font.pointSize: 14
                    color: "black"
                }

                RCIconButton
                {
                    width: 20;
                    height: 20;
                    anchors.top: parent.top
                    anchors.topMargin: 20
                    anchors.right: parent.right
                    anchors.rightMargin: 27
                    g_sizeCanva:Qt.size(15, 15)
                    enumCurrentIconType:RCIconButton.IconType.TYPE_NOBACKCLOSE
                    lineColor:"#9A9DA3"

                    onButtonClicked:
                    {
                        m_enumReturnResult = MessageBox.ReturnType.RESULT_CLOSE
                        signalReturnResult(m_enumReturnResult)
                    }
                }
            }
            Rectangle
            {
                width: parent.width
                height: parent.height - rect_1.height - titeRect.height

                Row
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 34
                    spacing: 14

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

            Rectangle
            {
                id:rect_1
                width: parent.width
                height: 72
                radius: 10

                Row
                {
                    anchors.right: parent.right
                    anchors.rightMargin: 34
                    anchors.top: parent.top
                    spacing: 28

                    RCButton
                    {
                        width:100
                        height:42
                        normalBackgroundColor:"#006EFF"
                        hoveredBackgroundColor:"#1A8CFF"
                        pressedBackgroundColor:"#0054E6"
                        g_btnText:"确定"
                        g_fontSize:12
                        visible: false
                    }

                    RCButton
                    {
                        width:100
                        height:42
                        normalBackgroundColor:"#FFFFFF"
                        hoveredBackgroundColor:"#E0E2E5"
                        pressedBackgroundColor:"#D4D6D9"
                        hoveredBorderColor:"#C8CACC"
                        pressedBorderColor:"#C8CACC"
                        normalBorderColor:"#E0E2E5"
                        textColor:"#606266"
                        g_btnText:"取消"
                        g_fontSize:12
                        visible: false
                    }

                    RCButton
                    {
                        width:100
                        height:42
                        normalBackgroundColor:"#006EFF"
                        hoveredBackgroundColor:"#1A8CFF"
                        pressedBackgroundColor:"#0054E6"
                        g_btnText:"是"
                        g_fontSize:12

                        onClicked:
                        {
                            m_enumReturnResult = MessageBox.ReturnType.RESULT_YES
                            signalReturnResult(m_enumReturnResult)
                        }
                    }

                    RCButton
                    {
                        width:100
                        height:42
                        normalBackgroundColor:"#FFFFFF"
                        hoveredBackgroundColor:"#E0E2E5"
                        pressedBackgroundColor:"#D4D6D9"
                        hoveredBorderColor:"#C8CACC"
                        pressedBorderColor:"#C8CACC"
                        normalBorderColor:"#E0E2E5"
                        textColor:"#606266"
                        g_btnText:"否"
                        g_fontSize:12

                        onClicked:
                        {
                            m_enumReturnResult = MessageBox.ReturnType.RESULT_NO
                            signalReturnResult(m_enumReturnResult)
                        }
                    }
                }
            }
        }
    }

    DropShadow {
        anchors.fill: rect
        horizontalOffset: 0
        verticalOffset: 0
        radius: 10
        samples: 22
        color: "#AA000000"
        source: rect
    }

    function setContentText(strTite, strContent)
    {
        txtTiteName.text = strTite
        txtContent.text = strContent
    }
}
