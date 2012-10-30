/*
* one line to give the program's name and an idea of what it does.
* Copyright (C) 2012  Riccardo Ferrazzo <f.riccardo87@gmail.com>

* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
import QtQuick 1.1
import com.nokia.meego 1.0
import QtMobility.gallery 1.1

Page {
    id: root
    tools: commonTools
    orientationLock: PageOrientation.LockPortrait
    property bool tracking: false
    property int globalX
    property int globalY
    property string currImg
    signal preload(string filepath);

    Rectangle{
        color: "black"
        anchors.fill: parent

        GridView{
            id: view
            anchors.fill: parent
            cellWidth: root.width/3
            cellHeight: cellWidth
            cacheBuffer: height*1.5
            clip: true
            pressDelay: 200
            model: DocumentGalleryModel{
                id: galleryModel
                rootType: DocumentGallery.Image
                properties: [ "filePath", "url", "orientation", "fileName" ]
                sortProperties: ["-dateTaken", "-lastModified"]
            }

            delegate: Image {
                property string file: filePath
                source: "image://cache/"+filePath
                width: view.cellWidth
                height: view.cellHeight
                sourceSize.width: width
                fillMode: Image.PreserveAspectCrop
                clip: true
                cache: true
                asynchronous: true
                MouseArea{
                    id: sendMouseArea
                    anchors.fill: parent
                    onPressed: {
                        currImg = url
                        view.interactive = false;
                        tracking = true;
                        var pos = sendMouseArea.mapToItem(root, mouseX, mouseY);
                        globalX = pos.x;
                        globalY = pos.y;
                        selected.opacity = 1;
                    }
                    onMousePositionChanged: {
                        if(tracking){
                            var pos = sendMouseArea.mapToItem(root, mouseX, mouseY);
                            globalX = pos.x;
                            globalY = pos.y;
                        }
                    }
                    onReleased: {
                        if(tracking){
                            if(globalY < send.height){
                                sender.sendImage(file, 0);
                                sender.toSend = true;
                            }
                            tracking = !tracking;
                            view.interactive = true;
                        }
                        selected.opacity = 0
                    }
                }
                Rectangle {
                    id: selected
                    anchors.fill: parent
                    color: "black"
                    opacity: 0
                }
            }
        }
        Rectangle{
            id: trackingBAckground
            anchors.fill: parent
            opacity: 0
            color: "black"
        }
        Rectangle{
            id: send
            width: parent.width
            height: 100
            anchors.top: parent.top
            anchors.topMargin: -100
            color: "green"
            Text{
                id: sendText
                color: "#ffffff"
                anchors.fill: parent
                text: "Send"
                font.pointSize: 30
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Image{
            id: fingercircle
            width: view.width/3
            height: width
            visible: false
            source: currImg
            sourceSize.width: width
            fillMode: Image.PreserveAspectCrop
            clip: true
            states: [
                State{
                    name: "active"
                    when: tracking
                    PropertyChanges {
                        target: fingercircle
                        x: globalX-(width/2)
                        y: globalY-(height/2)
                    }
                }
            ]
        }
        states: [
            State{
                name: "sendEnabled"
                when: tracking
                PropertyChanges{
                    target: trackingBAckground
                    opacity: 0.6
                }
                PropertyChanges {
                    target: send
                    anchors.topMargin: 0
                }
                PropertyChanges{
                    target: fingercircle
                    visible: true
                }
            },
            State{
                name: "sending"
                when: sender.toSend
                PropertyChanges{
                    target: trackingBAckground
                    opacity: 0.6
                }
                PropertyChanges {
                    target: send
                    anchors.topMargin: 0
                }
                PropertyChanges{
                    target: send
                    color: "orange"
                }
                PropertyChanges {
                    target: sendText
                    text: "Sending..."
                }
            }

        ]
        transitions: [
            Transition {
                from: ""
                to: "sendEnabled"
                ParallelAnimation{
                    NumberAnimation{target: trackingBAckground; property: "opacity"; duration: 500 }
                    NumberAnimation{target: send; property: "anchors.topMargin"; duration: 500}
                }
            },
            Transition {
                from: "sendingEnabled"
                to: "sending"
                ParallelAnimation{
                    NumberAnimation { target: send; property: "anchors.topMargin"; duration: 500; easing: Easing.InOutBack }
                }
            },
            Transition {
                from: "sending"
                to: ""
                ParallelAnimation{
                    NumberAnimation{target: trackingBAckground; property: "opacity"; duration: 500 }
                    NumberAnimation{target: send; property: "anchors.topMargin"; duration: 500}
                }
            }

        ]
    }
    Dialog{
        id: infoDialog
        title: Text {
            width: parent.width
            color: "white"
            font.pixelSize: 32
            text: "Photo Swiper"
            horizontalAlignment: Text.AlignHCenter
        }
        content: Text{
            color: "white"
            font.pixelSize: 24
            wrapMode: Text.WordWrap
            width: parent.width
            text: "<p>To learn more about photoSwiper and to keep in touch with updates on the client visit <a href=\"http://www.rfcode.eu/\">http://www.rfcode.eu</a></p>
                    <p>In order to use this application you have to download the open source client application on your desktop PC, you can find it here: <a href=\"http://www.rfcode.eu/?p=18\">http://goo.gl/zCusg</a></p>"
            onLinkActivated: {Qt.openUrlExternally(link)}
        }
    }
}
