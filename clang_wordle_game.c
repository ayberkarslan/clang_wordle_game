#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char inputWord[20];
char words[10][20] = {
    "ROKET", "YILDIZ", "TAKIM", "LINUX", "KONTROL", "AVIYONIK", "NEVSEHIR", "OTOMASYON", "MOTOR", "REKABET"
};
char hints[10][50] = {
    "Gokyuzune ulasan guclu arac", // ROKET
    "Gece gokyuzunde parlayan kutle", // YILDIZ
    "Birlikte calisan insan grubu", // TAKIM
    "Acik kaynakli isletim sistemi cekirdegi", // LINUX
    "Sistemleri yonetme ve denetleme isi", // KONTROL
    "Havacilik ve uzay elektroniginin ismi", // AVIYONIK
    "Peri bacalariyla unlu sehrimiz", // NEVSEHIR
    "Sistemlerin kendi kendine calismasi", // OTOMASYON
    "Enerjiyi harekete donusturen duzenek", // MOTOR
    "En iyisi olmak icin yapilan yaris" // REKABET
};


char wrongButExist[20];
char nonExist[20];
char currentWord[20];

int length;
int wordNum;
int wIdx, nIdx;
int totalTries = 0; // oyun sonunda kaç deneme ile tüm kelimeler bilindi


void printWord(int wordNum) {
    length = strlen(words[wordNum]);
    printf("Kelime için ipuclari:\n");
    printf("Toplam %d harfli bir kelime\n", length);
    printf("%s\n", hints[wordNum]);
}

void checkWord(int wordNum) {
    if (strcmp(inputWord, words[wordNum]) == 0) {
    } else {
        for (int i = 0; i < length; i++) {
            if (inputWord[i] == words[wordNum][i]) {
                currentWord[i] = inputWord[i];
            } else {
                if (strchr(words[wordNum], inputWord[i]) != NULL) {
                    //yeri yanlış olanlar
                    // Yanlış yerdeki harf için:
                    if (strchr(wrongButExist, inputWord[i]) == NULL) {
                        // Eğer listede yoksa
                        wrongButExist[wIdx++] = inputWord[i];
                    }
                } else {
                    // hiç olmayanlar
                    // Olmayan harf için:
                    if (strchr(nonExist, inputWord[i]) == NULL) {
                        // Eğer listede yoksa
                        nonExist[nIdx++] = inputWord[i];
                    }
                }
            }
        }
    }
}


void printStatus(int j) {
    printf("\n----------------------- ");
    printf("\n\033[0;33mYerleri Yanlis Olanlar: ");
    for (int i = 0; i < wIdx; i++) {
        printf("%c,", wrongButExist[i]);
    }

    printf("\n\033[0;31mOlmayan harfler: ");
    for (int i = 0; i < nIdx; i++) {
        printf("%c,", nonExist[i]);
    }
    printf("\n\033[0;32mKelimenin son hali: ");
    for (int i = 0; i < length; i++) {
        printf("%c ", currentWord[i]); // Her harften sonra bir boşluk bırakır
    }
    printf("\n----------------------- \033[0m");
    printf("\n");
}


int main(void) {
    printf("====================================================\n");
    printf("\t\t           --Wordle Game--\n");
    printf("====================================================\n");
    printf("Not:Türkce karakterler (İ,ı,ş,ç gibi) ve küçük harfler kullanmayınız.\n");


    wIdx = 0, nIdx = 0; // bunları kelime değişmeden önce bir kere sıfırlayacağız.

    for (int n = 0; n < 10; n++) {
        length = strlen(words[n]);
        int tryCount = 0; //kelimeyi bilince istatistik paneli eklemek için, her kelimede sıfırlansın
        for (int i = 0; i < length; i++) currentWord[i] = '_';
        //başta "_ _ _ _ _" şeklinde kelime çıktısını verelim, zamanla dolsun.
        currentWord[length] = '\0'; // string sonu işareti


        // listeleri ve sayaçları sıfırladık
        wIdx = 0;
        nIdx = 0;
        memset(wrongButExist, 0, sizeof(wrongButExist));
        memset(nonExist, 0, sizeof(nonExist));

        while (1) {
            tryCount++;
            printWord(n);
            printf("\n\t\t>>> ");
            scanf("%s", inputWord);
            checkWord(n);


            if (strcmp(inputWord, words[n]) == 0) {
                // eğer kelime doğruysa status basmayıp direkt döngüden çıktık
                totalTries += tryCount; //bu kelime için denemeleri toplam denemelere ekleyelim
                system("clear"); //ekran temiz dursun diye
                printf("\n\033[0;32mCevabiniz dogru! %s kelimesini %d denemede bildiniz.\n\033[0m\n", words[n],
                       tryCount);
                printf("Bir sonraki kelimeye geciyoruz...\n-----------------------------\n");
                break;
            }
            system("clear");
            printf("====================================================\n");
            printf("\t\t           --Wordle Game--\n");
            printf("====================================================\n");
            printf("Not:Türkce karakterler (İ,ı,ş,ç gibi) ve küçük harfler kullanmayınız.\n");
            printStatus(n);

            if (strcmp(inputWord, words[n]) == 0) break; // kelime bilindiğinde sonraki kelimeye geçişi yapıyoruz
        }
    }


    // oyun sonuna karizmatik bir istatistik paneli
    system("clear");
    printf("\033[1;35m");
    printf("====================================================\n");
    printf("            OYUN BITTI - TEBRIKLER!                 \n");
    printf("====================================================\n");
    printf(" Toplam Kelime Sayisi  : 10                         \n");
    printf(" Toplam Tahmin Sayisi  : %d                         \n", totalTries);
    float success = (10.0 / totalTries) * 100;
    //başarı oranı da hesapladık yüzde olarak - 10.0 yazdık çünkü tam sayı/tam sayı olursa gcc derleyicisi virgulden sonrasını atar
    printf(" Basari yuzdeniz       : %.1f                         \n", success);
    // %% kullanarak yüzdeyi, .1f ile küsuratı ayarladık
    printf("====================================================\n");
    printf("\033[0m\n");

    return 0;
}

