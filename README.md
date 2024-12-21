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
  # Menu Masuk
    1. Membuka file untuk menyimpan data kendaraan dan riwayat, serta membuat objek Ticket untuk menyimpan informasi tiket.
    2. Mendapatkan waktu saat ini dalam format HH:MM untuk mencatat jam masuk kendaraan.
    3. Menampilkan menu untuk pengguna dengan pilihan jenis kendaraan: Motor, Mobil, atau Kembali ke menu utama.
    4. Menerima input dari pengguna untuk menentukan jenis kendaraan yang masuk.
    5. Mengacu pada sektor parkir yang tersedia: B1 dan B2 untuk Motor, C1 dan C2 untuk Mobil.
    6. Jika pengguna memilih Motor, sistem memeriksa kapasitas sektor B1 dan B2 dan menentukan sektor yang masih tersedia atau memilih secara acak jika keduanya kosong.
    7. Jika pengguna memilih Mobil, sistem memeriksa kapasitas sektor C1 dan C2 dan menentukan sektor yang masih tersedia atau memilih secara acak jika keduanya kosong.
    8. Jika kedua sektor untuk jenis kendaraan penuh, menampilkan pesan bahwa parkir penuh dan memanggil ulang fungsi untuk mencoba lagi.
    9. Jika pengguna memilih opsi kembali, sistem memanggil fungsi main untuk kembali ke menu utama.
    10. Meminta pengguna untuk memasukkan nomor polisi kendaraan yang akan diparkir.
    11. Memformat nomor polisi agar sesuai dengan aturan yang ditentukan.
    12. Membuat tiket dengan menyimpan data nomor polisi, kode tiket unik, tipe kendaraan, sektor parkir, dan waktu masuk ke dalam objek Ticket.
    13. Menulis data tiket ke file log harian kendaraan (dbkendaraan) untuk mencatat parkir pada hari tersebut.
    14. Menulis data tiket ke file riwayat parkir umum (historyFile) untuk mencatat seluruh riwayat kendaraan.
    15. Menampilkan informasi tiket kepada pengguna, termasuk nomor polisi, kode tiket, sektor parkir, dan jam masuk kendaraan.
    16. Fungsi selesai setelah mencetak informasi tiket ke layar.
  # Menu Keluar 
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
