#include "backend.h"
#include <stack>
#include <QMessageBox>

Backend::Backend(QObject *parent)
    : QObject{parent}
{
}

void Backend::rem_end_zero(QString &s){
    while(s.back()=='0')
        s.removeLast();
}
void Backend::rem_lead_zero(QString &s){
    long long unsigned size = s.size();
    if (s[0] != 0)
        return;
    for (int i = 1; i < size; i++)
        if (s[i] != '0'){
            s = s.sliced(i, size - i);
            return;
        }
    s = "";
}
bool Backend::is_greater(QString a, QString b){
    if(a.size()!=b.size())
        return (a.size()>b.size());

    long long unsigned size=a.size();
    for (long long unsigned i=0; i<size; i++)
    {
        if(a[i]!=b[i])
            return (a[i]>b[i]);
    }
    return false;
}
bool Backend::is_less_than(QString a, QString b){
    if(a.size()!=b.size())
        return (a.size()<b.size());

    long long unsigned size=a.size();
    for (int i=0; i<size; i++)
    {
        if(a[i]!=b[i])
            return (a[i]<b[i]);
    }
    return false;
}
QString Backend::whole_part(QString s){
    long long unsigned size=s.size();
    for(int i=1; i<size; i++)
    {
        if(s[i]=='.')
            return s.sliced(0,i);
    }
    return s;
}
bool Backend::is_whole(QString s){
    long long unsigned size=s.size();
    for(int i=1; i<size; i++)
    {
        if(s[i]=='.')
            return false;
    }
    return true;
}
QString Backend::whole_vers(QString s){
    QString ris="";
    for(int i=s.size()-1; i>=0; --i)
        if(s[i]=='.')
            continue;
        else
            ris+=s[i];
    return ris;
}
bool Backend::bigger_pemdas(const QString s1, const QString s2){
    if (s1 == "+" || s1 == "-"){
        if (s2 == "log" || s2 == "!")
            return false;
        else if (s2 == "^" || s2 == "√")
            return false;
        else if (s1 == "*" || s1 == "/")
            return false;
    }
    else if (s1 == "*" || s1 == "/"){
        if (s2 == "log" || s2 == "!")
            return false;
        else if (s2 == "^" || s2 == "√")
            return false;
    }
    else if (s1 == "^" || s1 == "√"){
        if (s2 == "log" || s2 == "!")
            return false;
    }
    return true;
}

