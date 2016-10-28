/*
    SearchNemo - A program for search text in local files
    Copyright (C) 2016 SargoDevel
    Contact: SargoDevel <sargo-devel@go2.pl>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3.

    This program is distributed WITHOUT ANY WARRANTY.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QSettings>
#include <QDebug>
#include <QObject>
#include "exporter.h"
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#define M_NOTESDBPATH ".local/share/jolla-notes/QML/OfflineStorage/Databases/"
#define M_LOCALSHARE ".local/share/"
#define M_BOOKMARKSJSONPATH ".local/share/org.sailfishos/sailfish-browser/bookmarks.json"


Exporter::Exporter(QObject *parent) : QObject(parent) {

}

//TODO: bug -> delete Exporter::Exporter(QString path)
Exporter::Exporter(QString path) {

}

Exporter::~Exporter() {

}


bool Exporter::initDB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(findNotesFileName());

    return db.open();
}

int Exporter::nrOfNoteEntries() const {

    QSqlQuery * query = new QSqlQuery(db);

    int nr=0;

    query->prepare("SELECT count(*) FROM notes");
    if(query->exec()) {
        if(query->next())
            nr = query->value(0).toInt();
    }
    return nr;
}

QString Exporter::findNotesFileName() {
    QDir dir(QDir::homePath() + "/" + M_NOTESDBPATH);
    if (!dir.exists()) return QString();
    QStringList names = dir.entryList(QDir::Files);
    for (int i = 0 ; i < names.count() ; ++i) {
        QString filename = names.at(i);
        if (filename.endsWith("sqlite")) {
            QString inifilename = filename;
            QFile inifile( dir.absoluteFilePath(inifilename.remove(".sqlite").append(".ini")) );
            if( inifile.exists() ) {
                QSettings inisettings( dir.absoluteFilePath(inifilename), QSettings::IniFormat );
                if( inisettings.value("Name").toString() == "silicanotes" ) {
                    return dir.absoluteFilePath(filename);
                }
            }
        }
    }
    return QString();
}

void Exporter::write(QString note,  QString path) { 
    QFile file(QDir::homePath() + path);
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream( &file );
        stream.setCodec("UTF-8");
        stream << note;
    }
    file.close();

    //TODO return something or write about possible errors
}

QString Exporter::getNotes() {
    QString note;

    if (Exporter::initDB()) {

        QSqlQuery * query = new QSqlQuery(db);
        int notesOverall = nrOfNoteEntries();

        for(int i = 0; i < notesOverall+1; i++) {

            query->prepare("SELECT body FROM notes WHERE pagenr=(:index)");
            query->bindValue(":index", i);
            if(query->exec()) {
                if(query->next())
                    note = note + query->value(0).toString();
                    note = note + "\n" + "|==============================|" + "\n";
            }
        }
    }
    db.close();

    return note;
}

QString Exporter::getBookmarks() {
    QTextStream out(stdout);
    QString bookmarks;

    QString val;
    QFile file(M_BOOKMARKSJSONPATH);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject json = d.object();


    out << d.isNull(); //DEBUG
    out << json["url"].toString();
    //out << json.value(QString("url")); //???
    bookmarks = json["url"].toString();

    QJsonArray test = json["usr"].toArray(); //TEST
    out << test[0].toString(); //DEBUG

    file.close();

    return bookmarks;
}
