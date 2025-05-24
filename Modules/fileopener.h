#ifndef FILEOPENER_H
#define FILEOPENER_H

#include <QObject>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QDir>

class FileOpener : public QObject
{
    Q_OBJECT
public:
    explicit FileOpener(QObject *parent = nullptr);

    Q_INVOKABLE void generateAndOpenFile(QString s);
signals:

};

#endif // FILEOPENER_H
