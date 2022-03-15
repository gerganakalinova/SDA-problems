/*
След поредното онлайн контролно при Ч², Ч² е обещал да провери контролните на всички веднага. Дори е решил, че ако 
някой предаде по-рано, то Ч² веднага ще започне да проверява, за да не губи време. Ч² обаче иска да проверява така 
че средното време за чакане за проверка на всички да е минимално, за да не се сърди никой, че е останал последен. 
Ч² проверява 1 ред код за 1 секунда.

Намерете минималното средно време, което трябва да чака един студент, за да му бъде проверено контролното.

Забележка: Ч² не може да вижда бъдещето, така че ако не проверява на никого и някой студент предаде контролно Ч² 
започва веднага да проверява. Това предполага че може в следващият момент да бъде предадено по-удачно за проверяване 
контролно, но Ч² няма как да знае за него.
*/


#include <bits/stdc++.h>
using namespace std;

struct Student {
    int submitTime;
    int linesCode;
};


bool operator<(Student one, Student two) {
    return one.submitTime < two.submitTime;
}

struct compareLines {
    bool operator() (const Student& one, const Student two) {
        return one.linesCode > two.linesCode;
    }
};



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 0;
    cin>>N;

    vector<Student> students;
    priority_queue<Student, vector<Student>, compareLines> to_check;

    int time = 0, lines = 0;
    Student student;

    for(int i=0; i<N; i++) {
        cin>>time>>lines;
        student.submitTime = time;
        student.linesCode = lines;
        students.push_back(student);
    }

    sort(students.begin(), students.end());
    long long total_time = 0;
    long long current_time = 0;
    int count = 0;

    while(count < N || !to_check.empty()){
        while(count < N && students[count].submitTime <= current_time) {
            to_check.push(students[count]);
            count++;
        }

        if(to_check.empty()) {
            current_time = students[count].submitTime;
        }
        else {
            Student tmp = to_check.top();
            current_time += tmp.linesCode;
            total_time += current_time - tmp.submitTime;
            to_check.pop();
        }

    }

    cout<<total_time/N;

    return 0;
}
