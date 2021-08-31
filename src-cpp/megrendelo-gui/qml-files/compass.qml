import QtQuick 2.0

Item {
    id: root
    property real fok: 0

    Image{
        id:comp
        source: "qrc:/horizon/resources/compass.svg"
        rotation: root.fok
        height: 300
        width: 300
        Image{
            id:nyil
            source: "qrc:/horizon/resources/compass-nyil.png"
            anchors.centerIn: comp
            height: 50
            width: 50
            rotation: -root.fok
        }
    }
}
