/*
Имате даден претеглен неориентиран граф с N върха номерирани с числата от 0 до N-1 и M ребра. Върховете на графа са 
разделени на 2 множества: S и T. Всеки връх на графа е или в първото или във второто множество.

Напишете програма, която отговаря на Q заявки. Всяка заявка се състои от връх от множеството S. Вие трябва да отговорите 
колко е минималното разстояние до връх от множеството T.
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <climits>
using namespace std;


int main() {

    long N = 0, M = 0;
    cin>>N>>M;

    vector<pair<long, long>> graph[N+1];
    for(long i = 0; i < M; i++) {
        long u = 0, v = 0, w = 0;
        cin>>u>>v>>w;

        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }

    long K = 0;
    cin>>K;

    for(long i = 0; i < K; i++) {
        long input = 0;
        cin>>input;
        //T.insert(input);
        graph[N].push_back(make_pair(input, 0));
    }

    priority_queue<pair<long, long>, vector<pair<long, long>> , greater<pair<long, long>>> pq;
    vector<long> dist(N+1, LONG_MAX);

    pq.push(make_pair(0, N));
    dist[N] = 0;

    while(!pq.empty()) {
        long u = pq.top().second;
        pq.pop();

        vector<pair<long, long>>::iterator i;
        for(i = graph[u].begin(); i != graph[u].end(); ++i) {
            long v = (*i).first;
            long weight = (*i).second;

            long tmp = dist[u] + weight;
            if(dist[v] > tmp) {
                dist[v] = tmp;
                pq.push(make_pair(dist[v], v));
            }
        }
    }


    long Q = 0;
    cin>>Q;
    for(long i = 0; i < Q; i++) {
        long input = 0;
        cin>>input;
        cout<<dist[input]<<endl;
    }

    return 0;
}
