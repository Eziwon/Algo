// 'data.txt' 의 내용을 읽어오는 코드
#include <fstream>
#include <iostream>

using namespace std;
const int num_nodes = 5;

void Read_from_file(int distance[][num_nodes]);

int main () {
    int distance[num_nodes][num_nodes];
    Read_from_file(distance);
    return 0;
}

void Read_from_file(int distance[][num_nodes]) {
    ifstream inputFile ("data.txt");
    for (int i=0; i<num_nodes; i++) {
        for (int j=0; j<num_nodes; j++) {
            inputFile >> distance[i][j];
            cout << distance[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}