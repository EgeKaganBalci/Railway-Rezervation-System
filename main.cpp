#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Tren {
private:
    string kimlik;
    string seferAdi;
    string koltukBilgileri[2][20][3];

public:
    static const int vagonSayisi = 2;
    static const int koltukSayisi = 20;

    Tren(string kimlik, string seferAdi) : kimlik(kimlik), seferAdi(seferAdi) {
        for (int i = 0; i < vagonSayisi; ++i) {
            for (int j = 0; j < koltukSayisi; ++j) {
                koltukBilgileri[i][j][0] = ""; // Ad
                koltukBilgileri[i][j][1] = ""; // Yaş
                koltukBilgileri[i][j][2] = ""; // Cinsiyet
            }
        }
        rastgeleDoluluk(); // Rastgele doluluk ataması yapılıyor.
    }

    Tren() : kimlik("Bos Tren"), seferAdi("Bilinmiyor") {
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
                if (koltukBilgileri[i][j][0] == "") {
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

        if (koltukNumarasi < 1 || koltukNumarasi > vagonSayisi * koltukSayisi || koltukBilgileri[vagonIndeksi][koltukIndeksi][0] != "") {
            return false;
        }

        // Yaş kontrolü ekleniyor
        if (yas <= 0 || yas > 100) {
            cout << "Gecersiz yas! Lutfen 1 ile 100 arasinda bir yas girin." << endl;
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
        }
        else if (koltukBilgileri[vagonIndeksi][koltukIndeksi][0] == "") {
            return "Koltuk Sahipsizdir";
        }
        else {
            return koltukBilgileri[vagonIndeksi][koltukIndeksi][0] + " - " +
                koltukBilgileri[vagonIndeksi][koltukIndeksi][1] + " - " +
                koltukBilgileri[vagonIndeksi][koltukIndeksi][2];
        }
    }

    void rastgeleDoluluk() {
        srand(time(nullptr)); // Rastgelelik için zamanı kullan

        for (int i = 0; i < vagonSayisi; ++i) {
            for (int j = 0; j < koltukSayisi; ++j) {
                if (rand() % 2 == 0) { // Her koltuk için %50 olasılıkla dolu veya boş atanıyor.
                    string isim = "Yolcu" + to_string(i * koltukSayisi + j + 1);
                    int yas = rand() % 60 + 20; // 20-79 arası yaş atanıyor.
                    string cinsiyet = (isim[isim.size() - 1] == 'a') ? "Kadin" : "Erkek"; // İsim son harfine göre cinsiyet atanıyor.
                    koltukBilgileri[i][j][0] = isim;
                    koltukBilgileri[i][j][1] = to_string(yas);
                    koltukBilgileri[i][j][2] = cinsiyet;
                }
            }
        }
    }

    void ekranTemizle() const {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
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
    Tren aktifTrenler[3];
    string seferAdlari[5] = {"Ankara - Istanbul", "Istanbul - Ankara", "Izmir - Ankara", "Ankara - Izmir", "Istanbul - Izmir"};

    for (int i = 0; i < 3; ++i) {
        string seferAdi = "[" + to_string(i + 1) + "] " + seferAdlari[rand() % 5];
        aktifTrenler[i] = Tren("Tren " + to_string(i + 1), seferAdi);
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
                cout << aktifTrenler[i].seferAdiAl() << ": " << endl;
                aktifTrenler[i].bosKoltuklariGoster();
                cout << endl;
            }
            cout << endl;
            break;
        }
        case 2: {
            int trenIndeksi;
            cout << "Rezervasyon yapmak istediginiz trenin numarasini girin (1-3): ";
            cin >> trenIndeksi;
            --trenIndeksi;

            int koltukNumarasi;
            cout << "Rezervasyon yapmak istediginiz koltuk numarasini girin: ";
            cin >> koltukNumarasi;

            string ad;
            string yasString;
            int yas;
            string cinsiyet;
            bool dogruYas = false;

            cout << "Adinizi girin: ";
            cin >> ad;

            while (!dogruYas) {
                cout << "Yasinizi girin: ";
                cin >> yasString;

                for (char c : yasString) {
                    if (!isdigit(c)) {
                        cout << "Yas sadece rakam iceriyor olmalidir. Lutfen tekrar deneyin." << endl;
                        break;
                    }
                }

                if (all_of(yasString.begin(), yasString.end(), ::isdigit)) {
                    yas = stoi(yasString);
                    if (yas <= 0 || yas > 100) {
                        cout << "Gecersiz yas! Lutfen 1 ile 100 arasinda bir yas girin." << endl;
                    } else {
                        dogruYas = true;
                    }
                }
            }

            cout << "Cinsiyetinizi girin (Erkek/Kadin): ";
            cin >> cinsiyet;

            if (aktifTrenler[trenIndeksi].koltukRezerveEt(koltukNumarasi, ad, yas, cinsiyet)) {
                cout << endl << "-----------------------------------------------------------------------";
                cout << endl << koltukNumarasi << ". koltuk " << aktifTrenler[trenIndeksi].seferAdiAl() << " treninde " << ad << " adina basariyla rezerve edildi." << endl;
                cout << "-----------------------------------------------------------------------" << endl;
            }
            else {
                cout << "Rezervasyon basarisiz oldu. Lutfen gecerli bir koltuk numarasi girin." << endl;
            }
            cout << endl;
            break;
        }

        case 3: {
            ekranTemizle();
            int trenIndeksi;
            cout << "Koltuk sahibini sorgulamak istediginiz trenin indeksini girin (1-3): ";
            cin >> trenIndeksi;
            --trenIndeksi;

            int koltukNumarasi;
            cout << "Sorgulamak istediginiz koltuk numarasini girin: ";
            cin >> koltukNumarasi;

            if (koltukNumarasi >= 1 && koltukNumarasi <= Tren::vagonSayisi * Tren::koltukSayisi) {
                string koltukSahibi = aktifTrenler[trenIndeksi].koltukSahibi(koltukNumarasi);
                if (koltukSahibi == "Koltuk Sahipsizdir") {
                    cout << endl << "-----------------------------------------------------------------------" << endl;
                    cout << aktifTrenler[trenIndeksi].seferAdiAl() << " trenindeki " << koltukNumarasi << ". koltuk " << "Sahipsizdir" << endl;
                    cout << "-----------------------------------------------------------------------" << endl;
                }
                else if (koltukSahibi != "") {
                    cout << endl << "-----------------------------------------------------------------------" << endl;
                    cout << koltukNumarasi << ". koltuk " << aktifTrenler[trenIndeksi].seferAdiAl() << " treninde " << koltukSahibi << " tarafindan rezerve edilmistir." << endl;
                    cout << "-----------------------------------------------------------------------" << endl;
                }
                else {
                    cout << "Belirtilen koltuk numarasi bos veya gecersiz." << endl;
                }
            }
            else {
                cout << "Gecersiz koltuk numarasi. Lutfen tekrar deneyin." << endl;
            }
            cout << endl;
            break;
        }

        case 4: {
            ekranTemizle();
            cout << "RailYou'yu kullandiginiz icin tesekkur ederiz. Iyi gunler dileriz!" << endl;
            break;
        }
        default: {
            cout << "Gecersiz secim. Lutfen tekrar deneyin." << endl;
        }
        }

        if (secim == 2 || secim == 3) {
            system("pause");
            ekranTemizle();
        }

    } while (secim != 4);

    return 0;
}
