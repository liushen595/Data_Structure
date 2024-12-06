#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
//#include <variant>
//#include <memory>
#include <string>
using namespace std;

struct  Node {
    string StuName;
    int CourseCount;
    vector<int> SelCourse;
    Node* next;
    Node(string name, int CourseCt, const vector<int> &sel) :StuName(name), CourseCount(CourseCt),
        SelCourse(sel), next(nullptr) {}
};

/*struct CourseAndStuName
{
    int CourseNum; //课程编号
    vector<string> StuName; //学生名单
    CourseAndStuName(int num, const vector<string> &name) :CourseNum(num), StuName(name) {};
};*/


Node* CreatLinklist(const vector<string> &names, const vector<int> &count, const vector<vector<int>> &values) {
    if (values.empty())
        return nullptr;

    Node* head = new Node(names[0], count[0], values[0]);
    Node* current = head;

    for (size_t i = 1; i < values.size(); i++) {
        current->next = new Node(names[i], count[i], values[i]);
        current = current->next;
    }

    return head;
}

void StatisSelCount(Node* head, vector<int> &num_of_stu_in_course) {
    Node* curr = head;
    while (curr != nullptr) {
        for (int course : curr->SelCourse)
            num_of_stu_in_course[course]++;

        curr = curr->next;
    }
}

bool Find(const vector<int> vec, int key) {
    for (int num : vec) {
        if (num == key)
            return true;
    }
    return false;
}

void StatisStuName(Node* head, unordered_map<int, vector<string>> &CAndS, int CourseCount) {
    Node* curr = head;
    vector<string> names; //某课程选课名单

    for (int i = 1; i <= CourseCount; i++) {
        while (curr != nullptr) {
            if (Find(curr->SelCourse, i))
                names.push_back(curr->StuName);

            curr = curr->next;
        }
        sort(names.begin(), names.end());
        CAndS[i] = names;
        names.clear();
        curr = head;
    }
}

void OutPut(const vector<int> &num_of_stu_in_course, const unordered_map<int, vector<string>> &CAndS) {
    for (size_t num = 0; num < num_of_stu_in_course.size() - 1; num++) {
        cout << num + 1 << " " << num_of_stu_in_course[num + 1] << endl;
        for (string stuname : CAndS.at(num + 1))
            cout << stuname << endl;
    }
}

void DeleteLinklist(Node* head) {
    Node* current = head;
    Node* next_node = nullptr;

    while (current != nullptr) {
        next_node = current->next;
        delete current;
        current = next_node;
    }
}

int main() {
    int StuCount, CourseCount, SelectedCount, TempCourses;
    vector<int> SelectedCourses; //一个学生选择的课程
    vector<vector<int>> valus; //每一个学生选课情况
    vector<string> names; //每一个学生姓名
    vector<int> count; //每一个学生选课门数
    string StuName; //学生姓名
    cin >> StuCount >> CourseCount;

    vector<int> num_of_stu_in_course(CourseCount + 1, 0); //每一个课程选课人数
    unordered_map<int, vector<string>> CAndS; //课程编号及选课名单

    for (int i = 0; i < StuCount; i++) {
        cin >> StuName >> SelectedCount;
        names.push_back(StuName);
        count.push_back(SelectedCount);
        for (int i = 0; i < SelectedCount; i++) {
            cin >> TempCourses;
            SelectedCourses.push_back(TempCourses);
        }
        valus.push_back(SelectedCourses);
        SelectedCourses.clear();
    }

    Node* head = CreatLinklist(names, count, valus);

    StatisSelCount(head, num_of_stu_in_course);
    StatisStuName(head, CAndS, CourseCount);
    OutPut(num_of_stu_in_course, CAndS);

    DeleteLinklist(head);

    system("pause");
    return 0;
}