//Froked version from from: https://github.com/omnight/phonehook/blob/master/client/gui/qml/pages/ControlBigButton.qml

import QtQuick 2.0
import Sailfish.Silica 1.0

MouseArea {
    id: p
    width: (parent.width - Theme.paddingLarge) / 2
    height: width

    property string icon
    property string link
    property string text

    Rectangle {
        id: btn
        color: p.pressed ? Theme.rgba(Theme.highlightColor, 0.5) : Theme.rgba(Theme.highlightDimmerColor, 0.01)
        anchors.fill: parent
        smooth: true

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: Theme.paddingLarge*2
            width: parent.width*.4
            height: parent.width*.4
            source: p.icon
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Theme.paddingLarge
            color: Theme.primaryColor
            font.weight: Font.Bold
            text: p.text
        }
    }
}
