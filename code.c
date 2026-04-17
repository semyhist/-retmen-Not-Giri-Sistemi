#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 100

/* ===================== STRUCT TANIMLARI (structs.h) ===================== */

typedef struct {
    int numara;
    char ad[MAX_STRING];
    char soyad[MAX_STRING];
    char email[MAX_STRING];
} Ogrenci;

typedef struct {
    char kod[MAX_STRING];
    char ad[MAX_STRING];
    char dosya_yolu[MAX_STRING];
    char hesapYontemi[MAX_STRING];
} Ders;

typedef struct {
    Ogrenci *ogrenciler;
    int ogrenci_sayisi;

    Ders *dersler;
    int ders_sayisi;

    char ogrenci_dosya_yolu[MAX_STRING];
    char ders_dosya_yolu[MAX_STRING];
} Sistem;

/* ===================== FONKSIYON PROTOTIPLERI ===================== */

/* osman.c */
void ogrenci_menu(Sistem *sistem);
void not_menu(Sistem *sistem);
void ogrenci_dosyasi_oku(Sistem *sistem);
void ogrenci_dosyasi_yaz(Sistem *sistem);
void ogrenci_ekle(Sistem *sistem);
void ogrencileri_listele(Sistem *sistem);
void not_gir(Sistem *sistem);
void harf_notlari_hesapla(Sistem *sistem);

/* semih.c */
void ders_menu(Sistem *sistem);
void dersleri_listele(Sistem *sistem);
void ders_dosyasi_oku(Sistem *sistem);
void ders_dosyasi_yaz(Sistem *sistem);
void ders_ekle(Sistem *sistem);
void dosyalari_kaydet(Sistem *sistem);

/* ihsan.c */
void rapor_menu(Sistem *sistem);
void ders_notlarini_listele(Sistem *sistem);

/* main.c */
void ayarlar_oku(Sistem *sistem);

/* ===================== IHSAN.C ===================== */

void rapor_menu(Sistem *sistem) {
    int secim;
    printf("\n=== RAPORLAMA VE LISTELEME ===\n");
    printf("1. Ders Notlarini Listele\n");
    printf("2. Ana Menu\n");
    printf("Secim: ");
    scanf("%d", &secim);

    if (secim == 1)
        ders_notlarini_listele(sistem);
}

void ders_notlarini_listele(Sistem *sistem) {
    if(sistem->ders_sayisi == 0) {
        printf("Ders yok!\n");
        return;
    }

    printf("\n=== DERSLER ===\n");
    for(int i = 0; i < sistem->ders_sayisi; i++) {
        printf("%d. %s - %s\n", i+1, sistem->dersler[i].kod, sistem->dersler[i].ad);
    }

    int ders_secim;
    printf("Ders secin: ");
    scanf("%d", &ders_secim);

    if(ders_secim < 1 || ders_secim > sistem->ders_sayisi) return;

    Ders *secilen = &sistem->dersler[ders_secim-1];
    FILE *f = fopen(secilen->dosya_yolu, "r");
    if(!f) {
        printf("Not dosyasi bulunamadi!\n");
        return;
    }

    float toplam = 0, en_yuksek = 0, en_dusuk = 100;
    int ogr_say = 0;

    char satir[200];
    while(fgets(satir, sizeof(satir), f)) {
        if(satir[0] == '#') continue;
        int no;
        float v, fn, b;
        if(sscanf(satir, "%d %f %f %f", &no, &v, &fn, &b) >= 3) {
            float genel = v*0.4 + fn*0.6;
            if(b > fn) genel = v*0.4 + b*0.6;
            toplam += genel;
            if(genel > en_yuksek) en_yuksek = genel;
            if(genel < en_dusuk) en_dusuk = genel;
            ogr_say++;
        }
    }
    fclose(f);

    if(ogr_say > 0) {
        printf("Ortalama: %.2f\n", toplam / ogr_say);
        printf("En Yuksek: %.2f\n", en_yuksek);
        printf("En Dusuk: %.2f\n", en_dusuk);
    }
}