QString Backend::add_whole(QString s1, QString s2){
    int carry = 0;
    QString result;
    int i = s1.length() - 1, j = s2.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += s1.sliced(i--, 1).toInt();
        if (j >= 0) sum += s2.sliced(j--, 1).toInt();
        result += (QChar)(sum % 10 + '0');
        carry = sum / 10;
    }

    reverse(result.begin(), result.end());
    return result;
}
QString Backend::sub_whole(QString s1, QString s2){
    int borrow = 0;
    QString result;
    int i = s1.length() - 1, j = s2.length() - 1;

    while (i >= 0) {
        int diff = s1[i].unicode() - '0' - (j >= 0 ? s2[j].unicode() - '0' : 0) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back((QChar)(diff + '0'));
        i--;
        j--;
    }

    reverse(result.begin(), result.end());
    rem_lead_zero(result);
    return result;
}
// decimal Backend::add_dec(decimal a, decimal b);
// decimal Backend::sub_dec(decimal a, decimal b);
QString Backend::norm_mult(QString a, QString b){
    if (a=="0" || b=="0"){
        return "0";
    }
    int m = a.size() - 1, n = b.size() - 1, carry = 0;
    QString product;
    int temp1=m+n;
    int temp2;
    for (int i=0; i<=temp1 || carry; ++i) {
        temp2=min(i,m);
        for (int j=max(0, i-n); j<=temp2; ++j)
            carry += (a[m-j].unicode() - '0') * (b[n-i+j].unicode() - '0');
        product += (QChar)(carry % 10 + '0');
        carry /= 10;
    }
    reverse(begin(product), end(product));
    return product;
}
// decimal Backend::norm_mult_dec(decimal a, decimal b);
QString Backend::kar_mult(QString a, QString b){
    if (a.length() > b.length())
        swap(a, b);

    int n1 = a.length(), n2 = b.length();

    if(n2>2*n1 && n2<1250)
        return norm_mult(a,b);

    while (n2 > n1) {
        a = "0" + a;
        n1++;
    }

    if (n1 <= 313)
    {
        rem_lead_zero(a);
        return norm_mult(a,b);
    }

    if (n1 % 2 == 1) {
        n1++;
        a = "0" + a;
        b = "0" + b;
    }

    QString al=a.sliced(0,n1/2), ar=a.sliced(n1/2, n1/2), bl=b.sliced(0,n1/2), br=b.sliced(n1/2, n1/2);

    QString p = kar_mult(al, bl);

    QString q = kar_mult(ar, br);

    QString temp1=add_whole(al, ar), temp2=add_whole(bl, br);

    QString r = sub_whole(
        kar_mult(
            temp1,
            temp2
            ),
        add_whole(p, q)
        );

    p+=QString(n1,'0');

    r+=QString(n1/2,'0');

    QString ans = add_whole(p, add_whole(q, r));


    rem_lead_zero(ans);

    return ans;
}
QString Backend::pow(QString a, long long int b){
    string ris="1";
    if(b==1)
        return a;
    else if(b==0)
        return "1";
    else if(b>=1){
        if(b%2==0)
            return pow(kar_mult(a,a),(b/2));
        else
            return norm_mult(a,pow(kar_mult(a,a),((b-1)/2)));
    }
    return "";
}
// decimal Backend::pow_dec(decimal a, long long unsigned b);
QString Backend::basic_mod(QString a, QString b){
    while(is_greater(a,b))
        a=sub_whole(a,b);
    return a;
}
QString Backend::div2(QString n){
    if(n.size()<3)
        return QString::number(n.toInt()/2);
    long long unsigned size=n.size();
    int num=0;
    int pos=0;

    if(n[0].unicode()-'0'<=1)
        pos=2;
    else
        pos=1;

    QString ris="";
    num=n.sliced(0,pos).toInt();

    while(pos<size)
    {
        num=10*num+n[pos].unicode()-'0';
        ris+=to_string(num/2);
        num=num%2;
        pos++;
    }
    return ris;
}
QString Backend::div_whole(QString a, QString b){
    if (a.size() < b.size())
        return "0";

    QString divisors[10];
    long long unsigned size_b = b.size(),
        size_a = a.size();

    for (int i = 0; i < 10; i++){
        divisors[i] = norm_mult((QChar)(i + '0'), b);
    }

    QString curr = a.sliced(0, size_b), ris = "";
    long long unsigned pos = size_b;
    if (is_greater(b, curr) && size_b != size_a){
        curr+=a[size_b];
        pos++;
    }
    while(pos < size_a){
        auto it = lower_bound(divisors, divisors+10, curr, is_less_than);
        // cout << "pos: " << divi_pos << " it=" << *it << endl;
        if (it == divisors+10){
            ris+="9";
            curr = sub_whole(curr, divisors[9]);
        }
        else{
            QString divi = *it;
            ptrdiff_t divi_pos = it-divisors;
            if (is_greater(divi, curr))
                ris+=to_string(divi_pos - 1);
            else
                ris+=to_string(divi_pos);

            if (divi_pos != 0 && divi_pos < 10){
                rem_lead_zero(curr);
                if (!is_greater(divi, curr))
                    curr = sub_whole(curr, divi);
                else
                    curr = sub_whole(curr, divisors[divi_pos-1]);
            }
            else if (curr == divi)
                curr = "0";
        }

        curr += a[pos];
        rem_lead_zero(curr);
        // cout << "curr: " << curr << " pos: " << pos << " ris: " << ris << endl;
        pos++;
    }

    auto it = lower_bound(divisors, divisors+10, curr, is_less_than);
    if (it == divisors+10)
        ris+="9";
    else{
        QString divi = *it;
        ptrdiff_t divi_pos = it-divisors;
        if (is_greater(divi, curr))
            ris+=to_string(divi_pos - 1);
        else
            ris+=to_string(divi_pos);
    }
    return ris;
}
// pair<QString,QString> Backend::fib_luc(long long unsigned n);
// QString Backend::fib(long long unsigned n);
// QString Backend::luc(long long unsigned n);
long long unsigned Backend::count_fact(long long unsigned a, long long unsigned b){
    long long unsigned sum=0;
    while(b>=1)
    {
        sum+=b/a;
        b/=a;
    }
    return sum;
}
QString Backend::fact(long long unsigned n){
    bool arr[n+1];
    fill(arr, arr+n+1, true);
    arr[0]=false;
    arr[1]=false;
    for(int i=2; i*i<=n; i++)
    {
        if(arr[i])
        {
            for(int j=i*i; j<=n; j+=i)
            {
                arr[j]=false;
            }

        }
    }

    QString ris="1";
    for(int i=0; i<=n; i++)
    {
        if(arr[i])
        {
            ris=norm_mult(ris,pow(QString::number(i), count_fact(i,n)));
        }
    }
    return ris;

}
// QString Backend::perfect_number(long long unsigned n);
QString Backend::calc_e(int limit){
    QString num="1", den=fact(limit);
    QString temp="1";
    for(int i=limit; i>0; i--)
    {
        temp=norm_mult(temp,QString::number(i));
        num=add_whole(num,temp);
    }
    return div_whole(num+QString(4*limit,'0'),den);
}
pair<QString,QString> Backend::fast_calc_e_helper(QString a, QString b){
    if (b == add_whole(a, "1")){
        return {"1", b};
    }
    else{
        QString m = div2(add_whole(a, b));
        pair<QString,QString> temp1=fast_calc_e_helper(a,m), temp2=fast_calc_e_helper(m,b);
        return {
            add_whole(
                kar_mult(
                    temp1.first,
                    temp2.second
                    ),
                temp2.first
                ),
            kar_mult(
                temp1.second,
                temp2.second
                )
        };
    }
}
QString Backend::fast_calc_e(long long unsigned limit){
    pair<QString,QString> temp = fast_calc_e_helper("0", QString::number(limit));
    return div_whole(temp.first + QString(4*limit,'0'), temp.second);
}
// vector<QString> Backend::collatz(QString n);

