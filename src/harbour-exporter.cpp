/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include "exporter.h"
#include <QTextStream>

int main(int argc, char *argv[])
{
    if(argc > 1) {
        QTextStream out(stdout);
        if (strcmp(argv[1],"-b") == 0) {
            //work in progress...

        } else if (strcmp(argv[1],"-n") == 0) {
            //Exporter * myExporter = new Exporter();
            //myExporter->getNotes();

            //Exporter myExporter;
            //out << myExporter.getNotes();
            Exporter myExporter;
            myExporter.write(myExporter.getNotes(), "/Documents/exported-notes.txt"); //TODO remake!!!

        } else {
            out << "Usage: harbour-exporter [OPTION]" << endl;
            out << "  -b" << endl;
            out << "    export bookmarks (exports ONLY to the terminal)" << endl;
            out << "  -n" << endl;
            out << "    export notes (exports ONLY to the terminal)" << endl;
            out << "  -h" << endl;
            out << "    display this help and exit" << endl;
        }

        exit(0);
    }

    QGuiApplication *app = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView();

    qmlRegisterType<Exporter>("Exporter", 1, 0, "Exporter");

    view->setSource(SailfishApp::pathTo("qml/harbour-exporter.qml"));
    view->showFullScreen();
    return app->exec();

}
