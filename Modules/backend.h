#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtDebug>
#include <QFile>
using namespace std;

class decimal{
public:

    QString num="";
    long long unsigned comma=0;
    decimal(QString num1, long long unsigned comma1){
        if (comma1==0)
        {
            num1+=".";
        }
        num=num1;
        comma=comma1;
    }
};

class fraction{
public:
    QString num;
    QString den;

    fraction(QString num1, QString den1)
    {
        num=num1;
        den=den1;
    }

};


class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mainString READ mainString WRITE setMainString NOTIFY mainStringChanged FINAL)
public:
    explicit Backend(QObject *parent = nullptr);

    static void rem_lead_zero(QString &s);
    static void rem_end_zero(QString &s);
    static bool is_greater(QString a, QString b);
    static bool is_less_than(QString a, QString b);
    static QString whole_part(QString s);
    static bool is_whole(QString s);
    static QString whole_vers(QString s);
    static bool bigger_pemdas(const QString s1, const QString s2);
    static bool isUnary(const QString s);

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

    static QString add_whole(QString s1, QString s2);
    static QString sub_whole(QString s1, QString s2);
    static decimal add_dec(decimal a, decimal b);
    static decimal sub_dec(decimal a, decimal b);
    static QString norm_mult(QString a, QString b);
    static decimal norm_mult_dec(decimal a, decimal b);
    static QString kar_mult(QString a, QString b);
    static QString pow(QString a, long long int b);
    static decimal pow_dec(decimal a, long long unsigned b);
    static QString basic_mod(QString a, QString b);
    static QString div2(QString n);
    static QString div_whole(QString a, QString b);
    static pair<QString,QString> fib_luc(long long unsigned n);
    static QString fib(long long unsigned n);
    static QString luc(long long unsigned n);
    static long long unsigned count_fact(long long unsigned a, long long unsigned b);
    static QString fact(long long unsigned n);
    static QString perfect_number(long long unsigned n);
    static QString calc_e(int limit);
    static pair<QString,QString> fast_calc_e_helper(QString a, QString b);
    static QString fast_calc_e(long long unsigned limit);
    static vector<QString> collatz(QString n);

    static QString final_eval(QString s1, QString s2, QString op);
    static Q_INVOKABLE QString expr_eval(QString s);
signals:
    void mainStringChanged();
private:
    QString m_mainString;
};

#endif // BACKEND_H
