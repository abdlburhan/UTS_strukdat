#include <iostream> // Memasukkan header file untuk input/output standar

using namespace std;

// Tipe data untuk struct customer
struct Customer {
  string nama;         // String untuk menyimpan nama customer
  string alamat;        // String untuk menyimpan alamat customer
  char jenisKelamin;    // Karakter untuk menyimpan jenis kelamin customer (L/P)
  int lamaMenginap;     // Integer untuk menyimpan lama menginap customer
  int hargaKamar;      // Integer untuk menyimpan harga kamar customer
  long long totalHarga; // Long long untuk menyimpan total harga yang harus dibayar customer
  Customer* next;       // Pointer ke struktur data Customer berikutnya (untuk linked list)
};

// Array 1 dimensi untuk menyimpan harga kamar
int hargaTipeKamar[] = {100000, 200000, 300000};

// Array 2 dimensi untuk menyimpan data kamar
// Dimensi pertama: Tipe kamar (Standar, Deluxe, Suite)
// Dimensi kedua: Ketersediaan kamar (0: Tersedia, 1: Tidak Tersedia)
int kamarTersedia[3][2] = {{1, 1}, {1, 1}, {1, 1}};

// Pointer untuk head dan tail linked list
Customer* head = NULL; // Pointer ke awal linked list (NULL karena belum ada data)
Customer* tail = NULL; // Pointer ke akhir linked list (NULL karena belum ada data)

// Variabel global
int totalHarga;        // Variabel untuk menyimpan total harga
int lamaInap;         // Variabel untuk menyimpan lama menginap
int hargaKamar;      // Variabel untuk menyimpan harga kamar

void pilihKamar(Customer* customer) {
  int pilihKamar;
  cout << "\033[2J\033[1;1H" << endl; // Membersihkan layar (clear screen)

  cout << "Pilih Kamar : " << endl;
  for (int i = 0; i < 3; i++) {
    cout << i + 1 << ". " << (i == 0 ? "Kamar Standar" : (i == 1 ? "Kamar Deluxe" : "Kamar Suite")) << ", Harga/Hari : Rp. " << hargaTipeKamar[i] << endl;
  }
  cout << "Pilih Kamar : ";
  cin >> pilihKamar;

  // Validasi pilihan kamar
  while (pilihKamar < 1 || pilihKamar > 3) {
    cout << "Pilihan kamar tidak valid. Pilih kembali: ";
    cin >> pilihKamar;
  }

  // Cek ketersediaan kamar
  while (kamarTersedia[pilihKamar - 1][1] == 0) {
    cout << "Kamar pilihan penuh. Pilih kamar lain: ";
    cin >> pilihKamar;
  }

  // Set data customer
  customer->hargaKamar = hargaTipeKamar[pilihKamar - 1];
  kamarTersedia[pilihKamar - 1][1] = 0; // Tandai kamar sebagai tidak tersedia

  cout << "Lama Inap : ";
  cin >> lamaInap;
  customer->lamaMenginap = lamaInap;

  if (lamaInap >= 5) {
    cout << "Selamat Anda Mendapatkan Diskon 2%!" << endl;
    totalHarga = lamaInap * customer->hargaKamar;
    totalHarga = totalHarga - (totalHarga * 0.02);
  } else {
    totalHarga = lamaInap * customer->hargaKamar;
  }

  customer->totalHarga = totalHarga;
  cout << "Total Harga : Rp. " << totalHarga << endl;
}

void tambahCustomer() {
  cout << "\033[2J\033[1;1H";

  // Buat customer baru
  Customer* newCustomer = new Customer;

  cout << "Nama Customer : ";
  cin.ignore();   // Mengabaikan karakter yang tersisa di buffer input
  getline(cin, newCustomer->nama);  // Membaca input nama customer

  cout << "Alamat Customer : ";
  cin.ignore();  // Mengabaikan karakter yang tersisa di buffer input
  getline(cin, newCustomer->alamat);  // Membaca input alamat customer

  cout << "Jenis Kelamin Customer (L/P) : ";
  cin >> newCustomer->jenisKelamin;  // Membaca input jenis kelamin customer

  pilihKamar(newCustomer);  // Memanggil fungsi untuk memilih kamar

  // Menambahkan customer ke linked list
  if (head == NULL) {
    head = tail = newCustomer;  // Jika linked list kosong, jadikan customer baru sebagai head dan tail
  } else {
    tail->next = newCustomer;   // Menambahkan customer baru ke akhir linked list
    tail = newCustomer; // Update pointer tail ke customer baru

  }

  cout << "Data customer berhasil ditambahkan" <<endl;
}
 // Fungsi untuk menampilkan customer
void tampilCustomer() {
  cout << "\033";  // Membersihkan layar

  if (head == NULL) {
    cout << "Belum ada data customer." << endl;
    return;
  }

  Customer* current = head;  // Pointer untuk traversal linked list
  int counter = 1; // Penghitung untuk nomor urut customer

  while (current != NULL) {
    cout << "Customer " << counter << ":" << endl;
    cout << "  Nama: " << current->nama << endl;
    cout << "  Alamat: " << current->alamat << endl;
    cout << "  Jenis Kelamin: " << current->jenisKelamin << endl;
    cout << "  Lama Menginap: " << current->lamaMenginap << " hari" << endl;
    cout << "  Harga Kamar: Rp. " << current->hargaKamar << endl;
    cout << "  Total Harga: Rp. " << current->totalHarga << endl;
    current = current->next;  // Pindah ke customer berikutnya
    counter++;
  }

  cout << "Tekan Enter untuk kembali" << endl;
  cin.ignore();   // Mengabaikan karakter yang tersisa di buffer input
  cin.get(); // Menunggu input Enter dari user
  }

  // Fungsi untuk menampilkan menu dan mengelola pilihan
void menu() {
  while (true) {

    cout << "1. Tambah Customer" << endl;
    cout << "2. Tampilkan Customer" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilih Menu : ";
    int input;
    cin >> input;

    switch (input) {
      case 1:
        tambahCustomer();
        break;
      case 2:
        tampilCustomer();
        break;
      case 3:
        cout << "Terima Kasih" << endl;
        // Free memory allocated for customers (optional)
        Customer* current = head;
        while (current != NULL) {
          Customer* temp = current;
          current = current->next;
          delete temp;
        }
        head = tail = NULL;
        return;

        cout << "Menu Tidak Tersedia" << endl;
        break;
    }
  }
}

int main() {
  menu();
  return 0;
}


