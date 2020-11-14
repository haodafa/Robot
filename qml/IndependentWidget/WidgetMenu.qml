import QtQuick 2.5
import QtQuick.Controls 2.5
import BaseWidget 1.0

Menu
{
    width:220

    signal signalMenuReturnResult(var enumResult)

    enum IconType
    {
        MENU_USERINFO,
        MENU_DATAANALYSE,
        MENU_MONITOR,
        MENU_LOGOUT,
        MENU_QUIT
     }

    Action
    {
        text: qsTr("用户信息");
        onTriggered:
        {
            signalMenuReturnResult(WidgetMenu.IconType.MENU_USERINFO)
        }
    }

    Action
    {
        text: qsTr("数据分析");
        onTriggered:
        {
            signalMenuReturnResult(WidgetMenu.IconType.MENU_DATAANALYSE)
        }
    }

    Action
    {
        text: qsTr("添加监测点");
        onTriggered:
        {
            signalMenuReturnResult(WidgetMenu.IconType.MENU_MONITOR)
        }
    }

    MenuSeparator
    {
        contentItem: Rectangle
        {
            implicitWidth: 220
            implicitHeight: 1
            color: "#1E000000"
        }
    }

    Action
    {
        text: qsTr("注销");
        onTriggered:
        {
            signalMenuReturnResult(WidgetMenu.IconType.MENU_LOGOUT)
        }
    }

    Action
    {
        text: qsTr("退出");
        onTriggered:
        {
            signalMenuReturnResult(WidgetMenu.IconType.MENU_QUIT)
        }
    }

    background:Rectangle
    {
        implicitWidth: parent.width
        implicitHeight: 55
        color: "#0E4269"
    }

    delegate:RCMenuDelegate
    {

    }
}
