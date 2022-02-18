import QtQml.Models 2.2
import QtQml 2.2
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
        height: 250
        width: 90
    }
        Rectangle{
            id:g1
            x: 80
            y: 5
            function getCol(){
                var bb1=it.b1
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            height: 10
            width: 10
        }
        Rectangle{
            id:g2
            x: 80
            function getCol(){
                var bb1=it.b2
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g1.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g3
            x: 80
            function getCol(){
                var bb1=it.b3
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g2.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g4
            x: 80
            function getCol(){
                var bb1=it.b4
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g3.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g5
            x: 80
            function getCol(){
                var bb1=it.b5
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g4.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g6
            x: 80
            function getCol(){
                var bb1=it.b6
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g5.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g7
            x: 80
            function getCol(){
                var bb1=it.b7
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g6.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g8
            x: 80
            function getCol(){
                var bb1=it.b8
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g7.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g9
            x: 80
            function getCol(){
                var bb1=it.b9
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g8.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g10
            x: 80
            function getCol(){
                var bb1=it.b10
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g9.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g11
            x: 80
            function getCol(){
                var bb1=it.b11
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g10.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }
        Rectangle{
            id:g12
            x: 80
            function getCol(){
                var bb1=it.b12
                if(bb1===0){
                    return "green"
                }
                else{
                    return "blue"
                }

            }
            color:getCol()
            smooth: true
            anchors.top: g11.top
            anchors.topMargin: 19
            height: 10
            width: 10
        }

    Text {
        text: "Gomb 1: <br>Gomb 2: <br>Gomb 3: <br>Gomb 4: <br>Gomb 5: <br>Gomb 6: <br>Gomb 7: <br>Gomb 8: <br>Gomb 9: <br>Gomb 10: <br>Gomb 11: <br>Gomb 12: <br>"
        font.family: "Helvetica"
        font.pointSize: 12
        color: "black"
    }
    states: [
        State {
            name: "State1"
        }
    ]

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.66}
}
##^##*/
