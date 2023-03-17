#if 1
#include <iostream>
using namespace std;

struct Element {
    char name[10];
    int id;
    char school[20];
};

const int MAX_HEAP_SIZE = 30;

class Minpriority {
public:
    Element heap[MAX_HEAP_SIZE];
    int size;
};

using element = Element*;

//insert를 위한 정보를 입력받는 function
void insert(element h, element k) {
    cout << "Enter name of element: " ;
    cin >> k->name;
    cout << "Enter id of element: ";
    cin >> k->id;
    cout << "Enter school of element: ";
    cin >> k->school;
    return;
}


int main() {
    char m;     //입력 받을 menu
    Element que[30];
    Element e;
    int size = 1;
    
    while(1) {
        cout << "*********** MENU ****************" << endl;
        cout << "I : Insert new element into queue." << endl;
        cout << "D : Delete element with smallest key from queue." << endl;
        cout << "C : Decrease key of element in queue." << endl;  
        cout << "P : Print out all elements in queue." << endl;
        cout << "Q : Quit" << endl << endl;

        cout << "Choose menu: ";
        cin >> m;
        // Q를 입력받은 경우 반복 중지
        if (m == 'Q') break;
        // if (m == 'I') 삽입하는 함수 호출
        else if (m == 'I') {
            // insert할 정보를 입력받고
            insert(que, &e);
            // insert(S, x) 를 이용해서 집합 S에 요소 x를 집어넣기
            que[size] = e;
            cout << "New element [" << que[size].name << ", " << que[size].id << ", " << que[size].school << "] is inserted." << endl << endl;
            size++;
        }
        else if (m == 'D') {
            // min-priority로 정렬 후
            // 1번 키의 정보 출력 후
            // 정보 지우기
        }
        else if (m == 'C') {
            // 바꿀 인덱스 입력받고
            // id value 값을 입력받아서 바꾸고
            // min-priority로 정리
        }
        else if (m == 'P') {
            // 인덱스 순으로 출력하기
            for (int i=size-1; i>0; i--) {
                cout << "[" << que[i].name << ", " << que[i].id << ", " << que[i].school << "] "; 
            }
            cout << endl << endl;
        }
        else cout << "Retry!" << endl;
    }
    
    cout << "Thank you, Bye!" << endl << endl;
    
    return 0;
}
#endif

#if 0

#include <iostream>
#include <string>
using namespace std;

const int MAX_HEAP_SIZE = 30;

struct Element {
    string name;
    int id;
    string school;
};

class MinPriorityQueue {
private:
    Element heap[MAX_HEAP_SIZE];
    int size;

    int parent(int i) {
        return i / 2;
    }

    int left(int i) {
        return 2 * i;
    }

    int right(int i) {
        return 2 * i + 1;
    }

    void minHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l <= size && heap[l].id < heap[i].id) {
            smallest = l;
        }
        if (r <= size && heap[r].id < heap[smallest].id) {
            smallest = r;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            minHeapify(smallest);
        }
    }

public:
    MinPriorityQueue() {
        size = 0;
    }

    void insert(Element x) {
        if (size >= MAX_HEAP_SIZE) {
            cout << "Heap overflow!" << endl;
            return;
        }
        size++;
        heap[size] = x;
        int i = size;
        while (i > 1 && heap[parent(i)].id > heap[i].id) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    Element minimum() {
        if (size < 1) {
            cout << "Heap underflow!" << endl;
            return {"", 0, ""};
        }
        return heap[1];
    }

    Element extractMin() {
        if (size < 1) {
            cout << "Heap underflow!" << endl;
            return {"", 0, ""};
        }
        Element min = heap[1];
        heap[1] = heap[size];
        size--;
        minHeapify(1);
        return min;
    }

    void decreaseKey(int i, int k) {
        if (k > heap[i].id) {
            cout << "New key is larger than current key!" << endl;
            return;
        }
        heap[i].id = k;
        while (i > 1 && heap[parent(i)].id > heap[i].id) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void printHeap() {
        for (int i = 1; i <= size; i++) {
            cout << heap[i].name << " " << heap[i].id << " " << heap[i].school << endl;
        }
    }
};

int main() {
    MinPriorityQueue pq;
    char choice;
    while (true) {
        cout << "Enter I to insert element, D to extract minimum element, C to decrease key, P to print heap, or Q to quit: ";
        cin >> choice;
        if (choice == 'I') {
            Element x;
            cout << "Enter name, ID, and school of student: ";
            cin >> x.name >> x.id >> x.school;
            pq.insert(x);
        } else if (choice == 'D') {
            Element min = pq.extractMin();
            if (min.id != 0) {
                cout << "Minimum element is: " << min.name << " " << min.id << " " << min.school << endl;
           

#endif