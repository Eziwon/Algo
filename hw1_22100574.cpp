/*
참고자료:
(1) 데이터 구조 수업 때 직접 짠 Heapsort 코드
(2) blog
    - https://coding-factory.tistory.com/697
    - https://develop-dream.tistory.com/91
    - https://www.delftstack.com/ko/howto/cpp/compare-strings-ignore-case-cpp/
    - https://kyu9341.github.io/C-C/2020/01/17/C++getline()/
*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// Assume maximun heap size is 30.
const int MAX_HEAP_SIZE = 30;
const int MAX_NAME_SIZE = 10;

struct Element {
    string name;
    int id;
    string school;
};

class minPriority {
public:
    Element heap[MAX_HEAP_SIZE];
    int size = 0;

    Element nElement() {    // 새로운 요소를 입력받는 함수
        Element x;                                      // 입력받기용 구조체 선언
        string s[] = {"Handong", "Doodong", "Sedong"};  // 1. 학교 이름을 저장한 string 배열
        int s_size = sizeof(s)/sizeof(string);          // 2. 저장되어 있는 학교의 수           --> 이 두가지 선언을 통해 추후에 학교를 확장하기 쉽게 함
        int flag = 0; 

        // 이름 입력받기 -> 10글자가 넘는 경우에는 다시 입력받기
        while(1) {
            cout << "Enter name of element: ";
            cin.ignore();
            getline(cin, x.name);                                           // 공백을 포함하여 입력받기
            if (x.name.length() <= MAX_NAME_SIZE) break;                    // 1. 입력받은 이름의 길이가 10보다 작아야 한다.
            cout << "Retry! (at most 10 characters)" << endl << endl;       // 2. 그렇지 않으면(10보다 크면) 다시 입력받기
        }

        // id 입력받기 -> 4 digit number가 아닌 경우 다시 입력받기
        while(1) {
            cout << "Enter id of element: ";
            cin >> x.id;
            if (x.id > 999 && x.id < 10000) break;              // 1. 4 digit number가 아닌 경우 다시 입력받기 -> 999보다 크고 10000보다 작아야 한다.
            cout << "Retry! (1000~9999)" << endl << endl;       // 2. 그렇지 않으면 다시 입력받기
        }
        
        // 학교 입력 받기 -> 학교 이름이 배열에 저장되어 있는 값(Handong, Doodong, Sedong)과 다르면 다시 입력받기
        while(1) {
            cout << "Enter school of element: " ;
            cin >> x.school;
            for (int i=0; i<s_size; i++) {      
                if (strcasecmp(x.school.c_str(), s[i].c_str()) == 0)    // 학교의 이름 대소문자 구분 없이 입력받기. 이름이 같다면?
                    flag = 1;                                           // flag = 1     (flag=0은 학교의 이름이 일치하지 않음/ flag=1은 학교의 이름이 일치함)
            }
            if (flag == 1) break;                                                                               // 학교 이름을 잘 입력받았다면, 반복문 빠져나오기
            cout <<  "Retry! ('school' is either \"Handong\", \"Doodong\", or \"Sedong\".)" << endl << endl;    // 그렇지 않으면 다시 입력받기
        }
        // 새롭게 입력받은 x 요소를 return
        return x;
    }
    
    // funciton that inserts element x into set S.
    void insert(Element S[], Element a) {
        // 이미 30명이 찬 경우 -> 더이상 입력받지 않음
        if (size > MAX_HEAP_SIZE) {
            cout << "Overflow!" <<endl;
            return;
        }
        S[++size] = a;                                          // a에 있는 요소를 S에 넣기
        if (S[size/2].id > S[size].id) heapsort(S, size/2);    // 새롭게 입력한 요소의 key값이 parent의 key값보다 작은 경우 -> heap으로 정렬
        return;
    }

    // 두 요소를 바꿔주는 함수
    void swap(Element S[], int k, int j) {
        Element temp;
        temp = S[k];        // temp 안에 S[k]를 저장해놓고
        S[k] = S[j];        // S[k]에 S[j]의 값을 저장
        S[j] = temp;        // S[j]에는 temp 안에 저장해놨던 S[k]의 값을 저장
        return;
    }

    // child와 parent의 key값을 비교하여 바꿔주는 함수
    void sink(Element S[], int k) {
        while (2*k <= size) {
            int j = 2*k;                                    // k: parent의 index    j: left child의 index
            if (j<size && S[j].id > S[j+1].id) j++;         // j가 배열의 사이즈보다 작고, left child의 key값보다 right child의 key값이 작은 경우 -> j: right child의 index
            if (S[k].id < S[j].id) break;                   // parent의 key 값이 child의 key값보다 작으면 -> while문 종료
            swap(S, k, j);                                  // 그게 아니면(child의 값이 더 작으면) --> 두 요소를 바꿔주고
            k = j;                                          // 그 아래로 내려가 또 비교해준다. (자식 노드가 없을 때 까지 비교) 
        }
        return;
    }

    // heap으로 정렬하는 함수
    void heapsort(Element S[], int k) {
        // S의 인덱스 역할을 하는 k 가 0이 될 때까지 반복해서 child와 parent를 비교한다.
        while(k>0) {
            sink(S, k--);
            //k--;
        }
        return;
    }

    // function that returns element of S with smallest key.
    Element minimun(Element S[]) {
        return S[1];        // 이미 항상 배열의 첫번쨰 요소가 가장 작은 값이기 때문에 S[1]을 return 해준다.
    }

    // function that removes and returns element of S with smallest key.
    void extract_min(Element S[]) {
        Element min = minimun(S);       // smallest key를 가지고 있는 S를 return하는 함수를 통해 min 요소를 구한다.
        cout << "[" << min.name << ", " << min.id << ", " << min.school << "] is deleted." << endl << endl;     // min 요소의 정보를 출력하고
        for (int i=1; i<=size; i++) S[i] = S[i+1];      // 해당 요소 지우기 -> 해당
        size--;
        heapsort(S, size/2);
        return;
    }
    
    // function that decreases value of element x's key to k.
    void decrease_key(Element S[], int x, int k) {
        S[x].id = k;                // x번째 index의 key값을 k로 바꾸기
        heapsort(S, x);             // 바꾼 값에 따라 heap 정렬
        return;
    }
};

int main() {
    char menu;
    minPriority pq;

    while(1) {
        cout << "*********** MENU ****************" << endl;
        cout << "I : Insert new element into queue." << endl;
        cout << "D : Delete element with smallest key from queue." << endl;
        cout << "C : Decrease key of element in queue." << endl;  
        cout << "P : Print out all elements in queue." << endl;
        cout << "Q : Quit" << endl << endl;

        cout << "Choose menu: ";
        cin >> menu;


        // 'Q'를 입력받은 경우 -->  실행 종료
        if (menu == 'Q') break;

        // 'I'를 입력받은 경우 --> Insert new element into queue.
        if (menu == 'I') {
            Element x = pq.nElement();      // 새로운 요소의 값 입력받고
            pq.insert(pq.heap, x);          // 배열에 min-priority queue 형식으로 저장하기
            cout << "New element [" << x.name << ", " << x.id << ", " << x.school << "] is inserted." << endl << endl;
        }

        // 'D'를 입력받은 경우 --> Delete element with smallest key from queue.
        else if (menu == 'D') {
            pq.extract_min(pq.heap);        // 최소 key값을 가지고 있는 요소를 지우기
        }

        // 'C'를 입력받은 경우 --> Decrease key of element in queue.
        else if (menu == 'C') {
            int n;          // 바꿀 요소의 index를 저장할 int
            int n_id;       // 새롭게 입력받을 id를 저장할 int
            cout << "Enter index of element: ";
            cin >> n;
            cout << "Enter id value: ";
            cin >> n_id;
            pq.decrease_key(pq.heap, n, n_id);      // 해당 요소릐 key값을 바꾸고 heap 정렬
            cout << endl << endl;
        }

        // 'p'를 입력받은 경우 --> Print out all elements in queue.
        else if (menu == 'P') {
            for (int i=1; i<=pq.size; i++) {
                cout << "[" << pq.heap[i].name << ", " << pq.heap[i].id << ", " << pq.heap[i].school << "] ";
            }
            cout << endl << endl;
        }

        // I, D, C, P, Q 가 아닌 다른 문자를 입력받은 경우 --> 다시 입력받기
        else cout << "Retry!" << endl << endl;
    }
    cout << "Thank you, Bye!" << endl << endl;

    return 0;
}