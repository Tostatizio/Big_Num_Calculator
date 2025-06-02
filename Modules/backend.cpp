#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>
using namespace std;

void rem_end_zero(string &s){
    while(s.back()=='0')
        s.pop_back();
}
void rem_lead_zero(string &s){
    long long unsigned size = s.size();
    if (s[0] != '0')
        return;
    for (long long i = 1; i < size; i++)
        if (s[i] != '0'){
            s = s.substr(i, size - i);
            return;
        }
    s = "";
}
bool is_greater(string a, string b){
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
bool is_less_than(string a, string b){
    if(a.size()!=b.size())
        return (a.size()<b.size());

    long long unsigned size=a.size();
    for (long long i=0; i<size; i++)
    {
        if(a[i]!=b[i])
            return (a[i]<b[i]);
    }
    return false;
}
string whole_part(string s){
    long long unsigned size=s.size();
    for(long long i=1; i<size; i++)
    {
        if(s[i]=='.')
            return s.substr(0,i);
    }
    return s;
}
bool is_whole(string s){
    long long unsigned size=s.size();
    for(long long i=1; i<size; i++)
    {
        if(s[i]=='.')
            return false;
    }
    return true;
}
string whole_vers(string s){
    string ris="";
    for(long long i=s.size()-1; i>=0; --i)
        if(s[i]=='.')
            continue;
        else
            ris+=s[i];
    return ris;
}
bool bigger_pemdas(const string s1, const string s2){
    if (s1 == "+" || s1 == "-"){
        if (s2 != "(")
            return false;
    }
    else if (s1 == "*" || s1 == "/"){
        if (s2 == "log" || s2 == "!")
            return false;
        else if (s2 == "^" || s2 == "√")
            return false;
        else if (s2 == "*" || s2 == "/")
            return false;
    }
    else if (s1 == "^" || s1 == "√"){
        if (s2 == "log" || s2 == "!")
            return false;
        else if (s2 == "^" || s2 == "√")
            return false;
    }
    return true;
}
bool isUnary(const string s){
    if (s == "!" || s == "√" || s == "log" || s == "ln")
        return true;
    return false;
}
bool isOperator(const string op){
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "mod" || op == "!" || 
    op == "log" || op == "ln" || op == "^" || op == "√"){
        return true;
    }
    return false;
}

