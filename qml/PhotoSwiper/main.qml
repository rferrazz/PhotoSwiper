import QtQuick 1.1
import com.nokia.meego 1.0
import QmlSettings 1.0

PageStackWindow {
    id: appWindow
    showStatusBar: false

    function firstBootTerminated(){
        settings.setOption("firstBootDone", true);
        Qt.quit();
    }

    MainPage {
        id: mainPage
    }

    FirstLoadPage{
        id: firstLoad
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
            if(optionName == "firstBootDone"){
                if(optionValue == "false"){
                    settings.setOption("firstBootDone", false);
                    pageStack.push(firstLoad);
                    firstLoad.startWork();
                } else {
                    pageStack.push(mainPage);
                }
            }
        }
    }

    Component.onCompleted: {
        settings.initSettings("RFCode", "PhotoSwiper");
        settings.getOption("firstBootDone")
    }
}
