/*
    22100574 이지원
    (1) lecture slide chapter 24 floyd, dijkstra 전체
    (2) Blog: 
        다익스트라: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
        다익스트라: https://alswnsdl.tistory.com/13
        플로이드: https://ansohxxn.github.io/algorithm/floyd/
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <climits>

#define INF 1000000000
using namespace std;

int city_num;

// read data from file "hw6.txt"
void dataFromFile(string filename, vector<string>& Cities, vector<vector<int>>& Data) {
    ifstream file(filename);
    if (!file) {
        cout << "Failed to open file" << endl;
        return;
    }

    string line;

    while(getline(file, line)) {
        vector<int> d;
        string city;
        string distance;
        istringstream iss(line);

        iss >> city;
        Cities.push_back(city);
        while(iss >> distance) {
            if(distance == "INF")
                d.push_back(INF);
            else
                d.push_back(stoi(distance));
        }
        Data.push_back(d);
        d.clear();
    }

    file.close();
}

//This is a function for making area vectore.
//area vectore is used for printing result.
vector<string> CreateVector(string line){
    vector<string> vec;
    string str = "";
    
    //to split, make one line including one space between each area.
    for(int i=0; i<line.length(); i++){
        if(isspace(line[i]) == 0){
             str += line[i];
        }else{
             if(str.compare("") && str[str.length()-1] != ' '){
                 str += ' ';
             }
        }
    }
    istringstream ss(str);
    string stringBuffer;
    vec.clear();
    
    //split
    while(getline(ss, stringBuffer, ' ')){
        vec.push_back(stringBuffer);
    }
     
    return vec;
}

//Dijkstra algorithm
vector<int> Dijkstra(vector<pair<int, int>> *adj, int src){
    vector<int> dist(city_num, INT_MAX); //store the shortest distance
    dist[src] = 0;
    priority_queue<pair<int, int>> pd;
    pd.push(make_pair(0, src)); // put source node.
    
    while(!pd.empty()){
        int di = -pd.top().first; // distance from a node to next node.
        int n = pd.top().second; // number of node to visit
        
        pd.pop();
        
        if(dist[n] < di) continue;
        
        for(int i=0; i<adj[n].size(); i++){
            int there = adj[n][i].first;
            int nextDist = di + adj[n][i].second;
        
            if(dist[there] > nextDist){
                dist[there] = nextDist;
                pd.push(make_pair(-nextDist, there));
            }
        }
    }
    return dist;
}

int main(int argc, const char * argv[]) {
    vector<string> cities;
    vector<vector<int>> data;

    dataFromFile("hw6.txt", cities, data);       // Create array of adjacency list
    city_num = data.size();    // number of node

    string line; //read one line from text file.
    int word_size = 0;
    
    //if number of area is more than 30, terminate.
    if(city_num > 30){
        cout << "Number of nodes in the graph should be less than or equal to 30" << endl;
        return 0;
    }
    
    //adjacency vector. first int: adjacency node. second int: weight
    vector<pair<int, int>> adj[city_num];
    
    for(int i=0; i<city_num; i++){
        for(int j=0; j<city_num; j++){
            if(data[i][j] != 0 && data[i][j] != INF){
                adj[i].push_back(make_pair(j, data[i][j]));
            }
        }
    }
    
    //for setw
    for(int i=0; i<city_num; i++){
        if(word_size < int(cities[i].length()))
            word_size = int(cities[i].length());
    }
    word_size++;
    
    vector<int> dist_arr;
    
    //print Dijkstra algorithm
    cout << left;
    cout <<  setw(word_size) << "DIJKSTRA";
    for(int i=0; i<city_num; i++){
        cout << setw(word_size) << cities[i];
    }
    cout << endl;
    
    for(int i=0; i<city_num; i++){
        //call Dijkstra function for |V| times
        dist_arr = Dijkstra(adj, i);
        cout << setw(word_size) << cities[i];
        for(int j=0; j<city_num; j++){
            cout << setw(word_size) << dist_arr[j];
        }
        cout << endl;
    }
    cout << endl;
    
    //Floyd
    for(int k=0; k<city_num; k++){
        for(int i=0; i<city_num; i++){
            for(int j=0; j<city_num; j++){
                int temp = data[i][k] + data[k][j];
                if(temp < data[i][j])
                    data[i][j] = temp;
            }
        }
    }
    
    //print Floyd algorithm
    cout <<  setw(word_size) << "FLOYD";
    for(int i=0; i<city_num; i++){
        cout << setw(word_size) << cities[i];
    }
    cout << endl;
    
    for(int i=0; i<city_num; i++){
        cout << setw(word_size) << cities[i];
        for(int j=0; j<city_num; j++){
            cout << setw(word_size) << data[i][j];
        }
        cout << endl;
    }

    return 0;
}
