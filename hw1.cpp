#include <iostream>
using namespace std;

int main() {
    char m;
    
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
    }
    
    cout << "Thank you, Bye!" << endl;
    
    return 0;
}
