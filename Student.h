//
//  Header.h
//  学生成绩
//
//  Created by 孙昊 on 16/5/30.
//  Copyright ? 2016年 孙昊. All rights reserved.
//

#ifndef Student_h
#define Student_h

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    float subject[5];
    long long ID_number;
    float average;
    char max_of_all_subject_name[5] = {0};
    float max_of_all_subject_grade;
    float cal_average() {
        float ave;
        for (int i=1; i<5; i++) {
            ave += subject[i];
        }
        return ave/4.0;
    }
    
public:
    Student();
    Student(const string& name, long long number, float subject[5]);
    ~Student();
    
    string val_name();
    float val_subject_1();
    float val_subject_2();
    float val_subject_3();
    float val_subject_4();
    long long val_ID_number();
    float val_average();
    char* val_max_of_all_subject_name();
    float val_max_of_all_subject_grade();
};


#endif /* Student_h */
