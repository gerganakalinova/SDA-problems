/*
В края на 2020 Outersloth обявиха новата DLC карта за играта Between Us - Euclidius. Името на картата идва от формата й - двумерна Евклидова равнина. 
Някои от новите за картата задачи се намират в специално отделение на картата - The Dealy Darkness (TDD). Звучи доста приятелско.

Заедно с новата карта пристига и нова роля - Necromancer. Necromancer-ът е crewmate, но може да съживява хора, които са умрели в TDD 
(колко добра идея е не знаем...за справка, WarCraft 3). Нашият Necromancer ще се казва Келто (без конкретна причина). 
Той иска да съживи максимално много crewmates, за да докаже, че е достоен necromancer. По зададена позицията на Келто и на наскоро убития crewmate, 
отговорете какво е минималното време, за което нашият млад necromancer може да стигне до най-новата си пионка...uhm жертва, до най-новата жертва.

Както казахме, Euclidius е като двумерна Евклидова равнина. Освен това, границата между основната част на картата и TDD е права хоризонтална линия. 
Нека тази граница е линията y=0. Всяка точка над нея е част от TDD, а всяка точка под нея - от основната част на картата. Скоростта, с която Келто 
се движи по суша ще бележим с v1, а скоростта му в TDD - с v2 (Скорост дефинираме като евклидовото разстояние, което Келто изминава за единица време). 
Текущата позиция на Келто ще бележим с (x1, y1) а на убития crewmate - с (x2, y2). Келто се намира в основната част на картата в началото.

Важно! В кода не си кръщавайте променливите y1, защото е запазен идентификатор в библиотеката cmath.
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;


void ternary_search_own(long& begin, long& end, int y_first, int y_second, int v_first, int v_second, long third_size_helper) {

    if(end - begin <= 3) {
        return;
    }

    long mid1 = (2*begin + end)/3;
    long mid2 = (begin + 2*end)/3;
    cout<<mid1<<" "<<mid2<<endl;

    long double distance1_first = sqrt(pow(y_first, 2) + pow(mid1, 2));
    long double distance1_second = sqrt(pow(y_second, 2) + pow(third_size_helper - mid1, 2));
    long double time1 = distance1_first/v_first + distance1_second/v_second;

    long double distance2_first = sqrt(pow(y_first, 2) + pow(mid2, 2));
    long double distance2_second = sqrt(pow(y_second, 2) + pow(third_size_helper - mid2, 2));
    long double time2 = distance2_first/v_first + distance2_second/v_second;

    if(time1 > time2) {
        begin = mid1;
    }

    if(time2 > time1) {
        end = mid2;
    }
    cout<<begin<<" "<<end<<endl<<endl;

    ternary_search_own(begin, end, y_first, y_second, v_first, v_second, third_size_helper);

}


int main() {

    int tests = 0;
    cin>>tests;

    vector<vector<int>> vec;
    int input = 0;
    for(int i=0; i<tests; i++) {
        vector<int> v1;
        for(int j=0; j<6; j++) {
            cin>>input;
            v1.push_back(input);
        }
        vec.push_back(v1);
    }

    vector<long double> times;
    for(int i=0; i<tests; i++) {

        int x_first = vec[i][0];
        int y_first = vec[i][1];
        int x_second = vec[i][2];
        int y_second = vec[i][3];
        int v_first = vec[i][4];
        int v_second = vec[i][5];

        if(y_first > 0) {
            return -1;
        }
        if(y_second < 0) {
            return -1;
        }

        y_first = fabs(y_first);

        long third_size_helper = fabs(x_second - x_first);
        long double time = 0.0;
        long begin = 0;
        long end = third_size_helper;

        ternary_search_own(begin, end, y_first, y_second, v_first, v_second, third_size_helper);

        long double distance_first = sqrt(pow(y_first, 2) + pow(begin, 2));
        long double distance_second = sqrt(pow(y_second, 2) + pow(third_size_helper - begin, 2));
        time = distance_first/v_first + distance_second/v_second;
        times.push_back(time);


        for(long double j=begin; j<=end; j=j+0.01) {
            distance_first = sqrt(pow(y_first, 2) + pow(j, 2));
            distance_second = sqrt(pow(y_second, 2) + pow(third_size_helper-j, 2));
            time = distance_first/v_first + distance_second/v_second;

            if(time < times[i]) {
                times[i] = time;
            }
        }

        /*long double distance_first = sqrt(pow(y_first, 2) + pow(third_size_helper, 2));
        long double distance_second = sqrt(pow(y_second, 2));
        time = distance_first/v_first + distance_second/v_second;
        times.push_back(time);


        for(long double j=third_size_helper; j>=0; j=j-0.01) {
            distance_first = sqrt(pow(y_first, 2) + pow(j, 2));
            distance_second = sqrt(pow(y_second, 2) + pow(third_size_helper-j, 2));
            time = distance_first/v_first + distance_second/v_second;

            cout<<j<<" "<<time<<endl;
            if(time < times[i]) {
                times[i] = time;
            }
        }*/
    }

    cout << fixed;
    for(vector<long double>::size_type i=0; i<times.size(); i++) {

        cout << setprecision(5) << times[i] << "\n";


    }

    return 0;
}

