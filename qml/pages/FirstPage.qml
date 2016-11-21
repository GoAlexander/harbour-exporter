import QtQuick 2.0
import Sailfish.Silica 1.0
import Exporter 1.0

Page {
    id: page

    property string notes
    property string bookmarks

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
                color: Theme.secondaryHighlightColor
                font.pixelSize: Theme.fontSizeExtraLarge
            }

            ControlBigButton {
                id: notesButton
                anchors.horizontalCenter: parent.horizontalCenter
                icon: "../images/notes.svg"
                text: qsTr("Export notes")

                onClicked: {
                    console.log("Export notes clicked!");
                    notes = myExporter.getNotes();
                    myExporter.write(notes, "/Documents/exported-notes.txt");
                    output.text = "Notes exported!";
                }
            }

            ControlBigButton {
                id: bookmarksButton
                anchors.horizontalCenter: parent.horizontalCenter
                icon: "../images/bookmarks.svg"
                text: qsTr("Export bookmarks")

                onClicked: {
                    console.log("Export bookmarks clicked!");
                    bookmarks = myExporter.getBookmarks();
                    myExporter.write(bookmarks, "/Documents/exported-bookmarks.txt");
                    output.text = "Bookmarks exported!";
                }
            }
        }
    }
}
