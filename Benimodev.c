#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*Hasta takip sistemi
? Hasta no, adý, yaþý ve hastalýk bilgisini tutacak
bir struct oluþtur
? Belli sayýda hasta giriþi yap.
? Dosya içerisinde hasta no’ya göre arama yap.
? Hasta kaydý sil
? Hasta kaydý düzenle.
? Dosyadan hastalarý listele*/

typedef struct 
{
   char hastaIsim[50];
 unsigned  int hastaNo;
 unsigned int hastaYas;
   char hastalik[20];
}KayitSistem;

void hastaEkle(const char* hastaData);
void hastaAra(const char* hastaData);
void hastaListe(const char* hastaData); 
void hastaSil(const char* hastaData);
int main(){
    const char* hastaData = "Hasta_Takip.txt";
    int secim;

    while (1)
    {
        printf("Hasta Takip Sistemi\n");
        printf("1. Hasta Ekle :\n");
        printf("2. Hasta Ara :\n");
        printf("3. Hastalari Goruntule :\n");
        printf("4. Hasta Sil :\n");
        printf("Cikis icin baska herhangi tusa basin!\n");
        printf("Yukaridaki seceneklerden birini secin!\n");
        scanf("%d",&secim);
        getchar(); 

        switch (secim)
        {
        case 1:
            hastaEkle(hastaData);
            break;
        case 2:
            hastaAra(hastaData);
            break;
        case 3:hastaListe(hastaData);
            break;
        case 4:
            hastaSil(hastaData);
            break;
        default:
            exit(0);

            break;
        }
    }      
    
    return 0;
}

void hastaEkle(const char* hastaData){
    FILE* dosya = fopen(hastaData,"a");
    if (dosya == NULL)
    {
      printf("Dosya Olusturma islemi Basarisiz!\n");
      return;
    }

 KayitSistem yeniHasta;

 printf("Hasta ad :");
 scanf("%49s",yeniHasta.hastaIsim);

 printf("Hasta No :");
 scanf("%d",&yeniHasta.hastaNo);

 printf("Hasta Yas :");
 scanf("%d",&yeniHasta.hastaYas);

 printf("Hastalik ? :");
 scanf("%19s",yeniHasta.hastalik);

 fprintf(dosya,"%49s,%d,%d,%19s",yeniHasta.hastaIsim,yeniHasta.hastaNo,yeniHasta.hastaYas,yeniHasta.hastalik);
 fclose(dosya);
 
 printf("\nHasta Kaydi Olusturuldu !\n");
}

void hastaAra(const char* hastaData){
    FILE* dosya = fopen(hastaData,"r");
    if (dosya == NULL)
    {
        printf("Dosya Bulunamadi !\n");
        return;
    }
    
    char aranan[50];
    printf("Aramak Ýstediðiniz Hastanin adini girin :");
    scanf("%[^\n]s",aranan);

    char Satir[100];
    int bulundu = 0;
    while (fgets(Satir, sizeof(Satir), dosya)) {
        if (strstr(Satir, aranan)) {
            printf("Hasta Bulundu: %s", Satir);
            bulundu = 1;
            break;
        }
    }

    if (!bulundu) {
        printf("Aradiginiz Hasta Bulunamadi.\n");
    }

    fclose(dosya);
}

void hastaListe(const char* hastaData){
    FILE* dosya = fopen(hastaData,"r");
    if (dosya == NULL)
    {
        printf("Dosya Bulunamadi !\n");
        return;
    }
   
    char satir[200];
    printf("\nMevcut Hasta Listesi:\n");
    printf("----------------------------------------------------\n");
    printf("%-20s%-10s%-10s%-30s\n", "Isim", "Hasta No", "Yas", "Hastalik");
    printf("----------------------------------------------------\n");

    while (fgets(satir, sizeof(satir), dosya)) {
        char isim[50], hastalik[100];
        int hastaNo, hastaYas;

        sscanf(satir, "%49[^;];%d;%d;%99[^\n]", isim, &hastaNo, &hastaYas, hastalik);

        printf("%-20s%-10d%-10d%-30s\n", isim, hastaNo, hastaYas, hastalik);
    }

    fclose(dosya);
}
void hastaSil(const char* hastaData){
     FILE *dosya = fopen(hastaData, "r");
    if (dosya == NULL) {
        printf("Dosya bulunamadi!\n");
        return;
    }

    FILE *geciciDosya = fopen("temp.txt", "w");
    if (geciciDosya == NULL) {
        printf("Geçici dosya oluþturulamadi!\n");
        fclose(dosya);
        return;
    }

    char aranan[50];
    printf("Silmek istediðiniz hastanin adini girin: ");
    scanf(" %[^\n]s", aranan);

    char satir[100];
    int bulundu = 0;

    while (fgets(satir, sizeof(satir), dosya)) {
        if (strstr(satir, aranan)) {
            printf("Hasta bulundu ve silindi: %s", satir);
            bulundu = 1;
            continue; // Bu satýrý geç, yani geçici dosyaya yazma
        }
        fputs(satir, geciciDosya); // Geçici dosyaya diðer satýrlarý yaz
    }

    fclose(dosya);
    fclose(geciciDosya);

    if (bulundu) {
        remove("Hasta_Takip.txt"); // Eski dosyayý sil
        rename("temp.txt", hastaData); // Geçici dosyayý eski dosya adýyla yeniden adlandýr
    } else {
        printf("Hasta bulunamadi.\n");
        remove("temp.txt"); // Geçici dosyayý sil
    }

}//devam edecek...