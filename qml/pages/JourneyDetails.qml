import QtQuick 2.0
import Sailfish.Silica 1.0
import com.nationalrail.previouscpmodel 1.0
import com.nationalrail.subsequentcpmodel 1.0


Dialog{
    id:dialog

    width:parent.width;
    height:parent.height;

    property string serviceID;

        PageHeader {
            id:header
            title: "Journey Details"
        }

        BusyIndicator {
            anchors.centerIn: parent
            size: BusyIndicatorSize.Large
            running: !previousCPModel.ready
        }

        SectionHeader{
            id:previousSection
            text:"Previous Calling Points"
            anchors {
                top: header.bottom
                left: parent.left
                right: parent.right
            }
        }

        SilicaListView{

            id:previousCallingPoints
            height: previousCallingPoints.count * Theme.itemSizeSmall

            anchors {
                top: previousSection.bottom
                left: parent.left
                right: parent.right
            }
//            ViewPlaceholder {
//                enabled: previousCPModel.ready && previousCallingPoints.count === 0
//                text: "No Previous Calling Points"
//                verticalOffset: -350
//            }

            model: previousCPModel
            delegate: BackgroundItem {

                width: ListView.view.width
                height: Theme.itemSizeSmall

                Label {
                    id:locationLabel
                    text: model.locationName
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }

                Label {
                    id: textTimeLabel
                    text: "Sch. Time: " + model.scheduledTime
                    font.pixelSize: Theme.fontSizeExtraSmall
                    anchors.right: parent.right
                    anchors.top: parent.top
                }

                Label {
                    id: amendedTimeLabel
                    text: "Act. Time: " + model.actualTime
                    font.pixelSize: Theme.fontSizeExtraSmall
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

        SectionHeader{
            id:subsequentSection
            text:"Subsequent Calling Points"
            anchors {
                top: previousCallingPoints.bottom
                left: parent.left
                right: parent.right
            }
        }


        SilicaListView{

            id:subCallingPoints

            height: subCallingPoints.count * Theme.itemSizeSmall

            anchors {
                top: subsequentSection.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            model: subsequentCPModel

//            ViewPlaceholder {
//                enabled: subsequentCPModel.ready && subsequentCPModel.count === 0
//                text: "No Subsequent Calling Points"
//                verticalOffset: -350
//            }

            delegate: BackgroundItem {

                width: ListView.view.width
                height: Theme.itemSizeSmall

                Label {
                    id:locationLabel1
                    text: model.locationName
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }


                Label {
                    id: scheduledLabel1
                    text: "Sch. Time: " + model.scheduledTime
                    font.pixelSize: Theme.fontSizeExtraSmall
                    anchors.right: parent.right
                    anchors.top: parent.top

                }

                Label {
                    id: actualTimeLabel1
                    text: "Act. Time: " + model.actualTime
                    font.pixelSize: Theme.fontSizeExtraSmall
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }

    SubsequentCPModel{
        id:subsequentCPModel
        source: networkRequest
    }

    PreviousCPModel{
        id:previousCPModel
        source: networkRequest
    }

    Timer {
        id:timer
        interval: 100
        running: true
        repeat: false
        onTriggered: networkRequest.sendServiceIDRequest(serviceID);
    }

    Component.onCompleted: {
        timer.start();
    }

}
