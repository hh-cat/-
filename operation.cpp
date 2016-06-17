//
//  operation.cpp
//  学生成绩
//
//  Created by 孙昊 on 16/5/30.
//  Copyright ? 2016年 孙昊. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "operation.h"
#include "Student.h"

extern string the_initial_password;


//返回 begin 和 end 之间的整数,排除不良输入
int accept_the_input_int(int begin, int end) {
    int input;
    
    while (1) {
        cin >> input;
        if (!cin) {//输入不合适的类型,例如字符
            cin.clear();
            while (cin.get() != '\n') {
                continue;
            }
        }
        else {
            if (cin.get()=='\n' && input>=begin && input<=end) {
                return input;
            }
            else {//输入的数据不合法,例如"-3"/"2a"
                while (cin.get() != '\n') {
                    continue;
                }
            }
        }
    }
}

//接受 begin 到 end 之间的浮点数,用于接受成绩参数,排除不良输入
float accept_the_input_grade(int begin, int end) {
    float input;
    
    while (1) {
        cin >> input;
        if (!cin) {
            cin.clear();
            cin.get();
        }
        else {
            if (input>=begin && input<=end) {
                return input;
            }
        }
    }
}

//清屏以显示下一页信息
void clear_the_screen(void) {
    system("cls");
}

//求姓名长度最大值
int maximum_name_length(struct student& data) {
    int Maximum_name_length = (int)data.the_grade_of_student.at(0).val_name().size();
    for (int i=0; i<data.count_of_records; i++) {
        if (data.the_grade_of_student.at(i).val_name().size() > Maximum_name_length) {
            Maximum_name_length = (int)data.the_grade_of_student.at(i).val_name().size();
        }
    }
    
    return Maximum_name_length;
}

//显示一个学生的信息
void show_the_info_of_student(struct student& data, int the_number, int max_retraction) {
    if (the_number<0 || the_number>data.count_of_records) {
        cout << "记录显示出错\n";
        return;
    }
    //姓名
    cout << setiosflags(ios::left)
         << setw(max_retraction + 1)
         << data.the_grade_of_student.at(the_number).val_name();
    //成绩
    cout << setiosflags(ios::left)
         << setw(10)
         << setprecision(2)
         << data.the_grade_of_student.at(the_number).val_subject_1();
    cout << setiosflags(ios::left)
         << setw(10)
         << setprecision(2)
         << data.the_grade_of_student.at(the_number).val_subject_2();
    cout << setiosflags(ios::left)
         << setw(10)
         << setprecision(2)
         << data.the_grade_of_student.at(the_number).val_subject_3();
    cout << setiosflags(ios::left)
         << setw(10)
         << setprecision(2)
         << data.the_grade_of_student.at(the_number).val_subject_4();
    cout << setiosflags(ios::left)
         << setw(10)
         << setprecision(2)
         << data.the_grade_of_student.at(the_number).val_average();
}

//按照一定格式显示成绩
void show_the_grade_of_all_student(struct student& data) {
    int input;
    clear_the_screen();
    
    //无数据可以输出
    if (data.count_of_records == 0) {
        cout << "无数据\n";
        cout << "\n1.导入成绩\n";
        cout << "2.返回主菜单\n";
        cout << "请选择相应操作:";
        input = accept_the_input_int(1, 2);
        if (input == 1) {
            lead_in_grade(data);
        }
        return;/*返回主菜单,因为导入成绩函数执行完后还会返回到上面这个 if 里面,
                所以不管 input 是1还是2都得结束这个函数*/
    }
    else {
        int max_retraction = maximum_name_length(data);
        
        for (int i=0; i<data.count_of_records; i++) {
            show_the_info_of_student(data, i, max_retraction);
            cout << endl;
        }
    }
}

//检查初始密码,允许用户错误输入3次
bool check_the_initial_password(void) {
    clear_the_screen();
    string input;
    
    cout << "请输入初始密码:";
    getline(cin, input);
    if (input == the_initial_password) {
        return true;
    }
    else {
        cout << "密码错误,还有2次机会:";
        getline(cin, input);
        if (input == the_initial_password) {
            return true;
        }
        else {
            cout << "密码错误,还有1次机会:";
            getline(cin, input);
            if (input == the_initial_password) {
                return true;
            }
            else {
                cout << "密码输入错误\n";
                return false;
            }
        }
    }
}

//版权页
void show_the_copyright(void) {
    cout << "Copyright © 2016 Nicecoder Sh. All rights reserved. \n";
    cout << "version:1.0\n";
    cout << "\n";
}

