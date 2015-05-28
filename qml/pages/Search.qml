import QtQuick 2.1
import Sailfish.Silica 1.0

Page {

    id:page

    width:parent.width;
    height:parent.height;

    Column{



        width:parent.width;
        height:parent.height;

        spacing: Theme.paddingLarge
        PageHeader {
            title: "Search"
        }

        ComboBox {
            id: location
            width: page.width
            label: "Location"
            function openFormDialog() {

                var dialog = pageStack.push("LocationSearch.qml")
                dialog.accepted.connect(function() {
                    location.label = dialog.selection;
                })
            }

            onClicked: openFormDialog();
        }

        ComboBox {
            width: page.width
            menu: ContextMenu {
                MenuItem { text: "From" }
                MenuItem { text: "To" }
            }
        }

        ComboBox {
            id: destination
            width: page.width
            label: "Destination"
            function openFormDialog() {

                var dialog = pageStack.push("LocationSearch.qml")
                dialog.accepted.connect(function() {
                    destination.label = dialog.selection;
                })
            }

            onClicked: openFormDialog();
        }




    }
}
