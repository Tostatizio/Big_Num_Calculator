import QtQuick

Item{
    id: menuIcon
    x: -10*root.wRatio
    y: 10*root.hRatio
    width: 40*root.wRatio
    height: 40*root.hRatio

    property alias source: image.source
    property var onClicked

    Image{
        id: image
        width: 40*root.wRatio
        height: 40*root.hRatio
        fillMode: Image.PreserveAspectCrop
    }

    Rectangle{
        id: shader
        visible: false
        color: "#AAAAAA"
        opacity: 0.5
        width: parent.width
        height: parent.height
    }
    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onEntered: { shader.visible = true }
        onExited: { shader.visible = false }
        onPressed: { shader.opacity = 1 }
        onReleased: {
            shader.opacity = 0.5;
            menuIcon.onClicked();
        }
    }
}
