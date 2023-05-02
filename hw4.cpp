// https://modoocode.com/304  random number 생성
// https://hijuworld.tistory.com/1  processing time 구하기
// https://www.tutorialspoint.com/cplusplus-program-to-solve-knapsack-problem-using-dynamic-programming  dynamic programming

// branch and bound
#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

struct Item {
    int benefit, weight;
    double value;
};

struct Node {
    int level;
    int weight;
    int benefit;
    double bound;
};

void merge(vector<Item>& items, int left, int mid, int right);
void mergeSort(vector<Item>& items, int left, int right);
int max(int a, int b);
int BruteForce(vector<Item>& items, int size, int capa);
int Greedy(vector<Item>& items, int size, int capa);
int DynamicProgramming(vector<Item>& items, int size, int capa);
int BranchAndBound(vector<Item>& items, int size, int capa);

int main(){
    int n;
    char* algo;
    int capacity;
    int maxProfit;
    clock_t start, end;

    cout << "Input a number of items: ";
    cin >> n;
    vector<Item> items(n);
    capacity = n * 25;
    cout << "capacity is " << capacity << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> benefitDist(1, 500);
    uniform_int_distribution<int> weightDist(1, 100);

    for (int i=0; i<n; i++) {
        items[i].benefit = benefitDist(gen);
        items[i].weight = weightDist(gen);
        items[i].value = ((double)items[i].benefit / (double)items[i].weight);
        cout << "[" << i+1 << "] benefit = " << items[i].benefit << ", weight = " << items[i].weight << ", value = " << items[i].value << endl;
    }
    while(1) {
        cout << "Choose an Algorithm.([1]Brute Force [2]Greedy [3]Dynamic Programming [4]Branch and Bound): ";
        cin >> algo;
        if (strcmp(algo, "quit") == 0) break;

        switch (*algo)
        {
        case '1':
            start = clock();
            maxProfit = BruteForce(items, n, capacity);
            end = clock();
            break;
        case '2':
            start = clock();
            maxProfit = Greedy(items, n, capacity);
            end = clock();
            break;
        case '3':
            start = clock();
            maxProfit = DynamicProgramming(items, n, capacity);
            end = clock();
        case '4':
            start = clock();
            maxProfit = BranchAndBound(items, n, capacity);
            end = clock();
        default:
            break;
        }

        double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
        cout << "\nresult: " << elapsedTime << "/" << maxProfit << endl << endl;
    }

    return 0;
}

void merge(vector<Item>& items, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Item> leftItem(n1);
    vector<Item> rightItem(n2);

    for (int i = 0; i < n1; ++i)
        leftItem[i] = items[left + i];
    for (int j = 0; j < n2; ++j)
        rightItem[j] = items[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftItem[i].value >= rightItem[j].value) {
            items[k].value = leftItem[i].value;
            ++i;
        } else {
            items[k] = rightItem[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        items[k] = leftItem[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        items[k] = rightItem[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<Item>& items, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(items, left, mid);
    mergeSort(items, mid + 1, right);

    merge(items, left, mid, right);
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int BruteForce(vector<Item>& items, int size, int capa){
    if (size == 0 || capa == 0)
        return 0;
    int In, Out;
    if (items[size-1].weight <= capa) {
        In = items[size-1].benefit + BruteForce(items, size-1, capa-items[size-1].weight);
        Out = BruteForce(items, size-1, capa);
    }
    else return BruteForce(items, size-1, capa);
    return max(In, Out);
}

int Greedy(vector<Item>& items, int size, int capa) {
    mergeSort(items, 0, size-1);
    cout << "\n...Sorting ..." << endl;
    for (int i=0; i<size; i++) {
        cout << "[" << i+1 << "] benefit = " << items[i].benefit << ", weight = " << items[i].weight << ", value = " << items[i].value << endl;
    }

    int w = capa;
    int benefit = 0;
    cout << "\ndoing...\n";
    for (int i=0; i<size; i++) {
        if (items[i].weight > w) {
            benefit += items[i].value * w;
            cout << "[" << i+1 << "] Weight = " << w << ", " << "Benefit = " << benefit << endl;
            break;
        }
        else {
            w -= items[i].weight;
            benefit += items[i].benefit;
            cout << "[" << i+1 << "] Weight = " << w << ", " << "Benefit = " << benefit << endl;
            if (w == 0) break;
        }
    }
    return benefit;
}

int DynamicProgramming(vector<Item>& items, int size, int capa) {
    int B[size+1][capa+1];

    for (int i=0; i<=size; i++) {
        for (int w=0; w<=capa; w++) {
            if (i == 0 || w == 0)       
                B[i][w] = 0;
            else if (items[i-1].weight <= w) 
                B[i][w] = max(items[i-1].benefit + B[i-1][w-items[i-1].weight], B[i-1][w]);
            else 
                B[i][w] = B[i-1][w];
        }
    }
    return B[size][capa];
}

int Bound(Node& node, vector<Item>& items, int size, int capa){
    int totalWeight = node.weight;
    int upperBound = node.benefit;

    int level = node.level+1;

    while (level < size && totalWeight + items[level].weight <= capa) {
        totalWeight += items[level].weight;
        upperBound += items[level].value;
        level++;
    }

    if (level < size) {
        upperBound += (capa - totalWeight)*items[level].value;
    }

    return upperBound;
}

int BranchAndBound(vector<Item>& items, int size, int capa){
    mergeSort(items, 0, size-1);

    queue<Node> q;
    int max_profit = 0;
    Node root = {-1, 0, 0, 0.0};
    Node current, left, right;
    q.push(root);

    while (!q.empty()){
        current = q.front();
        q.pop();
        current.bound = Bound(current, items, size, capa);
        cout << "current: level " << current.level << ", weight " << current.weight << ", benefit " << current.benefit <<  ", bound " << current.bound << endl;
        if (current.bound >= max_profit) {
            left = {current.level+1, current.weight + items[current.level+1].weight, current.benefit + items[current.level+1].benefit, 0.0};
            if (left.weight <= capa) {
                left.bound = Bound(left, items, size, capa);
                cout << "left: level " << left.level << ", weight " << left.weight << ", benefit " << left.benefit <<  ", bound " << left.bound << endl;
                if (left.benefit > max_profit) max_profit = left.benefit;
                if (left.bound > max_profit) q.push(left);
            }

            right = {current.level+1, current.weight, current.benefit, 0.0};
            if (right.weight <= capa) {
                right.bound = Bound(right, items, size, capa);
                cout << "right: level " << right.level << ", weight " << right.weight << ", benefit " << right.benefit <<  ", bound " << right.bound << endl;
                if (right.bound > max_profit) q.push(right);
            }
        }
    }
    return max_profit;
}