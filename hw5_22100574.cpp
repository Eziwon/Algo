// 22100574 이지원
// https://iq.opengenus.org/transpose-graph/    알고리듬 참조
// https://myprivatestudy.tistory.com/48        istringstream 사용법
// 교수님께서 제공해주신 'graph_const_7.cpp' 파일
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const int num_nodes = 20;

// 파일애서 인덱스가 몇개인지 (vertex의 개수) 파악하는 함수
int numberNode(string line) {
    istringstream iss (line);
    string header;
    int n = 0;
    while(iss >> header) n++;

    // node의 개수가 20보다 큰 경우, 20으로 맞춰주기
    if (n > num_nodes) n = num_nodes;

    return n;
}

int main() {
    // 파일 읽어오기
    ifstream file("hw5_data.txt");

    string line;
    getline(file, line);
    int count;

    // node의 개수 파악
    count = numberNode(line);

    int edge[count][count];     // edge의 방향을 저장
    char node[count];           // node의 이름(알파벳 저장)
    string rows[count];         // 파일로부터 한 행씩 읽어와서 저장

    // edge라는 배열에 값 저장
    for (int i=0; i<count; i++){
        getline(file, rows[i]);
        istringstream row (rows[i]);
        row >> node[i];
        for (int j=0; j<count; j++) {
            row >> edge[i][j];
        }
    }

    // 파일 사용 완료 후 닫아주기
    file.close();

    // 데이터로 부터 가져온 원래 그래프 출력하기
    cout <<  "Original graph: " << endl;
    cout << line << endl;
    for (int i=0; i<count; i++) 
        cout << rows[i] << endl;
    cout <<  endl;

    int n_temp;         // node 저장용 temp
    string r_temp;      // rows 저장용 temp
    int e_temp;         // edge 저장용 temp

    // 알파벳 순서로 되어 있지 않다면 알파벳 순서로 바꿔주기
    for (int i=0; i<count; i++) {
        for (int j=0; j<i; j++) {
            // i번째 노드가 이전 노드보다 알파벳의 순서가 작다면 -> sorting이 필요한 경우
            if (node[i] < node[j]) {
                // node의 값 바꿔주기
                n_temp = node[j];
                node[j] = node[i];
                node[i] = n_temp;

                // 행 바꿔주기
                for (int k=0; k<count; k++) {
                    e_temp = edge[j][k];
                    edge[j][k] = edge[i][k];
                    edge[i][k] = e_temp;
                }

                // 열 바꿔주기
                for (int k=0; k<count; k++) {
                    e_temp = edge[k][j];
                    edge[k][j] = edge[k][i];
                    edge[k][i] = e_temp;
                }
            }
        }
    }

    // 알파벳 순으로 정렬된 그래프 출력하기
    cout << "Sorting Graph: " << endl;
    // node name 출력
    cout << "\t";
    for (int i=0; i<count; i++) cout << node[i] << "\t";
    cout << endl;
    // edge 출력
    for (int i=0; i<count; i++) {
        cout << node[i] << "\t";
        for (int j=0; j<count; j++) {
            cout << edge[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    
    int transpose[count][count];     // Transpose 를 저장할 변수

    // 서로 방향 바꿔주기 (Transpose)
    for (int i=0; i<count; i++) 
        for (int j=0; j<count; j++) 
            transpose[i][j] = edge[j][i];

    // Transpose 한 그래프 출력하기
    cout << "Transpose Graph: " <<endl;
    // node name 출력
    cout << "\t";
    for (int i=0; i<count; i++) cout << node[i] << "\t";
    cout << endl;
    // edge 출력
    for (int i=0; i<count; i++) {
        cout << node[i] << "\t";
        for (int j=0; j<count; j++) {
            cout << transpose[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Bye!" << endl;
    
    return 0;
}