// EEM120 Group Project : Railway Ticket Reservation System
// Simüle bir şekilde tren seferleri oluşturabilen, rezervasyon, sorgulama menülerini içinde barındırmaktadır
// Oluşturduğumuz havuzdan sefer isimleri alan, 2 vagonlu, her vagonu 20'şer koltuklu seferler
// Detaylı rezervasyon menüsü ve koltuklar boş ise boş olduğunu, doluysa da kullanıcı bilgilerini veren sorgu sistemini içermektedir.

#include <iostream> // Standart giriş/çıkış işlemleri için gerekli kütüphane
#include <string> // String işlemleri için gerekli kütüphane
#include <cstdlib> // Ekran temizlemek için sistem komutlarını çalıştırmak için gerekli kütüphane
#include <ctime>  // Zamanı almak ve rastgele sayı üretmek için gerekli kütüphane
#include <algorithm> // Algoritma işlemleri için gerekli kütüphane

using namespace std; // Standard kütüphane kullanım alanı [Kodların başına std koymaktan kurtarıyor]

class Tren { // Tren sınıfı tanımlanıyor
private:
    string kimlik; // Trenin kimliği
    string seferAdi; // Trenin sefer adı
    string koltukBilgileri[2][20][3]; // 2 vagon, her biri 20 koltuk, her birinde 3 bilgi (ad, yaş, cinsiyet)

public:
    static const int vagonSayisi = 2; // Sabit vagon sayısı [Her tren 2 vagona ve vagon başı 20 koltuğa sahip]
    static const int koltukSayisi = 20; // Sabit koltuk sayısı

    Tren(string kimlik, string seferAdi) : kimlik(kimlik), seferAdi(seferAdi) { // Tren yapıcı fonksiyonu
        // Her koltuğun bilgilerini boş olarak başlat
        for (int i = 0; i < vagonSayisi; ++i) { // Vagon sayısı kadar döngü [ 2 ]
            for (int j = 0; j < koltukSayisi; ++j) { // Koltuk sayısı kadar döngü [ 20 ]
                koltukBilgileri[i][j][0] = ""; // Ad
                koltukBilgileri[i][j][1] = ""; // Yaş
                koltukBilgileri[i][j][2] = ""; // Cinsiyet
            }
        }
    }

    Tren() : kimlik("Bos Tren"), seferAdi("Bilinmiyor") { // Boş tren yapıcı fonksiyonu.
        // Boş yapıcı
    }

    string kimlikAl() const { // Trenin kimliğini alıyoruz.
        return kimlik;
    }

    string seferAdiAl() const { // Trenin sefer adını alıyoruz.
        return seferAdi;
    }

    void bosKoltuklariGoster() const { // Boş koltukları göstermek için
        for (int i = 0; i < vagonSayisi; ++i) { // Vagon sayısı kadar döngü [2]
            cout << "Vagon " << i + 1 << ": "; // Vagon numarasını ekrana yazıyorum
            bool bosKoltukVar = false; // Boş koltuk var mı kontrolü
            for (int j = 0; j < koltukSayisi; ++j) { // Koltuk sayısı kadar döngü [20]
                if (koltukBilgileri[i][j][0] == "") { // Eğer koltuk boşsa
                    cout << (i * koltukSayisi + j + 1) << " "; // Koltuk numarasını ekrana yaz
                    bosKoltukVar = true; // Boş koltuk var olduğunu belirt
                }
            }
            if (!bosKoltukVar) { // Eğer boş koltuk yoksa
                cout << "Seferde Bos Yer Kalmamistir";
            }
            cout << endl;
        }
    }

