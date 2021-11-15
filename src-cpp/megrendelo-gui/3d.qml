import QtQuick 2.1

Item {
    property string col: "black" //jó fekete szín
Rectangle{
    height: parent.height
    width: parent.width
    color:col

    anchors.centerIn: parent.Center
    Text {
        id: txt
        color: "#fff"
        height: parent.height
        width: parent.width
        text: qsTr("Grafika - fejlesztés alatt")
    }
}
}
