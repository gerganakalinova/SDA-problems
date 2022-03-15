/*
Дадени са ви N точки в двумерна координатна система, всяко от които е зададена по стандартният начин с две координати (x,y). 
Намерете изпъкналия полигон с най-малък периметър, такъв че всички точки лежат или във вътрешността му или на периметъра му.
*/


#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;
};

bool operator<(Point a, Point b) {
    if(a.x < b.x) {
        return true;
    }
    else if(a.x == b.x) {
        if(a.y < b.y) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}


double distance(Point a, Point b) {
    long dist =(a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    return sqrt(dist);
}


bool direction(Point a, Point b, Point c) {
    int dir = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

    if(dir < 0) {
        return true;
    }
    else {
        return false;
    }
}


double perimeter(vector<Point> vec) {
    double P = distance(vec[0], vec[vec.size() - 1]);

    for(int i = 0; i < vec.size() - 1; i++) {
        P += distance(vec[i], vec[i + 1]);
    }

    return P;
}


vector<Point> poligon(vector<Point> points) {
    if(points.size() <= 3) {
        return points;
    }

    vector<Point> poligon_points;
    int first_point_index = 0;
    int curr_point_index = 0;
    int next_point_index = 0;
    
    do {
            
        poligon_points.push_back(points[curr_point_index]);
        next_point_index = curr_point_index + 1;
    
        for(int i = 0; i < points.size(); i++) {
           if(direction(points[curr_point_index], points[i], points[next_point_index]) == true)
               next_point_index = i;
        }

        curr_point_index = next_point_index;

    } while (curr_point_index != first_point_index);

    return poligon_points;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
      cout << fixed << setprecision(2);

    int N = 0;
    cin>>N;

    vector<Point> points;
    Point point;
    for(int i=0; i<N; i++) {
        cin>>point.x>>point.y;
        points.push_back(point);
    }

    sort(points.begin(), points.end());

    vector<Point> vec = poligon(points);
    cout<<perimeter(vec);


    return 0;
}
