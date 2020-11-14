import QtQuick 2.12
import QtGraphicalEffects 1.0


Rectangle {
    property var g_imagePath;
    property var g_radius;

    anchors.fill: parent
    radius: g_radius
    Image
    {
        id: _image
        smooth: true
        anchors.fill: parent
        visible: false
        fillMode: Image.Stretch
        source: g_imagePath
        sourceSize: Qt.size(parent.size, parent.size)
        antialiasing: true
    }
    Rectangle
    {
        id: _mask
        color: "black"
        anchors.fill: parent
        radius: g_radius
        visible: false
        antialiasing: true
        smooth: true
    }
    OpacityMask
    {
        id: mask_image
        anchors.fill: _image
        source: _image
        maskSource: _mask
        visible: true
        antialiasing: true
    }
}
