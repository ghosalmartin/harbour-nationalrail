import QtQuick 2.1
import Sailfish.Silica 1.0

Page {

    id:page

    width:parent.width;
    height:parent.height;

    Column{

        PageHeader {
            title: "Search"
        }

        width:parent.width;
        height:parent.height;

        spacing: Theme.paddingLarge


        BackgroundItem {
            id: location
            width: page.width
            Label{
                id:locationLabel
                text:"Location"
                anchors.left: parent.left
                anchors.leftMargin: Theme.paddingLarge
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

                        location.label = location2;
                        destination.label = location1;
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
                anchors.leftMargin: Theme.paddingLarge
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

        ValueButton {

            id: timeButton
            width: parent.width * 0.5
            value: new Date().toTimeString()
            onClicked:{
                var date = new Date();

                var dialog = pageStack.push(
                            "Sailfish.Silica.TimePickerDialog", {
                                hour: date.getHours(),
                                minute: date.getMinutes()
                            })

                dialog.accepted.connect(function() {
                    timeButton.value = dialog.hour+":"+dialog.minute;
                })
            }
        }


        Button{

            text:"Test"
            onClicked: {

                if(locationLabel.text != "Location"){

                    var location = locationLabel.text.split(" - ")[1];

                    if(destinationLabel.text != "Location"){
                        var destination = destinationLabel.text.split(" - ")[1];
                    }else{
                        destination="";
                    }

                    var dialog = pageStack.push("SearchResults.qml", {"method": "GetDepartureBoard", "rows": 10 ,"location": location ,"destination": destination, "fromto" : fromto.value.toLowerCase()})

                }
            }

        }
    }
}

