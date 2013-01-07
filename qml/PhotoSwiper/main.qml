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
import QmlSettings 1.0
import QmlSharing 1.0

PageStackWindow {
    id: appWindow
    showStatusBar: false
    initialPage: mainPage

    function firstBootTerminated(){
        settings.setOption("firstBootDone", true);
        Qt.quit();
    }

    ImageSender{
        id: sender
        property bool toSend: false;
        onImageSent: {
            toSend = false;
        }
    }

    MainPage {
        id: mainPage
    }

    PageSettings{
        id: settingsPage

    }

    Menu {
        id: appMenu
        visualParent: pageStack
        visible: true
        MenuLayout {
            MenuItem { text: qsTr("Sample menu item") }
        }
    }

    Settings{
        id: settings
        onOptionGetted:{
            if(optionValue !== "" && optionValue !== false){
                if(optionName == "adress"){
                    settingsPage.adress = optionValue;
                }
                if(optionName == "port"){
                    settingsPage.port = optionValue;
                }
            }
        }
    }

    ToolBarLayout {
        id: commonTools
        visible: true
        ToolIcon{
            platformIconId:(enabled) ? "toolbar-back" : "toolbar-back-dimmed"
            onClicked: {
                pageStack.pop();
            }
            enabled: (pageStack.depth > 1) ? true : false
        }
        ToolIcon {
            platformIconId: "toolbar-settings"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: pageStack.push(settingsPage);
        }
    }

    Component.onCompleted: {
        theme.inverted = true;
        settings.initSettings("RFCode", "PhotoSwiper");
        settings.getOption("adress");
        settings.getOption("port");
    }
}
