#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;


void masuk(const string& dateclean);
bool checkdatabase(const string& formatted_date) {
    ofstream dbkendaraan;
    if (ifstream(formatted_date + ".txt")) {
        return true;
    } else {
        dbkendaraan.open(formatted_date + ".txt", ios::app);
        return false;
    }
}

int rdnumber() {
    int digits[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // Digits to pick from
    int randomNumber = 0;  // The final 4-digit number
    int counter = 0;  // Counter to simulate the "random" factor

    // Generate a 4-digit number
    for (int i = 0; i < 4; ++i) {
        // A simple formula to choose a "random" index from 0 to 8
        int index = (counter * 12345 + 6789) % 9;  // A basic function to vary the index
        int digit = digits[index];  // Get the corresponding digit from the array

        // Append the digit to the random number
        randomNumber = randomNumber * 10 + digit;

        // Increment the counter to ensure different results each time
        counter++;
    }

    return randomNumber;  // Return the random 4-digit number
}

int main() {
    time_t timestamp;
    char datelengkap[50];
    char dateclean[50];
    struct tm* datetime;

    time(&timestamp);
    datetime = localtime(&timestamp);
    strftime(datelengkap, sizeof(datelengkap), "%d %m %Y", datetime);
    strftime(dateclean, sizeof(dateclean), "%d%m%Y", datetime);

    string dateformat(dateclean);
    if (!checkdatabase(dateformat)) {
        cout << "Selamat Pagi, \n" << datelengkap << endl << endl;
    }

    int p1;
    cout << "=== Sistem Pengelolaan Parkir ===" << endl;
    cout << "1. Kendaraan Masuk" << endl;
    cout << "2. Kendaraan keluar" << endl;
    cout << "3. Lihat Slot Parkir" << endl;
    cout << "4. Exit Program" << endl;
    cout << "Pilih Opsi: ";
    cin >> p1;

    switch(p1) {
        case 1:
            masuk(dateclean);
            break;
        case 2:
            cout << ".." << endl;
            break;
        case 3:
            cout << "..." << endl;
            break;
        case 4:
            cout << "...." << endl;
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
            break;
    }

    return 0;
}

void masuk(const string& dateclean) {
    ofstream dbkendaraan;
    string nopol;
    string intipe;
    int tipe;
    cout << "=============================" << endl;
    cout << "Selamat datang pada menu masuk" << endl;
    cout << "=============================" << endl << endl << endl;
    cout << "Pilih Tipe Kendaraan : \n1. Motor\n2. Mobil\n";
    cin >> tipe;
    if (tipe==1) {
        intipe = "Motor";
    } else {
        intipe = "Mobil";
    }
    cout << "Masukkan Nomor Polisi (tanpa spasi): ";
    cin >> nopol;
    dbkendaraan.open(dateclean + ".txt", ios::app);
    dbkendaraan << "\n" << nopol << ";" << rdnumber() << ";" << "sektor" <<";" << intipe;
    cout << "*mencetak karcis untuk: \nNopol : " << nopol << "\nKode : " << rdnumber();
}