/* ===================== OSMAN.C ===================== */
void ogrenci_menu(Sistem *sistem) {
    int secim;
    printf("\n=== OGRENCI ISLEMLERI ===\n");
    printf("1. Ogrenci Ekle\n");
    printf("2. Ogrencileri Listele\n");
    printf("3. Ana Menu\n");
    printf("Secim: ");
    scanf("%d", &secim);

    switch(secim) {
        case 1: ogrenci_ekle(sistem); break;
        case 2: ogrencileri_listele(sistem); break;
        case 3: break;
    }
}

void not_menu(Sistem *sistem) {
    int secim;
    printf("\n=== NOT ISLEMLERI ===\n");
    printf("1. Derse Not Gir\n");
    printf("2. Dersin Harf Notlarini Hesapla\n");
    printf("3. Ana Menu\n");
    printf("Secim: ");
    scanf("%d", &secim);

    switch(secim) {
        case 1: not_gir(sistem); break;
        case 2: harf_notlari_hesapla(sistem); break;
        case 3: break;
    }
}

void ogrenci_dosyasi_oku(Sistem *sistem) {
    FILE *f = fopen(sistem->ogrenci_dosya_yolu, "r");
    if(f) {
        char satir[300];
        while(fgets(satir, sizeof(satir), f)) {
            Ogrenci *temp = realloc(sistem->ogrenciler, (sistem->ogrenci_sayisi + 1) * sizeof(Ogrenci));
            if(temp) {
                sistem->ogrenciler = temp;
                if(sscanf(satir, "%d,%99[^,],%99[^,],%99s",
                    &sistem->ogrenciler[sistem->ogrenci_sayisi].numara,
                    sistem->ogrenciler[sistem->ogrenci_sayisi].ad,
                    sistem->ogrenciler[sistem->ogrenci_sayisi].soyad,
                    sistem->ogrenciler[sistem->ogrenci_sayisi].email) == 4) {
                    sistem->ogrenci_sayisi++;
                }
            }
        }
        fclose(f);
    }
}

void ogrenci_dosyasi_yaz(Sistem *sistem) {
    FILE *f = fopen(sistem->ogrenci_dosya_yolu, "w");
    if(f) {
        int i;
        for(i = 0; i < sistem->ogrenci_sayisi; i++) {
            fprintf(f, "%d,%s,%s,%s\n",
                sistem->ogrenciler[i].numara,
                sistem->ogrenciler[i].ad,
                sistem->ogrenciler[i].soyad,
                sistem->ogrenciler[i].email);
        }
        fclose(f);
    }
}

void ogrenci_ekle(Sistem *sistem) {
    Ogrenci *temp = realloc(sistem->ogrenciler, (sistem->ogrenci_sayisi + 1) * sizeof(Ogrenci));
    if(!temp) return;
    sistem->ogrenciler = temp;

    printf("Numara: ");
    scanf("%d", &sistem->ogrenciler[sistem->ogrenci_sayisi].numara);

    printf("Ad: ");
    scanf("%99s", sistem->ogrenciler[sistem->ogrenci_sayisi].ad);

    printf("Soyad: ");
    scanf("%99s", sistem->ogrenciler[sistem->ogrenci_sayisi].soyad);

    printf("Email: ");
    scanf("%99s", sistem->ogrenciler[sistem->ogrenci_sayisi].email);

    sistem->ogrenci_sayisi++;
    ogrenci_dosyasi_yaz(sistem);
    printf("Ogrenci eklendi.\n");
}

void ogrencileri_listele(Sistem *sistem) {
    if(sistem->ogrenci_sayisi == 0) {
        printf("Ogrenci yok.\n");
        return;
    }
    printf("\n=== OGRENCI LISTESI ===\n");
    int i;
    for(i = 0; i < sistem->ogrenci_sayisi; i++) {
        printf("%d - %s %s (%s)\n",
            sistem->ogrenciler[i].numara,
            sistem->ogrenciler[i].ad,
            sistem->ogrenciler[i].soyad,
            sistem->ogrenciler[i].email);
    }
}


