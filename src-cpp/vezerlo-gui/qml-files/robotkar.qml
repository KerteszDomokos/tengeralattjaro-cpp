import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    id: item1
    height: 300
    width: 600
    property int alapV: alap.value
    property int pot2V: pot2.value
    property int forgV: forg.value
    property int pot3V: pot3.value

    Rectangle {
        id: rectangle1
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        anchors.centerIn: parent.Center
        color: "#95f170"

        Dial {
            id: alap
            objectName: "alap"
            x: 271
            y: 257
            width: 58
            height: 35
            value: 90
            to: 180
        }


        Rectangle {
            id: kar1
            x: 290
            y: 154
            width: 10
            height: 45
            color: "#350abe"
            transformOrigin: Item.Bottom
            rotation: alap.angle
            anchors.bottom: alap.top
            anchors.bottomMargin: 3



            Dial {
                id: pot2
                objectName: "pot2"
                y: -80
                width: 39
                height: 36
                anchors.horizontalCenterOffset: 1
                anchors.bottomMargin: 44
                value: 90
                anchors {
                    bottom: kar1.top;
                    horizontalCenter: kar1.horizontalCenter
                    topMargin: 184
                }

                Dial {
                    id: forg
                    objectName: "forg"
                    x: -1
                    y: 40
                    width: 51
                    height: 37
                    anchors.bottom: kar1.top
                    to:180
                }

                Rectangle {
                    id: kar2
                    x: 13
                    y: -133
                    width: 10
                    height: 55
                    color: "#350abe"
                    anchors.bottom: pot2.top
                    Dial {
                        id: pot3
                        objectName: "pot3"
                        width: 39
                        height: 36
                        anchors.bottom: kar2.top
                        value: 90
                        anchors.horizontalCenter: kar2.horizontalCenter
                        anchors.topMargin: 184
                        Rectangle {
                            id: kar3
                            x: 12
                            y: -59
                            width: 10
                            height: 55
                            color: "#350abe"
                            transformOrigin: Item.Bottom
                            rotation: pot3.angle
                            anchors.bottom: pot3.top
                            anchors.bottomMargin: 4
                        }
                        to: 180
                    }
                    rotation: pot2.angle
                    transformOrigin: Item.Bottom
                    anchors.bottomMargin: 3
                }

                to: 180
            }
        }

    }

}

/*##^##
Designer {
    D{i:0;height:300;width:600}
}
##^##*/
