import QtQuick 2.0
import QtQuick.Controls 2.15

Popup {
    id:test
    modal: true
    width: 100
    height: 100
    closePolicy: Popup.CloseOnEscape
    background: rect
    visible: false
    dim:false

    Rectangle{
        id: rect
        anchors.fill: parent
        color: "white"
        opacity: 1
        radius: 8

    }

    MouseArea {
        id: dragRegion
        anchors.fill: parent  //整个区域都接受鼠标事件
        property point clickPos: "0,0"
        visible: true
        onPressed: {
            clickPos = Qt.point(mouse.x,mouse.y)

        }
        onPositionChanged: {
            //鼠标偏移量
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            test.x = test.x+delta.x
            test.y = test.y+delta.y
            if(test.y < 0)
            {
                test.y = 0;
            }
        }
    }
}