int ogrenci_var_mi(Sistem* sistem, int numara) {
    for (int i = 0; i < sistem->ogrenci_sayisi; i++) {
        if (sistem->ogrenciler[i].numara == numara) {
            return 1;
        }
    }
    return 0;
}

void not_gir(Sistem *sistem) {
    if (sistem->ders_sayisi == 0) {
        printf("Once ders ekleyin!\n");
        return;
    }

    printf("\n=== DERSLER ===\n");
    int i;
    for (i = 0; i < sistem->ders_sayisi; i++) {
        printf("%d. %s - %s\n", i + 1, sistem->dersler[i].kod, sistem->dersler[i].ad);
    }

    int ders_secim;
    printf("Ders secin (1-%d): ", sistem->ders_sayisi);
    if (scanf("%d", &ders_secim) != 1 || ders_secim < 1 || ders_secim > sistem->ders_sayisi) {
        printf("Gecersiz ders!\n");
        while(getchar() != '\n'); // buffer temizle
        return;
    }

    int no;
    printf("Ogrenci no: ");
    if (scanf("%d", &no) != 1) {
        printf("Gecersiz ogrenci no!\n");
        while(getchar() != '\n'); // buffer temizle
        return;
    }

    if (!ogrenci_var_mi(sistem, no)) {
        printf("Bu numaraya sahip bir ogrenci bulunamadi!\n");
        return;
    }

    char *dosya_yolu = sistem->dersler[ders_secim - 1].dosya_yolu;
    char temp_dosya_yolu[256];
    sprintf(temp_dosya_yolu, "%s.tmp", dosya_yolu);

    FILE *f_read = fopen(dosya_yolu, "r");
    FILE *f_write = fopen(temp_dosya_yolu, "w");

    if (!f_write) {
        printf("Gecici dosya olusturulamadi!\n");
        if (f_read) fclose(f_read);
        return;
    }

    int kayit_bulundu = 0;
    int guncellendi = 0;

    if (f_read) {
        char satir[200];
        while (fgets(satir, sizeof(satir), f_read)) {
            int mevcut_no;
            float v, fn, b;
            if (sscanf(satir, "%d %f %f %f", &mevcut_no, &v, &fn, &b) >= 3) {
                if (mevcut_no == no) {
                    kayit_bulundu = 1;
                    printf("Bu ogrenci icin zaten not girilmis (Vize:%.1f, Final:%.1f, But:%.1f).\n", v, fn, b);
                    printf("Guncellemek ister misiniz? (E/H): ");
                    char cevap;
                    do {
                       scanf(" %c", &cevap); // boşluk karakteri tamponu temizler
                    } while (isspace(cevap));


                    if (cevap == 'E' || cevap == 'e') {
                        float vize, final, butunleme;
                        printf("Yeni Vize: ");
                        scanf("%f", &vize);
                        printf("Yeni Final: ");
                        scanf("%f", &final);
                        printf("Yeni Butunleme (-1 yoksa): ");
                        scanf("%f", &butunleme);
                        fprintf(f_write, "%d %.2f %.2f %.2f\n", no, vize, final, butunleme);
                        guncellendi = 1;
                    } else {
                        fprintf(f_write, "%s", satir); // Değişiklik yoksa orijinal satırı yaz
                    }
                } else {
                    fprintf(f_write, "%s", satir);
                }
            } else {
                 fprintf(f_write, "%s", satir); // Yorum veya boş satırları koru
            }
        }
        fclose(f_read);
    }

    if (!kayit_bulundu) {
        float vize, final, butunleme;
        printf("Ogrenci icin yeni not girisi.\n");
        printf("Vize: ");
        scanf("%f", &vize);
        printf("Final: ");
        scanf("%f", &final);
        printf("Butunleme (-1 yoksa): ");
        scanf("%f", &butunleme);
        fprintf(f_write, "%d %.2f %.2f %.2f\n", no, vize, final, butunleme);
        printf("Not kaydedildi.\n");
    }

    fclose(f_write);

    if (kayit_bulundu) {
        remove(dosya_yolu);
        rename(temp_dosya_yolu, dosya_yolu);
        if(guncellendi) {
            printf("Not guncellendi.\n");
        } else {
            printf("Islem iptal edildi, mevcut notlar korundu.\n");
        }
    } else {
        remove(dosya_yolu); // eski dosyayı sil
        rename(temp_dosya_yolu, dosya_yolu); // yeni oluşturulanı yeniden adlandır
    }
}


