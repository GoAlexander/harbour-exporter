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

    // returns number of entries in notes table
    int nrOfNoteEntries() const;
    // returns file name of notes database
    //static QString findNotesFileName();
    // returns complete note
    //QString getNote() const;

//иначе qml не увидит getNote как функцию
public slots:
    // returns file name of notes database
    static QString findNotesFileName();
    // returns complete note
    QString getNotes() const;


private:
    QSqlDatabase m_db;
    QSqlQuery* m_queryp = NULL;
};

#endif // DBSQLITE_H
