import QtQuick 2.1
import Sailfish.Silica 1.0

Page {

    id:page

    width:parent.width;
    height:parent.height;

    SilicaFlickable{

        anchors.fill: parent

        PullDownMenu {

            MenuItem {
                text: "Arrivals"
                onClicked: {
                    if(locationLabel.text != "Location"){

                        var location = locationLabel.text.split(" - ")[1];

                        if(destinationLabel.text != "Location"){
                            var destination = destinationLabel.text.split(" - ")[1];
                        }else{
                            destination="";
                        }

                        var dialog = pageStack.push("SearchResults.qml", {"method":"GetArrivalBoard",rows: 30 ,"location": location ,"destination": destination, "fromto" : fromto.value.toLowerCase(),"timeOffset":offset.value})

                    }
                }


            }

            MenuItem {
                text: "Departures"
                onClicked: {

                    if(locationLabel.text != "Location"){

                        var location = locationLabel.text.split(" - ")[1];

                        if(destinationLabel.text != "Location"){
                            var destination = destinationLabel.text.split(" - ")[1];
                        }else{
                            destination="";
                        }

                        var dialog = pageStack.push("SearchResults.qml", {"method":"GetDepartureBoard",rows: 30 ,"location": location ,"destination": destination, "fromto" : fromto.value.toLowerCase(), "timeOffset": offset.value})

                    }

                }
            }
        }

        Column{

            PageHeader {
                title: "Search"
            }

            width:parent.width;
            height:parent.height;

            spacing: Theme.paddingMedium


            BackgroundItem {
                id: location
                width: page.width
                Label{
                    id:locationLabel
                    text:"Location"
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.verticalCenter: parent.verticalCenter
                    textFormat: Text.StyledText

                }

                function openFormDialog() {

                    var dialog = pageStack.push("LocationSearch.qml")
                    dialog.accepted.connect(function() {
                        locationLabel.text = dialog.selection;
                    })
                }

                onClicked: openFormDialog();
            }

            ComboBox {
                id: fromto
                width: page.width
                menu: ContextMenu {
                    MenuItem { text: "To" }
                    MenuItem { text: "From" }
                }

                IconButton {
                    id: oppDirection
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    width: Theme.iconSizeMedium
                    height: width;
                    icon.source: "image://theme/icon-m-mobile-network"
                    onClicked: {

                        oppDirection.state == "rotated" ? oppDirection.state = "" : oppDirection.state = "rotated";

                        swapLocations()

                        function swapLocations(){
                            var location1 = locationLabel.text;
                            var location2 = destinationLabel.text;

                            locationLabel.text = location2;
                            destinationLabel.text = location1;
                        }
                    }

                    states: State {
                        name: "rotated"
                        PropertyChanges { target: oppDirection; rotation: 180 }
                    }

                    transitions: Transition {
                        RotationAnimation { duration: 250; direction: RotationAnimation.Clockwise }
                    }

                }

            }

            BackgroundItem {
                id: destination
                width: page.width
                Label{id:destinationLabel
                    text:"Location"

                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.verticalCenter: parent.verticalCenter
                    textFormat: Text.StyledText}
                function openFormDialog() {

                    var dialog = pageStack.push("LocationSearch.qml")
                    dialog.accepted.connect(function() {
                        destinationLabel.text = dialog.selection;
                    })
                }

                onClicked: openFormDialog();
            }

            Slider {
                id:offset
                width: parent.width
                minimumValue: -120
                maximumValue: 119
                value: 0
                stepSize: 1
                valueText: "Minutes+-: " + value
                label:"Time Offset"
            }
        }
    }
}

