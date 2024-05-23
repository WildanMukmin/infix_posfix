#include <bits/stdc++.h>
using namespace std;

bool isOperator(string op);
bool isOperator(char op);
vector<string> convertStringToInfix(const string& str);

int main(){
    string str; getline(cin, str);
    vector <string> infix = convertStringToInfix(str);
    for(auto i : infix) cout << i << " ";
    return 0;
}

// Fungsi untuk mengecek apakah ini operator
bool isOperator(string op){
    return (op == "*" || op == "/" || op == "%" || op == "+" || op == "-" || op == "(" || op == ")");
}
bool isOperator(char op){
    return (op == '*' || op == '/' || op == '%' || op == '+' || op == '-' || op == '(' || op == ')');
}

// FUngsi untuk mengkonversi string ke vektor infix
vector<string> convertStringToInfix(const string& str){
    vector <string> stck;
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
            stck.push_back(temp);
            i--;
        }
        else if(!isOperator(str[i])){
            while(i < str.size() && !isOperator(str[i]) && str[i] != ' '){
                temp = temp + str[i];
                i++;
            }
            stck.push_back(temp);
            i--;
        }else{
            temp = str[i];
            if(temp == "-" && (i == 0 || isOperator(str[i-1]) || str[i-1] == ' ' || str[i-1] == '(')) {
                if (i + 1 < str.size() && (isdigit(str[i+1]) || str[i+1] == '(')) {
                    stck.push_back("-1");
                    stck.push_back("*");
                } else stck.push_back(temp);
            }else stck.push_back(temp);
        }
    }   

    for(size_t i = 0; i < stck.size(); i++){
        if(stck[i] == "-" && isOperator(stck[i-1]) && isOperator(stck[i+1])){
            stck[i] = "-1";
            stck.insert(stck.begin() + 1 + i,"*");
            i++;
        }
        else if(stck[0] == "-" && isOperator(stck[i+1]) && i == 0){
            stck[i] = "-1";
            stck.insert(stck.begin() + 1 + i,"*");
            i++;
        }
    }
    return stck;
}