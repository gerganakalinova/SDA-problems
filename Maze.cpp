/*
Имате даден лабиринт. Лабиринтът е разделен на клетки (може да си го представим като матрица с N реда и M колони), 
всяка от които е или празна '.', или стена '#', или начална клетка 'S', или изход от лабиринта 'F' (има точно една 
начална клетка и един изход от лабиринта).

Движението в лабиринта е позволено само в четирите посоки: нагоре, надолу, наляво и надясно, не е позволено движението 
по диагонал. Преминаването от една клетка в друга е възможно само ако те са съседни (т.е. споделят страна) и целевата 
клетката е празна. Движението отнема, точно 1 секунда.

Освен нормалното придвижване, в лабиринта е възможно и телепортиране между определени клетки. По точно от дадена 
клетка е възможно телепортирането в четирите най-отдалечени, видими, от нея клетки, във всяка от посоките за движение 
(нагоре, надолу, наляво и надясно). Видима е клетка ако няма препядствие в същата посока, което е по-близо от нея. 
Този начин на придвижване също отнема, точно 1 секунда.

От вас се иска да откриете най-краткото време за което е възможно да се излезе от лабиринта (да се достигне келтката 'F' 
от клетката 'S'). Ако не е възможно да се излезе от лабиринта изведете -1.
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 1001;

struct Node {
    pair<int, int> position;
    int seconds;
    Node* next = nullptr;

    Node(pair<int, int> position, int seconds, Node* next = nullptr) {
        this->position = position;
        this->seconds = seconds;
        this->next = next;
    }
};

class Queue {
private:
    Node* front = nullptr;
    Node* back = nullptr;
public:
    Queue() = default;

    ~Queue() {
        while(front != nullptr) {
            Node* next = front->next;
            delete front;
            front = next;
        }
    }

    void push(pair<int, int> pos, int sec) {
        if (front == nullptr) {
            front = new Node(pos, sec);
            back = front;
        } else {
            back->next = new Node(pos, sec);
            back = back->next;
        }
    }

    void pop() {
        if (front != nullptr) {
            Node* oldFront = front;
            front = front->next;
            delete oldFront;
        }
    }

    Node* peek() const {
        return front;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void neighbour_spots(char arr[MAX_SIZE][MAX_SIZE], int& min_time, int N, int M) {

        Node* node = front;
        int i = node->position.first;
        int j = node->position.second;
        int sec = node->seconds;

        if(arr[i][j] == 'F') {
            min_time = sec;
            return;
        }

        if(arr[i][j] == 'x') {
            pop();
            return;
        }

        if(j+1 < M) {
            if(arr[i][j+1] != '#' && arr[i][j+1] != 'x') {
                int new_j = j+1;
                push(make_pair(i, new_j), sec+1);

                while(arr[i][new_j+1] != '#' && arr[i][new_j+1] != 'x') {
                    new_j++;
                }

                if(new_j != j+1 && new_j < M) {
                    push(make_pair(i, new_j), sec+1);
                }
            }
        }
        

        if(j-1 >= 0) {
            if(arr[i][j-1] != '#' && arr[i][j-1] != 'x') {
                int new_j = j-1;
                push(make_pair(i, new_j), sec+1);

                while(arr[i][new_j-1] != '#' && arr[i][new_j-1] != 'x') {
                    new_j--;
                }

                if(new_j != j-1 && new_j >= 0) {
                    push(make_pair(i, new_j), sec+1);
                }
            }
        }
        

        if(i+1 < N) {
            if(arr[i+1][j] != '#' && arr[i+1][j] != 'x') {
                int new_i = i+1;
                push(make_pair(new_i, j), sec+1);
            
                while(arr[new_i+1][j] != '#' && arr[new_i+1][j] != 'x') {
                    new_i++;
                }

                if(new_i != i+1 && new_i < N) {
                    push(make_pair(new_i, j), sec+1);
                }
            }
        }
        

        if(i-1 >= 0) {
           if(arr[i-1][j] != '#' && arr[i-1][j] != 'x') {
                int new_i = i-1;
                push(make_pair(new_i, j), sec+1);

                while(arr[new_i-1][j] != '#' && arr[new_i-1][j] != 'x') {
                    new_i--;
                }

                if(new_i != i-1 && new_i >= 0) {
                    push(make_pair(new_i, j), sec+1);
                }
            } 
        }
        

        arr[i][j] = 'x';
        pop();
        return;
    }

};


int main() {

    int N = 0, M = 0;
    cin>>N>>M;

    char maze[MAX_SIZE][MAX_SIZE];

    pair<int, int> begin, end;
    begin = make_pair(-1, -1);
    end = make_pair(-1, -1);

    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin>>maze[i][j];

            if(maze[i][j] == 'S') {
                begin = make_pair(i, j);
            }
            else if(maze[i][j] == 'F') {
                end = make_pair(i, j);
            }
        }
    }

    if(begin.first == -1 || end.first == -1) {
        cout<<-1;
        return 0;
    }

    Queue steps;
    steps.push(begin, 0);

    int min_time = MAX_SIZE;
    while(!(steps.isEmpty())) {
        steps.neighbour_spots(maze, min_time, N, M);
        if(min_time != MAX_SIZE) {
            break;
        }
    }

    if(min_time == MAX_SIZE) {
        cout<<-1;
    }
    else {
        cout<<min_time;
    }

    return 0;
}
