#include <iostream>

#include <ctime>

#include <fstream>

#include <cmath>

#include <string>

#include <cstring>

#include <cstdint>

using namespace std;

// Struct Karcis
struct Ticket {
  string nopol;
  int kode;
  string sektor;
  string tipeKendaraan;
  string entryTime;
};

// Struct Sektor
struct Sektor {
  string nama;
  int kapasitasMaks;
  int kendaraanSaatIni;
};

// Array sektor parkir
Sektor sektorparkir[] = {
  {
    "B1",
    800,
    0
  },
  {
    "B2",
    600,
    0
  },
  {
    "C1",
    600,
    0
  },
  {
    "C2",
    450,
    0
  }
};
const int jumlahSektor = 4;

void tampilkanSektor();
void masuk(const string & dateclean);
void keluar(const string & dateclean);
bool checkdatabase(const string & formatted_date) {
  ofstream dbkendaraan;
  if (ifstream(formatted_date + ".txt")) {
    return true;
  } else {
    dbkendaraan.open(formatted_date + ".txt", ios::app);
    return false;
  }
}

int rdnumber() {
  srand(time(NULL));
  return rand() % 9000 + 1000;
}

void loadSektorData() {
  ifstream sektorFile("sektor_data.txt");
  string line;
  if (sektorFile.is_open()) {
    int i = 0;
    while (getline(sektorFile, line) && i < jumlahSektor) {
      size_t pos1 = line.find(';');
      size_t pos2 = line.find(';', pos1 + 1);
      sektorparkir[i].kendaraanSaatIni = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1)); // Parse current vehicle count
      i++;
    }
    sektorFile.close();
  }
}

void saveSektorData() {
  ofstream sektorFile("sektor_data.txt");
  for (int i = 0; i < jumlahSektor; ++i) {
    sektorFile << sektorparkir[i].nama << ";" << sektorparkir[i].kendaraanSaatIni << "\n";
  }
  sektorFile.close();
}

void start() {
  time_t timestamp;
  char datelengkap[50];
  char dateclean[50];
  struct tm * datetime;

  time( & timestamp);
  datetime = localtime( & timestamp);
  strftime(datelengkap, sizeof(datelengkap), "%d %m %Y", datetime);
  strftime(dateclean, sizeof(dateclean), "%d%m%Y", datetime);

  string dateformat(dateclean);
  if (!checkdatabase(dateformat)) {
    cout << "Selamat Pagi, \n" << datelengkap << endl << endl;
  }

  // Load sektor data from file at the start
  loadSektorData();

  int p1;
  cout << "=== Sistem Pengelolaan Parkir ===" << endl;
  cout << "1. Kendaraan Masuk" << endl;
  cout << "2. Kendaraan keluar" << endl;
  cout << "3. Lihat Slot Parkir" << endl;
  cout << "4. Exit Program" << endl;
  cout << "Pilih Opsi: ";
  cin >> p1;

  switch (p1) {
  case 1:
    masuk(dateclean);
    break;
  case 2:
    keluar(dateclean);
    break;
  case 3:
    tampilkanSektor();
    break;
  case 4:
    cout << "Anda telah keluar dari program" << endl;
    break;
  default:
    cout << "Pilihan tidak valid" << endl;
    break;
  }

  // Save sektor data back to file after the operation
  saveSektorData();
}

int main() {
  string in = "y";
  do {
    start();
    cout << "\nJalankan kembali? (y/n): ";
    cin >> in;
  } while (in=="y");
  cout << "Terima Kasih!";
  return 0;
}

// Fungsi tampilkan sektor
void tampilkanSektor() {
  cout << "\n=== Status Sektor Parkir ===" << endl;
  for (int i = 0; i < jumlahSektor; i++) {
    cout << "Sektor " << sektorparkir[i].nama << "\nKapasitas Maks: " << sektorparkir[i].kapasitasMaks << "\nTerisi: " << sektorparkir[i].kendaraanSaatIni << "\n" << endl;
  }
}

string id; // disini agar bisa dipakai untuk masuk & keluar
// format agar outputnya memiliki spasi pada nopol, namun data di txt tetap tanpa spasi sebagi id
string formatID(const string & id) {
  string formatted;
  size_t length = id.length();
  int index = 0;

  while (index < length && ((id[index] >= 'A' && id[index] <= 'Z') || (id[index] >= 'a' && id[index] <= 'z'))) {
    formatted += id[index];
    index++;
  }
  if (!formatted.empty() && index < length) {
    formatted += " ";
  }

 while (index < length && (id[index] >= '0' && id[index] <= '9')) {
    formatted += id[index];
    index++;
  }
  if (!formatted.empty() && index < length) {
    formatted += " ";
  }

 while (index < length && ((id[index] >= 'A' && id[index] <= 'Z') || (id[index] >= 'a' && id[index] <= 'z'))) {
    formatted += id[index];
    index++;
  }
  return formatted;
}

