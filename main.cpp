// EEM120 Group Project : Railway Ticket Reservation System
// Simüle bir şekilde tren seferleri oluşturabilen, rezervasyon, sorgulama menülerini içinde barındırmaktadır
// Tren seferlerini belli oranlarda rastgele dolduran, oluşturulan isim havuzundan doldurulan koltuklara sahip bilgileri ekleyen;
// Oluşturduğumuz havuzdan sefer isimleri alan, 2 vagonlu, her vagonu 20'şer koltuklu seferler
// Detaylı rezervasyon menüsü ve koltuklar boş ise boş olduğunu, doluysa da kullanıcı bilgilerini veren sorgu sistemini içermektedir.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;

class Tren {
private:
    string kimlik;
    string seferAdi;
    vector<vector<vector<string>>> koltukBilgileri;

public:
    static const int vagonSayisi = 2;
    static const int koltukSayisi = 20;

    Tren(string kimlik, string seferAdi) : kimlik(kimlik), seferAdi(seferAdi), koltukBilgileri(vagonSayisi, vector<vector<string>>(koltukSayisi, vector<string>(3, ""))) {
    }

    Tren() : kimlik("Bos Tren"), seferAdi("Bilinmiyor"), koltukBilgileri(vagonSayisi, vector<vector<string>>(koltukSayisi, vector<string>(3, ""))) {
    }

    string kimlikAl() const {
        return kimlik;
    }

    string seferAdiAl() const {
        return seferAdi;
    }

    void bosKoltuklariGoster() const {
        for (int i = 0; i < vagonSayisi; ++i) {
            cout << "Vagon " << i + 1 << ": ";
            bool bosKoltukVar = false;
            for (int j = 0; j < koltukSayisi; ++j) {
                if (koltukBilgileri[i][j][0].empty()) {
                    cout << (i * koltukSayisi + j + 1) << " ";
                    bosKoltukVar = true;
                }
            }
            if (!bosKoltukVar) {
                cout << "Seferde Bos Yer Kalmamistir";
            }
            cout << endl;
        }
    }

    bool koltukRezerveEt(int koltukNumarasi, const string& ad, int yas, const string& cinsiyet) {
        int vagonIndeksi = (koltukNumarasi - 1) / koltukSayisi;
        int koltukIndeksi = (koltukNumarasi - 1) % koltukSayisi;

        if (koltukNumarasi < 1 || koltukNumarasi > vagonSayisi * koltukSayisi || !koltukBilgileri[vagonIndeksi][koltukIndeksi][0].empty()) {
            return false;
        }
        koltukBilgileri[vagonIndeksi][koltukIndeksi][0] = ad;
        koltukBilgileri[vagonIndeksi][koltukIndeksi][1] = to_string(yas);
        koltukBilgileri[vagonIndeksi][koltukIndeksi][2] = cinsiyet;
        return true;
    }

    string koltukSahibi(int koltukNumarasi) const {
        int vagonIndeksi = (koltukNumarasi - 1) / koltukSayisi;
        int koltukIndeksi = (koltukNumarasi - 1) % koltukSayisi;

        if (koltukNumarasi < 1 || koltukNumarasi > vagonSayisi * koltukSayisi) {
            return "Gecersiz koltuk numarasi.";
        } else if (koltukBilgileri[vagonIndeksi][koltukIndeksi][0].empty()) {
            return "Tren: " + kimlik + ", Sefer: " + seferAdi + ", Koltuk " + to_string(koltukNumarasi) + " sahipsizdir.";
        } else {
            return koltukBilgileri[vagonIndeksi][koltukIndeksi][0] + " - " +
                   koltukBilgileri[vagonIndeksi][koltukIndeksi][1] + " - " +
                   koltukBilgileri[vagonIndeksi][koltukIndeksi][2];
        }
    }

    void ekranTemizle() const {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void rastgeleKoltukDoldur(int doluKoltukSayisi, const vector<string>& erkekIsimleri, const vector<string>& kadinIsimleri) {
        srand(static_cast<unsigned int>(time(nullptr)));

        int toplamKoltukSayisi = vagonSayisi * koltukSayisi;
        vector<int> doluKoltuklar;

        while (doluKoltuklar.size() < doluKoltukSayisi) {
            int rastgeleKoltuk = rand() % toplamKoltukSayisi + 1;
            if (find(doluKoltuklar.begin(), doluKoltuklar.end(), rastgeleKoltuk) == doluKoltuklar.end()) {
                doluKoltuklar.push_back(rastgeleKoltuk);
            }
        }

        for (int koltukNumarasi : doluKoltuklar) {
            int vagonIndeksi = (koltukNumarasi - 1) / koltukSayisi;
            int koltukIndeksi = (koltukNumarasi - 1) % koltukSayisi;

            if (rand() % 2 == 0) {
                int isimIndeksi = rand() % erkekIsimleri.size();
                koltukBilgileri[vagonIndeksi][koltukIndeksi][0] = erkekIsimleri[isimIndeksi];
                koltukBilgileri[vagonIndeksi][koltukIndeksi][2] = "Erkek";
            } else {
                int isimIndeksi = rand() % kadinIsimleri.size();
                koltukBilgileri[vagonIndeksi][koltukIndeksi][0] = kadinIsimleri[isimIndeksi];
                koltukBilgileri[vagonIndeksi][koltukIndeksi][2] = "Kadin";
            }
            koltukBilgileri[vagonIndeksi][koltukIndeksi][1] = to_string(rand() % 100 + 1);
        }
    }
};

void menuGoster() {
    cout << "Ana Menu:" << endl;
    cout << "1. Mevcut trenleri ve bos koltuklari goruntule" << endl;
    cout << "2. Koltuk rezervasyonu yap" << endl;
    cout << "3. Koltuk sahibini sorgula" << endl;
    cout << "4. Cikis" << endl;
    cout << "Seciminizi girin: ";
}

void ekranTemizle() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    vector<Tren> aktifTrenler(3);

