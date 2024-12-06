#include "DNA.hpp"
#include <fstream>
#include <sstream>
#include <limits>
#include <iostream>

using namespace std;

int main() {
    ifstream readFile;
    DNA* dna = new DNA();
    readFile.open("Dna.txt");
    string line;

    // Dosyadan kromozom verilerini okuma
    while (getline(readFile, line)) {
        Kromozom* kromozom = new Kromozom();
        stringstream ss(line);
        char gen;

        while (ss >> gen) {
            kromozom->add(gen);
        }
        dna->add(kromozom);
    }
    readFile.close();

    // Kullanıcı menüsü
    int choice = 0;
    bool cikis = true;

    cout << "Program basladi. Lutfen menuden bir secenek secin." << endl;
    while (cikis) {
        cout << "\n1. Caprazlama\n"
             << "2. Mutasyon\n"
             << "3. Otomatik Islemler\n"
             << "4. Ekrana Yaz\n"
             << "5. Cikis\n"
             << "Seciminiz: ";
        cin >> choice;

        if (cin.fail()) { // Geçersiz giriş kontrolü
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Gecersiz giris! Lutfen bir sayi girin." << endl;
            continue;
        }

        switch (choice) {
            case 1: { // Caprazlama
                int index1, index2;
                cout << "Caprazlama icin ilk kromozomun satir numarasini girin: ";
                cin >> index1;
                cout << "Caprazlama icin ikinci kromozomun satir numarasini girin: ";
                cin >> index2;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Gecersiz numara girdiniz!" << endl;
                    break;
                }

                try {
                    dna->caprazlama(index1, index2);
                    cout << "Caprazlama basariyla tamamlandi." << endl;
                } catch (const char* e) {
                    cerr << "Hata: " << e << endl;
                }
                break;
            }

            case 2: { // Mutasyon
                int kromozomIndex, genIndex;
                cout << "Mutasyon yapmak icin Kromozom satir numarasini girin: ";
                cin >> kromozomIndex;
                cout << "Mutasyon yapmak icin Gen sutun numarasini girin: ";
                cin >> genIndex;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Gecersiz numara girdiniz!" << endl;
                    break;
                }

                try {
                    dna->mutate(kromozomIndex, genIndex, 'X');
                    cout << "Mutasyon basarili!" << endl;
                } catch (const char* e) {
                    cerr << "Hata: " << e << endl;
                }
                break;
            }
            case 3: // Otomatik işlemler
                dna->OtomatikIslemler();
                cout << "Otomatik islemler tamamlandi." << endl;
                break;

            case 4: // Ekrana yaz
                cout << endl;
                dna->yazdirKucukGenler();
                cout << endl;
                //cout<<*dna;  //yaparken dogru cıktı alıyor muyum diye denedim. 
                break;

            case 5: // Çıkış
                cikis = false;
                break;

            default:
                cout << endl;
                cout << "Gecersiz secim! Lutfen 1-5 arasinda bir sayi girin." << endl;
        }
    }

    // Bellek temizliği
    dna->clear();
    delete dna;

    return 0;
}