void masuk(const string & dateclean) {
  ofstream dbkendaraan, historyFile;
  string intipe;
  int tipe;
  Ticket ticket;

  // Mendapatkan waktu saat ini
  time_t now = time(0);
  tm * localtm = localtime( & now);
  char jamMasuk[6];
  strftime(jamMasuk, sizeof(jamMasuk), "%H:%M", localtm);

  cout << "=============================" << endl;
  cout << "Selamat datang pada menu masuk" << endl;
  cout << "=============================" << endl << endl << endl;
  cout << "Pilih Tipe Kendaraan : \n1. Motor\n2. Mobil\n3. Kembali\n";
  cout << "Pilihan: ";
  cin >> tipe;
  int sektorPilihan;
  Sektor* sektorB1 = &sektorparkir[0];
  Sektor* sektorB2 = &sektorparkir[1];
  Sektor* sektorC1 = &sektorparkir[2];
  Sektor* sektorC2 = &sektorparkir[3];
  int rdangka = (rand() % 2) + 1;
  cout << sektorB1->kendaraanSaatIni;
  if (tipe == 1) {
    intipe = "Motor";
    if (sektorB1->kendaraanSaatIni >= sektorB1->kapasitasMaks) {
        //sektor 1 penuh
        sektorB2->kendaraanSaatIni++;
        ticket.sektor = "B2";
        cout << "Sektor B1 penuh, otomatis masuk ke Sektor B2\n";
    } else if (sektorB2->kendaraanSaatIni >= sektorB2->kapasitasMaks) {
      //sektor 2 penuh
      sektorB1->kendaraanSaatIni++;
      ticket.sektor = "B1";
      cout << "Sektor B2 penuh, otomatis masuk ke Sektor B1\n";
    } else if ((sektorB1->kendaraanSaatIni >= sektorB1->kapasitasMaks) && (sektorB2->kendaraanSaatIni >= sektorB2->kapasitasMaks)) {
      cout << "Kedua sektor penuh, tidak ada tempat parkir tersedia untuk saat ini, silahkan coba lagi nanti.\n";

      masuk(dateclean);
    } else {
      sektorPilihan = (rand() % 2) + 1; // random antara 1 dan 2

      if (sektorPilihan == 1) {
        sektorB1->kendaraanSaatIni++;
        ticket.sektor = "B1";
      } else if (sektorPilihan == 2) {
        sektorB2->kendaraanSaatIni++;
        ticket.sektor = "B2";
      } else {
        cout << "Input Invalid, kembali ke menu utama";
        masuk(dateclean);
      }
    }
  } else if (tipe == 2) {
    intipe = "Mobil";
    if (sektorC1->kendaraanSaatIni >= sektorC1->kapasitasMaks && sektorC2->kendaraanSaatIni < sektorC2->kapasitasMaks) {
      sektorC2->kendaraanSaatIni++;
      ticket.sektor = "C2";
      cout << "Sektor C1 penuh, otomatis masuk ke Sektor C2\n";
    } else if (sektorC2->kendaraanSaatIni >= sektorC2->kapasitasMaks && sektorC1->kendaraanSaatIni < sektorC1->kapasitasMaks) {
      sektorC1->kendaraanSaatIni++;
      ticket.sektor = "C1";
      cout << "Sektor C2 penuh, otomatis masuk ke Sektor C1\n";
    } else {
      sektorPilihan = (rand() % 2) + 1; // random antara 1 dan 2

      if (sektorPilihan == 1) {
        sektorC1->kendaraanSaatIni++;
        ticket.sektor = "C1";
      } else if (sektorPilihan == 2) {
        sektorC2->kendaraanSaatIni++;
        ticket.sektor = "C2";
      } else {
        cout << "input invalid, kembali ke menu utama";
        masuk(dateclean);
      }
    }
  } else if (tipe == 3) {
    main();
  } else {
    cout << "Input invalid, kembali ke menu utama";
    masuk(dateclean);
  }

  cout << "Masukkan Nomor Polisi (tanpa spasi): ";
  cin >> id;

  string formattedID = formatID(id);
  ticket.nopol = formattedID;
  ticket.kode = rdnumber();
  ticket.tipeKendaraan = intipe;
  ticket.entryTime = string(jamMasuk);

  dbkendaraan.open(dateclean + ".txt", ios::app);
  dbkendaraan << "\n" << id << ";" << ticket.kode << ";" << ticket.sektor << ";" << ticket.tipeKendaraan << ";" << ticket.entryTime << ";" << "-\n";
  dbkendaraan.close();

  // Menulis data ke file history
  historyFile.open("history.txt", ios::app);
  historyFile << "\n" << dateclean << ";" << ticket.nopol << ";" << ticket.sektor << ";" << ticket.tipeKendaraan << ";" << ticket.entryTime << ";" << "-\n";
  historyFile.close();

  cout << "Mencetak karcis untuk: \nNopol : " << ticket.nopol << "\nKode : " << ticket.kode << "\nSektor : " << ticket.sektor << "\nJam Masuk : " << ticket.entryTime;
}

