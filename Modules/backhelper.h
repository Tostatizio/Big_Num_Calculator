#ifndef BACKHELPER_H
#define BACKHELPER_H

#include <QObject>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QProcess>
#include <QCoreApplication>
#include <QMessageBox>

class BackHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mainString READ mainString WRITE setMainString NOTIFY mainStringChanged FINAL)
public:
    explicit BackHelper(QObject *parent = nullptr);

    Q_INVOKABLE void useCalculatorCpp();
    void errMsgInit(QMessageBox &errMsgBox, QByteArray err);

    QString mainString() const{
        return m_mainString;
    }
    void setMainString(QString s){
        m_mainString = s;
        emit mainStringChanged();
    }
    Q_INVOKABLE void insertMainString(long long unsigned pos, QString s){
        m_mainString.insert(pos, s);
        emit mainStringChanged();
    }
    Q_INVOKABLE void removeMainString(long long unsigned pos, long long unsigned q){
        m_mainString.replace(pos, q, "");
        emit mainStringChanged();
    }

signals:
    void mainStringChanged();

private:
    QString m_mainString;
};

#endif // BACKHELPER_H
