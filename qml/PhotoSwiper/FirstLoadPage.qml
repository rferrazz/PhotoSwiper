// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import QmlSharing 1.0
import QtMobility.gallery 1.1

Page{
    id: root
    property bool workStarted: false
    function startWork(){
        workStarted = true;
        if(galleryModel.status == DocumentGalleryModel.Finished && workStarted){
            loadThumbs();
        }
    }

    function loadThumbs(){
        var thumbList = new Array();
        for(var i=0; i < galleryModel.count; i++){
            loader.addThumb(galleryModel.get(i).filePath);
        }
        loader.loadThumbs(root.width/3);
    }

    Rectangle{
        anchors.fill: parent
        color: "black"
        Column{
            anchors.centerIn: parent
            width: parent.width -30
            height: parent.height-30
            spacing: 10
            Item{
                height: 50
            }

            Text {
                width: parent.width
                color: "white"
                font.pixelSize: 32
                text: "Please wait"
                horizontalAlignment: Text.AlignHCenter
            }
            Text{
                color: "white"
                font.pixelSize: 24
                wrapMode: Text.WordWrap
                width: parent.width
                text: "<p>In order to use this application you have to download the open source client application on your desktop PC, you can find it here: <a href=\"http://www.rfcode.eu/?p=18\">http://goo.gl/zCusg</a></p>
                        <p>Image cache being rebuilt, wait until the process is completed.</p>
                        <p>after this step you can load again Photo Swiper and start swiping!</p>"
            }
            ProgressBar{
                width: parent.width
                minimumValue: 0
                maximumValue: galleryModel.count
                value: loader.thumbsLoaded
            }
        }
    }
    DocumentGalleryModel{
        id: galleryModel
        rootType: DocumentGallery.Image
        properties: [ "filePath", "url", "orientation", "fileName" ]
        sortProperties: ["-dateTaken", "-lastModified"]
        onStatusChanged: {
            if(status == DocumentGalleryModel.Finished && workStarted)
                loadThumbs();
        }
    }
    FirstTimeLoader{
        id: loader
        property int thumbsLoaded: 0
        onThumbLoaded: {
            thumbsLoaded++;
            if(thumbsLoaded == galleryModel.count){
                appWindow.firstBootTerminated();
            }
        }
    }
}
