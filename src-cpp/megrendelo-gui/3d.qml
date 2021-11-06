import QtQuick 2.0

Item {
    property string col: "#212121" //jó fekete szín
Rectangle{
    color:col
    height: parent.height
    width: parent.width

    anchors.centerIn: parent.Center
    Text {
        id: txt
        color: "white"
        height: parent.height
        width: parent.width
        text: qsTr("Grafika - fejlesztés alatt")
    }
}
}
