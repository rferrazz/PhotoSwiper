import QtQuick 1.1
import com.nokia.meego 1.1

Page{
    id: root
    tools: commonTools
    signal setServer(string ip, string port)

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
                text: qsTr("Server IP")
                font: UiConstants.FieldLabelFont
            }
            TextField{
                id: ip
                width: parent.width
                font: UiConstants.FieldLabelFont
                text: (!settings.getOption("adress")) ? "" : settings.getOption("adress")
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
                text: (!settings.getOption("port")) ? "6017" : settings.getOption("port")
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
