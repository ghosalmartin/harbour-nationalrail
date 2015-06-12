import QtQuick 2.0
import Sailfish.Silica 1.0

Page{

    id:page

    width:parent.width;
    height:parent.height;

    SilicaListView {
        anchors.fill: parent
        spacing: Theme.paddingMedium

        header: PageHeader {
            title: "Station Messages"
        }

        model:messagesModel

        delegate: Item {
            width: parent.width

            Label {
                textFormat: Text.RichText
                text: model.message
                wrapMode: Text.WordWrap
                font.pixelSize: Theme.fontSizeMedium
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: Theme.paddingLarge
                    rightMargin: Theme.paddingMedium
                }
                onLinkActivated: Qt.openUrlExternally(link)
            }
        }

        VerticalScrollDecorator {}
    }
}

