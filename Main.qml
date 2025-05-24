import QtQuick.Controls.Basic
import QtQuick
import QtQuick.Controls
import QtQuick.Effects
import BigNumCalculator.Modules
import "Components"
import "Assets"

Window{
    title: "Qt Big Num Calculator"
    color: "#222222"
    id: root
    width: 450
    height: 675
    visible: true

    property double hRatio: 1
    property double wRatio: 1
    property double wNumpad: 65
    property double hNumpad: 45
    property double fontSize: 20*root.width/450
    property bool isResizing: false
    property string mainString

    signal keyPressed(string text)

    Backend{
        id: backend
    }

    FileOpener{
        id: fileOpener
    }
    onWidthChanged: {
        if (!isResizing) {
            isResizing = true
            root.hRatio = root.width/450
            root.wNumpad = 65*root.hRatio
            root.height = 675*root.hRatio
            isResizing = false
        }
    }
    onHeightChanged: {
        if (!isResizing) {
            isResizing = true
            root.wRatio = root.height/675
            root.hNumpad = 45*root.wRatio
            root.width = 450*root.wRatio
            isResizing = false
        }
    }

    StackView{
        id: mainView
        anchors.fill: parent
        initialItem: mainMenu
    }

    Column{
        y: 10*root.hRatio
        z: 4
        anchors.right: mainView.right
        anchors.rightMargin: 10*root.wRatio
        spacing: 20*root.hRatio
        SideMenuItem{
            id: menuOpener
            onClicked: function(){
                if (sideMenu.width === 0){
                    sideMenu.width = root.width/4*3;
                    sideMenu.visible = true;
                    sideMenuIcons.visible = true;
                    sideMenuIcons.opacity = 1;
                }
                else{
                    sideMenu.width = 0;
                    sideMenu.visible = false;
                    sideMenuIcons.visible = false;
                    sideMenuIcons.opacity = 0;
                }
            }
            source: "../Assets/menu_icon"
        }
        Column{
            id: sideMenuIcons
            visible: false
            spacing: 22*root.hRatio

            Behavior on opacity{
                NumberAnimation{duration : 300}
            }

            SideMenuItem{
                source: "../Assets/menu_icon"
            }
            SideMenuItem{
                source: "../Assets/menu_icon"
            }
            SideMenuItem{
                source: "../Assets/menu_icon"
            }
            SideMenuItem{
                source: "../Assets/menu_icon"
            }
            SideMenuItem{
                source: "../Assets/menu_icon"
            }
        }
    }

    Rectangle{
        id: sideMenu
        z: 2
        anchors.right: mainView.right
        height: root.height
        width: 0
        color: "#111111"
        visible: false

        Behavior on width{
            NumberAnimation{duration : 300}
        }

        Behavior on visible{
            enabled: sideMenu.visible
            PropertyAnimation{duration : 300}
        }

        MultiEffect{
            source: mainView
            anchors.fill: sideMenu
            blurEnabled: true
            blurMax: 64
            blur: 1
            contrast: -1
            colorization: 0.6
            colorizationColor: "#222222"
            autoPaddingEnabled: false
        }

        Column{
            y: 70*root.hRatio
            x: 10*root.wRatio
            spacing: 10*root.hRatio
            Text{
                height: 40*root.hRatio
                text: "Settings"
                font.pointSize: root.fontSize
                color: "white"
            }
            Rectangle{
                height: 2*root.hRatio
                width: sideMenu.width
                color: "white"
            }

            Text{
                height: 40*root.hRatio
                text: "Settings"
                font.pointSize: root.fontSize
                color: "white"
            }
            Rectangle{
                height: 2*root.hRatio
                width: sideMenu.width
                color: "white"
            }
            Text{
                height: 40*root.hRatio
                text: "Settings"
                font.pointSize: root.fontSize
                color: "white"
            }
            Rectangle{
                height: 2*root.hRatio
                width: sideMenu.width
                color: "white"
            }
            Text{
                height: 40*root.hRatio
                text: "Settings"
                font.pointSize: root.fontSize
                color: "white"
            }
            Rectangle{
                height: 2*root.hRatio
                width: sideMenu.width
                color: "white"
            }
            Text{
                height: 40*root.hRatio
                text: "Settings"
                font.pointSize: root.fontSize
                color: "white"
            }
            Rectangle{
                height: 2*root.hRatio
                width: sideMenu.width
                color: "white"
            }
            Text{
                height: 40*root.hRatio
                text: "Settings"
                font.pointSize: root.fontSize
                color: "white"
            }
            Rectangle{
                height: 2*root.hRatio
                width: sideMenu.width
                color: "white"
            }
            Text{
                height: 40*root.hRatio
                text: "Settings"
                font.pointSize: root.fontSize
                color: "white"
            }
            Rectangle{
                height: 2*root.hRatio
                width: sideMenu.width
                color: "white"
            }
            Text{
                height: 40*root.hRatio
                text: "Settings"
                font.pointSize: root.fontSize
                color: "white"
            }
            Rectangle{
                height: 2*root.hRatio
                width: sideMenu.width
                color: "white"
            }
        }
    }

    onKeyPressed: (txt) => {
        let tArea = mainView.currentItem.textArea
        let cpos = tArea.cursorPosition
        switch (txt){
            case "(":
                backend.insertMainString(cpos, "()");
                break;
            case ")":
                backend.insertMainString(cpos, ")");
                break;
            case "!":
                backend.insertMainString(cpos, "!");
                break;
            case "mod":
                backend.insertMainString(tArea.length, " mod ");
                cpos = tArea.length-1
                break;
            case "⌫":
                backend.removeMainString(cpos-1, 1);
                cpos-=2;
                break;
            case "1":
                backend.insertMainString(cpos, "1");
                break;
            case "2":
                backend.insertMainString(cpos, "2");
                break;
            case "3":
                backend.insertMainString(cpos, "3");
                break;
            case "+":
                backend.insertMainString(cpos, "+");
                break;
            case "^":
                backend.insertMainString(cpos, "^");
                break;
            case "4":
                backend.insertMainString(cpos, "4");
                break;
            case "5":
                backend.insertMainString(cpos, "5");
                break;
            case "6":
                backend.insertMainString(cpos, "6");
                break;
            case "-":
                backend.insertMainString(cpos, "-");
                break;
            case "√":
                backend.insertMainString(cpos, "√");
                break;
            case "7":
                backend.insertMainString(cpos, "7");
                break;
            case "8":
                backend.insertMainString(cpos, "8");
                break;
            case "9":
                backend.insertMainString(cpos, "9");
                break;
            case "×":
                backend.insertMainString(cpos, "*");
                break;
            case "ln":
                backend.insertMainString(cpos, "ln()");
                cpos += 2;
                break;
            case ".":
                backend.insertMainString(cpos, ".");
                break;
            case "0":
                backend.insertMainString(cpos, "0");
                break;
            case "=":
                backend.mainString = backend.expr_eval(backend.mainString);
                cpos = backend.mainString.length - 1;
                // console.log(backend.expr_eval(backend.mainString));
                break;
            case "÷":
                backend.insertMainString(cpos, "/");
                break;
            case "log":
                backend.insertMainString(cpos, "log()");
                cpos += 3
                break;
        }
        tArea.cursorPosition = cpos+1;
    }

    Component{
        id: mainMenu
        Rectangle{
            width: root.width
            height: root.height
            property alias textArea: textArea
            color: "transparent"
            Rectangle{
                id: textAreaCont
                color: "#111111"
                bottomLeftRadius: 30
                bottomRightRadius: 30
                width: root.width
                height: root.height-numpad.height-40*root.hRatio
                anchors.bottom: numpad.top
                anchors.bottomMargin: 20*root.hRatio

                ScrollView {
                    anchors.fill: parent
                    TextArea{
                        id: textArea
                        text: backend.mainString
                        onTextChanged: {
                            if(backend.mainString !== textArea.text)
                                backend.mainString = textArea.text;
                        }
                        background: Rectangle{color: "transparent"}
                        color: "white"
                        selectionColor: "white"
                        selectedTextColor: "black"
                        font.pointSize: root.fontSize
                        placeholderText: "Type something...\nDrag and drop files?"
                        placeholderTextColor: "#AAAAAAAA"
                        wrapMode: Text.WrapAnywhere
                        Keys.onPressed: (event) => {if (event.key === Qt.Key_Escape) focus = false}
                    }
                }
            }
            Grid{
                id: numpad
                focus: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20*root.hRatio
                rowSpacing: 10*root.hRatio
                columnSpacing: 20*root.wRatio
                columns: 5

                NumpadButton{
                    text: "("
                    onButtonClicked: function(){keyPressed("(")}
                }
                NumpadButton{
                    text: ")"
                    onButtonClicked: function(){keyPressed(")")}
                }
                NumpadButton{
                    text: "!"
                    onButtonClicked: function(){keyPressed("!")}
                }
                NumpadButton{
                    text: "mod"
                    textSize: 17*root.wRatio
                    onButtonClicked: function(){keyPressed("mod")}
                }
                NumpadButton{
                    text: "⌫"
                    onButtonClicked: function(){keyPressed("⌫")}
                }
                NumpadButton{
                    text: "1"
                    onButtonClicked: function(){keyPressed("1")}
                }
                NumpadButton{
                    text: "2"
                    onButtonClicked: function(){keyPressed("2")}
                }
                NumpadButton{
                    text: "3"
                    onButtonClicked: function(){keyPressed("3")}
                }
                NumpadButton{
                    text: "+"
                    onButtonClicked: function(){keyPressed("+")}
                }
                NumpadButton{
                    text: "^"
                    onButtonClicked: function(){keyPressed("^")}
                }
                NumpadButton{
                    text: "4"
                    onButtonClicked: function(){keyPressed("4")}
                }
                NumpadButton{
                    text: "5"
                    onButtonClicked: function(){keyPressed("5")}
                }
                NumpadButton{
                    text: "6"
                    onButtonClicked: function(){keyPressed("6")}
                }
                NumpadButton{
                    text: "-"
                    onButtonClicked: function(){keyPressed("-")}
                }
                NumpadButton{
                    text: "√x"
                    onButtonClicked: function(){keyPressed("√")}
                }
                NumpadButton{
                    text: "7"
                    onButtonClicked: function(){keyPressed("7")}
                }
                NumpadButton{
                    text: "8"
                    onButtonClicked: function(){keyPressed("8")}
                }
                NumpadButton{
                    text: "9"
                    onButtonClicked: function(){keyPressed("9")}
                }
                NumpadButton{
                    text: "×"
                    onButtonClicked: function(){keyPressed("×")}
                }
                NumpadButton{
                    text: "ln"
                    onButtonClicked: function(){keyPressed("ln")}
                }
                NumpadButton{
                    text: "."
                    onButtonClicked: function(){keyPressed(".")}
                }
                NumpadButton{
                    text: "0"
                    onButtonClicked: function(){keyPressed("0")}
                }
                NumpadButton{
                    text: "="
                    onButtonClicked: function(){keyPressed("=")}
                }
                NumpadButton{
                    text: "÷"
                    onButtonClicked: function(){keyPressed("÷")}
                }
                NumpadButton{
                    text: "log"
                    onButtonClicked: function(){keyPressed("log")}
                }
            }
            Text{
                anchors.bottom: parent.bottom
                color: "white"
                font.pointSize: root.fontSize/2
                text: "Lines: " + textArea.lineCount + " Characters: " + textArea.length
            }
        }
    }
}
