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