//显示主菜单
void print_the_primary_menu(void) {
    clear_the_screen();
    cout << "1. 导入成绩\n";
    cout << "2. 增改记录\n";
    cout << "3. 显示成绩单\n";
    cout << "4. 分析成绩\n";
    cout << "5. 查询成绩\n";
    cout << "6. 修改密码\n";
    cout << "0. 退出程序\n";
    cout << "请选择相应操作:";
}

//导入成绩(手动和文件导入)
void lead_in_grade(struct student& data) {
    clear_the_screen();
    
    //判断函数是否是第一次调用,输入科目的名称
    static bool flag = 0;
    if (flag == 0) {
        cout << "请按顺序输入四个科目的名称:";
        for (int i=1; i<5; i++) {
            getline(cin, data.subject_name[i]);
        }
        flag = 1;
    }
    
    clear_the_screen();
    int input;//存放用户的选择,手动输入还是文件导入
    string temporary_name;//存放用户输入的姓名
    long long temporary_number;
    float temporary_subject_grade[5];//存放用户输入的成绩
    
    cout << "1.文件导入成绩\n";
    cout << "2.手动输入成绩\n";
    cout << "请选择相应操作:";
    input = accept_the_input_int(1, 2);
//    if (input == 1) {
//        clear_the_screen();
//        string file_name;
//        ifstream work("test.txt");
//        
//        while (1) {
//            cout << "请输入文件名:";
//            getline(cin, file_name);
//            work.open("test.txt");
//            
//            //文件打开失败
//            if (!work.is_open()) {
//                cout << "文件打开失败\n";
//                cout << '\n';
//                cout << "1.重新输入文件名\n";
//                cout << "2.手动输入成绩\n";
//                cout << "3.返回主菜单\n";
//                
//                int temporary_input;
//                temporary_input = accept_the_input_int(1, 3);
//                if (temporary_input == 1) {
//                    continue;
//                }
//                else if (temporary_input == 2) {
//                    input = 2;
//                    break;
//                }
//                else {
//                    return;
//                }
//            }
//            else {
//                while (work.good()) {
//                    work >> temporary_name;
//                    for (int i=1; i<5; i++) {
//                        work >> temporary_subject_grade[i];
//                    }
//                    Student void_object = Student(temporary_name, temporary_subject_grade);
//                    data.the_grade_of_student.insert(data.the_grade_of_student.end(), void_object);
//                }
//            }
    
//        }
//    }
    if (input == 2) {
        cout << "请输入姓名和成绩\n";
        while (1) {
            //输入姓名和成绩
            cout << "name:";
            getline(cin, temporary_name);
            cout << "grade:";
            for (int i=1; i<5; i++) {
                temporary_subject_grade[i] = accept_the_input_grade(0, 150);
            }
            cout << "number:";
            //输入学号,过滤不良输入
            while (1) {
                cin >> temporary_number;
                if (!cin) {
                    cin.clear();
                    cin.get();
                }
                else {
                    if (temporary_number<0) {
                        while (cin.get() != '\n') {
                            continue;
                        }
                    }
                    else {
                        while (cin.get() != '\n') {
                            continue;
                        }
                        break;
                    }
                }
            }
            
            ++data.count_of_records;
            //建立一个新的对象,并把用户方才输入的信息写进去,再把这个对象加到容器里面
            Student void_object = Student(temporary_name, temporary_number, temporary_subject_grade);
            data.the_grade_of_student.push_back(void_object);
            
            cout << "是否继续(1/0):";
            input = accept_the_input_int(0, 1);
            if (input == 0) {
                break;
            }
        }
    }
}//最后解决文件读取问题

//修改初始密码
void modify_the_initial_password(void) {
    clear_the_screen();
    if (check_the_initial_password() == true) {
        string password_a, password_b;
        cout << "请输入新密码:";
        while (1) {
            getline(cin, password_a);
            if (password_a == the_initial_password) {
                cout << "新密码不能和原密码一样,请重新输入:";
            }
            else {
                break;
            }
        }
        cout << "请确认输入新密码:";
        while (1) {
            getline(cin, password_b);
            if (password_b != password_a) {
                cout << "两次输入的密码不一样,请重新确认输入:";
            }
            else {
                break;
            }
        }
        the_initial_password = password_a;
        
        if (check_the_initial_password() == false) {
            cout << "密码确认失败,程序退出.\n";
            exit(1);
        }
    }
}

