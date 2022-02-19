import QtQml.Models 2.2
import QtQml 2.2

import QtQuick 2.0

Rectangle {
    id: root
    property real alt: 0
    property real maxAlt: 20
    property real minAlt: -200
    property real graticuleSpacing: 45-graticuleHeight
    property real graticuleAlt: 0.5 //metres
    property real graticuleHeight: 2

    anchors.verticalCenter: parent.verticalCenter

    height: parent.height*0.8
    z: 1
    clip: true
    smooth: true
    border.color: "black"
    color: Qt.rgba(0,0,0,0.2)

    function makeGraticule(){
        var length = (maxAlt - minAlt) / graticuleAlt + 1;
        var array = new Array(length);
        for (var i = 0; i < length; i++){
            array[i] = maxAlt - i * graticuleAlt;
        }
        return array;
    }

    Column{
        id: altColumn
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: graticuleSpacing

        Repeater {
            model: makeGraticule()

            Rectangle { // Graticule Light
                id:graticuleLight
                width: root.width
                height: 2
                color: "white"
                smooth: true
                opacity: 0.8
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    smooth: true
                    font.bold: true
                    text: modelData
                    color: "white"
                    style: Text.Outline
                    styleColor: "black"
                }
            }
        }
        transform: Translate {
            y: (alt-(maxAlt+minAlt)/2)*(graticuleSpacing+graticuleHeight)/graticuleAlt
        }
    }

    Rectangle { // Altitude Label
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: 20
        color: "black"
        border.color: "white"
        opacity: 1.0
        Text {
            anchors.centerIn: parent

            text: alt < 100 ? alt.toFixed(1) : alt.toFixed(0)
            color: "white"
            z: 2
        }
    }
}
