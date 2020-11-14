import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Window 2.12

import BaseWidget 1.0

import BusinessData 1.0
import BusinessLogic 1.0
import QRobotControl 1.0
import BaseData 1.0

Window {
    id:root
    modality:Qt.ApplicationModal
    flags: Qt.FramelessWindowHint
    width: 944
    height: 562
    color: "transparent"

    property color g_widgetRedColor:"#FF0000"
    property color g_widgetNormalColor:"#C0C4CC"
    property var isEdit: false

    UserInfo
    {
        id:userInfo
    }

    enum ReturnType
    {
        RESULT_CONFIRM,
        RESULT_CANCEL,
        RESULT_CLOSE
    }

    signal signalReturnResult(var enumReturn);

    signal signalGetUserInfo(var userInfo)

    Rectangle
    {
        id:rect
        anchors.fill: parent
        radius: 10

        Column
        {
            width: parent.width
            height: parent.height
            Rectangle
            {
                id:titeRect
                width: parent.width
                height:60
                color: "#DFE9F8"
                radius: 10

                MouseArea
                {
                    anchors.fill: parent  //整个区域都接受鼠标事件
                    property point clickPos: "0,0"
                    visible: true
                    propagateComposedEvents :true
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
                    anchors.leftMargin: 30
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("修改用户信息")
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
                        if(isEdit)
                        {
                            loader.sourceComponent = comMessageBox
                            loader.item.setContentText("提示", "是否保存当前用户信息？")
                        }
                        else
                        {
                            signalReturnResult(NewUserDialog.ReturnType.RESULT_CLOSE)
                        }
                    }
                }

                Rectangle
                {
                    width: parent.width
                    height: 10
                    color: "#DFE9F8"
                    anchors.bottom: parent.bottom
                }
            }

            Rectangle
            {

                width: parent.width
                height: parent.height-titeRect.height-bottomRect.height
                color: "white"

                Grid
                {
                    columns:2
                    columnSpacing:70
                    rowSpacing:60
                    topPadding: 90
                    leftPadding: 70
                    Rectangle
                    {
                        width: 373
                        height: 46
                        color: "white"

                        Row
                        {
                            height: parent.height
                            anchors.verticalCenter : parent.verticalCenter
                            Rectangle
                            {
                                id:asteriskRect
                                height: parent.height
                                width: asterisk.width
                                Text {
                                    id:asterisk
                                    text: qsTr("*")
                                    color: "red"
                                    font.pointSize: 12
                                    font.family: "微软雅黑"
                                    anchors.verticalCenter : parent.verticalCenter
                                }
                            }

                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("姓名：")
                                color: "#303133"
                                font.pointSize: 12
                                font.family: "微软雅黑"
                            }

                            RCTextField
                            {
                                id:userName
                                height: parent.height
                                width: 258
                                g_borderColor:g_widgetNormalColor
                                g_textColor:"#3E3F41"
                                g_textSize:11

                                onTextChanged:
                                {
                                    changeBorderColor()
                                }
                            }
                            Rectangle
                            {
                                height: parent.height
                                width: 8
                            }

                            Text {
                                id:userNameWarning
                                visible: false
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("必填")
                                font.pointSize: 12
                                color: "red"
                                font.family: "微软雅黑"
                            }
                        }

                    }

                    Rectangle
                    {
                        width: 373
                        height: 46
                        color: "white"

                        Row
                        {
                            height: parent.height
                            anchors.verticalCenter : parent.verticalCenter
                            Text {
                                text: qsTr("*")
                                color: "red"
                                font.pointSize: 12
                                font.family: "微软雅黑"
                                anchors.verticalCenter : parent.verticalCenter
                            }
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("账号：")
                                color: "#303133"
                                font.pointSize: 12
                                font.family: "微软雅黑"
                            }

                            RCTextField
                            {
                                id:userID
                                height: parent.height
                                width: 258
                                g_borderColor:g_widgetNormalColor
                                g_textColor:"#3E3F41"
                                g_textSize:11
                                g_regExp:/[1-9][0-9]{14}/
                                onTextChanged:
                                {
                                    changeBorderColor()
                                }
                            }
                            Rectangle
                            {
                                height: parent.height
                                width: 8
                            }

                            Text {
                                id:userIDWarning
                                visible: false
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("必填")
                                font.pointSize: 12
                                font.family: "微软雅黑"
                                color: "red"
                            }
                        }
                    }

                    Rectangle
                    {
                        width: 373
                        height: 46
                        color: "white"

                        Row
                        {
                            height: parent.height
                            anchors.verticalCenter : parent.verticalCenter
                            Text {
                                text: qsTr("*")
                                color: "red"
                                font.pointSize: 12
                                font.family: "微软雅黑"
                                anchors.verticalCenter : parent.verticalCenter
                            }
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("密码：")
                                color: "#303133"
                                font.pointSize: 12
                                font.family: "微软雅黑"
                            }

                            RCTextField
                            {
                                id:userPassword
                                height: parent.height
                                width: 258
                                g_borderColor:g_widgetNormalColor
                                g_textColor:"#3E3F41"
                                g_textSize:11
                                echoMode:TextInput.Password

                                onTextChanged:
                                {
                                    changeBorderColor()
                                }
                            }
                            Rectangle
                            {
                                height: parent.height
                                width: 8
                            }

                            Text {
                                id:userPasswordWarning
                                visible: false
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("必填")
                                font.pointSize: 12
                                font.family: "微软雅黑"
                                color: "red"
                            }
                        }
                    }

                    Rectangle
                    {
                        width: 373
                        height: 46
                        color: "white"

                        Row
                        {
                            height: parent.height
                            anchors.verticalCenter : parent.verticalCenter
                            Rectangle
                            {
                                height: parent.height
                                width: asteriskRect.width
                                Text {
                                    text: qsTr("*")
                                    color: "red"
                                    font.pointSize: 12
                                    anchors.verticalCenter : parent.verticalCenter
                                    visible: false
                                    font.family: "微软雅黑"
                                }
                            }
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("性别：")
                                color: "#303133"
                                font.pointSize: 12
                                font.family: "微软雅黑"
                            }

                            RCComboBox
                            {
                                id:userSex
                                height: parent.height
                                width: 258
                                g_borderColor:g_widgetNormalColor
                                g_textColor:"#3E3F41"
                                g_selectItemColor:"#EAF5FF"
                                g_selectItemTextColor:"#141415"
                                g_selectTextColor:"white"
                                g_textSize:11
                                g_readOnly:true
                                g_selectByMouse:false
                                g_model: ["男","女"]

                                onCurrentIndexChanged:
                                {
                                    isEdit = true;
                                }
                            }
                            Rectangle
                            {
                                height: parent.height
                                width: 8
                            }

                            Text {
                                visible: false
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("必填")
                                font.pointSize: 12
                                font.family: "微软雅黑"
                                color: "red"
                            }
                        }
                    }
                    Rectangle
                    {
                        width: 373
                        height: 46
                        color: "white"

                        Row
                        {
                            height: parent.height
                            anchors.verticalCenter : parent.verticalCenter
                            Text {
                                text: qsTr("*")
                                color: "red"
                                font.pointSize: 12
                                font.family: "微软雅黑"
                                anchors.verticalCenter : parent.verticalCenter
                            }
                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("职位：")
                                font.pointSize: 12
                                color: "#303133"
                                font.family: "微软雅黑"
                            }

                            RCTextField
                            {
                                id:userJob
                                height: parent.height
                                width: 258
                                g_borderColor:g_widgetNormalColor
                                g_textColor:"#3E3F41"
                                g_textSize:11

                                onTextChanged:
                                {
                                    changeBorderColor()
                                }
                            }
                            Rectangle
                            {
                                height: parent.height
                                width: 8
                            }

                            Text {
                                id:userJobWarning
                                visible: false
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("必填")
                                font.pointSize: 12
                                font.family: "微软雅黑"
                                color: "red"
                            }
                        }
                    }

                    Rectangle
                    {
                        width: 373
                        height: 46
                        color: "white"

                        Row
                        {
                            height: parent.height
                            anchors.verticalCenter : parent.verticalCenter
                            Rectangle
                            {
                                height: parent.height
                                width: asteriskRect.width
                                Text {
                                    text: qsTr("*")
                                    color: "red"
                                    font.pointSize: 12
                                    font.family: "微软雅黑"
                                    anchors.verticalCenter : parent.verticalCenter
                                    visible: false
                                }
                            }

                            Text {
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("权限：")
                                color: "#303133"
                                font.pointSize: 12
                                font.family: "微软雅黑"
                            }

                            RCComboBox
                            {
                                id:userType
                                height: parent.height
                                width: 258
                                g_borderColor:g_widgetNormalColor
                                g_textColor:"#3E3F41"
                                g_selectItemColor:"#EAF5FF"
                                g_selectItemTextColor:"#141415"
                                g_selectTextColor:"white"
                                g_textSize:11
                                g_readOnly:true
                                g_selectByMouse:false
                                model:["普通用户","管理员","超级管理员"]

                                onCurrentIndexChanged:
                                {
                                    isEdit = true;
                                }
                            }
                            Rectangle
                            {
                                height: parent.height
                                width: 8
                            }

                            Text {
                                visible: false
                                anchors.verticalCenter: parent.verticalCenter
                                text: qsTr("必填")
                                font.pointSize: 12
                                font.family: "微软雅黑"
                                color: "red"
                            }
                        }
                    }
                }
            }

            Rectangle
            {
                id:bottomRect
                width: parent.width
                height: 112
                radius: 10

                Row
                {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 130
                    RCButton
                    {
                        width:100
                        height:42
                        normalBackgroundColor:"#006EFF"
                        hoveredBackgroundColor:"#1A8CFF"
                        pressedBackgroundColor:"#0054E6"
                        g_btnText:"确认"
                        g_fontSize:12

                        onClicked:
                        {
                            if(!judgeWidgetIdEmpty())
                            {
                                signalReturnResult(NewUserDialog.ReturnType.RESULT_CONFIRM)

                            }
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
                        g_btnText:"取消"
                        g_fontSize:12

                        onClicked:
                        {
                            signalReturnResult(NewUserDialog.ReturnType.RESULT_CANCEL)
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted:
    {
        isEdit = false;
    }

    Loader
    {
        id:loader
    }

    Component
    {
        id:comMessageBox
        MessageBox
        {
            id:messageBox
            visible: true
        }
    }

    Connections
    {
        target: loader.item

        onSignalReturnResult:
        {
            loader.sourceComponent = undefined
            if(enumReturn === MessageBox.ReturnType.RESULT_YES)
            {
                if(!judgeWidgetIdEmpty())
                {
                    signalReturnResult(NewUserDialog.ReturnType.RESULT_CONFIRM)
                }
            }
            else
            {
                signalReturnResult(NewUserDialog.ReturnType.RESULT_CLOSE)
            }
        }
    }

    function judgeWidgetIdEmpty()
    {
        var bIsEmpty = false

        if(userName.text == "")
        {
            userName.g_borderColor = g_widgetRedColor
            userNameWarning.visible = true
            bIsEmpty = true
        }

        if(userID.text == "")
        {
            userID.g_borderColor = g_widgetRedColor
            userIDWarning.visible = true
            bIsEmpty = true
        }

        if(userPassword.text == "")
        {
            userPassword.g_borderColor = g_widgetRedColor
            userPasswordWarning.visible = true
            bIsEmpty = true
        }

        if(userJob.text == "")
        {
            userJob.g_borderColor = g_widgetRedColor
            userJobWarning.visible = true
            bIsEmpty = true
        }

        return bIsEmpty
    }

    function changeBorderColor()
    {
        isEdit = true
        if(userName.text != "")
        {
            userName.g_borderColor = g_widgetNormalColor
            userNameWarning.visible = false
        }

        if(userID.text != "")
        {
            userID.g_borderColor = g_widgetNormalColor
            userIDWarning.visible = false
        }

        if(userPassword.text != "")
        {
            userPassword.g_borderColor = g_widgetNormalColor
            userPasswordWarning.visible = false
        }

        if(userJob.text != "")
        {
            userJob.g_borderColor = g_widgetNormalColor
            userJobWarning.visible = false
        }
    }

    function getUserInfo()
    {
        userInfo.strUserID = userID.text
        userInfo.strUserName = userName.text
        userInfo.strUserPassword = userPassword.text
        userInfo.strUserJobType = userJob.text
        userInfo.strUserExual = userSex.g_text
        userInfo.enumUserType = userType.currentIndex

        return userInfo
    }


    function setUserInfo(value)
    {
        userName.text = value.strUserName
        userID.text = value.strUserID
        userPassword.text = value.strUserPassword
        userJob.text = value.strUserJobType
        userSex.currentIndex = userSex.find(value.strUserExual)
        userType.currentIndex = value.enumUserType

        userID.enabled = false
        if(value.strUserID === BusinessData.curUserInfo.strUserID)
        {
            userPassword.enabled = true
        }
        else
        {
            userPassword.enabled = false
        }

        // 普通用户 或 管理员 或者ID是admin   不能选择类型
       if(UserInfo.USERTYPE_GENERAL === BusinessData.curUserInfo.enumUserType ||
          UserInfo.USERTYPE_MANAGE === BusinessData.curUserInfo.enumUserType ||
          value.strUserID === "admin")
       {
           userType.enabled = false
       }

        isEdit = false
    }


    function initNewUserWidgte()
    {
        txtTiteName.text = "新建用户信息"

        if(UserInfo.USERTYPE_GENERAL === BusinessData.curUserInfo.enumUserType)
        {
            userType.enabled = false
        }
        else if(UserInfo.USERTYPE_MANAGE  === BusinessData.curUserInfo.enumUserType)
        {
            userType.enabled = false
        }
        else if(UserInfo.USERTYPE_SUPERMANAGE=== BusinessData.curUserInfo.enumUserType)
        {
            if("admin" === BusinessData.curUserInfo.strUserID)
            {
                userType.model = ["普通用户","管理员","超级管理员"]
            }
            else
            {
                userType.model = ["普通用户","管理员"]
            }
        }
    }

}
