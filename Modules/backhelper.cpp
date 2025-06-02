#include "backhelper.h"

BackHelper::BackHelper(QObject *parent)
    : QObject{parent}
{}

void BackHelper::errMsgInit(QMessageBox &errMsgBox, QByteArray err){
    errMsgBox.setText("Error!");
    errMsgBox.setInformativeText(QtPrivate::convertToQString(err));
    errMsgBox.setWindowTitle("ERROR");

    errMsgBox.setStyleSheet("QLabel{min-width: 350px; min-height: 30;}");
}

Q_INVOKABLE void BackHelper::useCalculatorCpp(){
    QProcess calc;
    calc.setProgram(QCoreApplication::applicationDirPath() + "/backend.exe");

    if (!QFile::exists(QCoreApplication::applicationDirPath() + "/backend.exe")) {
        QMessageBox errMsg;
        errMsgInit(errMsg, "\"backend.exe\" not found!");
        errMsg.exec();
        // qDebug() << "backend.exe not found!";
        return;
    }

    calc.start();
    if (!calc.waitForStarted()) {
        // qDebug() << "Failed to start process.";
        QMessageBox errMsg;
        errMsgInit(errMsg, "Failed to finish the program.");
        errMsg.exec();
        return;
    }
    // qDebug() << "Started!";
    calc.write(BackHelper::mainString().toUtf8() + "\n");
    // qDebug() << "Written!";
    calc.waitForFinished(-1);
    // qDebug() << "Finished!";

    if (calc.exitStatus() == QProcess::NormalExit){
        QByteArray err = calc.readAllStandardError();
        if (err != ""){
            qDebug() << err;
            QMessageBox errMsg;
            errMsgInit(errMsg, err);
            errMsg.exec();
            return;
        }
    }
    else{
        QMessageBox errMsg;
        errMsgInit(errMsg, "The process crashed.");
        errMsg.exec();
        return;
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath() + "/generated_output.txt"));
}