void harf_notlari_hesapla(Sistem *sistem) {
    if(sistem->ders_sayisi == 0) {
        printf("Ders yok!\n");
        return;
    }

    printf("\n=== DERSLER ===\n");
    int i;
    for(i = 0; i < sistem->ders_sayisi; i++) {
        printf("%d. %s - %s\n", i+1, sistem->dersler[i].kod, sistem->dersler[i].ad);
    }

    int ders_secim;
    printf("Ders secin: ");
    scanf("%d", &ders_secim);

    if(ders_secim < 1 || ders_secim > sistem->ders_sayisi) return;

    FILE *f = fopen(sistem->dersler[ders_secim-1].dosya_yolu, "r");
    if(!f) {
        printf("Not dosyasi yok!\n");
        return;
    }

    printf("\n%s - Harf Notlari:\n", sistem->dersler[ders_secim-1].ad);

    char satir[200];
    while(fgets(satir, sizeof(satir), f)) {
        if(satir[0] == '#') continue;

        int no;
        float vize, final, but;
        if(sscanf(satir, "%d %f %f %f", &no, &vize, &final, &but) >= 3) {
            float genel = vize * 0.4 + final * 0.6;
            if(but > 0 && but > final) genel = vize * 0.4 + but * 0.6;

            char harf[3];
            if(genel >= 85) strcpy(harf, "AA");
            else if(genel >= 75) strcpy(harf, "BA");
            else if(genel >= 65) strcpy(harf, "BB");
            else if(genel >= 55) strcpy(harf, "CB");
            else if(genel >= 45) strcpy(harf, "CC");
            else strcpy(harf, "FF");

            printf("No: %d, Genel: %.2f, Harf: %s\n", no, genel, harf);
        }
    }
    fclose(f);
}

/* ===================== SEMIH.C ===================== */
void ders_menu(Sistem *sistem) {
    int secim;
    printf("\n=== DERS ISLEMLERI ===\n");
    printf("1. Ders Ekle\n");
    printf("2. Dersleri Listele\n");
    printf("3. Ana Menu\n");
    printf("Secim: ");
    scanf("%d", &secim);

    switch(secim) {
        case 1: ders_ekle(sistem); break;
        case 2: dersleri_listele(sistem); break;
        case 3: break;
    }
}

void dersleri_listele(Sistem *sistem) {
    if(sistem->ders_sayisi == 0) {
        printf("Ders yok.\n");
        return;
    }
    printf("\n=== DERS LISTESI ===\n");
    int i;
    for(i = 0; i < sistem->ders_sayisi; i++) {
        printf("%s - %s (%s)\n", sistem->dersler[i].kod, sistem->dersler[i].ad, sistem->dersler[i].hesapYontemi);
    }
}

void ders_dosyasi_oku(Sistem *sistem) {
    FILE *f = fopen(sistem->ders_dosya_yolu, "r");
    if(f) {
        char satir[300];
        while(fgets(satir, sizeof(satir), f)) {
            Ders *temp = realloc(sistem->dersler, (sistem->ders_sayisi + 1) * sizeof(Ders));
            if(temp) {
                sistem->dersler = temp;
                if(sscanf(satir, "%99[^,],%99[^,],%99[^,],%99s",
                    sistem->dersler[sistem->ders_sayisi].kod,
                    sistem->dersler[sistem->ders_sayisi].ad,
                    sistem->dersler[sistem->ders_sayisi].dosya_yolu,
                    sistem->dersler[sistem->ders_sayisi].hesapYontemi) >= 2) {
                    sistem->ders_sayisi++;
                }
            }
        }
        fclose(f);
    }
}

