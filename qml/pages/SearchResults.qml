import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.nationalrail.servicemodel 1.0

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
    property string arrivaldeparture;

    SilicaListView{
        PullDownMenu {
            MenuItem {
                text: "Station Messages"
                onClicked: pageStack.push(Qt.resolvedUrl("StationMessages.qml"))
            }

            MenuItem {
                text: "Refresh"
                onClicked: timer.start()
            }
        }

        header: PageHeader {
            id:header
            title: {
                if(method == "GetDepartureBoard"){
                    header.title="Departures"
                }else{
                    header.title="Arrivals"
                }
            }
        }

        BusyIndicator {
            anchors.centerIn: parent
            size: BusyIndicatorSize.Large
            running: !serviceModel.ready
        }

        anchors.fill: parent
        currentIndex: -1

        model: serviceModel
        delegate: BackgroundItem {

            width: ListView.view.width
            height: Theme.itemSizeSmall


            Label {
                id:locationLabel
                text: {
                    if(method == "GetDepartureBoard"){
                        locationLabel.text=model.destination
                    }else{
                        locationLabel.text=model.stationName
                    }

                }
                //anchors.top: parent.top
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
            }

            Label {
                id: platformLabel
                text:{
                    if(model.platform ===""){
                        platformLabel.text ="Platform: -"
                    }else{
                        platformLabel.text="Platform: "+ model.platform
                    }
                }

                font.pixelSize: Theme.fontSizeExtraSmall
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingMedium
                anchors.verticalCenter: parent.verticalCenter
            }



            Label {
                id: textTimeLabel
                text: {
                    if(method == "GetDepartureBoard"){
                        textTimeLabel.text ="Dep. Time: " + model.departureTime
                    }else{
                        textTimeLabel.text ="Arrival Time: " + model.arrivalTime
                    }
                }
                font.pixelSize: Theme.fontSizeExtraSmall
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: Theme.paddingMedium

            }

            Label {
                id: amendedTimeLabel
                text: {

                    if(model.amendedDepartureTime === "" && model.amendedArrivalTime === "" ){
                        amendedTimeLabel.text="Status: -"
                    }else{
                        if(method == "GetDepartureBoard"){
                            amendedTimeLabel.text ="Status: " + model.amendedDepartureTime
                        }else{
                            amendedTimeLabel.text ="Status: " + model.amendedArrivalTime
                        }
                    }
                }
                font.pixelSize: Theme.fontSizeExtraSmall
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: Theme.paddingMedium
            }

            onClicked: pageStack.push("JourneyDetails.qml", {"serviceID":model.serviceID})
        }

        VerticalScrollDecorator{}

        Timer {
            id:timer
            interval: 250
            running: true
            repeat: false
            onTriggered: networkRequest.sendXYZRequest(method, rows, location, destination, fromto, timeOffset, timeWindow);
        }

        Component.onCompleted: {
            timer.start();
        }

        ServiceModel{
            id:serviceModel
            source: networkRequest
        }
    }
}