QString Backend::final_eval(QString s1, QString s2, QString op){
    if (op == "+")
        return add_whole(s1, s2);
    else if (op == "-"){
        return sub_whole(s1, s2);
    }
    else if (op == "*"){
        return kar_mult(s1, s2);
    }
    else if (op == "/"){
        return div_whole(s1, s2);
    }
    // else if (op == "log"){
    //     return log_10(s1);
    // }
    // else if (op == "ln"){
    //     return log_e(s1);
    // }
    else if (op == "!"){
        return fact(s1.toULongLong());
    }
    else if (op == "^"){
        return pow(s1, s2.toULongLong());
    }
    // else if (op == "√"){
    //     return radix(s1);
    // }
    else{
        throw("Unknown operator."); //fix this into an error dialog
    }
}

Q_INVOKABLE QString Backend::expr_eval(QString s){
    //multiple mismatched parenthesis
    stack<QString> values, ops;
    bool precIsOp = false;
    long long unsigned parenthesisCount = 0;
    for (long long unsigned i = 0, size = s.size(); i < size; i++){
        if (parenthesisCount < 0){
            throw("Mismatched parenthesis");
        }
        if (s[i] == '('){
            ops.push(s[i]);
            parenthesisCount++;
            precIsOp = false;
        }
        else if (s[i].isDigit()){
            QString temp;
            bool dot = false;

            temp += s[i];
            i++;
            while (i < size && (s[i].isDigit() || s[i] == '.')){
                if (s[i] == '.'){
                    if (!dot)
                        dot = true;
                    else
                        qDebug() << "too many dots"; //try/catch, dialog
                }

                temp += s[i];

                i++;
            }

            i--;
            values.push(temp);
            precIsOp = false;
        }
        else if (s[i] == ')'){
            parenthesisCount--;
            while(ops.top() != '('){
                QString val2 = values.top();
                values.pop();

                QString val1 = values.top();
                values.pop();

                QString t_op = ops.top();

                values.push(final_eval(val1, val2, t_op));
            }
            precIsOp = false;
        }
        else{
            if (precIsOp){
                throw("Two or more operators in a row.");
            }
            if (s[i] == 'l'){
                if (s[i+1] == 'n'){
                    ops.push("ln");
                }
                else if (s[i+1] == 'o' && s[i+2] == 'g'){
                    ops.push("log");
                }
            }
            else{
                while (!ops.empty() && !bigger_pemdas(s[i], ops.top())){
                    QString val2 = values.top();
                    values.pop();

                    QString val1 = values.top();
                    values.pop();

                    QString op = ops.top();
                    ops.pop();

                    values.push(final_eval(val1, val2, op));
                }
                ops.push(s[i]);
            }
            precIsOp = true;
        }
        // qDebug() << values.top() << " " << ops.top();
    }

    while(!ops.empty()){
        // if (values.size() == 1)
        //     qDebug() << "values.size() is one";

        QString val2 = values.top();
        values.pop();

        QString val1 = values.top();
        values.pop();

        QString op = ops.top();
        ops.pop();

        values.push(final_eval(val1, val2, op));
    }

    return values.top();
}
