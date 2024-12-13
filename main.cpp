#include <iostream>
using namespace std;

int main() {
   int p1;
   cout << endl << "=== Sistem Pengelolaan Parkir ===" << endl;
   cout << "1. Kendaraan Masuk" << endl;
   cout << "2. Kendaraan keluar" << endl;
   cout << "3. Lihat Slot Parkir" << endl;
   cout << "4. Exit Program" << endl;
   cout << "Pilih Opsi: ";
   cin >> p1;

    switch(p1){
        case 1:
            cout << "."<< endl;
            break;
        case 2:
            cout << ".."<< endl;
            break;
        case 3:
            cout << "..."<< endl;
            break;
        case 4:
            cout << "...."<< endl;
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
            break;
    }
return 0;
}
