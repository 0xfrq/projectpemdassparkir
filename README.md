``` Deadline : 1 hari lagi.```
# Project Pemdas Parkir
Program bertujuan untuk mengelola data kendaraan yang masuk dan keluar area parkir dengan sistem berbasis file sederhana. Data kendaraan akan dicatat berdasarkan nomor polisi (nopol) dan jenis kendaraan, dengan setiap entri diberi kode ID acak untuk identifikasi unik. Proses ini mempermudah pengelolaan data parkir dan memastikan keakuratan pencatatan.

Fitur Utama

Pendaftaran Kendaraan Masuk:
Program menerima input berupa nopol (nomor polisi) dan jenis kendaraan (contoh: mobil, motor, dll.).
Sistem menghasilkan kode parkir acak untuk setiap kendaraan yang masuk.
Data kendaraan (nopol, jenis kendaraan, waktu masuk, dan ID acak) dicatat dalam file

Pencocokan Saat Keluar:
Program meminta pengguna untuk memasukkan kode ID kendaraan saat keluar.
Sistem pemeriksaan keberadaan ID tersebut di file.
Jika ID cocok, data kendaraan dihapus dari file.

# Step By Step

  # Menu keluar 
    1. Inisialisasi Variabel
        ifstream dbkendaraanInput, historyFileInput: Untuk membaca file kendaraan dan file sejarah.
        ofstream dbkendaraanOutput, historyFileOutput: Untuk menulis file kendaraan yang telah diperbarui dan file sejarah           yang baru.
        string line, nopol, kode, sektor, tipe, jamMasuk, jamKeluar: Untuk menyimpan data yang dibaca dari file.
        bool found = false: Untuk menandai apakah kendaraan yang dicari ditemukan.
        time_t now = time(0): Mendapatkan waktu saat ini.
        tm * localtm = localtime(&now): Mengonversi waktu menjadi struktur waktu lokal.
        char currentJam[6]: Menyimpan jam saat ini dalam format "HH:MM".
    2. Mendapatkan waktu keluar
        strftime mengonversi waktu lokal menjadi format "HH:MM" dan menyimpannya dalam variabel jamKeluar.
    3. Pengguna menginput ID
        id merupakan nopol tanpa tanda spasi
    4. Membuka File Kendaraan
        Membuka file dengan tanggal hari ini dengan dateclean + ".txt"
    5. Membuka/membuat File Sementara
        Membuat file sementara ("temp.txt") untuk menyimpan data baru.
    6. Membaca dan Memproses Data Kendaraan
        Menggunakan getline untuk membaca setiap baris data dari file kendaraan.
        menggunakan ; untuk memisah bagian-bagian data nopol, kode, sektor, tipe, dan jamMasuk.
        Jika nopol dalam file(tanpa spasi) sama dengan id yang diinput, maka:
            Set found menjadi true untuk menandakan kendaraan ditemukan.
            Menampilkan informasi kendaraan.
            Mengurangi jumlah kendaraan di sektor yang sesuai.
    7. Mengubah history
        Membuka(history.txt) untuk menambah jam keluar kendaraan.
        Menyimpan perubahan di file sementara ("temp_history.txt").
        Menghapus history lama, dan merubah nama file sementara menjadi history.txt sebagai pengganti.
    8. Menutup File
    9. Mengganti File(perhari)
        Jika id ditemukan dan file telah diperbarui, file lama (berdasarkan tanggal) dihapus, dan file sementara diganti namanya menjadi file baru.
        Jika tidak ditemukan, program akan menampilkan pesan kesalahan dan menghapus file sementara yang dibuat.
