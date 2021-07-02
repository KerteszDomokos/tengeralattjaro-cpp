import QtQuick 2.0

Item {
    id: it
    property real t1: 0
    property real t2: 0
    property real t3: 0
    property real b1: 0
    property real b2: 0
    property real b3: 0
    property real b4: 0
    property real b5: 0
    property real b6: 0
    property real b7: 0
    property real b8: 0
    property real b9: 0
    property real b10: 0
    property real b11: 0
    property real b12: 0
    height: 150
    width: 100
    anchors.fill: parent


    Rectangle{
        id:back
        color: "green"
        smooth: true
        anchors.centerIn: parent
        height: 350
        width: 300
    }
    Rectangle{
        id:g
        function getCol(){
            var bb1=it.b1
            if(bb1===0){
                return "blue"
            }
            else{
                return "blue"
            }

        }
        color:getCol()
        smooth: true
        anchors.centerIn: parent
        height: 10
        width: 10
    }
    Text {
        text: "Gomb 1: <br>Gomb 2: <br>Gomb 3: <br>Gomb 4: <br>Gomb 5: <br>Gomb 6: <br>Gomb 7: <br>Gomb 8: <br>Gomb 9: <br>Gomb 10: <br>Gomb 11: <br>Gomb 12: <br>"
        font.family: "Helvetica"
        font.pointSize: 11
        color: "black"
    }

}
