import QtQuick.Controls 2.12
import QtQuick 2.12
import QtGraphicalEffects 1.0


ComboBox{
    id:comboBoxId

    property var g_model
    property var g_radius:4
    property var g_regExp:/[1-9A-Za-z][0-9A-Za-z]{14}/
    property var g_readOnly:false

    property color g_backgroundColor:"white"
    property color g_selectBackgroundColor:"#0078D7"

    property color g_borderColor:"#0078D8"

    property color g_textColor:"black"
    property color g_selectTextColor:"white"

    property color g_selectItemColor:"#136EB1"
    property color g_normalItemColor:"white"

    property color g_selectItemTextColor:"white"

    property var g_textSize:11

    property var g_text: inputText.text

    property var g_width:300
    property var g_height:45

    property var g_selectByMouse:true

    signal signalTextChange()

    implicitWidth:g_width
    implicitHeight:g_height
    width:g_width
    height: g_height
    focus: true
    model:g_model

    delegate: ItemDelegate
    {
        implicitWidth: comboBoxId.implicitWidth
        implicitHeight: comboBoxId.implicitHeight
        width: comboBoxId.width
        leftPadding: 20
        contentItem: Text
        {
            text: comboBoxId.textRole
                  ? (Array.isArray(comboBoxId.model)
                     ? modelData[comboBoxId.textRole]
                     : model[comboBoxId.textRole])
                  : modelData

            font.pointSize: g_textSize
            color: (comboBoxId.highlightedIndex === index)?g_selectItemTextColor:g_textColor
            elide: Text.ElideRight
            renderType: Text.NativeRendering
            verticalAlignment: Text.AlignVCenter
            font.family: "微软雅黑"
        }
        background: Rectangle
        {
            width: parent.width
            color:(comboBoxId.highlightedIndex === index) ?g_selectItemColor : g_normalItemColor
        }
    }

    //box显示item
    contentItem: TextField
    {
        id:inputText
        readOnly:g_readOnly
        width: comboBoxId.width-comboBoxId.indicator.width-comboBoxId.rightPadding
        leftPadding: 20
        text: comboBoxId.currentText
        color: g_textColor
        font.pointSize: g_textSize
        font.family: "微软雅黑"
        selectByMouse:g_selectByMouse
        selectionColor:g_selectBackgroundColor
        selectedTextColor:g_selectTextColor
        focus: true
        validator: RegExpValidator
        {
            regExp: g_regExp
        }
        background:Rectangle
        {
            radius:g_radius
            color: "transparent"
        }
        onTextEdited:
        {
            signalTextChange()
        }
    }

    background: Rectangle
    {
       radius: g_radius
       color:enabled ? g_backgroundColor : "#E3E6EA"
       border.color:g_borderColor
       border.width:1
    }

    indicator:Rectangle
    {
        anchors.right: comboBoxId.right
        anchors.top: comboBoxId.top
        width: 40
        height: comboBoxId.height
        radius: g_radius
        color: "transparent"
        Image {
            anchors.centerIn: parent
            width: 11
            height:6
            source: "qrc:/Item/cbbDownBtn.png"
        }
    }

    popup: Popup {
        y: comboBoxId.height
        width: comboBoxId.width
        implicitHeight: contentItem.implicitHeight < 200 ? contentItem.implicitHeight : 200
        padding: 1
        background:rect

        contentItem: ListView {
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            implicitHeight: comboBoxId.model.length * 45 < 200 ? comboBoxId.model.length * 45 + 2 : 200
            model: comboBoxId.popup.visible ? comboBoxId.delegateModel : null
            currentIndex: comboBoxId.highlightedIndex
            ScrollIndicator.vertical: ScrollIndicator { }
        }

        Rectangle
        {
            id:rect
            color: "transparent"//"#96C0C4CC"
            width: parent.width
            height: parent.height
            border.width: 1
            border.color: "#96C0C4CC"
        }

//        DropShadow {
//            anchors.fill: rect
//            horizontalOffset: 0
//            verticalOffset: 0
//            radius: 8
//            samples: 17
//            color: "#AA000000"
//            source: rect
//        }
    }
}
