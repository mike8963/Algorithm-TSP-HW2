#include "tsp.hpp"

TSP::TSP(char* filename)
{
    string cityname;
    double temp_x;
    double temp_y;
    cityList.clear();

    // read file
    fin.open(filename); 
    if(!fin.is_open()){
        throw filename;
    }
    else{
        while(fin >> cityname)
        {
            fin >> temp_x;
            fin >> temp_y;
            cityList.push_back(city(cityname,temp_x,temp_y));
        }

        // 動態宣告2d array
        distance_between_city = new double*[cityList.size()];
        for(unsigned int i=1;i<cityList.size();i++)
        {
            distance_between_city[i] = new double[i];
        }
        // 儲存各city間距離
        for(unsigned int i=1;i<cityList.size();i++)
        {
            for(unsigned int j=0;j<i;j++)
            {
                distance_between_city[i][j] = distance(cityList[i],cityList[j]);
            }
        }
        //初始化探訪city順序(0 為未探訪)
        visited = new int[cityList.size()];
        visited[0] = 0;
        for(unsigned int i=1;i<cityList.size();i++)
        {
            visited[i] = 0;
        }
        // 初始化探訪過city數量為 0
        count_for_visited = 0;
    }
};

//return {saleman in which city, {route}, total distance}
SET_ TSP::get_shortest_distance()
{
    //initialize minimum to upper limit of type double
    double minimum = std::numeric_limits<double>::max();
    SET_ re;//return set

    unsigned int listN = cityList.size();		//number of cities

    //leaf node: return {{0}, 0.0}	!!lower boundary
    if((unsigned int)count_for_visited == listN){
        re.route = (unsigned int*)malloc(sizeof(unsigned int));
        re.route[0] = 0;
        re.total_distance = 0.0;
        return re;
    }

    //record the minimum situation
    SET_ minset;
    int minindex;

    //root node: return {{optimize tsp route}, shortest distance} !!upper boundary
    if(count_for_visited == 0){
        count_for_visited = 1;
        visited[0] = 1;
        count_for_visited++;
        for(unsigned int i=1;i<listN;i++){
            visited[i] = count_for_visited;

            SET_ temp = get_shortest_distance();

            if(i >= temp.route[0])
                temp.total_distance += distance_between_city[i][temp.route[0]];
            else
                temp.total_distance += distance_between_city[temp.route[0]][i];
            //don't forget the distance between first and second cities
            temp.total_distance += distance_between_city[i][0];

            if(temp.total_distance < minimum){
                minimum = temp.total_distance;
                minset = temp;
                minindex = i;
            }

            visited[i] = 0;
        }
        count_for_visited--;            
        //save minimum distance route to SET_ re
        re.total_distance = minset.total_distance;

        re.route = (unsigned int*)malloc(sizeof(unsigned int)*(listN+1));
        re.route[0] = 0;
        re.route[1] = minindex;
        for(unsigned int i=2;i<listN+1;i++)
            re.route[i] = minset.route[i-2];
        return re;
    }

    //normal node
    count_for_visited++;
    for(unsigned int i=1;i<cityList.size();i++){
        if(visited[i] == 0){
            visited[i] = count_for_visited;

            SET_ temp = get_shortest_distance();

            if(i >= temp.route[0])
                temp.total_distance += distance_between_city[i][temp.route[0]];
            else
                temp.total_distance += distance_between_city[temp.route[0]][i];
            if(temp.total_distance < minimum){
                minimum = temp.total_distance;
                minset = temp;
                minindex = i;
            }

            visited[i] = 0;
        }
    }
    count_for_visited--;

    //length of route
    unsigned int length_of_route = listN-count_for_visited+1;

    re.route = (unsigned int*)malloc(sizeof(unsigned int)*(length_of_route));
    re.route[0] = minindex;
    for(unsigned int i=1;i<length_of_route;i++)
        re.route[i] = minset.route[i-1];

    re.total_distance = minset.total_distance;

    return re;
    /*for(unsigned int i=0;i<cityList.size();i++)
    {
        cout << cityList[i].getName() << "\t" << cityList[i].get_x() << "\t" << cityList[i].get_y() << endl;
    }
    return re;*/
}
void TSP::output(){
    SET_ rootset = get_shortest_distance();
    
    for(unsigned int i=0;i<=cityList.size();i++)
        cout << cityList[rootset.route[i]].getName() << " ";
    cout << endl << "distance: " << rootset.total_distance << endl;
}
