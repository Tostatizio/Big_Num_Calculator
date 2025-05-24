#include "fileopener.h"

FileOpener::FileOpener(QObject *parent)
    : QObject{parent}
{}

Q_INVOKABLE void FileOpener::generateAndOpenFile(QString s) {
    QString filePath = QDir::currentPath() + "/generated_output.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << s;
    file.close();

    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}
