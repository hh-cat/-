//
//  main.cpp
//  学生成绩
//
//  Created by 孙昊 on 16/5/30.
//  Copyright ? 2016年 孙昊. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Student.h"
#include "operation.h"

using namespace std;
string the_initial_password = "hello,sunhao";

int main(int argc, const char * argv[]) {
    student first;
	int selection;
	
//    if (check_the_initial_password() == false) {
//        exit(1);
//    }
    
    while (1) {
        print_the_primary_menu();
        selection = accept_the_input_int(0, 6);
        
        if (selection == 1) {
            lead_in_grade(first);
        }
        else if (selection == 4) {
            analyse_the_grade(first);
        }
        else if (selection == 5) {
            find_the_record_of_grade(first);
        }
        else if (selection == 6) {
            modify_the_initial_password();
        }
    }
    
    return 0;
}
