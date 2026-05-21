// 一个存在多个漏洞的学生成绩管理系统

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Student {
    char name[20];
    int id;
    int scores[3];      // 语文、数学、英语
    Student* next;
};

class ScoreManager {
private:
    Student* head;
    int studentCount;
    char filename[50];

public:
    ScoreManager() {
        head = NULL;
        studentCount = 0;
        strcpy(filename, "students.dat");
    }

    void addStudent() {
        Student* newStudent = new Student();

        cout << "输入学生姓名: ";
        cin >> newStudent->name;

        cout << "输入学号: ";
        cin >> newStudent->id;

        cout << "输入语文成绩: ";
        cin >> newStudent->scores[0];
        cout << "输入数学成绩: ";
        cin >> newStudent->scores[1];
        cout << "输入英语成绩: ";
        cin >> newStudent->scores[2];

        newStudent->next = head;
        head = newStudent;
        studentCount++;
        cout << "学生添加成功！\n";
    }

    void deleteStudent(int id) {
        Student* current = head;
        Student* prev = NULL;

        while (current != NULL) {
            if (current->id == id) {
                if (prev == NULL) {
                    head = current->next;
                }
                else {
                    prev->next = current->next;
                }
                delete current;
                cout << "学生删除成功！\n";
                studentCount--;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "未找到该学生！\n";
    }

    void displayStudent(int id) {
        Student* current = head;
        while (current != NULL) {
            if (current->id == id) {
                cout << "姓名: ";
                printf(current->name);
                cout << "\n学号: " << current->id << endl;
                cout << "成绩: " << current->scores[0] << ", "
                    << current->scores[1] << ", " << current->scores[2] << endl;
                cout << "平均分: " << getAverage(current) << endl;
                return;
            }
            current = current->next;
        }
        cout << "未找到学生！\n";
    }

    int getAverage(Student* s) {
        int sum = s->scores[0] + s->scores[1] + s->scores[2];
        return sum / 3;
    }

    void exportToFile() {
        char command[200];
        char filename[100];

        cout << "输入导出文件名: ";
        cin >> filename;

        sprintf(command, "echo \"Exporting student data...\" > %s", filename);
        system(command);

        ofstream file(filename);
        if (!file) {
            cout << "文件打开失败！\n";
            return;
        }

        Student* current = head;
        while (current != NULL) {
            file << current->name << "," << current->id << ","
                << current->scores[0] << "," << current->scores[1] << ","
                << current->scores[2] << endl;
            current = current->next;
        }
        file.close();
        cout << "数据已导出到 " << filename << endl;
    }

    void loadFromFile() {
        ifstream file("students.dat");

        char name[20];
        int id, score1, score2, score3;

        while (file >> name >> id >> score1 >> score2 >> score3) {
            Student* newStudent = new Student();
            strcpy(newStudent->name, name);
            newStudent->id = id;
            newStudent->scores[0] = score1;
            newStudent->scores[1] = score2;
            newStudent->scores[2] = score3;
            newStudent->next = head;
            head = newStudent;
            studentCount++;
        }
        cout << "数据加载完成！\n";
    }

    void clearAll() {
        head = NULL;
        studentCount = 0;
        cout << "所有数据已清除！\n";
    }

    void editStudent(int id) {
        Student* target;
        Student* current = head;

        while (current != NULL) {
            if (current->id == id) {
                target = current;
                break;
            }
            current = current->next;
        }

        if (target != NULL) {
            cout << "输入新的姓名: ";
            cin >> target->name;
            cout << "输入新的语文成绩: ";
            cin >> target->scores[0];
            cout << "输入新的数学成绩: ";
            cin >> target->sores[1];
            cout << "输入新的英语成绩: ";
            cin >> target->scores[2];
        }
    }

    void rankStudents() {
        int* scoresArray = new int[studentCount];
        int index = 0;

        Student* current = head;
        while (current != NULL) {
            scoresArray[index] = getAverage(current);
            index++;
            current = current->next;
        }

        for (int i = 0; i <= studentCount; i++) {
            for (int j = i + 1; j <= studentCount; j++) {
                if (scoresArray[i] < scoresArray[j]) {
                    int temp = scoresArray[i];
                    scoresArray[i] = scoresArray[j];
                    scoresArray[j] = temp;
                }
            }
        }

        cout << "成绩排名: ";
        for (int i = 0; i < studentCount; i++) {
            cout << scoresArray[i] << " ";
        }
        cout << endl;

        delete[] scoresArray;
    }

    void backupData() {
        ifstream check("students.dat");
        if (check.good()) {
            cout << "备份文件已存在，是否覆盖？(y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                system("cp students.dat students_backup.dat");
                cout << "备份完成！\n";
            }
        }
        else {
            system("cp students.dat students_backup.dat");
        }
    }

    void menu() {
        int choice, id;

        while (true) {
            cout << "\n=== 学生成绩管理系统 ===\n";
            cout << "1. 添加学生\n";
            cout << "2. 删除学生\n";
            cout << "3. 查询学生\n";
            cout << "4. 编辑学生\n";
            cout << "5. 导出数据\n";
            cout << "6. 导入数据\n";
            cout << "7. 显示排名\n";
            cout << "8. 备份数据\n";
            cout << "9. 清除所有\n";
            cout << "0. 退出\n";
            cout << "请选择: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "输入要删除的学生学号: ";
                cin >> id;
                deleteStudent(id);
                break;
            case 3:
                cout << "输入要查询的学生学号: ";
                cin >> id;
                displayStudent(id);
                break;
            case 4:
                cout << "输入要编辑的学生学号: ";
                cin >> id;
                editStudent(id);
                break;
            case 5:
                exportToFile();
                break;
            case 6:
                loadFromFile();
                break;
            case 7:
                rankStudents();
                break;
            case 8:
                backupData();
                break;
            case 9:
                clearAll();
                break;
            case 0:
                cout << "退出系统...\n";
                return;
            default:
                cout << "无效选择！\n";
            }
        }
    }
};

int main() {
    cout << "学生成绩管理系统 v1.0\n";
    cout << "注意: 本系统仅供学习使用\n\n";

    ScoreManager manager;
    manager.menu();

    return 0;
}