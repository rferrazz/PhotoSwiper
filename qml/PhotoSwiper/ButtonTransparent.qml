// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
Rectangle{
    id: root
    property string text: ""
    signal clicked()
    width: 100
    height: 100
    color: "#96000000"
    border.width: 1;
    border.color: "#96ffffff"
    radius: width / 2.4
    Text{
        anchors.centerIn: parent
        color: "white"
        text: root.text
        font.pixelSize: root.height/1.5
    }
    MouseArea{
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            root.clicked();
        }
    }
    states: [
        State {
            name: "clicked"
            when: mouseArea.pressed
            PropertyChanges {
                target: root
                color: "#ff4290ff"
                border.width: 0
            }
        }

    ]
}
