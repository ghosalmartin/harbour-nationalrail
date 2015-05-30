import QtQuick 2.1
import Sailfish.Silica 1.0

Dialog {
    id: searchDialog
    property string searchString: ""
    property bool keepSearchFieldFocus
    property string selection: ""

    onSearchStringChanged: stationsModel.filter = searchString

    canAccept:false;

    Loader {
        anchors.fill: parent
        sourceComponent: listViewComponent
    }



    Column {
        id: headerContainer

        width: parent.width

        PageHeader {
            title: "Train Stations"
        }

        SearchField {
            id: searchField
            width: parent.width

            Binding {
                target: searchDialog
                property: "searchString"
                value: searchField.text.toLowerCase().trim()
            }
        }
    }

    Component {
        id: listViewComponent
        SilicaListView {
            id:listview
            model: stationsModel
            anchors.fill: parent
            currentIndex: -1 // otherwise currentItem will steal focus
            header:  Item {
                id: header
                width: headerContainer.width
                height: headerContainer.height
                Component.onCompleted: headerContainer.parent = header
            }

            delegate: BackgroundItem {
                id: backgroundItem

                ListView.onAdd: AddAnimation {
                    target: backgroundItem
                }
                ListView.onRemove: RemoveAnimation {
                    target: backgroundItem
                }

                Label {
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingLarge
                    anchors.verticalCenter: parent.verticalCenter

                    color: searchString.length > 0 ? (highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor)
                                                   : (highlighted ? Theme.highlightColor : Theme.primaryColor)
                    textFormat: Text.StyledText
                    text: Theme.highlightText(model.station, searchString, Theme.highlightColor)

                }

                IconButton {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    icon.source: model.favorited ? "image://theme/icon-m-favorite-selected" : "image://theme/icon-m-favorite"
                    onClicked: {
                        model.favorited = !model.favorited;
                    }
                    highlighted: down || backgroundItem.highlighted
                }

                function selectItem(){
                    canAccept = true
                    selection = model.station
                    pageStack.navigateForward()
                }

                onClicked:selectItem();

            }

            VerticalScrollDecorator {}

            Component.onCompleted: {
                if (keepSearchFieldFocus) {
                    searchField.forceActiveFocus()
                }
                keepSearchFieldFocus = false
                stationsModel.filter = "";
            }
        }
    }
}