//查询成绩
void find_the_record_of_grade(struct student& data) {
    int input;
    int flag = 0;
    clear_the_screen();
    
    //无数据可以输出
    if (data.count_of_records == 0) {
        cout << "无数据\n";
        cout << "\n1.导入成绩\n";
        cout << "2.返回主菜单\n";
        cout << "请选择相应操作:";
        input = accept_the_input_int(1, 2);
        if (input == 1) {
            lead_in_grade(data);
        }
        return;/*返回主菜单,因为导入成绩函数执行完后还会返回到上面这个 if 里面,
                所以不管 input 是1还是2都得结束这个函数*/
    }
    else {
        cout << "1.按学号查找\n";
        cout << "2.按姓名查找\n";
        cout << "请选择相应操作:";
        input = accept_the_input_int(1, 2);
        if (input == 1) {
            while (1) {
                long long input_number;
                cout << "请输入学号:";
                while (1) {
                    cin >> input_number;
                    if (!cin) {
                        cin.clear();
                        while (cin.get() != '\n') {
                            continue;
                        }
                        cout << "输入有误，请重新输入:";
                    }
                    else {
                        if (cin.get()!='\n' || input_number<0) {
                            cout << "输入有误，请重新输入:";
                            while (cin.get() != '\n') {
                                continue;
                            }
                        }
                        else {
                            break;
                        }
                    }
                }
                
                int max_retraction = maximum_name_length(data);
                for (int i=0; i<data.count_of_records; i++) {
                    if (input_number == data.the_grade_of_student.at(i).val_ID_number()) {
                        show_the_info_of_student(data, i, max_retraction);
                        cout << endl;
                        flag = 1;
                    }
                }
                if (flag == 0) {
                    cout << "没有找到相关数据\n";
                }
                
                cout << "是否继续(1/0):";
                input = accept_the_input_int(0, 1);
                if (input == 0) {
                    break;
                }
            }
        }
        else {
            while (1) {
                string input_name;
                cout << "请输入姓名:";
                getline(cin, input_name);
                for (int i=0; i<data.count_of_records; i++) {
                    if (input_name == data.the_grade_of_student.at(i).val_name()) {
                        show_the_info_of_student(data, i, 10);
                        cout << endl;
                        flag = 1;
                    }
                }
                if (flag == 0) {
                    cout << "没有找到相关数据\n";
                }
                
                cout << "是否继续(1/0):";
                input = accept_the_input_int(0, 1);
                if (input == 0) {
                    break;
                }
            }
        }
    }
}