    vector<string> seferAdlari = { "Ankara-Kocaeli", "Ankara-Eskisehir", "Ankara-Sivas", "Ankara-Istanbul", "Ankara-Antalya" };
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<string> seciliSeferler(3);
    for (int i = 0; i < 3; ++i) {
        seciliSeferler[i] = "[" + to_string(i + 1) + "] " + seferAdlari[rand() % seferAdlari.size()];
        aktifTrenler[i] = Tren("Tren " + to_string(i + 1), seciliSeferler[i]);
    }

    vector<string> erkekIsimleri = { "Ali", "Ahmet", "Mehmet", "Mustafa", "Hakan" };
    vector<string> kadinIsimleri = { "Ayse", "Fatma", "Elif", "Zeynep", "Meryem" };

    for (int i = 0; i < 3; ++i) {
        aktifTrenler[i].rastgeleKoltukDoldur(15, erkekIsimleri, kadinIsimleri);
    }

    cout << "RailYou'ya Hosgeldiniz!" << endl;

    int secim;

    do {
        menuGoster();
        cin >> secim;
        cout << endl;

        switch (secim) {
            case 1: {
                ekranTemizle();
                cout << "Aktif trenler:" << endl;
                for (int i = 0; i < 3; ++i) {
                    cout << seciliSeferler[i] << ": " << endl;
                    aktifTrenler[i].bosKoltuklariGoster();
                    cout << endl;
                }
                break;
            }
            case 2: {
                ekranTemizle();
                int trenNumarasi, koltukNumarasi, yas;
                string ad, cinsiyet;

                cout << "Tren numarasini girin (1-3): ";
                cin >> trenNumarasi;
                if (trenNumarasi < 1 || trenNumarasi > 3) {
                    cout << "Gecersiz tren numarasi. Tekrar deneyin." << endl;
                    break;
                }

                cout << "Koltuk numarasini girin (1-40): ";
                cin >> koltukNumarasi;
                if (koltukNumarasi < 1 || koltukNumarasi > 40) {
                    cout << "Gecersiz koltuk numarasi. Tekrar deneyin." << endl;
                    break;
                }

                cout << "Isminizi girin: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, ad);

                cout << "Yasinizi girin: ";
                cin >> yas;

                cout << "Cinsiyetinizi girin (Erkek/Kadin): ";
                cin >> cinsiyet;

                if (aktifTrenler[trenNumarasi - 1].koltukRezerveEt(koltukNumarasi, ad, yas, cinsiyet)) {
                    cout << endl << "----------------------------------------" << endl;
                    cout << "Rezervasyon basarili!" << endl;
                    cout << "----------------------------------------" << endl;
                } else {
                    cout << "Rezervasyon basarisiz. Koltuk zaten dolu olabilir veya gecersiz bir deger girdiniz." << endl;
                }

                cout << endl;
                break;
            }
            case 3: {
                ekranTemizle();
                int trenNumarasi, koltukNumarasi;

                cout << "Tren numarasini girin (1-3): ";
                cin >> trenNumarasi;
                if (trenNumarasi < 1 || trenNumarasi > 3) {
                    cout << "Gecersiz tren numarasi. Tekrar deneyin." << endl;
                    break;
                }

                cout << "Koltuk numarasini girin (1-40): ";
                cin >> koltukNumarasi;
                if (koltukNumarasi < 1 || koltukNumarasi > 40) {
                    cout << "Gecersiz koltuk numarasi. Tekrar deneyin." << endl;
                    break;
                }

                cout << endl << "Koltuk sahibi: " << aktifTrenler[trenNumarasi - 1].koltukSahibi(koltukNumarasi) << endl;
                cout << endl;
                break;
            }
            case 4: {
                ekranTemizle();
                cout << "RailYou'yu kullandiginiz icin tesekkurler. Iyi gunler!" << endl;
                break;
            }
            default: {
                ekranTemizle();
                cout << "Gecersiz bir secim yaptiniz. Lutfen tekrar deneyin." << endl;
                break;
            }
        }
    } while (secim != 4);

    return 0;
}
