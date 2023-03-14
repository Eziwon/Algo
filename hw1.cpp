#include <iostream>
using namespace std;

class Heap {
public:
    char name[10];
    int id[4];
    char school[20];
};

//insert를 위한 정보를 입력받는 function
void getI() {
    char n_name[10];
    int n_id;
    char n_school[20];
    cout << "Enter name of element: " ;
    cin >> n_name ;
    cout << "Enter id of element: ";
    cin >> n_id;
    cout << "Enter school of element: ";
    cin >> n_school;
}

void insert(Heap h[], Heap k) {

}

int main() {
    char m;     //입력 받을 menu
    Heap que[30];
    
    while(1) {
        cout << "*********** MENU ****************" << endl;
        cout << "I : Insert new element into queue." << endl;
        cout << "D : Delete element with smallest key from queue." << endl;
        cout << "C : Decrease key of element in queue." << endl;  
        cout << "P : Print out all elements in queue." << endl;
        cout << "Q : Quit" << endl << endl;

        cout << "Choose menu: ";
        m = getchar();
        // Q를 입력받은 경우 반복 중지
        if (m == 'Q') break;
        // if (m == 'I') 삽입하는 함수 호출
        if (m == 'I') {
            getI();
        }
    }
    
    cout << "Thank you, Bye!" << endl;
    
    return 0;
}
