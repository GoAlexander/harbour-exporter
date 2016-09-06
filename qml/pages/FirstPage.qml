import QtQuick 2.0
import Sailfish.Silica 1.0
import DbSqlite 1.0

Page {
    id: page

    //create class for exporting
    DbSqlite {
        id: myDbSqlite
    }

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
            }
        }

        contentHeight: column.height

        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader {
                title: qsTr("Exporter.")
            }

            /*
            Label {
                x: Theme.paddingLarge
                text: qsTr("Hello Sailors")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }
            */

            Button {
                id: notesButton
                text: qsTr("Export notes")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    //output.text = buttonAnswer();
                    console.log("Export notes clicked!");
                    //console.log(myDbSqlite.findNotesFileName());
                    console.log(myDbSqlite.getNote());
                    console.log("Export notes clicked!2");

                }
            }

            //TODO more space between buttons!

            Button {
                id: bookmarksButton
                text: qsTr("Export bookmarks")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    //output.text = buttonAnswer();
                    console.log("Export bookmarks clicked!");
                }
            }
        }
    }
}

