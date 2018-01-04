
//
// Created by isavillamiel on 12/7/17.
//
#include "Parse.h"
#include "actions.h"
vector<vector<String>>file;
vector<String>OpMap;
map<String,int>VarMap;

void InitMap(void){
    OpMap.push_back("*");
    OpMap.push_back("/");
    OpMap.push_back("+");
    OpMap.push_back("-");
    OpMap.push_back("==");
    OpMap.push_back("~");
    OpMap.push_back("!");
    OpMap.push_back("!=");
    OpMap.push_back(">");
    OpMap.push_back("<");
    OpMap.push_back("//");
    OpMap.push_back("%");
    OpMap.push_back("&&");
    OpMap.push_back("||");
    OpMap.push_back("<=");
    OpMap.push_back(">=");
}

bool isOper(String& str){
    vector<String>::iterator OperatorsIt;
    for(OperatorsIt = OpMap.begin(); OperatorsIt != OpMap.end(); OperatorsIt++){
        if(str == OperatorsIt->c_str()){
            return true;
        }
    }
    return false;
}
bool isNum(const char* str){
    for(int i = 0; str[i] != 0; i++){
        if(str[i] > '9' || str[i]<'0')
            return false;
    }
    return true;
}
int doOp(int var, int var2, const String& operand) {
    if (operand == "*"){
        return (var*var2);
    }
    if (operand == "/"){
        return (var/var2);
    }
    if (operand == "+"){
        return (var + var2);
    }
    if (operand == "-"){
        return (var - var2);
    }
    if (operand == "=="){
        return (var == var2);
    }
    if (operand == "!="){
        return (var != var2);
    }
    if (operand == ">"){
        return (var > var2);
    }
    if (operand == "<"){
        return (var < var2);
    }
    if (operand == "%"){
        return (var % var2);
    }
    if (operand == "&&"){
        return (var && var2);
    }
    if (operand == "||"){
        return (var || var2);
    }
    if (operand == "<="){
        return (var <= var2) ? 1 : 0;
    }
    if (operand == ">="){
        return (var >= var2) ? 1 : 0;
    }
    return 0;
}
int doOp1(int varA, const String& operand){
    if(operand == "~"){
        return -varA;
    }
    if (operand == "!"){
        return !varA;
    }
    return 0;

}