void keluar(const string & dateclean) {
  ifstream dbkendaraanInput, historyFileInput;
  ofstream dbkendaraanOutput, historyFileOutput;
  string line, nopol, kode, sektor, tipe, jamMasuk, jamKeluar;
  bool found = false;

  // Waktu saat ini
  time_t now = time(0);
  tm * localtm = localtime( & now);
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
      nopol = line.substr(0, pos); // Nopol ada di posisi pertama
      size_t kodePos = line.find(';', pos + 1); // Cari posisi kode setelah Nopol
      if (kodePos != string::npos) {
        kode = line.substr(pos + 1, kodePos - pos - 1); // Ambil kode
        size_t sektorPos = line.find(';', kodePos + 1); // Cari posisi sektor
        if (sektorPos != string::npos) {
          sektor = line.substr(kodePos + 1, sektorPos - kodePos - 1); // Ambil sektor
          size_t tipePos = line.find(';', sektorPos + 1); // Cari posisi tipe
          if (tipePos != string::npos) {
            tipe = line.substr(sektorPos + 1, tipePos - sektorPos - 1); // Ambil tipe kendaraan
            jamMasuk = line.substr(tipePos + 1); // Ambil jamMasuk setelah tipe kendaraan
          }
        }
      }

      // Jika ditemukan Nopol yang sesuai
      if (nopol == id) {
        // Data ditemukan
        found = true;

        cout << "Kendaraan ditemukan:\n";
        cout << "Nopol: " << formatID(nopol) << "\n";
        cout << "Kode Karcis: " << kode << "\n";
        cout << "Sektor: " << sektor << "\n";
        cout << "Tipe Kendaraan: " << tipe << "\n";
        cout << "Jam Masuk: " << jamMasuk << "\n";
        cout << "Jam Keluar: " << jamKeluar << "\n";
        cout << "Kendaraan berhasil keluar. Terima kasih!" << endl;

        // Update jumlah kendaraan di sektor
        for (int i = 0; i < jumlahSektor; ++i) {
          if (sektor == sektorparkir[i].nama) {
            sektorparkir[i].kendaraanSaatIni--;
            break;
          }
        }

        // Tambah data di file history dengan jam keluar
        historyFileInput.open("history.txt");
        historyFileOutput.open("temp_history.txt");
        string historyLine;
        while (getline(historyFileInput, historyLine)) {
          if (historyLine.find(formatID(nopol)) != string::npos &&
            historyLine.find("-") != string::npos) {
            size_t lastDelimiter = historyLine.rfind(';');
            historyLine = historyLine.substr(0, lastDelimiter) + ";" + jamKeluar;
          }
          historyFileOutput << historyLine << "\n";
        }
        historyFileInput.close();
        historyFileOutput.close();

        // Ganti File history dengan yang sudah update
        remove("history.txt");
        rename("temp_history.txt", "history.txt");

        continue;
      }
    }
    // Menyalin data file utama yang bukan kendaraan yang keluar ke file sementara.
    dbkendaraanOutput << line << "\n";
  }
  dbkendaraanInput.close();
  dbkendaraanOutput.close();

  // Ganti file lama dengan file baru jika kendaraan ditemukan
  if (found) {
    remove((dateclean + ".txt").c_str()); // Hapus file lama
    rename("temp.txt", (dateclean + ".txt").c_str()); // Ganti nama file sementara
  } else {
    cout << "Kendaraan dengan Nopol " << formatID(id) << " tidak ditemukan!" << endl;
    remove("temp.txt"); // Hapus file sementara jika tidak ada perubahan
  }
}
