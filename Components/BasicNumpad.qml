import QtQuick

Grid{
    id: numpad
    columnSpacing: 20*root.wRatio
    rowSpacing: 10*root.hRatio
    columns: 3

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
}