//分析成绩
void analyse_the_grade(struct student& data) {
    int input;
    clear_the_screen();
    
    //无数据可以输出
    if (data.count_of_records == 0) {
        cout << "无数据\n";
        cout << "\n1.导入成绩\n";
        cout << "2.返回主菜单\n";
        cout << "请选择相应操作:";
        input = accept_the_input_int(1, 2);
        if (input == 1) {
            lead_in_grade(data);
        }
        return;/*返回主菜单,因为导入成绩函数执行完后还会返回到上面这个 if 里面,
                所以不管 input 是1还是2都得结束这个函数*/
    }
    else {
        cout << "1.科目最高分\n";
        cout << "2.平均分最高分\n";
        cout << "3.学生分数最高的科目\n";
        cout << "请选择相应操作:";
        input = accept_the_input_int(1, 3);
        if (input == 1) {
            for (int i=1; i<5; i++) {
                switch (i) {
                    case 1: {
                        float max = data.the_grade_of_student.at(0).val_subject_1();
                        int the_count_of_max = 0;
                        //找到最高分
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_1() > max) {
                                max = data.the_grade_of_student.at(j).val_subject_1();
                            }
                        }
                        cout << setw(10) << setiosflags(ios::right) << data.subject_name[1] << "最高分:" << setw(5) << setiosflags(ios::left) << max;
                        //计算最高分的同学的个数
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_1() == max) {
                                ++the_count_of_max;
                            }
                        }
                        //为了姓名之间正确使用标点符号
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_1() == max) {
                                cout << data.the_grade_of_student.at(j).val_name();
                                if (the_count_of_max != 1) {
                                    cout << "、";
                                    --the_count_of_max;
                                }
                            }
                        }
                        cout << endl;
                        
                        break;
                    }
                    
                    case 2: {
                        float max = data.the_grade_of_student.at(0).val_subject_2();
                        int the_count_of_max = 0;
                        //找到最高分
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_2() > max) {
                                max = data.the_grade_of_student.at(j).val_subject_2();
                            }
                        }
                        cout << setw(10) << setiosflags(ios::right) << data.subject_name[2] << "最高分:" << setw(5) << setiosflags(ios::left) << max;
                        //计算最高分的同学的个数
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_2() == max) {
                                ++the_count_of_max;
                            }
                        }
                        //为了姓名之间正确使用标点符号
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_2() == max) {
                                cout << data.the_grade_of_student.at(j).val_name();
                                if (the_count_of_max != 1) {
                                    cout << "、";
                                    --the_count_of_max;
                                }
                            }
                        }
                        cout << endl;
                        
                        break;
                    }
                        
                    case 3: {
                        float max = data.the_grade_of_student.at(0).val_subject_3();
                        int the_count_of_max = 0;
                        //找到最高分
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_3() > max) {
                                max = data.the_grade_of_student.at(j).val_subject_3();
                            }
                        }
                        cout << setw(10) << setiosflags(ios::right) << data.subject_name[3] << "最高分:" << setw(5) << setiosflags(ios::left) << max;
                        //输出得最高分的同学的姓名
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_3() == max) {
                                ++the_count_of_max;
                            }
                        }
                        //为了姓名之间正确使用标点符号
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_3() == max) {
                                cout << data.the_grade_of_student.at(j).val_name();
                                if (the_count_of_max != 1) {
                                    cout << "、";
                                    --the_count_of_max;
                                }
                            }
                        }
                        cout << endl;
                        
                        break;
                    }
                        
                    case 4: {
                        float max = data.the_grade_of_student.at(0).val_subject_4();
                        int the_count_of_max = 0;
                        //找到最高分
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_4() > max) {
                                max = data.the_grade_of_student.at(j).val_subject_4();
                            }
                        }
                        cout << setw(10) << setiosflags(ios::right) << data.subject_name[4] << "最高分:" << setw(5) << setiosflags(ios::left) << max;
                        //输出得最高分的同学的姓名
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_4() == max) {
                                ++the_count_of_max;
                            }
                        }
                        //为了姓名之间正确使用标点符号
                        for (int j=0; j<data.count_of_records; j++) {
                            if (data.the_grade_of_student.at(j).val_subject_4() == max) {
                                cout << data.the_grade_of_student.at(j).val_name();
                                if (the_count_of_max != 1) {
                                    cout << "、";
                                    --the_count_of_max;
                                }
                            }
                        }
                        cout << endl;
                        
                        break;
                    }
                }
                
            }
        }
        else if (input == 2) {
            float max = data.the_grade_of_student.at(0).val_average();
            int the_count_of_max = 0;
            //找到最高分
            for (int j=0; j<data.count_of_records; j++) {
                if (data.the_grade_of_student.at(j).val_average() > max) {
                    max = data.the_grade_of_student.at(j).val_average();
                }
            }
            cout << "平均分最高分:" << setw(5) << setiosflags(ios::left) << max;
            //计算得最高分的同学的个数
            for (int j=0; j<data.count_of_records; j++) {
                if (data.the_grade_of_student.at(j).val_average() == max) {
                    ++the_count_of_max;
                }
            }
            //为了姓名之间正确使用标点符号
            for (int j=0; j<data.count_of_records; j++) {
                if (data.the_grade_of_student.at(j).val_average() == max) {
                    cout << data.the_grade_of_student.at(j).val_name();
                    if (the_count_of_max != 1) {
                        cout << "、";
                        --the_count_of_max;
                    }
                }
            }
            cout << endl;
        }
        else if (input == 3) {
            int max_retraction = maximum_name_length(data);
            
            for (int i=0; i<data.count_of_records; i++) {
                int the_count_of_max = 0;
                char *subject;
                
                cout << setw(max_retraction + 1) << setiosflags(ios::left)
                     << data.the_grade_of_student.at(i).val_name();
                cout << setw(6) << setiosflags(ios::left) << setprecision(2)
                     << data.the_grade_of_student.at(i).val_max_of_all_subject_grade();
                
                for (int j=1; j<5; j++) {
                    subject = data.the_grade_of_student.at(i).val_max_of_all_subject_name();
                    if (subject[j] == '1') {
                        ++the_count_of_max;
                    }
                }
                cout << "the_count_of_max:" << the_count_of_max;
                
                for (int j=1; j<5; j++) {
                    subject = data.the_grade_of_student.at(i).val_max_of_all_subject_name();
                    if (subject[j] == '1') {
                        cout << data.subject_name[j];
                        if (the_count_of_max != 1) {
                            cout << "、";
                            --the_count_of_max;
                        }
                    }
                }
                cout << endl;
            }
        }
    }
}