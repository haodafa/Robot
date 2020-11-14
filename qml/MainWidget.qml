import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Window 2.12

import BaseWidget 1.0
import IndependentWidget 1.0
import WorkWidget 1.0

import BusinessData 1.0
import BusinessLogic 1.0
import QRobotControl 1.0
import BaseData 1.0

Window {
    id:mainWidget
    title: qsTr("机器人管理平台")
    color: "transparent"

    flags: Qt.FramelessWindowHint | Qt.Window | Qt.WindowSystemMenuHint | Qt.WindoMinimizeButtonHint
            | Qt.WindowMaximizeButtonHint | Qt.WindowMinMaxButtonsHint

    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight

    Image
    {
        anchors.fill: parent
        fillMode: Image.Stretch
        source:"qrc:/Item/MainWidget_1.jpg"
    }

    Rectangle
    {
        color: "#96003C58"
        anchors.fill:parent
    }

    Column{
        width: parent.width
        height: parent.height
        Rectangle
        {
            id:titeRec
            color: "#78012440"
            width:parent.width
            height:60

            Row
            {
                leftPadding:15
                spacing: 20
                Image
                {
                    width: 50
                    height: 58
                    anchors.verticalCenter: parent.verticalCenter
                    fillMode: Image.PreserveAspectCrop
                    source:"qrc:/Item/Robot.png"
                }

                Text
                {
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("机器人管理平台")
                    font.pointSize: 15
                    font.family: "微软雅黑"
                    color:"white"
                    font.letterSpacing: 6
                }
            }

            Row
            {
                anchors.right: parent.right
                
                RCIconButton
                {
                    id:btnMenu
                    width: 45;
                    height: 36;
                    enumCurrentIconType:RCIconButton.IconType.TYPE_MENU
                    bIsRadius: false;
                    g_sizeCanva:Qt.size(20, 36)

                    onButtonClicked:
                    {
                        widgetMenu.popup()
                    }
                }
                
                RCIconButton
                {
                    id:btnMini
                    width: 60;
                    height: 36;
                    enumCurrentIconType:RCIconButton.IconType.TYPE_MINI
                    bIsRadius: false;
                    g_sizeCanva:Qt.size(15, 15)

                    onButtonClicked:
                    {
                        mainWidget.showMinimized()
                    }
                }
                RCIconButton
                {
                    id:btnClose
                    width: 60;
                    height: 36;
                    enumCurrentIconType:RCIconButton.IconType.TYPE_CLOSE;
                    bIsRadius: false;
                    g_sizeCanva:Qt.size(14, 14)

                    onButtonClicked:
                    {
                        mainWidget.close()
                    }
                }
            }
        }

        Rectangle
        {
            width: parent.width
            height: parent.height - 60
            color: "transparent"
            Row
            {
                anchors.fill: parent
                Rectangle
                {
                    width: 230
                    height: parent.height
                    color: "#50082740"

                    LeftFunWidget
                    {
                        id:leftFunBtn
                        width: parent.width
                        height: parent.height - 50
                        anchors.top: parent.top
                        anchors.topMargin: 50
                    }
                }

                Rectangle
                {
                    id:workWidgetRect
                    width: parent.width - 230
                    height: parent.height
                    color: "transparent"

                    Loader
                    {
                        id:workWidget
                        anchors.fill: parent
                    }
                }
            }
        }
    }


    WidgetMenu
    {
        id:widgetMenu

    }

    Connections
    {
        target:leftFunBtn

        property FunBtnInfo funBtnInfo;

        onSignalLeftFunBtnClicked:
        {
            funBtnInfo = BusinessLogic.slotGetLeftFunBtnInfo(strID);

            workWidget.source = funBtnInfo.strFilePath
        }
    }

    Connections
    {
        target:widgetMenu

        onSignalMenuReturnResult:
        {
            if(WidgetMenu.IconType.MENU_LOGOUT === enumResult)
            {
                MainWindow.qmlLogoutClicked()
            }

            if(WidgetMenu.IconType.MENU_QUIT === enumResult)
            {
                mainWidget.close()
            }
        }
    }


    /*---------------------------------------------------------------------------
    函数名：initQmlWidgetData
    功能：初始化qml窗口数据
    参数：
    返回值：
    作者：guokai
    创建时间：2020-06-30
    备注：

    ---------------------------------------------------------------------------*/
    function initQmlWidgetData()
    {
        leftFunBtn.indexfunBtnSelected(0,true)

        var funBtnInfo = BusinessLogic.slotGetLeftFunBtnInfo(BusinessData.listFunBtnID[0]);

        workWidget.source = funBtnInfo.strFilePath
    }


    /*---------------------------------------------------------------------------
    函数名：controlWidgetShowHide
    功能：控制窗口显示和隐藏
    参数：
        bShow 是否显示
    返回值：
    作者：guokai
    创建时间：2020-06-30
    备注：

    ---------------------------------------------------------------------------*/
    function controlWidgetShowHide(bShow)
    {
        if(bShow)
        {
            mainWidget.showMaximized();
        }
        else
        {
            mainWidget.hide();
        }
    }
}
