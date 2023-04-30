// https://modoocode.com/304  random number 생성

// brute force
// Greedy
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

int main(){
    int n, algo;
    int capacity;
    int maxProfit;
    clock_t start, end;

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
        items[i].value = ((double)items[i].benefit / (double)items[i].weight);
        cout << "[" << i << "] benefit = " << items[i].benefit << ", weight = " << items[i].weight << ", value = " << items[i].value << endl;
    }

    cout << "Choose an Algorithm.([1]Brute Force [2]Greedy [3]Dynamic Programming [4]Branch and Bound): ";
    cin >> algo;

    switch (algo)
    {
    case 2:
        start = clock();
        maxProfit = Greedy(items, n, capacity);
        end = clock();
        break;
    
    default:
        break;
    }

    double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << "result: " << elapsedTime << "/" << maxProfit << endl;

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
    return benefit;
}