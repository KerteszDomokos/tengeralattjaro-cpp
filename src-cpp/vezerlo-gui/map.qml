import QtQuick 2.0
import QtLocation 5.15
Item{
    Plugin {
           id: mapPlugin
           name: "osm" // "mapboxgl", "esri", ...
           // specify plugin parameters if necessary
           // PluginParameter {
           //     name:
           //     value:
           // }
       }
    Map {
        id: map
        width: 300
        height: 300
        plugin: mapPlugin
        zoomLevel: 10

        Rectangle {
            x: 70
            width: input.width + 20
            height: input.height + 4
            anchors.bottom: parent.bottom; anchors.bottomMargin: 5
            radius: 5
            opacity: map.status === "Ready" ? 1 : 0

            TextInput {
                id: input
                text: map.address
                anchors.centerIn: parent
                Keys.onReturnPressed: map.address = input.text
            }
        }

        Text {
            id: loading
            anchors.centerIn: parent
            text: map.status === "Error" ? "Error" : "Loading"
            opacity: map.status === "Ready" ? 0 : 1
            font.pixelSize: 30

            Behavior on opacity { NumberAnimation{} }
        }
    }
}
