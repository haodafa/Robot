import QtQuick.Controls 2.12
import QtQuick 2.12


Rectangle {
    width: 330
    height: 50
    radius: 4
    color: "white"

    signal signalSearchClicked(var strContext)
    signal signalTextChange()

    RCTextField
    {
        id:input
        height: parent.height
        width: 330 - 45
        g_borderColor:"transparent"
        g_textColor:"#3E3F41"
        g_textSize:12
        focus: true

        onTextChanged:
        {
            signalTextChange()
        }
    }

    RCButton
    {
        anchors.right: parent.right
        width: 45
        height: parent.height

        Image
        {
            width: 22
            height: 22
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectCrop
            source: "qrc:/Item/searchBtn.png"
        }

        onClicked:
        {
            signalSearchClicked(input.text)
        }
    }

    Keys.enabled: true;
    Keys.onReturnPressed:
    {
        signalSearchClicked(input.text)
    }

}
