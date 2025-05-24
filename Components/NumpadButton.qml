import QtQuick

Item{
    id: fScope
    width: container.width
    height: container.height
    property alias text: txt.text
    property alias textSize: txt.font.pointSize
    property alias w: container.width
    property alias h: container.height
    property var onButtonClicked
    Rectangle{
        id: container
        focus: true
        width: 65*root.wRatio
        height: 45*root.hRatio
        radius: 10
        color: "transparent"

        property double rememberTextSize
        Component.onCompleted: {rememberTextSize = fScope.textSize}

        Rectangle {
            id: rootRectangle
            width : parent.width
            height : parent.height
            color: "black"
            anchors.centerIn: parent
            border.color: "#AAAAAAAA"
            border.width: 2
            radius: 10

            Text{
                id:txt
                anchors.centerIn: parent
                color: "white"
                font.pointSize: 20*root.wRatio
            }

            function startAnim(){
                if (rootRectangle.width < fScope.w){
                    anim.stop()
                    anim2.restart()
                    tAnim.stop()
                    tAnim2.restart()
                }
                else{
                    anim.restart()
                    tAnim.restart()
                }

                if (rootRectangle.height < fScope.h){
                    anim3.stop()
                    anim4.restart()
                }
                else
                    anim3.restart()
            }

            SequentialAnimation {
                id: tAnim
                NumberAnimation{
                    target: txt
                    properties: "font.pointSize"
                    to: container.rememberTextSize-5
                    duration: 200
                }
                NumberAnimation{
                    target: txt
                    properties: "font.pointSize"
                    to: container.rememberTextSize
                    duration: 200
                }
            }

            SequentialAnimation{
                id: tAnim2
                SmoothedAnimation {
                    target: txt
                    property: "font.pointSize"
                    to: container.rememberTextSize
                    easing.type: Easing.OutExpo
                    duration: 50
                }
                NumberAnimation{
                    target: txt
                    properties: "font.pointSize"
                    to: container.rememberTextSize-5
                    duration: 200
                }
                NumberAnimation{
                    target: txt
                    property: "font.pointSize"
                    to: container.rememberTextSize
                    duration: 100
                }
            }

            SequentialAnimation {
                id: anim
                NumberAnimation{
                    target: rootRectangle
                    properties: "width"
                    to: fScope.w-20
                    duration: 200
                }
                NumberAnimation{
                    target: rootRectangle
                    to: fScope.w
                    property: "width"
                    duration: 200
                }
            }

            SequentialAnimation{
                id: anim2
                SmoothedAnimation {
                    to: fScope.w
                    easing.type: Easing.OutExpo
                    duration: 50
                    target: rootRectangle
                    property: "width"
                }
                NumberAnimation{
                    target: rootRectangle
                    properties: "width"
                    to: fScope.w-20
                    duration: 200
                }
                NumberAnimation{
                    target: rootRectangle
                    to: fScope.w
                    property: "width"
                    duration: 100
                }
            }

            SequentialAnimation {
                id: anim3
                NumberAnimation{
                    target: rootRectangle
                    properties: "height"
                    to: fScope.h-15
                    duration: 200
                }
                NumberAnimation{
                    target: rootRectangle
                    to: fScope.h
                    property: "height"
                    duration: 200
                }
            }

            SequentialAnimation{
                id: anim4
                SmoothedAnimation {
                    to: fScope.h
                    easing.type: Easing.OutExpo
                    duration: 50
                    target: rootRectangle
                    property: "height"
                }
                NumberAnimation{
                    target: rootRectangle
                    properties: "height"
                    to: fScope.h-15
                    duration: 200
                }
                NumberAnimation{
                    target: rootRectangle
                    to: fScope.h
                    property: "height"
                    duration: 100
                }
            }

            MouseArea{
                z: 0
                propagateComposedEvents: false
                anchors.fill: parent
                onClicked: {fScope.onButtonClicked(); rootRectangle.startAnim()}
            }
        }
    }
}
