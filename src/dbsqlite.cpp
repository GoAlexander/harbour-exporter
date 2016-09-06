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
#include "dbsqlite.h"
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

#define M_NOTESDBPATH ".local/share/jolla-notes/QML/OfflineStorage/Databases/"
#define M_LOCALSHARE ".local/share/"

//NEW:
DbSqlite::DbSqlite(QObject *parent) : QObject(parent) {

}

DbSqlite::DbSqlite(const QString &path) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        //qDebug() << "Error: connection with database fail: " << path;
    }
    else
    {
        if (NULL == m_queryp) m_queryp = new QSqlQuery(m_db);
        //qDebug() << "Database: connection ok: " << path;
    }
}

DbSqlite::~DbSqlite() {
    if (NULL != m_queryp) {
        delete m_queryp;
        m_queryp = NULL;
    }
    QString connection = m_db.connectionName();

    if (m_db.isOpen())
    {
        m_db.close();
        //qDebug() << "Database: connection closed: " << m_db.databaseName();
    }
    m_db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connection);
}

int DbSqlite::nrOfNoteEntries() const {

    QSqlQuery * query = new QSqlQuery(db);

    int nr=0;

    query->prepare("SELECT count(*) FROM notes");
    if(query->exec()) {
        if(query->next())
            nr = query->value(0).toInt();
    }
    return nr;
}

QString DbSqlite::findNotesFileName() {
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

void DbSqlite::writeNotes(QString note) {
    //TODO: mkdir
    QFile file(QDir::homePath() + "/Documents/" + "exported-notes.txt");
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream( &file );
        stream << note;
    }
    file.close();

    //TODO return something or write about possible errors
}

QString DbSqlite::getNotes() {
    QString note;

    //TODO вынести инициализацию DB в отдельную функцию
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(findNotesFileName());

    if (db.open()) {

        QSqlQuery * query = new QSqlQuery(db);
        int notesOverall = nrOfNoteEntries();

        //nr-1 (instead of nr) because of strange behavior
        for(int i = 0; i < notesOverall-1; i++) {

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

    writeNotes(note);

    return note;
}