void ders_dosyasi_yaz(Sistem *sistem) {
    FILE *f = fopen(sistem->ders_dosya_yolu, "w");
    if(f) {
        int i;
        for(i = 0; i < sistem->ders_sayisi; i++) {
            fprintf(f, "%s,%s,%s,%s\n",
                sistem->dersler[i].kod,
                sistem->dersler[i].ad,
                sistem->dersler[i].dosya_yolu,
                sistem->dersler[i].hesapYontemi);
        }
        fclose(f);
    }
}

void ders_ekle(Sistem *sistem) {
    Ders *temp = realloc(sistem->dersler, (sistem->ders_sayisi + 1) * sizeof(Ders));
    if(!temp) return;
    sistem->dersler = temp;

    printf("Ders kodu: ");
    scanf("%99s", sistem->dersler[sistem->ders_sayisi].kod);

    printf("Ders adi: ");
    getchar();
    fgets(sistem->dersler[sistem->ders_sayisi].ad, MAX_STRING, stdin);
    sistem->dersler[sistem->ders_sayisi].ad[strcspn(sistem->dersler[sistem->ders_sayisi].ad, "\n")] = 0;

    printf("Hesaplama yontemi (bagil/can): ");
    scanf("%99s", sistem->dersler[sistem->ders_sayisi].hesapYontemi);

    sprintf(sistem->dersler[sistem->ders_sayisi].dosya_yolu, "%s_notlar.txt", sistem->dersler[sistem->ders_sayisi].kod);

    FILE *f = fopen(sistem->dersler[sistem->ders_sayisi].dosya_yolu, "w");
    if(f) {
        fprintf(f, "# %s dersi notlari\n", sistem->dersler[sistem->ders_sayisi].ad);
        fclose(f);
    }

    sistem->ders_sayisi++;
    ders_dosyasi_yaz(sistem);
    printf("Ders eklendi.\n");
}

void dosyalari_kaydet(Sistem *sistem) {
    ders_dosyasi_yaz(sistem);
    ogrenci_dosyasi_yaz(sistem);
    printf("Veriler kaydedildi.\n");
}
/* ===================== MAIN.C ===================== */

void ayarlar_oku(Sistem *sistem) {
    FILE *f = fopen("ayarlar.conf", "r");
    if(f) {
        char satir[200];
        while(fgets(satir, sizeof(satir), f)) {
            if(strstr(satir, "ogrenci_dosyasi="))
                sscanf(satir, "ogrenci_dosyasi=%s", sistem->ogrenci_dosya_yolu);
            else if(strstr(satir, "ders_dosyasi="))
                sscanf(satir, "ders_dosyasi=%s", sistem->ders_dosya_yolu);
        }
        fclose(f);
    } else {
        strcpy(sistem->ogrenci_dosya_yolu, "ogrenciler.txt");
        strcpy(sistem->ders_dosya_yolu, "dersler.txt");
    }
}

int main() {
    Sistem sistem = {0};

    ayarlar_oku(&sistem);
    ogrenci_dosyasi_oku(&sistem);
    ders_dosyasi_oku(&sistem);

    int secim;
    do {
        printf("\n1.Ders\n2.Ogrenci\n3.Not\n4.Rapor\n5.Cikis\n");
        printf("Secim: ");
        scanf("%d", &secim);

        switch(secim) {
            case 1:
                ders_menu(&sistem);
                break;
            case 2:
                ogrenci_menu(&sistem);
                break;
            case 3:
                not_menu(&sistem);
                break;
            case 4:
                rapor_menu(&sistem);
                break;
            case 5:
                dosyalari_kaydet(&sistem);
                break;
            default:
                printf("Gecersiz secim! (1-5 arasi)\n");
        }
    } while(secim != 5);

    free(sistem.ogrenciler);
    free(sistem.dersler);
    return 0;
}

