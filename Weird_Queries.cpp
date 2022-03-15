/*
Дадена ви е редица от N цели числа a1,...,an. Вие трябва да отговорите на Q заявки от вида:
По дадени две цели числа Si и Pi намерете броят на числата в подредицата ai1,...,aik за която е изпълнено че:
ако всеки път избирате най-голямото не превишаващо Pi число, докато сумата на избраните числа не превишава Si 
и спрете да взимате числа ако не можете да изберете поредното най-голямо, колко числа ще изберете?
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void merge(vector<int>& vec, int lower, int middle, int upper)
{
    int size1 = middle - lower + 1;
    int size2 = upper - middle;

    vector<int> vec1, vec2;

    for(int i = 0; i < size1; i++) {
        vec1.push_back(vec[lower + i]);
    }

    for(int i = 0; i < size2; i++) {
        vec2.push_back(vec[middle + 1 + i]);
    }

    int i = 0;
    int j = 0;
    int k = lower;

    while(i < size1 && j < size2) {
        if(vec1[i] <= vec2[j]) {
            vec[k] = vec1[i];
            i++;
        }
        else {
            vec[k] = vec2[j];
            j++;
        }
        k++;
    }

    while(i < size1) {
        vec[k] = vec1[i];
        i++;
        k++;
    }

    while(j < size2) {
        vec[k] = vec2[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& vec, int lower, int upper) {

    if(lower < upper) {

        int middle = (lower + upper) / 2;

        mergeSort(vec, lower, middle);
        mergeSort(vec, middle+1, upper);

        merge(vec, lower, middle, upper);
    }
}


int partition(vector<int>& vec, int lower_border, int upper_border) {
    int pivot = vec[upper_border];
    int i = lower_border;

    for(int j=lower_border; j<upper_border; ++j) {

        if(vec[j] <= pivot) {
            swap(vec[i], vec[j]);
            ++i;
        }
    }
    swap(vec[i], vec[upper_border]);
    return i;

}

void quick_sort(vector<int>& vec, int lower_border, int upper_border) {
    if (lower_border < upper_border) {

        int pivot = partition(vec, lower_border, upper_border);

        quick_sort(vec, lower_border, pivot-1);
        quick_sort(vec, pivot+1, upper_border);
    }
}


long binary_search_iterative(vector<int>& vec, long lower_border, long upper_border, long P) {

    long middle = 0;

    while(lower_border <= upper_border) {
        middle = (lower_border + upper_border) / 2;
        if(vec[middle] > P) {
            upper_border = middle - 1;
        }
        else {
            lower_border = middle + 1;
        }
    }

    return upper_border;
}


int binary_search_sum(vector<long long>& vec, long lower_border, long new_up, long S) {

    long middle = 0;
    long upper = new_up;

    while(lower_border <= new_up) {
        cout<<"borders: "<<lower_border<<" "<<new_up<<" ";
        middle = (lower_border + new_up) / 2;
        long sum = vec[upper] - vec[middle];
        cout<<"sum: "<<sum<<endl;

        if(sum <= S) {
            new_up = middle - 1;
        }
        else {
            lower_border = middle + 1;
        }

    }
    cout<<"borders: "<<lower_border<<" "<<new_up<<endl;

    int res = upper - new_up - 1;
    if(res == upper) {
        res++;
    }
    return res;
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 0, Q = 0;
    scanf("%d",&N);
    scanf("%d",&Q);

    vector<int> numbers;
    vector<long long> sums;
    int number = 0;
    long long sum = 0;
    for(int i=0; i<N; ++i) {
        scanf("%d",&number);
        numbers.push_back(number);
    }

    //quick_sort(numbers, 0, N-1);
    mergeSort(numbers, 0, N-1);

    for(vector<int>::size_type i=0; i<numbers.size(); i++) {
        cout<<numbers[i]<<" ";
        sum += numbers[i];
        sums.push_back(sum);
    }
    cout<<endl;

    vector<pair<long, long>> intervals;

    long S = 0;
    long P = 0;

    for(int i=0; i<Q; ++i) {
        scanf("%ld",&S);
        scanf("%ld",&P);

        intervals.push_back(make_pair(S,P));
    }

    for(int i=0; i<Q; ++i) {

        /*vector<int>::iterator up;
        up = upper_bound(numbers.begin(), numbers.end(), P);

        int up_int = up - numbers.begin();
        cout<<up_int<<endl;

        while((sum + numbers[up_int-1]) <= intervals[i].first && up_int != 0) {
            up_int--;
            sum += numbers[up_int];
            counter++;
        }*/


        long new_up = binary_search_iterative(numbers, 0, N-1, intervals[i].second);
        cout<<new_up<<endl;
        long counter = 0;


        if(new_up < 10) {
            int sum = numbers[new_up];

            while(sum <= intervals[i].first && new_up >= 0) {
                ++counter;
                --new_up;
                sum += numbers[new_up];
            }
        }
        else {
            counter = binary_search_sum(sums, 0, new_up, intervals[i].first);
        }

         printf("%ld \n", counter);
         cout<<endl;

    }


    return 0;
}
