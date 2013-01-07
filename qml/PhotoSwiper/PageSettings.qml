import QtQuick 1.1
import com.nokia.meego 1.1

Page{
    id: root
    tools: commonTools
    signal setServer(string ip, string port)
    property string adress: ""
    property string port: "6017"

    HeaderBar{
        id: header
        title: qsTr("Settings")
    }

    Column{
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: UiConstants.DefaultMargin
        spacing: UiConstants.ButtonSpacing
        Column{
            width: parent.width
            Label{
                text: qsTr("Server IP or hostname")
                font: UiConstants.FieldLabelFont
            }
            TextField{
                id: ip
                width: parent.width
                font: UiConstants.FieldLabelFont
                text: root.adress
                inputMethodHints: Qt.ImhUrlCharactersOnly
            }
        }
        Column{
            width: parent.width
            Label{
                text: qsTr("Port")
                font: UiConstants.FieldLabelFont
            }
            TextField{
                id: port
                width: parent.width
                font: UiConstants.FieldLabelFont
                inputMask: "9999"
                text: root.port
                inputMethodHints: Qt.ImhDigitsOnly
            }
        }
        Button{
            width: parent.width
            text: "apply"
            onClicked:{
                sender.setReciver(ip.text, parseInt(port.text));
                settings.setOption("adress", ip.text);
                settings.setOption("port", parseInt(port.text));
                pageStack.pop();
            }
        }
    }
}
