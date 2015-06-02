import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog{
    id:dialog

    width:parent.width;
    height:parent.height;

    property string method;
    property int rows;
    property string location;
    property string destination;
    property string fromto;
    property string timeOffset;
    property string timeWindow;



    SilicaListView{

        header:   PageHeader {
            title: "Results"
        }



        anchors.fill: parent
        currentIndex: -1

        model: serviceModel
        delegate: BackgroundItem {
            width: ListView.view.width
            height: Theme.itemSizeSmall

            Label {
                text: destination
            }

            Label {
                id: platformLabel
                text: {"Platform: "+platform }
                font.pixelSize: Theme.fontSizeExtraSmall
                anchors.right: parent.right
               // anchors.baseline: parent.TopRight
            }

//            Label {
//                id: departureTimeLabel
//                text: {"Departure Time: "+departureTime }
//                font.pixelSize: Theme.fontSizeExtraSmall
//                anchors.right: parent.right
//                anchors.baseline: parent.Bottom
//            }
        }

        VerticalScrollDecorator{}

    }

    Component.onCompleted: {
        networkrequest.sendXYZRequest(method, rows, location, destination, fromto, timeOffset, timeWindow);
    }
}