int myAtoi(const char *str) {
    int res = 0;
    int i = 0;

    for (; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';

    return res;
}

class PolishNode{
public:
    bool isOperator;
    int num;
    String oper;

    PolishNode(){
        num = 0;
        oper = "";
        isOperator = false;
    }
};
int processOut(int x, int start,
               vector<vector<String>>& file,
               map<String,int>&VarMap) {
    vector<PolishNode> reverse;
    for (int b = start; b < file[x].size(); b++) {
        PolishNode hey;
        if (isNum(file[x][b].c_str())) {
            hey.isOperator = false;
            hey.num = myAtoi(file[x][b].c_str());
        } else if (isOper(file[x][b])) {   // it won't find the operator
            hey.isOperator = true;
            hey.oper = file[x][b];
        } else {
            hey.isOperator = false;
            hey.num = VarMap[file[x][b]];
        }
        reverse.push_back(hey);
    }

    stack<int> expression;
    int result;

    for(int i = reverse.size() - 1; i >= 0; i--){
        if(reverse[i].isOperator){
            if(reverse[i].oper == "!" || reverse[i].oper == "~"){
                int pop1 = expression.top(); expression.pop();
                expression.push(doOp1(pop1, reverse[i].oper));
            } else {
                int pop1 = expression.top(); expression.pop();
                int pop2 = expression.top(); expression.pop();
                expression.push(doOp(pop1, pop2, reverse[i].oper));
            }
        } else {
            expression.push(reverse[i].num);
        }
    }
    result = expression.top();
    return result;
}
int processDo(int x, int start,
               vector<vector<String>>& file){
    int here = x;
    int end = 0;
    // int ret = processOut(x,start,file,VarMap);
    while(processOut(here,start,file,VarMap)){
        map<String, int>::iterator VarIt;
        if (file[x][0] == "text") {
            cout << file[x][1].c_str();
            x++;
        } else if (file[x][0] == "var") {
            VarIt = VarMap.find(file[x][1]);
            String variable = file[x][1];
            if (VarIt != VarMap.end()) {
                cout << file[x][1].c_str() << " incorrectly reinitialized" << endl;
            }
            if (isNum(file[x][2].c_str())) {
                VarMap[variable] = myAtoi(file[x][2].c_str());
            } else if (isOper(file[x][2])) {
                VarMap[variable] = processOut(x, 2, file, VarMap);
            } else { VarMap[variable] = VarMap[file[x][3]]; }
            x++;
        } else if (file[x][0] == "set") {
            String variable = file[x][1];
            VarIt = VarMap.find(file[x][1]);
            if (VarIt == VarMap.end()) {
                cout << file[x][1].c_str() << " not declared" << endl;
            }
            if (isNum(file[x][2].c_str())) {
                VarMap[variable] = myAtoi(file[x][2].c_str());
            } else if (VarMap.find(file[x][2]) != VarMap.end()) {
                VarMap[variable] = VarMap[file[x][2]];
            } else { VarMap[variable] = processOut(x, 2, file, VarMap); }
            x++;
        } else if (file[x][0] == "output") {
            if (isNum(file[x][1].c_str())) {
                cout << file[x][1].c_str();
            } else if (VarMap.find(file[x][1]) != VarMap.end()) {
                cout << VarMap[file[x][1]];
            } else { cout << processOut(x, 1, file, VarMap); }
            x++;
        }
        else if(file[x][0] == "od"){
            x = here;
        }else x++;
    }
    while(file[x][0] != "od"){
        x++;
    }
    end = x;
    return end;
}
int processIf(int x, int start,map<String,int>& VarMap, vector<vector<String>>file) {
    int ret = processOut(x, start, file, VarMap);
    int erase_start = x;
    if (ret == 0) {
        while (file[x][0] != "else") {      // this is (if exp) is false
            x++;                            // || file[x][0] != "fi"
        }
    }
    x++;
    while (file[x][0] != "fi") {
        if(ret != 0){
            if(file[x][0] == "else"){
                while(file[x][0] != "fi"){
                    x++;
                }
                int erase_end = x;
                return erase_end;
            }
        }
        map<String, int>::iterator VarIt;
        if (file[x][0] == "text") {
            cout << file[x][1].c_str();
            x++;
        } else if (file[x][0] == "var") {
            VarIt = VarMap.find(file[x][1]);
            String variable = file[x][1];
            if (VarIt != VarMap.end()) {
                cout << file[x][1].c_str() << " incorrectly reinitialized" << endl;
            }
            if (isNum(file[x][2].c_str())) {
                VarMap[variable] = myAtoi(file[x][2].c_str());
            } else if (isOper(file[x][2])) {
                VarMap[variable] = processOut(x, 2, file, VarMap);
            } else { VarMap[variable] = VarMap[file[x][3]]; }
            x++;
        } else if (file[x][0] == "set") {
            String variable = file[x][1];
            VarIt = VarMap.find(file[x][1]);
            if (VarIt == VarMap.end()) {
                cout << file[x][1].c_str() << " not declared" << endl;
            }
            if (isNum(file[x][2].c_str())) {
                VarMap[variable] = myAtoi(file[x][2].c_str());
            } else if (VarMap.find(file[x][2]) != VarMap.end()) {
                VarMap[variable] = VarMap[file[x][2]];
            } else { VarMap[variable] = processOut(x, 2, file, VarMap); }
            x++;
        } else if (file[x][0] == "output") {
            if (isNum(file[x][1].c_str())) {
                cout << file[x][1].c_str();
            } else if (VarMap.find(file[x][1]) != VarMap.end()) {
                cout << VarMap[file[x][1]];
            } else { cout << processOut(x, 1, file, VarMap); }
            x++;
        }
        else if(file[x][0] == "else"){
            while(file[x][0] != "fi"){
                x++;
            }
        }

    }
    return x;
}
void processVector(vector<vector<String>>file, map<String,int>& VarMap){
    vector<String>::iterator iterator;
    map<String,int>::iterator VarIt;

    for(int x = 0; x < file.size(); x++) {
        if (file[x][0] == "text") {
            cout << file[x][1].c_str();
        } else if (file[x][0] == "var") {
            VarIt = VarMap.find(file[x][1]);
            String variable = file[x][1];
            if (VarIt != VarMap.end()) {
                cout << file[x][1].c_str() << " incorrectly reinitialized" << endl;
            }
            if(isNum(file[x][2].c_str())){
                VarMap[variable] = myAtoi(file[x][2].c_str());
            }
            else if(isOper(file[x][2])){
                VarMap[variable] = processOut(x,2,file,VarMap);
            }
            else{ VarMap[variable] = VarMap[file[x][3]]; }

        } else if (file[x][0] == "set") {
            String variable = file[x][1];
            VarIt = VarMap.find(file[x][1]);
            if (VarIt == VarMap.end()) {
                cout << file[x][1].c_str() << " not declared" << endl;}
            if (isNum(file[x][2].c_str())) {
                VarMap[variable] = myAtoi(file[x][2].c_str());
            } else if (VarMap.find(file[x][2]) != VarMap.end()) {
                VarMap[variable] = VarMap[file[x][2]];
            } else{ VarMap[variable] = processOut(x,2,file,VarMap); }

        } else if (file[x][0] == "output") {
            if (isNum(file[x][1].c_str())) {
                cout << file[x][1].c_str();
            } else if (VarMap.find(file[x][1]) != VarMap.end()) {
                cout << VarMap[file[x][1]];
            } else { cout << processOut(x,1,file,VarMap); }
        } else if (file[x][0] == "do"){
            x = processDo(x,1,file);
        }
        else if (file[x][0] == "if") {
            if(file[x+1][0] == "else" || file[x+1][0] == "fi"){
            }
            else{
                x = processIf(x,1,VarMap,file);
            }
        }
        else return;
    }
}



void run(){
    InitMap();
    do{
        processFile(file);
    } while(next_token_type != END);
    processVector(file,VarMap);
    OpMap.clear();
    file.clear();
    VarMap.clear();
}
int main(){
    set_input("test_grader.blip");
    run();
//    set_input("test3.blip");
//    run();
//    set_input("test6.blip");
//    run();
//    set_input("test7.blip");
//    run();
}
