import QtQuick 2.0
import Sailfish.Silica 1.0
import Exporter 1.0

Page {
    id: page

    property string notes


    //create class for exporting
    Exporter {
        id: myExporter
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

            Label {
                id: output
                x: Theme.paddingLarge
                horizontalAlignment: Text.Center
                //text: qsTr("")
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }

            Button {
                id: notesButton
                text: qsTr("Export notes")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    console.log("Export notes clicked!");
                    //console.log(myExporter.findNotesFileName());
                    //console.log(myExporter.getNotes());
                    //console.log(myExporter.write(myExporter.getNotes(), "/Documents/exported-notes.txt"));

                    notes = myExporter.getNotes();
                    console.log(notes)
                    console.log(myExporter.write(notes, "/Documents/exported-notes.txt"))

                    console.log("Export notes clicked!2");
                    output.text = "Notes exported!";

                }
            }

            //TODO more space between buttons!

            Button {
                id: bookmarksButton
                text: qsTr("Export bookmarks")
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    console.log("Export bookmarks clicked!");
                    //in progress
                    output.text = "Bookmarks exported!";
                }
            }       
        }
    }
}


