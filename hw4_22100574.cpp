// https://modoocode.com/304  random number 생성
// https://hijuworld.tistory.com/1  processing time 구하기
// https://www.tutorialspoint.com/cplusplus-program-to-solve-knapsack-problem-using-dynamic-programming  dynamic programming
// chatGPT
// 강의 slide chapter 6. page 16-21

// did not implement data size greater than 60 of branch and bound approach
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

int BruteForce(vector<Item>& items, int size, int capa);
void merge(vector<Item>& items, int left, int mid, int right);
void mergeSort(vector<Item>& items, int left, int right);
int max(int a, int b);
int Greedy(vector<Item>& items, int size, int capa);
int DynamicProgramming(vector<Item>& items, int size, int capa);
int Bound(Node& node, vector<Item>& items, int size, int capa);
int BranchAndBound(vector<Item>& items, int size, int capa);

int main(){
    int n;
    char* algo;
    int capacity;
    int maxProfit;
    clock_t start, end;

    // item의 수 입력받기
    cout << "Input a number of items: ";
    cin >> n;
    vector<Item> items(n);      // item 구조체 할당
    capacity = n * 25;          // capacity 값 설정
    cout << "capacity is " << capacity << endl;

    // 랜덤 수 할당
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> benefitDist(1, 500);
    uniform_int_distribution<int> weightDist(1, 100);
    for (int i=0; i<n; i++) {
        items[i].benefit = benefitDist(gen);
        items[i].weight = weightDist(gen);
        items[i].value = ((double)items[i].benefit / (double)items[i].weight);
    }

    // 같은 랜덤 수로 알고리즘끼리 비교하기 위해 while문을 사용하여 quit을 입력하기 전까지 계속 구하기
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
            break;
        case '4':
            start = clock();
            maxProfit = BranchAndBound(items, n, capacity);
            end = clock();
            break;
        default:
            break;
        }

        double elapsedTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
        cout << "\nresult: " << elapsedTime << "/" << maxProfit << endl << endl;        // 결과 출력    "processing time / maxprofit"
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
    // base case of recursion
    if (size == 0 || capa == 0)
        return 0;
    int In, Out;

    // 만약 size-1번째 아이템의 weight이 capacity보다 작으면
    // 현재 아이템을 knapsack에 포함(In)한 것과
    // 포함하지 않은 것(Out)을 구하기
    if (items[size-1].weight <= capa) {
        In = items[size-1].benefit + BruteForce(items, size-1, capa-items[size-1].weight);
        Out = BruteForce(items, size-1, capa);
    }

    // 그게 아니라면( size-1번째 아이템의 weight이 capacity보다 크면 ) knapsack에 포함하지 않으
    else return BruteForce(items, size-1, capa);

    // 현재 아이템을 넣은 것과 넣지 않은 것 중 더 큰 benefit을 가지는 값을 리턴
    return max(In, Out);
}

int Greedy(vector<Item>& items, int size, int capa) {
    cout << "Greedy\n";
    // item의 value값을 기준으로 sorting
    mergeSort(items, 0, size-1);

    int w = capa;
    int benefit = 0;

    for (int i=0; i<size; i++) {
        // 만약 현재 아이템의 무게가 넣을 수 있는 무게보다 많으면
        // 잘라서 넣기
        if (items[i].weight > w) {
            benefit += items[i].value * w;
            break;
        }
        // 그게 아니라면 다 넣기
        // 앞으로 더 넣을 수 있는 무게 수(w)를 현재 아이템의 무게만큼 줄이고
        // 지금까지 얻은 benefit에 현재 아이템의 benefit 더해주기
        // w가 0이 되면 끝내기
        else {
            w -= items[i].weight;
            benefit += items[i].benefit;
            if (w == 0) break;
        }
    }
    return benefit;
}

int DynamicProgramming(vector<Item>& items, int size, int capa) {
    cout << "DP\n";
    // intermediate results를 저장하기 위해 vector 선언
    vector<vector<int>> B(size+1, vector<int>(capa+1,0));

    for (int i=1; i<=size; i++) {   // i는 item의 index를 나타내고 w는 현재 capacity를 나타냄
        Item currentItem = items[i-1];
        for (int w=1; w<=capa; w++) {
            if (i == 1 || w == 1)       
                B[i-1][w-1] = 0;        // base case ->  B[0][] 과 B[][0]의 값 = 0
            
            // 현재 아이템의 무게가 다 들어갈 수 있으면
            // 현재 아이템을 knapsack에 넣는 것과 넣지 않는 것 중 더 큰 benefit을 가지는 것을 선택
            else if (currentItem.weight <= w) 
                B[i][w] = max(currentItem.benefit + B[i-1][w-currentItem.weight], B[i-1][w]);
            
            // 그게 아니면 넣지 않음
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

    // level의 크기가 items의 수를 넘지 않고, 다음 item을 knapsack에 전부 넣을 수 있으면
        // 총 무게 = 원래 총 무게 + 다음 아이템의 무게
        // bound = 원래 bound + 다음 아이템의 benefit
    while (level < size && totalWeight + items[level].weight <= capa) {
        totalWeight += items[level].weight;
        upperBound += items[level].benefit;
        level++;
    }

    // level의 크기가 items의 수를 넘지 않지만, 전체를 다 넣을 수 없는 경우
        // 잘라서 넣어주기
    if (level < size) {
        upperBound += static_cast<int>((capa - totalWeight)*items[level].value);
    }

    return upperBound;
}

int BranchAndBound(vector<Item>& items, int size, int capa){
    cout << "Branch and Bound\n";
    // item의 value값을 기준으로 sorting
    mergeSort(items, 0, size-1);

    queue<Node> q;      // tree의 node를 저장하기 위해
    int max_profit = 0;
    Node root = {-1, 0, 0, 0.0};
    Node current, left, right;
    q.push(root);

    while (!q.empty()){
        current = q.front();
        q.pop();
        current.bound = Bound(current, items, size, capa);
        // bound가 지금까지 얻은 실제 최대 이익 (max_profit)보다 크면 -> tree 확장
        if (current.bound >= max_profit) {
            // 다음 레벨로 가도 item의 사이즈를 넘지 않으면
            if (current.level+1 < size) {
                // left: 다음 item을 knapsack에 넣는 경우
                // knapsack에 넣을 수 있다면
                    // bound값 계산하기
                    // 확장 후 benefit이 현재보다 크다면 max_profit = left.benefit
                    // bound가 지금까지 얻은 실제 최대 이익 (max_profit)보다 크면 -> tree에 집어 넣기
                left = {current.level+1, current.weight + items[current.level+1].weight, current.benefit + items[current.level+1].benefit, 0.0};
                if (left.weight <= capa) {
                    left.bound = Bound(left, items, size, capa);
                    if (left.benefit > max_profit) max_profit = left.benefit;
                    if (left.bound > max_profit) q.push(left);
                }
                // right: 다음 item을 knapsack에 넣지 않는 경우
                // knapsack에 넣을 수 있다면
                    // bound값 계산하기
                    // bound가 지금까지 얻은 실제 최대 이익 (max_profit)보다 크면 -> tree에 집어 넣기
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