    bool koltukRezerveEt(int koltukNumarasi, const string& ad, int yas, const string& cinsiyet) { // Koltuk rezervasyonu yapmak için
        int vagonIndeksi = (koltukNumarasi - 1) / koltukSayisi; // Koltuğun bulunduğu vagonun indeksi
        int koltukIndeksi = (koltukNumarasi - 1) % koltukSayisi; // Koltuğun bulunduğu sıranın indeksi
        
        // Eğer koltuk numarası geçersizse veya koltuk doluysa
        if (koltukNumarasi < 1 || koltukNumarasi > vagonSayisi * koltukSayisi || koltukBilgileri[vagonIndeksi][koltukIndeksi][0] != "") {
            return false; // Rezervasyon başarısız
        }
        koltukBilgileri[vagonIndeksi][koltukIndeksi][0] = ad; // Adı kaydetmek için
        koltukBilgileri[vagonIndeksi][koltukIndeksi][1] = to_string(yas); // Yaşı kaydetmek için
        koltukBilgileri[vagonIndeksi][koltukIndeksi][2] = cinsiyet; // Cinsiyeti kaydetmek için
        return true; // Rezervasyon başarılı
    }

    string koltukSahibi(int koltukNumarasi) const { // Koltuğun sahibini sorgulamak için
        int vagonIndeksi = (koltukNumarasi - 1) / koltukSayisi; // Koltuğun bulunduğu vagonun indeksi
        int koltukIndeksi = (koltukNumarasi - 1) % koltukSayisi; // Koltuğun bulunduğu sıranın indeksi

        // Eğer koltuk numarası geçersizse [1 ila 40 arasında değilse (vagon sayısı * koltuk sayisi -> 2*20 = 40)]
        if (koltukNumarasi < 1 || koltukNumarasi > vagonSayisi * koltukSayisi) { 
            return "Gecersiz koltuk numarasi.";
        }
        else if (koltukBilgileri[vagonIndeksi][koltukIndeksi][0] == "") { // Eğer koltuk boşsa
            return "Koltuk Sahipsizdir";
        }
        else {
            // Koltuk sahibinin bilgilerini döndür. Ad-Yaş-Cinsiyet
            return koltukBilgileri[vagonIndeksi][koltukIndeksi][0] + " - " + 
                koltukBilgileri[vagonIndeksi][koltukIndeksi][1] + " - " +
                koltukBilgileri[vagonIndeksi][koltukIndeksi][2]; 
        }
    }

    void ekranTemizle() const { // Ekranı temizleme fonksiyonu
#ifdef _WIN32 // Windows işletim sistemi için temizleme kodu
        system("cls");
#else // Diğer işletim sistemleri için temizleme kodu
        system("clear");
#endif
    }
};

void menuGoster() { // Ana menüyü gösteren fonksiyon
    cout << "Ana Menu:" << endl; // Başlık
    cout << "1. Mevcut trenleri ve bos koltuklari goruntule" << endl; //Menü 1, Trenleri Görüntüleme
    cout << "2. Koltuk rezervasyonu yap" << endl; // Menü 2, Rezervasyon Sistemi
    cout << "3. Koltuk sahibini sorgula" << endl; // Menü 3, Sorgulama Sistemi
    cout << "4. Cikis" << endl; // Menü 4, Çıkış
    cout << "Seciminizi girin: "; // Kullanıcıdan seçim yapmasını istiyorum.
}

void ekranTemizle() { // Ekranı temizleme fonksiyonu
#ifdef _WIN32 // Windows işletim sistemi için temizleme kodu
    system("cls");
#else // Diğer işletim sistemler için temizleme kodu
    system("clear");
#endif
}

