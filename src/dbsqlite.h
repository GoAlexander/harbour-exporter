#ifndef DBSQLITE_H
#define DBSQLITE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QHash>
#include <QObject>

#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

class DbSqlite : public QObject{
    Q_OBJECT
signals:

public:
    explicit DbSqlite (QObject *parent = 0); //???

    // Constructor sets up connection with db and opens it
    // @param path - absolute path to db file
    DbSqlite(const QString& path);

     //Close the db connection
    ~DbSqlite();

//иначе qml не увидит getNotes как функцию
public slots:
    // returns all notes
    QString getNotes();

private:
    QSqlDatabase db;
    QSqlDatabase m_db; //TEST
    QSqlQuery* m_queryp = NULL;

    // returns number of entries in notes table
    int nrOfNoteEntries() const;

    // returns file name of notes database
    static QString findNotesFileName();

    void writeNotes(QString note); //TODO make public?
};

#endif // DBSQLITE_H
