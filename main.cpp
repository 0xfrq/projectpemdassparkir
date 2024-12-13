#include <iostream>
#include <ctime>
#include <fstream>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdint>
using namespace std;


void masuk(const string& dateclean);
void keluar(const string& dateclean);
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
            keluar(dateclean);
            break;
        case 3:
            cout << "..." << endl;
            break;
        case 4:
            cout << "Anda telah keluar dari program" << endl;
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
            break;
    }

    return 0;
}

// format agar outputnya memiliki spasi pada nopol, namun data di txt tetap tanpa spasi sebagi id
string formatID(const string& id) {
    string formatted;
    size_t length = id.length();

    for (size_t i = 0; i < length; ++i) {
        char c = id[i];
        formatted += c;

        if (i == 0 && isalpha(c) && i + 1 < length && isdigit(id[i + 1])) {
            formatted += " ";
        }

        if (i + 1 < length && isdigit(c) && isalpha(id[i + 1])) {
            formatted += " ";
        }
    }
    return formatted;
}

string id; // disini agar bisa dipakai untuk masuk & keluar
void masuk(const string& dateclean) {
    ofstream dbkendaraan, historyFile;
    string intipe;
    int tipe;

    //Mendapatkan waktu saat ini
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char jamMasuk[6];
    strftime (jamMasuk, sizeof (jamMasuk), "%H:%M", localtm);

    cout << "=============================" << endl;
    cout << "Selamat datang pada menu masuk" << endl;
    cout << "=============================" << endl << endl << endl;
    cout << "Pilih Tipe Kendaraan : \n1. Motor\n2. Mobil\n";
    cout << "Pilihan: ";
    cin >> tipe;
    if (tipe==1) {
        intipe = "Motor";
    } else {
        intipe = "Mobil";
    }
    cout << "Masukkan Nomor Polisi (tanpa spasi): ";
    cin >> id;

    string formattedID = formatID(id);
    
    dbkendaraan.open(dateclean + ".txt", ios::app);
    dbkendaraan << "\n" << id << ";" << rdnumber() << ";" << "sektor" <<";" << intipe;

    //Menulis data ke file history
    historyFile.open("history.txt", ios::app);
    historyFile << dateclean << ";" << "sektor" << ";" << intipe << ";" << jamMasuk << ";-\n";
    historyFile.close();

    cout << "*mencetak karcis untuk: \nNopol : " << formattedID << "\nKode : " << rdnumber();
}

void keluar(const string& dateclean){
    ifstream dbkendaraanInput, historyFileInput;
    ofstream dbkendaraanOutput, historyFileOutput;
    string line, nopol, kode, sektor, tipe, jamMasuk, jamKeluar;
    bool found = false;

    //Waktu saat ini
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char currentJam[6];
    strftime(currentJam, sizeof(currentJam), "%H:%M", localtm);
    jamKeluar = string(currentJam);

    cout << "=============================" << endl;
    cout << "Selamat datang pada menu keluar" << endl;
    cout << "=============================" << endl;

    cout << "Masukkan Nomor Polisi (tanpa spasi): ";
    cin >> id;

     // Membuka file
    dbkendaraanInput.open(dateclean + ".txt");
    if (!dbkendaraanInput.is_open()) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    // Buat file sementara menyimpan data baru
    dbkendaraanOutput.open("temp.txt");

    // Baca file
    while (getline(dbkendaraanInput, line)) {
        size_t pos = line.find(';');
        if (pos != string::npos) {
            nopol = line.substr(0, pos);
            if (nopol == id) {
                // Data ditemukan
                found = true;

                // Mencari informasi kendaraan untuk ditampilkan
                size_t kodePos = line.find(';', pos + 1);
                size_t sektorPos = line.find(';', kodePos + 1);

                kode = line.substr(pos + 1, kodePos - pos - 1);
                sektor = line.substr(kodePos + 1, sektorPos - kodePos - 1);
                tipe = line.substr(sektorPos + 1);

                cout << "Kendaraan ditemukan:\n";
                cout << "Nopol: " << formatID(nopol) << "\n";
                cout << "Kode Karcis: " << kode << "\n";
                cout << "Sektor: " << sektor << "\n";
                cout << "Tipe Kendaraan: " << tipe << "\n";
                cout << "Kendaraan berhasil keluar. Terima kasih!" << endl;
                
                //Tambah data di file history dengan jam keluar
                historyFileInput.open("history.txt");
                historyFileOutput.open("temp_history.txt");
                string historyLine;
                while (getline(historyFileInput, historyLine)){
                    if (historyLine.find(nopol) != string::npos &&
                    historyLine.find("-") != string::npos) {
                        size_t lastDelimiter = historyLine.rfind(';');
                        historyLine = historyLine.substr(0, lastDelimiter) + ";" + jamKeluar;
                    }
                    historyFileOutput << historyLine << "\n";
                }
                historyFileInput.close();
                historyFileOutput.close();
                //Ganti File history dengan yang sudah update
                remove("history.txt");
                rename("temp_history.txt", "history.txt");
                continue;
            }
        }
        //Menyalin data file utama yang bukan kendaraan yang keluar ke file sementara.
        dbkendaraanOutput << line << "\n";
    }
    dbkendaraanInput.close();
    dbkendaraanOutput.close();



    // Ganti file lama dengan file baru jika kendaraan ditemukan
    if (found) {
        if (remove((dateclean + ".txt").c_str()) != 0) {
            cout << "Gagal menghapus file lama!" << endl;
        } else if (rename("temp.txt", (dateclean + ".txt").c_str()) != 0) {
            cout << "Gagal mengganti file sementara!" << endl;
        }
    } else {
        cout << "Kendaraan dengan Nopol " << formatID(id) << " tidak ditemukan!" << endl;
        remove("temp.txt"); // Hapus file sementara jika tidak ada perubahan
    }
}
