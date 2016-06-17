//
//  student_class.cpp
//  学生成绩
//
//  Created by 孙昊 on 16/5/30.
//  Copyright ? 2016年 孙昊. All rights reserved.
//

#include <iostream>
#include "Student.h"

Student::Student() {
    name = "no name";
    for (int i=1; i<5; i++) {
        subject[i] = -1;
    }
    ID_number = 0;
    average = -1;
    max_of_all_subject_grade = -1;
}

Student::Student(const string& input_val_name,long long number, float input_val_subject[5]) {
    name = input_val_name;
    for (int i=1; i<5; i++) {
        subject[i] = input_val_subject[i];
    }
    ID_number = number;
    average = cal_average();
    //找最高分
    float max = 0;
    for (int i=1; i<5; i++) {
        if (subject[i] > max) {
            max = subject[i];
        }
    }
    max_of_all_subject_grade = max;
    //找最高分儿科目名称
    for (int i=1; i<5; i++) {
        if (subject[i] == max) {
            max_of_all_subject_name[i] = 1;
        }
    }
}

Student::~Student() {
    ;
}

string Student::val_name() {
    return name;
}

float Student::val_subject_1() {
    return subject[1];
}

float Student::val_subject_2() {
    return subject[2];
}

float Student::val_subject_3() {
    return subject[3];
}

float Student::val_subject_4() {
    return subject[4];
}

long long Student::val_ID_number() {
    return ID_number;
}

float Student::val_average() {
    return average;
}

char* Student::val_max_of_all_subject_name() {
    return max_of_all_subject_name;
}

float Student::val_max_of_all_subject_grade(){
    return max_of_all_subject_grade;
}