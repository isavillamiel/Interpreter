//
// Created by isavillamiel on 12/7/17.
//

#ifndef PROJECT_9B_ACTIONS_H
#define PROJECT_9B_ACTIONS_H

#include "String.h"
#include "LinkedList.h"

#include <vector>
#include <map>
#include <stack>

using namespace std;

void processFile(vector<vector<String>>& file){
    read_next_token();
    if(next_token_type == SYMBOL){ skip_line();}
    else if(next_token_type == KEYWORD) {
        vector<String> lines;
        lines.push_back(next_token());
        if((String)next_token() != "fi" && (String)next_token() != "else"){
            read_next_token();
        }
        while(next_token_type != KEYWORD){
            lines.push_back(next_token());
            String readT = peek_next_token();
            if(readT!= "text" &&
               readT!= "output" &&
               readT!= "var" &&
               readT!= "set" &&
               readT!= "if" &&
               readT!= "do" &&
               readT!= "else" &&
               readT != "od" &&
               readT != "fi"){
                read_next_token();
                if(readT == "//"){ skip_line(); break;}
                if(next_token_type == END){break;}
            }
        }file.push_back(lines);
    }
}


#endif //PROJECT_9B_ACTIONS_H
