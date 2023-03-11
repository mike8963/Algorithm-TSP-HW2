#ifndef __TSP_H__
#define __TSP_H__

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>
#include <map>

using namespace std;

typedef struct TSPset{
    unsigned int* route;
    double total_distance;
}SET_;

class city{
    public:
        city(string,double,double);
        string getName();
        double get_x();
        double get_y();
        friend double distance(city,city);
    private:
        string cityname;
        double x;
        double y;
};

class TSP{
    public:
        TSP(char*);
        SET_ get_shortest_distance();
        void output();
    private:
        int count_for_visited; // 紀錄已探訪的City數量
        int* visited; // 紀錄已探訪的 City; 0 代表未探訪 1~n代表探訪順序
        
        double** distance_between_city; // 紀錄 city 之間的距離
        fstream fin; // 讀取檔案
        vector<city> cityList;

};

#endif
