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
            items[k] = leftItem[i];
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

int Bound(Node& node, vector<Item>& items, int size, int capa){
    int totalWeight = node.weight;
    int upperBound = node.benefit;
    int level = node.level+1;

    while (level < size && totalWeight + items[level].weight <= capa) {
        totalWeight += items[level].weight;
        upperBound += items[level].benefit;
        level++;
    }

    if (level < size) {
        upperBound += static_cast<int>((capa - totalWeight)*items[level].value);
    }

    return upperBound;
}

int BranchAndBound(vector<Item>& items, int size, int capa){
    cout << "Branch and Bound\n";
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
        if (current.bound >= max_profit) {
            if (current.level+1 < size) {
                left = {current.level+1, current.weight + items[current.level+1].weight, current.benefit + items[current.level+1].benefit, 0.0};
                if (left.weight <= capa) {
                    left.bound = Bound(left, items, size, capa);
                    if (left.benefit > max_profit) max_profit = left.benefit;
                    if (left.bound > max_profit) q.push(left);
                }
                right = {current.level+1, current.weight, current.benefit, 0.0};
                if (right.weight <= capa) {
                    right.bound = Bound(right, items, size, capa);
                    if (right.bound > max_profit) q.push(right);
                }
            }
        }
    }
    return max_profit;
}

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
    }
    
     
        start = clock();
        maxProfit = BranchAndBound(items, n, capacity);
        end = clock();

        double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
        cout << "\nresult: " << elapsedTime << "/" << maxProfit << endl << endl;

    return 0;
}