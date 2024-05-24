#include <bits/stdc++.h>
using namespace std;

bool isOperator(char op);
bool isOperator(string op);
int priorityOp(string op);
vector<string>convertStringToInfix(const string& str);
vector<string>infixToPostfix(vector <string> str);
int evaluatePostfix(vector<string> exp);

int main(){
    string str;
    getline(cin, str);
    vector <string> stck;
    stck = convertStringToInfix(str);
    stck = infixToPostfix(stck);
    cout<<evaluatePostfix(stck);
    return 0;
}

//Fungsi mengecek apakah operator versi char
bool isOperator(char op) {
    return (op == '*' || op == '/' || op == '+' || op == '-' || op == '%' || op == '(' || op == ')');
}

//Fungsi mengecek apakah operator versi string
bool isOperator(string op) {
    return (op == "*" || op == "/" || op == "+" || op == "-" || op == "%" || op == "(" || op == ")");
}

//Fungsi menentukan prioritas operator
int priorityOp(string op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

//Fungsi mengkonversi string ke infix
vector<string> convertStringToInfix(const string& str){
    vector <string> infix;
    for(size_t i = 0; i < str.size(); i++){
        string temp = "";
        if(str[i] == ' '){
            continue;
        }else if(str[0] == '-' && i == 0){
            temp = "-";
            i++;
            while(i < str.size() && !isOperator(str[i]) && str[i] != ' '){
                temp = temp + str[i];
                i++;
            }
            infix.push_back(temp);
            i--;
        }
        else if(!isOperator(str[i])){
            while(i < str.size() && !isOperator(str[i]) && str[i] != ' '){
                temp = temp + str[i];
                i++;
            }
            infix.push_back(temp);
            i--;
        }else if(isOperator(str[i])){
            temp = str[i];
            infix.push_back(temp);
            
        }
    }
    return infix;
}

//Fungsi mengkonversi ekspresi infix ke postfix
vector<string> infixToPostfix(vector<string> str) {
    stack<string> stk;
    vector<string> postfix;

    for (auto i : str) {
        if (!isOperator(i)) {
            postfix.push_back(i);
        } else if (i == "(") {
            stk.push(i);
        } else if (i == ")") {
            while (!stk.empty() && stk.top() != "(") {
                postfix.push_back(stk.top());
                stk.pop();
            }
            stk.pop(); // Pop "("
        } else if (isOperator(i)) {
            if (stk.empty() || stk.top() == "(") {
                stk.push(i);
            } else {
                while (!stk.empty() && stk.top() != "(" && priorityOp(i) <= priorityOp(stk.top())) {
                    postfix.push_back(stk.top());
                    stk.pop();
                }
                stk.push(i);
            }
        }
    }
    while (!stk.empty()) {
        postfix.push_back(stk.top());
        stk.pop();
    }
    return postfix;
}

//Fungsi mengevaluasi ekspresi postfix
int evaluatePostfix(vector<string> exp) {
    stack<int> stk;
    for(auto i : exp){
        if(!isOperator(i)){
            stk.push(stoi(i));
        }
        else if(isOperator(i)){
            int a , b;
            a = stk.top();
            stk.pop();
            b = stk.top();
            stk.pop();
            
            if(i == "*") stk.push(b * a);
            else if(i == "/") stk.push(b/a);
            else if(i == "%") stk.push(b%a);
            else if(i == "+") stk.push(b+a);
            else if(i == "-") stk.push(b-a);
        }
    }
    return stk.top();
}