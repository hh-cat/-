//
//  operation.hpp
//  学生成绩
//
//  Created by 孙昊 on 16/5/30.
//  Copyright ? 2016年 孙昊. All rights reserved.
//

#ifndef operation_h
#define operation_h

#include <iostream>
#include "Student.h"
#include <vector>

using std::vector;

struct student{
    vector<Student> the_grade_of_student;
    string subject_name[5];
    int count_of_records;
};

void show_the_copyright(void);//显示版权信息
bool check_the_initial_password(void);//检查初始密码
void clear_the_screen(void);//清屏
void print_the_primary_menu(void);//显示主菜单
int maximum_name_length(struct student& data);
int accept_the_input_int(int begin, int end);//接受 begin 到 end 之间的合法输入(int类型)
float accept_the_input_grade(int begin, int end);//接受 begin 到 end 之间的合法输入(float类型)
void lead_in_grade(struct student& data);//导入成绩
void modify_the_record(void);//增改记录
void show_the_grade_of_all_student(struct student& data);//显示成绩
void analyse_the_grade(struct student& data);//分析成绩
void find_the_record_of_grade(struct student& data);//查询成绩
void modify_the_initial_password(void);//修改密码
void save_all_the_record_of_grade(void);//保存成绩
void show_the_info_of_student(struct student& data, int the_number, int max_retraction);//输出单条学生成绩记录

#endif /* operation_h */
