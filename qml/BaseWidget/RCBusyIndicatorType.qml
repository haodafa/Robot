import QtQuick 2.7
import QtGraphicalEffects 1.0

Item {

    Rectangle {
        id: rect
        width: parent.width
        height: parent.height
        color: Qt.rgba(0, 0, 0, 0)
        radius: width / 2
        border.width: width / 20
        visible: false
    }

    ConicalGradient {
        width: rect.width
        height: rect.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#DFEFFF" }
            GradientStop { position: 1.0; color: "#007DFD" }
        }

        source: rect

        Rectangle {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: rect.border.width
            height: width
            radius: width / 2
            color: "#409EFF"
        }

        RotationAnimation on rotation {
            from: 0
            to: 360
            duration: 1200
            loops: Animation.Infinite
        }
    }
}
