// https://modoocode.com/304  random number 생성
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

struct Item {
    int benefit, weight;
    float value;
};

// int BruteForce(vector<Item>& items, int size, int capa);
//int Greedy(vector<Item>& items, int n, int capa);
int DynamicProgramming(vector<Item>& items, int size, int capa);
// int BranchAndBound();
int max(int a, int b);

int main() {
    int n;
    int algo;
    int capacity;
    clock_t start, end;
    int maxProfit;
    double time_result;

    cout << "Input a number of items: ";
    cin >> n;
    vector<Item> items(n);
    capacity = n * 25;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> benefitDist(1, 500);
    uniform_int_distribution<int> weightDist(1, 100);

    for (int i=0; i<n; i++) {
        items[i].benefit = benefitDist(gen);
        items[i].weight = weightDist(gen);
        items[i].value = (float)(items[i].benefit / items[i].weight);
    }

    cout << "Choose an Algorithm.([1]Brute Force [2]Greedy [3]Dynamic Programming [4]Branch and Bound): ";
    cin >> algo;

    switch (algo) {
        /*
        case 1:
            start = clock();
            maxProfit = BruteForce(items, n, capacity);
            end = clock();
        case 2:
            start = clock();
            maxProfit = Greedy(items, n, capacity);
            end = clock();
        */
        case 3:
            start = clock();
            maxProfit = DynamicProgramming(items, n, capacity);
            end = clock();
        /*
        case 4:
            start = clock();
            maxProfit = BranchAndBound();
            end = clock();
        */
        default:
            break;
    }
    
    time_result = (double)(end - start);
    printf("result: %f/%d\n", time_result, maxProfit);

    return 0;
}

/*
int BruteForce(vector<Item>& items, int size, int capa) {
    int maxProfit = 0;

    for (int i=0; i<size; i++) {
        
    }
}

int Greedy(vector<Item>& items, int size, int capa){

    int w = capa;
    int benefit = 0;
    for (int i=0; i<size; i++) {
        if (items[i].weight > w) {
            benefit += items[i].value * w;
            break;
        }
        else {
            w -= items[i].weight;
            benefit += items[i].benefit;
            if (w == 0) break;
        }
    }
}
*/

int max(int a, int b) {
    return (a > b) ? a : b;
}

int DynamicProgramming(vector<Item>& items, int size, int capa) {
    int w = capa;
    int B[size][w];

    for (int i=0; i<size; i++) {
        for (int j=1; j<capa; j++) {
            if (i == 0 || j == 0)
                B[i][j] = 0;
            else if (items[i].weight <= w) {
                B[i][j] = max(items[i].benefit + B[i-1][j-items[i].weight], B[i-1][j]);
            }
            else
                B[i][j] = B[i-1][j];
        }
    }

    return B[size][w];
}