/*
Имате последователност от разноцветни топчета, долепени едно до друго и номерирани с чилата от 0 до N-1. 
Можете да изстрелвате топчета с определен цвят към редицата от топчета. Изстреляното топче попада точно след топчето 
с номер P, измествайки всички топчета на позиции по-големи от P с една позиция в дясно. Aко P e част от последователност
от топчета с еднакъв цвят с дължина поне 3, цялата последователност от едноцветни топчета бива унищожена, а лявата и 
дясната получени последователности се залепят. Ако мястото на залепянето е част от последователност от топчета с 
еднакъв цвят с дължина поне 3, процедурата се повтаря, в противен случай можете да изстреляте ново топче. 
Играта прикючва когато не останат топчета в редицата.

От вас се иска да напишете програма която по дадена редица от N разноцветни топчета, отговаря на Q на брой заявки. 
Всяка заявка се състои от две цели числа Pi и Ci - номера на топчето, към което трябва да стреляте и цвета на топчето, 
което изстрелвате. Номера на изстрелятното топче е най-малкото, неизползвано за номер на топче, естествено число. 
Топчето към което е насочен изстрела винаги съществува (не е унищожено). От вас се иска да намерите броя на 
унищожените топчета след всеки изстрел. Ако след поредия изстрел не останат никакви топчета, играта приключва и на 
всяка следваща заявка трябва да отговорите с "Game Over".

След приключване на заявките изведете получената редица от топчета или -1 ако всички топчета са унищожени.
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>
using namespace std;

struct Node {
    pair<long, long> data;
    Node* next = nullptr;
    Node* previous = nullptr;

    Node(pair<long, long> data, Node* next = nullptr, Node* previous = nullptr) {
        this->data = data;
        this->next = next;
        this->previous = previous;
    }
};

long position = 0;
vector<Node*> positions;

class LList {
private:
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    LList() = default;

    void push_front(pair<long, long> number) {
        Node* newHead = new Node(number, head, nullptr);
        head = newHead;
        if (tail == nullptr) {
            tail = head;
        }
    }

    void push_back(pair<long, long> number) {
        if (head == nullptr) {
            head = new Node(number);
            tail = head;
        } else {
            tail->next = new Node(number, nullptr, tail);
            tail = tail->next;
        }
    }

    void print() const {
        Node* i = head;
        while (i != nullptr) {
            cout << i->data.second << " ";
            i = i->next;
        }
        cout << "\n";
    }

    Node* peek_front() {
        return head;
    }

    Node* peek_back() {
        return tail;
    }

    void pop_front() {
        if (head != nullptr) {

            if (tail == head) {
                Node* oldHead = head;
                tail = nullptr;
                head = nullptr;
                delete oldHead;
                return;
            }

            Node* oldHead = head;
            head = head->next;
            head->previous = nullptr;
            delete oldHead;
        }
        return;
    }

    void pop_back() {
        if (head != nullptr) {
            if (head == tail) {
                Node* oldHead = head;
                head = nullptr;
                tail = nullptr;
                delete oldHead;
                return;
             }

             Node* oldTail = tail;
             tail = tail->previous;
             tail->next = nullptr;
             delete oldTail;
        }
        return;
    }

     void insert(pair<long, long> query, long& size) {

         long deleted = 0;

         if(size == 0) {
            cout<<"Game Over"<<endl;
            return;
         }

         pair<long, long> add = make_pair(position, query.second);
         position++;


         if(query.first == tail->data.first) {
            push_back(add);
            size++;
            positions.push_back(peek_back());
            erase(tail, size, deleted);

            return;
         }

         Node* current = positions[query.first];

         /*while(current->data.first != query.first && current->next != nullptr) {
            current = current->next;
         }*/

         Node* cur_next = current->next;
         Node* to_insert = new Node(add, cur_next, current);
         current->next = to_insert;
         cur_next->previous = to_insert;
         size++;

         positions.push_back(current->next);

         erase(current->next, size, deleted);

         return;
    }

    void erase(Node* node, long& size, long& deleted) {

        if(node == nullptr) {
            return;
        }

        if(size < 3) {
            cout<<deleted<<endl;
            return;
        }

        if(size == 3) {
            node = head;
            if(node->data.second == node->next->data.second && node->data.second == node->next->next->data.second) {
                remove(node->next->next, size);
                remove(node->next, size);
                remove(node, size);
                deleted += 3;
            }
            cout<<deleted<<endl;
            return;
        }

        if(node == tail) {
            long count = 1;
            Node* below_tail = node->previous;
            while(below_tail->data.second == node->data.second && below_tail != nullptr) {
                below_tail = below_tail->previous;
                count++;
            }
            below_tail = below_tail->next;

            if(count >= 3) {
                while(below_tail != tail) {
                    remove(below_tail, size);
                    below_tail = below_tail->next;
                }
                remove(below_tail, size);
                deleted += count;
            }

            cout<<deleted<<endl;
            return;

        }

        if(node == head) {
            long count = 1;
            Node* above_head = node->next;
            while(above_head->data.second == node->data.second && above_head != nullptr) {
                above_head = above_head->next;
                count++;
            }
            above_head = above_head->previous;

            if(count >= 3) {
                while(above_head != head) {
                    remove(above_head, size);
                    above_head = above_head->previous;
                }
                remove(above_head, size);
                deleted += count;
            }

            cout<<deleted<<endl;
            return;

        }

        Node* below = node->previous;
        Node* above = node->next;
        long counter = 1;

        while(below->data.second == node->data.second && below->previous != nullptr) {
            below = below->previous;
            counter++;
        }
        Node* below_check = below;

        if(below->previous == nullptr && below->data.second == node->data.second) {
            counter++;
            below_check = nullptr;
            below = head;
        }
        else {
            below = below->next;
        }


        while(above->data.second == node->data.second && above->next != nullptr) {
            above = above->next;
            counter++;
        }
        Node* above_check = above;

        if(above->data.second == node->data.second && above->next == nullptr) {
            counter++;
            above_check = nullptr;
            above = tail;
        }
        else {
            above = above->previous;
        }

        if(counter >= 3) {
            while(below != above) {
                remove(below, size);
                below = below->next;
            }
            remove(below, size);
            deleted += counter;
        }
        else {
            cout<<deleted<<endl;
            return;
        }

        if(size < 3) {
            cout<<deleted<<endl;
            return;
        }

        if(above_check == nullptr || below_check == nullptr) {
            cout<<deleted<<endl;
            return;
        }
        if(above_check->data.second != below_check->data.second) {
            cout<<deleted<<endl;
            return;
        }

        if(size == 3) {
            node = head;
            if(node->data.second == node->next->data.second && node->data.second == node->next->next->data.second) {
                remove(node->next->next, size);
                remove(node->next, size);
                remove(node, size);
                deleted += 3;
            }
            cout<<deleted<<endl;
            return;
        }

        erase(below_check, size, deleted);

    }

    void remove(Node* node, long& size) {

        if (node == head && node == tail) {
            Node* to_remove = node;
            head = nullptr;
            tail = nullptr;
            delete to_remove;
            size = 0;
            return;
        }

        if (node == head) {
            pop_front();
            size--;
            return;
        }

        if (node == tail) {
            pop_back();
            size--;
            return;
        }

        Node* to_remove = node;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        delete to_remove;
        size--;

        return;

    }


};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long N = 0;
    cin>>N;

    LList colours;
    long colour = 0;
    for(long i=0; i<N; i++) {
        cin>>colour;
        colours.push_back(make_pair(position, colour));
        positions.push_back(colours.peek_back());
        position++;
    }

    long Q = 0;
    cin>>Q;

    list<pair<long, long>> queries;
    long P = 0;
    long C = 0;
    for(long i=0; i<Q; i++) {
        cin>>P>>C;
        queries.push_back(make_pair(P, C));
    }

    long size = N;
    list<pair<long, long>>::iterator i = queries.begin();
    for(; i != queries.end(); i++) {
        pair<long, long> query = *i;

        colours.insert(query, size);
    }

    if(size != 0) {
        colours.print();
    }
    else {
        cout<<-1;
    }

    return 0;
}
