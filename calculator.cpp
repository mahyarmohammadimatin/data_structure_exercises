#include <iostream>
#include<string>
#include<iomanip>
using namespace std;

int abs(int a){
    if(a<0) return -1*a;
    return a;
}

class CharStack{
public:
    CharStack(int n){
        stSize=n;
        p=new char [n];
        for(int i=0;i<n;i++) p[i]='_';
    }
    void push(char a){
        char * temp = new char [stSize];
        for(int i=1;i<stSize;i++) temp[i]=p[i-1];
        temp[0]=a;
        delete [] p;
        p=temp;
    }
    char pop(){
        char c;
        char * temp = new char [stSize];
        for(int i=0;i<stSize-1;i++) temp[i]=p[i+1];
        temp[stSize-1]='-';
        c=p[0];
        delete [] p;
        p=temp;
        return c;
    }
    char top() {return p[0];}
private:
    char * p;
    int stSize=0;
};

class DoubleStack{
public:
    DoubleStack(int n){
        stSize=n;
        p=new double [n];
        for(int i=0;i<n;i++) p[i]=3.14;
    }
    void push(double a){
        double * temp = new double [stSize];
        for(int i=1;i<stSize;i++) temp[i]=p[i-1];
        temp[0]=a;
        delete [] p;
        p=temp;
    }
    double pop(){
        double c;
        double * temp = new double [stSize];
        for(int i=0;i<stSize-1;i++) temp[i]=p[i+1];
        temp[stSize-1]=3.14;
        c=p[0];
        delete [] p;
        p=temp;
        return c;
    }
    double top() {return p[0];}
private:
    double * p;
    int stSize=0;
};

int value(char a){ //return value of operator
    if(a=='*' || a=='/') return 2;
    if(a=='+' || a=='-') return 1;
    return 0;
}

string postfix(string s);
int intMaker(char c);
double calc(double,double,char);
double calculate(string s);

int main(){
    int n;cin>>n;
    string * input = new string [n];
    for(int i=0;i<n;i++) cin>>input[i];
    for(int i=0;i<n;i++){
        cout<<postfix(input[i])<<endl;
        cout<<fixed<<setprecision(3)<<calculate(input[i])<<endl;
    }
}


string postfix(string s){
    CharStack mySt(s.size());
    string res="";
    for(int i=0;i<s.size();i++){
        switch(s[i]){
            case '+':case '-':case '*':case '/':{
                if(value(mySt.top())<value(s[i])) mySt.push(s[i]);
                else{
                    while(value(mySt.top())>=value(s[i])) res+=mySt.pop();
                    mySt.push(s[i]);
                }
                break;
            }
            case '(':{
                mySt.push(s[i]);
                break;
            }
            case ')':{
                while(mySt.top()!='(') res+=mySt.pop();
                mySt.pop();
                break;
            }
            default:{
                res+=s[i];
                break;
            }
        }
    }
    while(mySt.top()!='_') res+=mySt.pop();
    return res;
}


double calculate(string s){
    CharStack oprtSt(s.size());
    DoubleStack valueSt(s.size());

    for(int i=0;i<s.size();i++){
        switch(s[i]){
            case '+':case '-':case '*':case '/':{
                while(oprtSt.top()!='_' && value(oprtSt.top())>=value(s[i])){
                    valueSt.push(calc(valueSt.pop(),valueSt.pop(),oprtSt.pop()));
                }
                oprtSt.push(s[i]);
                break;
            }
            case '(':{
                oprtSt.push(s[i]);
                break;
            }
            case ')':{
                while(oprtSt.top()!='('){
                    valueSt.push(calc(valueSt.pop(),valueSt.pop(),oprtSt.pop()));
                }
                oprtSt.pop();
                break;
            }
            default:{
                valueSt.push(intMaker(s[i]));
                break;
            }
        }
    }
    while(oprtSt.top()!='_'){
        valueSt.push(calc(valueSt.pop(),valueSt.pop(),oprtSt.pop()));
    }
    return valueSt.top();
}

double calc(double a,double b,char oprt){
    switch(oprt){
        case '+':{
            return a+b;
        }
        case '-':{
            return a-b;
        }
        case '*':{
            return a*b;
        }
        case '/':{
            return a/b;
        }
    }
}

int intMaker(char c){
    for(int i=0;i<10;i++) if("0123456789"[i]==c) return i;
}
