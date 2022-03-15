/*
Даден ви е символният низ s състоящ се от малки латински букви. Наставка на s ще наричаме подниз намиращ се накрая на s.
От вас се иска по даден s да намерите редицата от индекси обозначаващи началото на поредната наставка в редицата от 
наредени лексикографски наставки на s.
*/


#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    getline(cin, str);

    map<char, vector<int>> suff;

    for(int i = str.size()-1; i >= 0; i--) {
        suff[str[i]].push_back(i);
    }

    for(auto i : suff) {
        vector<int> vec = i.second;
        
        sort(vec.begin(), vec.end(), [&str](auto lhs, auto rhs) {
            return str.compare(lhs, str.size() - lhs, str, rhs, str.size() - rhs) < 0;});
        
        for(auto j : vec) {
            cout<<j<<" ";
        }
    }

    return 0;
}
