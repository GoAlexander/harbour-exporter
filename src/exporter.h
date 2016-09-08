#ifndef Exporter_H
#define Exporter_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QHash>
#include <QObject>

#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

class Exporter : public QObject{
    Q_OBJECT
signals:

public:
    explicit Exporter (QObject *parent = 0); //???

    Exporter(QString path);

     //Close the db connection
    ~Exporter();

//иначе qml не увидит getNotes как функцию
public slots:
    // returns all notes
    QString getNotes();
    QString getBookmarks();
    void write(QString note,  QString path);

private:
    QSqlDatabase db;

    // returns number of entries in notes table
    int nrOfNoteEntries() const;

    // returns file name of notes database
    static QString findNotesFileName();

    //returns status of DB (works/doesn`t work)
    bool initDB();
};

#endif // Exporter_H
