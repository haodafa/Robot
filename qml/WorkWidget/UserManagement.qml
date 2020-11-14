import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import BaseWidget 1.0
import IndependentWidget 1.0

import BusinessData 1.0
import BusinessLogic 1.0
import QRobotControl 1.0
import BaseData 1.0
import RobotControl.UserManager 1.0

Item {
    anchors.fill: parent
    visible: true

    property var bIsNew: true
    property var nCurIndex: -1

    Column
    {
        width: parent.width-160
        height: parent.height-110
        topPadding:40
        bottomPadding:70
        leftPadding: 80
        rightPadding: 80
        Rectangle
        {
            id:qqq
            width: parent.width
            height: 50
            color: "transparent"

            Row
            {
                anchors.right: parent.right
                spacing: 25

                RCComboBox
                {
                    id:searchType
                    width: 180
                    height: 50
                    g_borderColor:"transparent"
                    g_textColor:"#3E3F41"
                    g_selectItemColor:"#EAF5FF"
                    g_selectItemTextColor:"#141415"
                    g_selectTextColor:"white"
                    g_textSize:12
                    g_readOnly:true
                    model: ["用户名称","用户账号","用户职位"]

                    onCurrentIndexChanged:
                    {
                        search.focus = true
                    }
                }
                RCSearchWidget
                {
                    id:search
                    focus: true
                    property var textChange: false
                    onSignalSearchClicked:
                    {
                        if(textChange)
                        {
                            MainWindow.userManagement.passConditionSelectUserInfo(strContext, searchType.currentIndex)
                            setSelectRow(0)

                            textChange = false
                        }
                    }

                    onSignalTextChange:
                    {
                        textChange = true
                    }
                }
            }
        }

        Row
        {
            topPadding:30
            bottomPadding:20
            width: parent.width
            Rectangle
            {
                id:www
                width: parent.width
                height: 45
                color: "transparent"

                RCButton
                {
                    width: 150
                    height: 45
                    anchors.right: parent.right
                    normalBackgroundColor:"#006EFF"
                    hoveredBackgroundColor:"#1A8CFF"
                    pressedBackgroundColor:"#0054E6"
                    g_btnText:"新建用户"
                    g_fontSize:12

                    onClicked:
                    {
                        newUserInfo()
                    }
                }
            }
        }

        RCTableView
        {
            id:tableview
            width: parent.width
            height: parent.height - qqq.height - www.height - 50

            Component.onCompleted:
            {
                setSelectRow(0)
            }

            model:BusinessData.listModelUserInfo.objectlist

            RCTableViewColumn {
                title: "序号"
            }

            RCTableViewColumn {
                role: "strUserName"
                title: "用户姓名"
                _width: 150
            }

            RCTableViewColumn {
                role: "strUserID"
                title: "用户账号"
                _width: 170

                delegate: Rectangle
                {
                    color:"transparent"
                    RCToolTipText
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        font.pointSize: 12
                        text:styleData.value
                        horizontalAlignment:Text.AlignLeft
                        width:parent.width - 20
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            setSelectRow(styleData.row)
                        }
                    }
                }
            }

            RCTableViewColumn {
                role: "strUserExual"
                title: "性别"
                _width: 110
            }

            RCTableViewColumn {
                role: "strUserJobType"
                title: "工作职位"
                _width: 180
            }

            RCTableViewColumn {
                role: "strUserType"
                title: "管理权限"
                _width: 200

                delegate: Rectangle
                {
                    color:"transparent"
                    RCToolTipText
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        font.pointSize: 12
                        text: styleData.value ? (styleData.value.enumUserType === UserInfo.USERTYPE_GENERAL) ? "普通用户"
                             : (styleData.value.enumUserType === UserInfo.USERTYPE_MANAGE) ? "管理员" : "超级管理员" :""
                        horizontalAlignment:Text.AlignLeft
                        width:parent.width - 20
                    }

                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked:
                        {
                            setSelectRow(styleData.row)
                        }
                    }
                }
            }

            RCTableViewColumn {
                role: "strUserBuildTime"
                title: "注册/修改时间"
                _width: 300
            }

            RCTableViewColumn {
                role: "operate"
                title: "操作"
                _width: 320

                delegate: Rectangle
                {
                    color:"transparent"

                    Row
                    {
                        spacing: 40
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        RCButton
                        {
                            width:120
                            height:40
                            normalBackgroundColor:"#006EFF"
                            hoveredBackgroundColor:"#1A8CFF"
                            pressedBackgroundColor:"#0054E6"
                            g_btnText:"修改"
                            g_fontSize:12

                            onClicked:
                            {
                                modificationBtnClicked(styleData.row)
                            }
                        }

                        RCButton
                        {
                            width:120
                            height:40
                            normalBackgroundColor:"#006EFF"
                            hoveredBackgroundColor:"#1A8CFF"
                            pressedBackgroundColor:"#0054E6"
                            g_btnText:"删除"
                            g_fontSize:12

                            onClicked:
                            {
                                deleteBtnClicked(styleData.row)
                            }
                        }
                    }
                }
            }
        }
    }

    Loader
    {
        id:loaderVanishBox
    }

    Component
    {
        id:vanishBox
        AutoVanishBox
        {

        }
    }

    Loader
    {
        id:loaderUserDialo
    }

    Component
    {
        id:newUserDialog
        NewUserDialog
        {
            visible: true
        }
    }

    Loader
    {
        id:loaderBox
    }
    Component
    {
        id:comMessageBox
        MessageBox
        {
            visible: true
        }
    }

    Connections
    {
        target: loaderBox.item

        onSignalReturnResult:
        {
            if(enumReturn === MessageBox.ReturnType.RESULT_YES)
            {
                MainWindow.userManagement.deleteUser(nCurIndex)

                if(nCurIndex === tableview.rowCount && tableview.rowCount != 1)
                {
                    tableview.selection.select(nCurIndex - 1)
                }
                else
                {
                    tableview.selection.select(nCurIndex)
                }
            }
            loaderBox.sourceComponent = undefined
        }
    }

    Connections
    {
        target: loaderUserDialo.item

        onSignalReturnResult:
        {
            if(enumReturn === NewUserDialog.ReturnType.RESULT_CONFIRM)
            {
                var userInfo = loaderUserDialo.item.getUserInfo()
                var strContext
                var bSuccess

                if(bIsNew)
                {
                    bSuccess = MainWindow.userManagement.newUserInfo(userInfo)

                    if(bSuccess === 0)
                    {
                        strContext = "新建用户成功！"
                    }
                    else if(bSuccess === -1)
                    {
                        strContext = "新建用户失败！"
                    }
                    else
                    {
                        strContext = "用户账号已存在！"
                    }
                }
                else
                {
                    bSuccess = MainWindow.userManagement.modificationUserInfo(userInfo, nCurIndex)

                    if(bSuccess)
                    {
                        strContext = "修改用户成功！"
                    }
                    else
                    {
                        strContext = "修改用户失败！"
                    }
                }

                loaderVanishBox.sourceComponent = vanishBox
                loaderVanishBox.item.setTxtContent(strContext)
            }
            loaderUserDialo.sourceComponent = undefined
        }
    }

    Connections
    {
        target: loaderVanishBox.item

        onSignalClose:
        {
            loaderVanishBox.sourceComponent = undefined
        }
    }

    function setSelectRow(nRow)
    {
        tableview.selection.clear()

        if(nRow >= 0 && nRow < tableview.rowCount)
        {
            tableview.selection.select(nRow)
        }
    }


    /*---------------------------------------------------------------------------
    函数名：modificationBtnClicked
    功能：修改按键点击
    参数：
        index 索引
    返回值：
    作者：guokai
    创建时间：2020-11-02
    备注：

    ---------------------------------------------------------------------------*/
    function newUserInfo()
    {
        loaderUserDialo.sourceComponent = newUserDialog

        loaderUserDialo.item.initNewUserWidgte()

        bIsNew = true;
    }


    /*---------------------------------------------------------------------------
    函数名：modificationBtnClicked
    功能：修改按键点击
    参数：
        index 索引
    返回值：
    作者：guokai
    创建时间：2020-11-02
    备注：

    ---------------------------------------------------------------------------*/
    function modificationBtnClicked(index)
    {
        setSelectRow(index)

        bIsNew = false;
        nCurIndex = index

        var userInfo = MainWindow.userManagement.getUserInfo(index)

        if(BusinessData.curUserInfo.strUserID === userInfo.strUserID)
        {
            loaderUserDialo.sourceComponent = newUserDialog
            loaderUserDialo.item.setUserInfo(userInfo)
        }
        else
        {
            if(BusinessData.curUserInfo.enumUserType === UserInfo.USERTYPE_GENERAL)
            {
                loaderVanishBox.sourceComponent = vanishBox
                loaderVanishBox.item.setTxtContent("权限不足，无法修改该用户！")
            }
            else if(BusinessData.curUserInfo.enumUserType === UserInfo.USERTYPE_MANAGE)
            {
                if(userInfo.enumUserType === UserInfo.USERTYPE_MANAGE
                   || userInfo.enumUserType === UserInfo.USERTYPE_SUPERMANAGE)
                {
                    loaderVanishBox.sourceComponent = vanishBox
                    loaderVanishBox.item.setTxtContent("权限不足，无法修改该用户！")
                }
                else
                {
                    loaderUserDialo.sourceComponent = newUserDialog
                    loaderUserDialo.item.setUserInfo(userInfo)
                }
            }

            else
            {
                if(BusinessData.curUserInfo.strUserID === "admin"
                        && userInfo.strUserID !== "admin")
                {
                    loaderUserDialo.sourceComponent = newUserDialog
                    loaderUserDialo.item.setUserInfo(userInfo)
                }
                else
                {
                    if(userInfo.enumUserType === UserInfo.USERTYPE_GENERAL
                       || userInfo.enumUserType === UserInfo.USERTYPE_MANAGE)
                    {
                        loaderUserDialo.sourceComponent = newUserDialog
                        loaderUserDialo.item.setUserInfo(userInfo)
                    }
                    else
                    {
                        loaderVanishBox.sourceComponent = vanishBox
                        loaderVanishBox.item.setTxtContent("无法修改该用户！")
                    }
                }
            }
        }
    }


    /*---------------------------------------------------------------------------
    函数名：deleteBtnClicked
    功能：删除按键点击
    参数：
        index 索引
    返回值：
    作者：guokai
    创建时间：2020-11-02
    备注：

    ---------------------------------------------------------------------------*/
    function deleteBtnClicked(index)
    {
        setSelectRow(index)
        nCurIndex = index
        var userInfo = MainWindow.userManagement.getUserInfo(index)

        if(BusinessData.curUserInfo.enumUserType === UserInfo.USERTYPE_GENERAL)
        {
            loaderVanishBox.sourceComponent = vanishBox
            loaderVanishBox.item.setTxtContent("权限不足，无法删除该用户！")
        }
        else if(BusinessData.curUserInfo.enumUserType === UserInfo.USERTYPE_MANAGE)
        {
            if(userInfo.enumUserType === UserInfo.USERTYPE_MANAGE
               || userInfo.enumUserType === UserInfo.USERTYPE_SUPERMANAGE)
            {
                loaderVanishBox.sourceComponent = vanishBox
                loaderVanishBox.item.setTxtContent("权限不足，无法删除该用户！")
            }
            else
            {
                loaderBox.sourceComponent = comMessageBox
                loaderBox.item.setContentText("提示", "是否永久删除该用户信息？")
            }
        }
        else
        {
            if(BusinessData.curUserInfo.strUserID === "admin")
            {
                if(userInfo.strUserID === "admin")
                {
                    loaderVanishBox.sourceComponent = vanishBox
                    loaderVanishBox.item.setTxtContent("无法删除该用户！")
                }
                else
                {
                    loaderBox.sourceComponent = comMessageBox
                    loaderBox.item.setContentText("提示", "是否永久删除该用户信息？")
                }
            }
            else
            {
                if(userInfo.enumUserType === UserInfo.USERTYPE_GENERAL
                   || userInfo.enumUserType === UserInfo.USERTYPE_MANAGE)
                {
                    loaderBox.sourceComponent = comMessageBox
                    loaderBox.item.setContentText("提示", "是否永久删除该用户信息？")
                }
                else
                {
                    loaderVanishBox.sourceComponent = vanishBox
                    loaderVanishBox.item.setTxtContent("无法删除该用户！")
                }
            }
        }
    }
}