string add_whole(string s1, string s2){
    long long carry = 0;
    string result;
    long long i = s1.length() - 1, j = s2.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        long long sum = carry;
        if (i >= 0) sum += s1[i--] - '0';
        if (j >= 0) sum += s2[j--] - '0';
        result += sum % 10 + '0';
        carry = sum / 10;
    }

    reverse(result.begin(), result.end());
    return result;
}
string sub_whole(string s1, string s2){
    long long borrow = 0;
    string result;
    long long i = s1.length() - 1, j = s2.length() - 1;

    while (i >= 0) {
        long long diff = s1[i] - '0' - (j >= 0 ? s2[j] - '0' : 0) - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back((diff + '0'));
        i--;
        j--;
    }

    reverse(result.begin(), result.end());
    rem_lead_zero(result);
    return result;
}
// decimal add_dec(decimal a, decimal b);
// decimal sub_dec(decimal a, decimal b);
string norm_mult(string a, string b){
    if (a=="0" || b=="0"){
        return "0";
    }
    long long m = a.size() - 1, n = b.size() - 1, carry = 0;
    string product;
    long long temp1=m+n;
    long long temp2;
    for (long long i=0; i<=temp1 || carry; ++i) {
        temp2=min(i,m);
        for (long long j=max((long long)0, i-n); j<=temp2; ++j)
            carry += (a[m-j] - '0') * (b[n-i+j] - '0');
        product += (char)(carry % 10 + '0');
        carry /= 10;
    }
    reverse(begin(product), end(product));
    return product;
}
// decimal norm_mult_dec(decimal a, decimal b);
string kar_mult(string a, string b){
    if (a.length() > b.length())
        swap(a, b);

    long long n1 = a.length(), n2 = b.length();

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

    string al=a.substr(0,n1/2), ar=a.substr(n1/2, n1/2), bl=b.substr(0,n1/2), br=b.substr(n1/2, n1/2);

    string p = kar_mult(al, bl);

    string q = kar_mult(ar, br);

    string temp1=add_whole(al, ar), temp2=add_whole(bl, br);

    string r = sub_whole(
        kar_mult(
            temp1,
            temp2
            ),
        add_whole(p, q)
        );

    p+=string(n1,'0');

    r+=string(n1/2,'0');

    string ans = add_whole(p, add_whole(q, r));


    rem_lead_zero(ans);

    return ans;
}
string pow(string a, long long b){
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
// decimal pow_dec(decimal a, long long unsigned b);
string basic_mod(string a, string b){
    while(is_greater(a,b))
        a=sub_whole(a,b);
    return a;
}
string div2(string n){
    if(n.size()<3){
        string temp = to_string(stoll(n)/(long long)2);
        return temp;
    }
    long long unsigned size=n.size();
    long long num=0;
    long long pos=0;

    if(n[0]-'0'<=1)
        pos=2;
    else
        pos=1;

    string ris="";
    num=stoll(n.substr(0,pos));

    while(pos<size)
    {
        num=10*num+n[pos]-'0';
        ris+=to_string(num/2);
        num=num%2;
        pos++;
    }
    return ris;
}
string div_whole(string a, string b)
{
    if (a.size() < b.size())
        return "0";

    string divisors[10];
    string temp;
    long long unsigned size_b = b.size(),
                       size_a = a.size();

    for (long long i = 0; i < 10; i++){
        divisors[i] = norm_mult(string(1, (char)(i + '0')), b);
    }
    
    string curr = a.substr(0, size_b), ris = "";
    long long unsigned pos = size_b;
    if (is_greater(b, curr) && size_b != size_a){
        curr+=a[size_b];
        pos++;
    }
    while(pos < size_a){
        if (curr == "")
            curr = "0";
        auto it = lower_bound(divisors, divisors+10, curr, is_less_than);
        // cout << "pos: " << divi_pos << " it=" << *it << endl;
        if (it == divisors+10){
            ris+="9";
            curr = sub_whole(curr, divisors[9]);
        }
        else{
            string divi = *it;
            ptrdiff_t divi_pos = it-divisors;
            if (is_greater(divi, curr))
                ris+=string(1, divi_pos - 1 + '0');
            else
                ris+=string(1, divi_pos + '0');
        
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

    if (curr == "")
            curr = "0";
    auto it = lower_bound(divisors, divisors+10, curr, is_less_than);
    if (it == divisors+10)
        ris+="9";
    else{
        string divi = *it;
        ptrdiff_t divi_pos = it-divisors;
        if (is_greater(divi, curr))
            ris+=string(1, divi_pos - 1 + '0');
        else
            ris+=string(1, divi_pos + '0');
    }
    return ris;
}
// pair<string,string> fib_luc(long long unsigned n);
// string fib(long long unsigned n);
// string luc(long long unsigned n);
long long unsigned count_fact(long long unsigned a, long long unsigned b){
    long long unsigned sum=0;
    while(b>=1)
    {
        sum+=b/a;
        b/=a;
    }
    return sum;
}
string fact(const long long unsigned n){
    vector<bool> arr(n+1, true);
    arr[0]=false;
    arr[1]=false;
    for(long long i=2; i*i<=n; i++)
    {
        if(arr[i])
        {
            for(long long j=i*i; j<=n; j+=i)
            {
                arr[j]=false;
            }

        }
    }

    string ris="1";
    for(long long i=0; i<=n; i++)
    {
        if(arr[i])
        {
            ris=norm_mult(ris,pow(string(1, i + '0'), count_fact(i,n)));
        }
    }
    return ris;

}
// string perfect_number(long long unsigned n);
string calc_e(long long limit){
    string num="1", den=fact(limit);
    string temp="1";
    for(long long i=limit; i>0; i--)
    {
        temp=norm_mult(temp, string(1, i + '0'));
        num=add_whole(num,temp);
    }
    return div_whole(num+string(4*limit,'0'),den);
}
pair<string,string> fast_calc_e_helper(string a, string b){
    if (b == add_whole(a, "1")){
        return {"1", b};
    }
    else{
        string m = div2(add_whole(a, b));
        pair<string,string> temp1=fast_calc_e_helper(a,m), temp2=fast_calc_e_helper(m,b);
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
string fast_calc_e(long long unsigned limit){
    pair<string,string> temp = fast_calc_e_helper("0", to_string(limit));
    return div_whole(temp.first + string(4*limit,'0'), temp.second);
}
// vector<string> collatz(string n);

string final_eval(string s1, string s2, string op){
    //s2 for unary operators
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
    //     return log_10(s2);
    // }
    // else if (op == "ln"){
    //     return log_e(s2);
    // }
    else if (op == "!"){
        return fact(stoull(s2));
    }
    else if (op == "^"){
        return pow(s1, stoll(s2));
    }
    // else if (op == "√"){
    //     return radix(s2);
    // }
    else{
        throw runtime_error("Unknown operator."); //fix this long longo an error dialog
    }
}

string expr_eval(string s){
    stack<string> values, ops;
    bool precIsOp = false;
    try{
        for (long long unsigned i = 0, size = s.size(); i < size; i++){
            if (s[i] == ' ')
                continue;
            else if (s[i] == '('){
                if (i > 0 && isdigit(s[i-1])){
                    while (!ops.empty() && !bigger_pemdas("*", ops.top())){
                        string op = ops.top();
                        ops.pop();

                        string val2 = values.top();
                        values.pop();

                        string val1 = "";
                        if (!isUnary(op)){
                            val1 = values.top();
                            values.pop();
                        }

                        values.push(final_eval(val1, val2, op));
                    }
                    ops.push("*");
                }
                ops.push("(");
                precIsOp = true;
            }
            else if (isdigit(s[i])){
                string temp;
                bool dot = false;

                temp += s[i];
                i++;
                while (i < size && (isdigit(s[i]) || s[i] == '.')){
                    if (s[i] == '.'){
                        if (!dot)
                            dot = true;
                        else
                            throw runtime_error("Too many dots."); //try/catch, dialog
                    }

                    temp += s[i];

                    i++;
                }

                i--;
                values.push(temp);
                precIsOp = false;
            }
            else if (s[i] == ')'){
                if (ops.empty())
                    throw runtime_error("Mismatched parenthesis.");
                while(ops.top() != "("){
                    if (ops.empty())
                        throw runtime_error("Mismatched parenthesis.");

                    string op = ops.top();
                    ops.pop();

                    string val2 = values.top();
                    values.pop();

                    string val1 = "";
                    if (!isUnary(op)){
                        val1 = values.top();
                        values.pop();
                    }

                    values.push(final_eval(val1, val2, op));
                }
                ops.pop();
                precIsOp = false;
            }
            else{
                if (s[i] == 'l'){
                    while (!ops.empty() && !bigger_pemdas("log", ops.top())){
                        if (s[i] == '^' && ops.top() == "^")
                            break;

                        string op = ops.top();
                        ops.pop();

                        string val2 = values.top();
                        values.pop();

                        string val1 = "";
                        if (!isUnary(op)){
                            val1 = values.top();
                            values.pop();
                        }

                        values.push(final_eval(val1, val2, op));
                    }
                    if (s[i+1] == 'n'){
                        ops.push("ln");
                    }
                    else if (s[i+1] == 'o' && s[i+2] == 'g'){
                        ops.push("log"); //log(log(n)) da fixare
                    }
                    else throw runtime_error("Unknown operator.");
                }
                else{
                    if (!isOperator(string(1, s[i])))
                        throw runtime_error("Unknown operator.");
                    if (precIsOp)
                        throw runtime_error("Two or more operators in a row.");
                    while (!ops.empty() && !bigger_pemdas(string(1, s[i]), ops.top())){
                        if (s[i] == '^' && ops.top() == "^")
                            break;

                        string op = ops.top();
                        ops.pop();

                        string val2 = values.top();
                        values.pop();

                        string val1 = "";
                        if (!isUnary(op)){
                            val1 = values.top();
                            values.pop();
                        }

                        values.push(final_eval(val1, val2, op));
                    }
                    string temp{s[i]};
                    ops.push(temp);
                    if (s[i] != '!')
                        precIsOp = true;
                    else
                        precIsOp = false;
                }
            }
        }

        while(!ops.empty()){
            // if (values.size() == 1)
            //     qDebug() << "values.size() is one";
            if (ops.top() == "(" || ops.top() == ")")
                throw runtime_error("Mismatched parenthesis.");

            string op = ops.top();
            ops.pop();

            string val2 = values.top();
            values.pop();

            string val1 = "";
            if (!isUnary(op)){
                val1 = values.top();
                values.pop();
            }
            values.push(final_eval(val1, val2, op));
        }

        return values.top();
    }
    catch(const exception &err){
        cerr << err.what();
        return s;
    }
}

int main(){
    ofstream out("generated_output.txt");
    
    string s;
    cin >> s;
    out << expr_eval(s);

    out.close();

	return 0;
}