int main() { // Ana fonksiyon
    Tren aktifTrenler[3]; // En fazla 3 tren oluşturuyoruz
    
    // Tren sefer adları [Keyfimizce rastgele isimler verilmesi için 5 sefer adı]
    string seferAdlari[] = { "Ankara-Kocaeli", "Ankara-Eskisehir", "Ankara-Sivas", "Ankara-Istanbul", "Ankara-Antalya" };
    srand(time(nullptr)); // Rastgelelik için zamanı kullanıyorum

    // Rastgele sefer adlarını belirliyoruz
    string seciliSeferler[3];
    for (int i = 0; i < 3; ++i) { // Döngü 3 kez dönerek, 3 treni de isimlendiriyor
        seciliSeferler[i] = "[" + to_string(i + 1) + "] " + seferAdlari[rand() % 5]; // Rastgele sefer adı belirle
        aktifTrenler[i] = Tren("Tren " + to_string(i + 1), seciliSeferler[i]); // Trenleri oluştururken sefer adını ekliyoruz
    }

    cout << "RailYou'ya Hosgeldiniz!" << endl; // Kullanıcıya Hoş Geldiniz Mesajı

    int secim;

    do { // Ana menü döngüsü [while şartı 4 Girilmediği sürece]
         menuGoster(); // Ana menüyü göster
        cin >> secim; // Kullanıcıdan seçim alma
        cout << endl;

        switch (secim) { // Kullanıcının seçimine göre işlem yapıyoruz [Switch Case ile]
        
            case 1: { // Menü 1, Trenleri Gösterme Menüsü
            ekranTemizle(); // Ekranı temizleme

             // Olusturulan aktif ve müsait koltukları gosterme
            cout << "Aktif trenler:" << endl;
            for (int i = 0; i < 3; ++i) { // Döngü 3 kez dönerek 3 treni de ekrana getirecek
                cout << seciliSeferler[i] << ": " << endl; // Sefer adını ekrana yazma
                aktifTrenler[i].bosKoltuklariGoster(); // Boş koltukları gösterme
                cout << endl;
            }
            cout << endl;
            break;
        }
            
        case 2: { // Menü 2, Rezervasyon menüsü
            
            // Belirli bir tren için koltuk rezervasyonu yapmak adına:
            int trenIndeksi;
            cout << "Rezervasyon yapmak istediginiz trenin numarasini girin (1-3): "; // Kullanıcıdan tren numarası al
            cin >> trenIndeksi; // Kullanıcının girdiği tren numarasını al
            --trenIndeksi; // Kullanıcının girdiği indeks sıfırdan başladığı için bir azaltılır [Çünkü indekste 1.tren 0'dır haliyle 1 azaltacağız]

            int koltukNumarasi; // Koltuk numarası
            cout << "Rezervasyon yapmak istediginiz koltuk numarasini girin: "; // Kullanıcıdan koltuk numarası al
            cin >> koltukNumarasi; // Kullanıcının girdiği koltuk numarasını al

            string ad; // Ad
            int yas; // Yaş
            string cinsiyet; // Cinsiyet
            bool dogruYas = false; // Doğru yaş kontrolü [Yanlış başlatıyoruz, istenilen şartlar sağlandığında doğruya dönüyor]

            cout << "Adinizi girin: "; // Kullanıcıdan adını alıyoruz
            cin >> ad; // Girilen adı alıyoruz

            // Doğru yaş girişi yapılıncaya kadar döngüyü devam ettir [string olarak alıyoruz ki rakam mı diye kontrol edeceğiz]
            while (!dogruYas) {
                cout << "Yasinizi girin (1-100): "; // Kullanıcıdan yaş al
                cin >> yas; // Girilen yaşı al

                // Yaş girişinin doğru olup olmadığını kontrol et
                if (cin.fail() || yas < 1 || yas > 100) { // 1-100 aralığında mı diye kontrol ediyoruz
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Yas 1 ile 100 arasinda olmalidir. Lutfen tekrar deneyin." << endl;
                }
                else {
                    dogruYas = true; // Yaş girişi doğruysa false olarak başlatılan değer true'ya döndürülüyor
                }
            }

            cout << "Cinsiyetinizi girin (Erkek/Kadin): "; // Kullanıcıdan cinsiyet istiyoruz
            cin >> cinsiyet; // Girilen cinsiyeti alıyoruz

            // Rezervasyon yapılırken yaş ve cinsiyet bilgileri de dahil edilyor
            if (aktifTrenler[trenIndeksi].koltukRezerveEt(koltukNumarasi, ad, yas, cinsiyet)) { // Koltuk rezervasyonu yapılırsa
                cout << endl << "-----------------------------------------------------------------------";
                cout << endl << koltukNumarasi << ". koltuk " << aktifTrenler[trenIndeksi].seferAdiAl() << " treninde " << ad << " adina basariyla rezerve edildi." << endl;
                cout << "-----------------------------------------------------------------------" << endl;
            }
            else { // Koltuk rezervasyonu yapılamazsa
                cout << "Rezervasyon basarisiz oldu. Lutfen gecerli bir koltuk numarasi girin." << endl;
            }
            cout << endl;
            break;
        }

        case 3: { // Menü 3, Sorgulama Menüsü
            ekranTemizle(); // Ekranı temizle

            // Belirli bir trenin belirli bir koltuğunun sahibini sorgula
            int trenIndeksi;
            cout << "Koltuk sahibini sorgulamak istediginiz trenin indeksini girin (1-3): "; // Kullanıcıdan tren numarası al
            cin >> trenIndeksi; // Kullanıcının girdiği tren numarasını al.
            --trenIndeksi; 
            // Kullanıcının girdiği indeks sıfırdan başladığı için bir azaltılır [Tren 1 aslında indekste 0 olarak kayıtlı, bu yüzden 1 azaltılır]
            
            int koltukNumarasi; // Koltuk numarası
            cout << "Sorgulamak istediginiz koltuk numarasini girin: "; // Kullanıcıdan koltuk numarası al
            cin >> koltukNumarasi;

            if (koltukNumarasi >= 1 && koltukNumarasi <= Tren::vagonSayisi * Tren::koltukSayisi) { // Eğer koltuk numarası geçerliyse [1-40 arası]
                string koltukSahibi = aktifTrenler[trenIndeksi].koltukSahibi(koltukNumarasi); // Koltuğun sahibini sorgula
                if (koltukSahibi == "Koltuk Sahipsizdir") {  // Eğer koltuk boşsa
                    cout << endl << "-----------------------------------------------------------------------" << endl;
                    cout << aktifTrenler[trenIndeksi].seferAdiAl() << " trenindeki " << koltukNumarasi << ". koltuk " << "Sahipsizdir" << endl; // Koltuk sahibi yok mesajı yazdırılır
                    cout << "-----------------------------------------------------------------------" << endl;
                }
                else if (koltukSahibi != "") { // Eğer koltuk doluysa
                    cout << endl << "-----------------------------------------------------------------------" << endl;
                    cout << koltukNumarasi << ". koltuk " << aktifTrenler[trenIndeksi].seferAdiAl() << " treninde " << koltukSahibi << " tarafindan rezerve edilmistir." << endl; // Koltuk sahibi bilgileri yazdırılır
                    cout << "-----------------------------------------------------------------------" << endl;
                }
                else { // Diğer durumlarda uyarı mesajı yazdırılır
                    cout << "Belirtilen koltuk numarasi bos veya gecersiz." << endl;
                }
            }
            else { // Eğer koltuk numarası geçersizse uyarı mesajı yazdırılır
                cout << "Gecersiz koltuk numarasi. Lutfen tekrar deneyin." << endl;
            }
            cout << endl;
            break;
        }

        case 4: { // Menü 4, Çıkış menüsü
            ekranTemizle();
            cout << "RailYou'yu kullandiginiz icin tesekkur ederiz. Iyi gunler dileriz!" << endl; // Kullanıcıya veda mesajı
            break;
        }
        default: { // Diğer durumlarda
            cout << "Gecersiz secim. Lutfen tekrar deneyin." << endl; // 1-4 değerleri dışında bir şey girilirse
        }
        }

        // Ekranı temizleme sadece 2. ve 3. menü kullanıldığında yapılır
        if (secim == 2 || secim == 3) { // Seçim 2 veya 3 ise
            system("pause"); // Ekran kapanması beklenir
            ekranTemizle(); // Ekran temizleme
        }

    } while (secim != 4); // Kullanıcı çıkış yapana kadar döngüyü devam ettir

    return 0; // Programı sonlandır
}
