import QtQuick 1.1
import com.nokia.meego 1.1

Item {
    width: parent.width
    height: 70
    z:7

    property alias title: h_title.text
    property alias subtitle: h_subtilte.text
    property bool loading: false

    Rectangle {
        width: parent.width
        height: parent.height
        color: "orange"
    }

    Rectangle {
        id: top_banner
        x: -1
        y: -1
        width: parent.width + 1
        height: 71
        color: "#1086d6"

        Text {
            id:h_title
            visible: true
            anchors.verticalCenter: parent.verticalCenter
            x:20
            color: "#ffffff"
            font.family: "Nokia Pure Text Light"
            font.pixelSize: 30
        }

        Text {
            id:h_subtilte
            y:42
            x:20
            font.family: "Nokia Pure Text Light"
            font.pixelSize: 22
            color:"#fff"
        }

        BusyIndicator{
            id: busyIndicator
            running: loading
            visible: loading
            anchors.verticalCenter: top_banner.verticalCenter
            anchors.right: top_banner.right
            anchors.rightMargin: 20
        }
    }
}
