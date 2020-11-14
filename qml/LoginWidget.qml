import QtQuick 2.12
import QtQuick.Window 2.12
import BaseWidget 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.12

import BusinessData 1.0
import QRobotControl 1.0
import BaseData 1.0

Window
{
    id:loginWidget
    width: 676
    height: 480
    visible: false
    title: qsTr("机器人管理平台")
    color: "transparent"

    flags: Qt.FramelessWindowHint | Qt.Window | Qt.WindowSystemMenuHint
            | Qt.WindowMaximizeButtonHint | Qt.WindowMinMaxButtonsHint


    RCWaitingDialog
    {
        id:waitingDialog
        visible: false
    }

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
            loginWidget.setX(loginWidget.x+delta.x)
            loginWidget.setY(loginWidget.y+delta.y)
        }
    }

    RadiusImage
    {
        g_imagePath: "qrc:/Item/LoginWidget.jpg";
        g_radius:10;
    }

    Rectangle
    {
        anchors.fill: parent
        color: "#4B1196CD"
        radius: 10
    }

    Row
    {
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top : parent.top
        anchors.topMargin: 10
        spacing: 15
        RCIconButton
        {
            id:btnMini
            width: 20;
            height: 20;
            enumCurrentIconType:RCIconButton.IconType.TYPE_MINI
            bIsRadius: true;

            onButtonClicked:
            {
                loginWidget.showMinimized()
            }
        }
        RCIconButton
        {
            id:btnClose
            width: 20;
            height: 20;
            enumCurrentIconType:RCIconButton.IconType.TYPE_CLOSE;
            bIsRadius: true;

            onButtonClicked:
            {
                loginWidget.close()
            }
        }
    }

    Rectangle
    {
        width: parent.width
        height: parent.height*0.2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: parent.height*0.1
        color: "transparent"
        Text
        {
            text: qsTr("机器人管理平台")
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 28
            color: "white"
            font.family: "微软雅黑"
            font.letterSpacing: 13
        }
    }

    Column
    {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height*0.045
        width:parent.width

        Rectangle
        {
            anchors.horizontalCenter: parent.horizontalCenter
            width: userloginIDRow.width
            height:userloginIDRow.height
            color: "transparent"

            Row
            {
                id:userloginIDRow
                anchors.horizontalCenter: parent.horizontalCenter

                Rectangle
                {
                    width: recRegister.width
                    height: recRegister.height
                    color: "transparent"
                    Text
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("账号")
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                        font.pointSize: 12
                        font.family: "微软雅黑"
                        color:"white"
                    }
                }

                RCComboBox
                {
                    id:loginIDInput
                    g_textColor:"#303133"
                    g_backgroundColor:"#96146AA3"
                    g_borderColor:"#96C0C4CC"
                    g_normalItemColor:"#1768AC"//"#0C90C9"
                    g_selectItemColor:"#0C90C9"
                    focus: true
                    g_regExp:/[1-9][0-9]{14}/
                    g_model: BusinessData.listUserLoginID

                    onCurrentIndexChanged:
                    {
                        currentUserAccountChanged(currentIndex)
                    }

                    onSignalTextChange:
                    {
                        loginPassword.clear();
                        chkRememberPassword.checked = false;
                        chkAutoLogin.checked = false;
                    }
                }

                Rectangle
                {
                    id:recRegister
                    width: btnRegister.width+25
                    height: btnRegister.height
                    color: "transparent"
                    RCButton
                    {
                        id:btnRegister
                        anchors.left: parent.left
                        anchors.leftMargin: 25
                        height: loginIDInput.height
                        width:80
                        g_btnText:"注册账号"
                        g_fontSize:9
                    }
                }
            }
        }

        Rectangle
        {
            anchors.horizontalCenter: parent.horizontalCenter
            width: userloginIDRow.width
            height:35
            color: "transparent"
            Text
            {
                id:erroeInfor
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: recRegister.width+5
                font.pointSize: 9
                font.family: "微软雅黑"
                color:"red"
            }
        }

        Rectangle
        {
            anchors.horizontalCenter: parent.horizontalCenter
            width: userloginIDRow.width
            height:userloginIDRow.height
            color: "transparent"

            Row
            {
                anchors.horizontalCenter: parent.horizontalCenter

                Rectangle
                {
                    width: recRegister.width
                    height: recRegister.height
                    color: "transparent"
                    Text
                    {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("密码")
                        font.pointSize: 12
                        font.family: "微软雅黑"
                        color:"white"
                        anchors.right: parent.right
                        anchors.rightMargin: 20
                    }
                }
                RCTextField
                {
                    id:loginPassword
                    g_textColor:"#303133"
                    g_backgroundColor:"#96146AA3"
                    g_borderColor:"#96C0C4CC"
                    echoMode:TextInput.Password
                }

                Rectangle
                {
                    width: recRegister.width
                    height: recRegister.height
                    color: "transparent"
                    RCButton
                    {
                        anchors.left: parent.left
                        anchors.leftMargin: 25
                        height: btnRegister.height
                        width: btnRegister.width
                        g_btnText:"忘记密码"
                        g_fontSize:9
                    }
                }
            }
        }

        Rectangle
        {
            anchors.horizontalCenter: parent.horizontalCenter
            width: userloginIDRow.width
            height:userloginIDRow.height+20
            color: "transparent"

            Rectangle
            {
                width: loginIDInput.width
                height:parent.height
                anchors.left: parent.left
                anchors.leftMargin: recRegister.width
                anchors.top: parent.top
                anchors.topMargin: 10
                color: "transparent"

                RCCheckBox
                {
                    id:chkRememberPassword
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    g_checkBoxName: "记住密码"

                    onClicked:
                    {
                        if(!checked)
                        {
                            chkAutoLogin.checked = false
                            timer.running = false
                        }
                    }
                }

                RCCheckBox
                {
                    id:chkAutoLogin
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    g_checkBoxName: "自动登录"

                    onClicked:
                    {
                        if(checked)
                        {
                            chkRememberPassword.checked = true;
                            timer.running = true
                        }
                        else
                        {
                            timer.running = false
                        }
                    }
                }
            }
        }

        RCButton
        {
            anchors.horizontalCenter: parent.horizontalCenter
            width: loginIDInput.width
            height:45
            normalBackgroundColor:"#2F8DED"
            hoveredBackgroundColor:"#2F8DED"
            pressedBackgroundColor:"#2F8DED"
            g_btnText:"登录"

            onClicked:
            {
                loginClicked()
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
            waitingDialog.visible = false
            loginClicked()
        }
    }

    /*---------------------------------------------------------------------------
    函数名：loginClicked
    功能：登录点击函数
    参数：
    返回值：bool
    作者：guokai
    创建时间：2020-06-30
    备注：

    ---------------------------------------------------------------------------*/
    function loginClicked()
    {
        // 判断必填项
        if(infoIsComplete())
        {
            userLogin()
        }
    }

    /*---------------------------------------------------------------------------
    函数名：infoIsComplete
    功能：信息是否填写完全
    参数：
    返回值：bool
    作者：guokai
    创建时间：2020-06-30
    备注：

    ---------------------------------------------------------------------------*/
    function infoIsComplete()
    {
        var bIsComplete = false;

        if(loginIDInput.g_text == "")
        {
            erroeInfor.visible = true
            erroeInfor.text = qsTr("用户名不能为空！");
            bIsComplete = false;
        }
        else if(loginPassword.text == "")
        {
            erroeInfor.visible = true
            erroeInfor.text = qsTr("密码不能为空！");
            bIsComplete = false;
        }
        else
        {
            erroeInfor.visible = false
            bIsComplete = true;
        }

        return bIsComplete;
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
            loginWidget.requestActivate()
            loginWidget.show();
        }
        else
        {
            loginWidget.hide();
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
        var userLoginInfo = BusinessData.listModelUserLoginInfo.getIndexValue(0)
        loginPassword.text = ""
        if(userLoginInfo.bIsRememberPassword)
        {
            loginPassword.text = userLoginInfo.strPassword
        }

        if(userLoginInfo.bIsAutoLogin)
        {
            timer.running = true
            //waitingDialog.visible = true
        }

        chkRememberPassword.checked = userLoginInfo.bIsRememberPassword
        chkAutoLogin.checked = userLoginInfo.bIsAutoLogin
        erroeInfor.visible = false
    }


    /*---------------------------------------------------------------------------
    函数名：currentUserAccountChanged
    功能：当前用户索引改变
    参数：
    返回值：
    作者：guokai
    创建时间：2020-06-30
    备注：

    ---------------------------------------------------------------------------*/
    function currentUserAccountChanged(index)
    {
        timer.running = false
        var userLoginInfo = BusinessData.listModelUserLoginInfo.getIndexValue(index)

        loginPassword.text = ""
        if(userLoginInfo.bIsRememberPassword)
        {
            loginPassword.text = userLoginInfo.strPassword
        }

        if(userLoginInfo.bIsAutoLogin)
        {
            timer.running = true
        }

        chkRememberPassword.checked = userLoginInfo.bIsRememberPassword
        chkAutoLogin.checked = userLoginInfo.bIsAutoLogin
        erroeInfor.visible = false
    }


    /*---------------------------------------------------------------------------
    函数名：UserLogin
    功能：用户登录
    参数：
    返回值：
    作者：guokai
    创建时间：2020-06-30
    备注：

    ---------------------------------------------------------------------------*/
    function userLogin()
    {
        var bSuccess = userLoginWidget.qmlBtnLoginClicked(loginIDInput.g_text, loginPassword.text,
                                                          chkRememberPassword.checked, chkAutoLogin.checked);

        if(bSuccess)
        {
            erroeInfor.visible = false
        }
        else
        {
            erroeInfor.visible = true
            erroeInfor.text = qsTr("用户名或密码错误！");
        }
    }
}
