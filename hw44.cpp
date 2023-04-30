// https://modoocode.com/304  random number 생성

// brute force
// dynamic programming
// branch and bound
#include <iostream>
#include <random>
#include <vector>
#include <ctime>

using namespace std;

struct Item
{
    int benefit, weight;
    double value;
};

void merge(vector<Item>& items, int left, int mid, int right);
void mergeSort(vector<Item>& items, int left, int right);
int Greedy(vector<Item>& items, int size, int capa);
int DynamicProgramming(vector<Item>& items, int size, int capa);
int max(int a, int b);

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
        case '2':
            start = clock();
            maxProfit = Greedy(items, n, capacity);
            end = clock();
            break;
        case '3':
            start = clock();
            maxProfit = DynamicProgramming(items, n, capacity);
            end = clock();
        default:
            break;
        }

        double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
        cout << "\nresult: " << elapsedTime << "/" << maxProfit << endl;
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

int max(int a, int b){
    return (a > b) ? a : b;
}

int DynamicProgramming(vector<Item>& items, int size, int capa) {
    vector<vector<int>> dp(size + 1, vector<int>(capa+1, 0));
    for (int i = 1; i <= size; ++i) {
        for (int w = 1; w <= capa; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    int W = capa;

    for (int i=0; i<size; i++) {
        for (int w=0; w<capa; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i].weight <= W) 
                dp[i][w] = max(items[i].benefit + dp[i-1][w-items[i].weight], dp[i-1][w]);
            else 
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[size][capa];
}