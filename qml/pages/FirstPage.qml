import QtQuick 2.0
import Sailfish.Silica 1.0
import org.nemomobile.notifications 1.0
import Exporter 1.0

Page {
    id: page

    property string notes
    property string bookmarks

    //create class for exporting
    Exporter {
        id: myExporter
    }

    Notification {
        id: outputNotifications
        category: "Exporter."
        //appIcon: "/usr/share/example-app/icon-l-application"
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


            Row {
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: Theme.paddingLarge

                ControlBigButton {
                    id: notesButton
                    icon: "../images/notes.svg"
                    text: qsTr("Export notes")

                    onClicked: {
                        console.log("Export notes clicked!");
                        notes = myExporter.getNotes();
                        myExporter.write(notes, "/Documents/exported-notes.txt");

                        outputNotifications.close()
                        outputNotifications.previewBody = qsTr("Notes exported!")
                        outputNotifications.publish()
                    }
                }

                ControlBigButton {
                    id: bookmarksButton
                    icon: "../images/bookmarks.svg"
                    text: qsTr("Export bookmarks")

                    onClicked: {
                        console.log("Export bookmarks clicked!");
                        bookmarks = myExporter.getBookmarks();
                        myExporter.write(bookmarks, "/Documents/exported-bookmarks.txt");

                        outputNotifications.close()
                        outputNotifications.previewBody = qsTr("Bookmarks exported!")
                        outputNotifications.publish()
                    }
                }
            }

        }
    }
}
