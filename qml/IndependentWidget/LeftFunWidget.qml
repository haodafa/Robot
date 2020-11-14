import QtQuick.Controls 2.12
import QtQuick 2.12

import BusinessData 1.0
import BusinessLogic 1.0
import QRobotControl 1.0
import BaseData 1.0


Flickable {
    id:funWidget

    contentHeight :_largeColumn.height
    boundsBehavior: Flickable.StopAtBounds
    clip:true

    property var m_nCurrentSelectIndex:-1
    property color m_backgroundNormal:"transparent"
    property color m_backgroundSelected:"#006699"
    property color m_backgroundEnter:"#96006699"

    property var m_fontSizeNormal:11
    property var m_fontSizeSelected:12
    property var m_fontSizeEnter:11

    signal signalLeftFunBtnClicked(var strID)

    Column {
        id:         _largeColumn
        width:      parent.width
        spacing:    20

        Repeater
        {
            id:www
            model: BusinessData.listFunBtnID
            Loader {
                sourceComponent:funBtn
                property color m_backgroundColor:m_backgroundNormal
                property var m_nFontSize:m_fontSizeNormal
                property var g_bFuncBtnSelected:false

                property FunBtnInfo m_funBtnInfo:BusinessLogic.slotGetLeftFunBtnInfo(modelData)

                function funBtnSelected(bSelected)
                {
                    g_bFuncBtnSelected = bSelected
                    if(bSelected)
                    {
                        if(m_nCurrentSelectIndex >= 0)
                        {
                            www.itemAt(m_nCurrentSelectIndex).funBtnSelected(false)
                        }
                        m_nCurrentSelectIndex = index
                        m_backgroundColor = m_backgroundSelected
                        m_nFontSize = m_fontSizeSelected
                    }
                    else
                    {
                        m_backgroundColor = m_backgroundNormal
                        m_nFontSize = m_fontSizeNormal
                    }
                }
            }
        }
    }

    Component
    {
        id:funBtn

        Rectangle
        {
            id:funBtnRec
            clip: true
            width: funWidget.width
            height: 60
            color: m_backgroundColor

            Text {
                anchors.left: parent.left
                anchors.leftMargin:40
                anchors.verticalCenter: parent.verticalCenter
                text: m_funBtnInfo.strName
                color:"white"
                font.family: "微软雅黑"
                font.pointSize: m_nFontSize
                font.letterSpacing: 3
            }

            MouseArea
            {
                anchors.fill: parent
                hoverEnabled:true
                onClicked:
                {
                    if(!g_bFuncBtnSelected)
                    {
                        funBtnSelected(true)

                        signalLeftFunBtnClicked(m_funBtnInfo.strID)
                    }
                }

                onEntered:
                {
                    if(!g_bFuncBtnSelected)
                    {
                        m_nFontSize = m_fontSizeEnter
                        m_backgroundColor = m_backgroundEnter
                    }
                }

                onExited:
                {
                    if(!g_bFuncBtnSelected)
                    {
                        m_nFontSize = m_fontSizeNormal
                        m_backgroundColor = m_backgroundNormal
                    }
                }
            }
        }
    }

    function indexfunBtnSelected(nIndex,bSelected)
    {
        if(www.count > 0)
        {
            www.itemAt(nIndex).funBtnSelected(bSelected)
        }
    }
}
