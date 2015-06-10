import QtQuick 2.0
import Sailfish.Silica 1.0
import com.nationalrail.networkrequest 1.0
import com.nationalrail.servicemodel 1.0

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

    BusyIndicator {
            anchors.centerIn: parent
            running: !serviceModel.ready
    }

    SilicaListView{
        PullDownMenu {
            MenuItem {
                text: "Refresh"
                onClicked: networkrequest.sendXYZRequest(method, rows, location, destination, fromto, timeOffset, timeWindow);
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
                anchors.top: parent.top
                anchors.left: parent.left
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
            }
        }

        VerticalScrollDecorator{}



        Component.onCompleted: {
            networkrequest.sendXYZRequest(method, rows, location, destination, fromto, timeOffset, timeWindow);
        }

        NetworkRequest {
            id:networkrequest
        }

        ServiceModel{
            id:serviceModel
            source: networkrequest
        }
    }
}
