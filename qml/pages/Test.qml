import QtQuick 2.0

import QtQuick 2.0
import Sailfish.Silica 1.0

Page{

    SilicaListView{

        Button{

         text: "Test";
         onClicked: networkrequest.sendRequest("GetDepartureBoard",30,"LDS","","","","");
        }

        width: 480;
        height: 960;

        model: serviceModel
        delegate: Row {
            width: ListView.view.width
            height: Theme.itemSizeSmall

            Label { text: destination + " " + departureTime}
        }

        VerticalScrollDecorator{}

    }


}
