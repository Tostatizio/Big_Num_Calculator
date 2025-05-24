import QtQuick

Rectangle{
    id: container
    color: "transparent"
    radius: 10
    width: 100*root.wRatio
    height: 130*root.hRatio
    border.width: 2
    border.color: "black"

    property alias source: img.source
    property alias text: txt.text
    property alias textSize: txt.font.pointSize
    property var onClicked
    property double originalTextSize: {originalTextSize = textSize}

    Column{
        anchors.centerIn: parent
        Image{
            id: img
            anchors.horizontalCenter: parent.horizontalCenter
            width: 80*root.wRatio
            height: 80*root.hRatio
        }
        Text{
            id: txt
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 15
        }
    }

    ParallelAnimation{
        id: diminish
        NumberAnimation{
            target: container
            properties: "scale"
            to: 1
            duration: 200
        }
        NumberAnimation{
            target: img
            properties: "scale"
            to: 1
            duration: 200
        }
        NumberAnimation{
            target: txt
            properties: "scale"
            to: 1
            duration: 200
        }
    }

    ParallelAnimation{
        id: enlarge
        NumberAnimation{
            target: container
            properties: "scale"
            to: 1.4
            duration: 100
        }
        NumberAnimation{
            target: img
            properties: "scale"
            to: 1.1
            duration: 100
        }
        NumberAnimation{
            target: txt
            properties: "scale"
            to: 1.1
            duration: 100
        }
    }

    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onContainsMouseChanged:{
            if (containsMouse){
                enlarge.restart();
                diminish.stop()
            }
            else{
                diminish.restart();
                enlarge.stop()
            }
        }
        onClicked: container.onClicked()
    }
}
