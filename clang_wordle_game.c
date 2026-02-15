#include <stdio.h>
#include <string.h>


char inputWord[20];
char words[10][20] = {
    "ROKET", "YILDIZ", "TAKIM", "LINUX", "KONTROL", "AVIYONIK", "NEVSEHIR", "OTOMASYON", "MOTOR", "REKABET"
};

char wrongButExist[20];
char nonExist[20];
char currentWord[20];

int length;
int wordNum;
int wIdx, nIdx;





void writeWord(int wordNum) {
    length = strlen(words[wordNum]);
    printf("Toplam %d harfli bir kelime: ", length);
    // for (; length>0; length--) {
    //   printf("_ ");
    //   }
}

void checkWord(int wordNum) {



    //önceki tahminden kalan veriler karışmasın diye indexleri ve geçici  dizilerimizi sıfırlıyoruz
    wIdx=0 , nIdx = 0;
    memset(wrongButExist, 0, sizeof(wrongButExist));
    memset(nonExist, 0, sizeof(nonExist));


    if (strcmp(inputWord, words[wordNum]) == 0) {
        printf("Tebrikler! %s kelimesini doğru bildiniz!\n", words[wordNum]);
    }
    else {
        for (int i = 0; i < length; i++) {
            if (inputWord[i] == words[wordNum][i]) {
              //  printf("%c", inputWord[i]); // ya da words[wordNum][i]
                currentWord[i] = inputWord[i];

            }
            else {
                if (strchr(words[wordNum], inputWord[i]) != NULL) { //yeri yanlış olanlar
                    wrongButExist[wIdx++] = inputWord[i];

                }
                else {                                              // hiç olmayanlar
                    nonExist[nIdx++] = inputWord[i];
                }
            }
        }
    }

}



void printStatus(int j) {

    printf("\n Yerleri Yanlış Olanlar:");
    for (int i = 0; i < wIdx; i++) {
        printf("%c,", wrongButExist[i]);
    }

    printf("\nOlmayan harfler:");
    for (int i = 0; i < nIdx; i++) {
        printf("%c,", nonExist[i]);
    }
    printf("\nKelimenin son hali: %s",currentWord);

}





int main(void) {
    printf("wordle game baby\n");


    length = strlen(words[0]);
    for(int i = 0; i < length; i++) currentWord[i] = '_'; //başta "_ _ _ _ _" şeklinde kelime çıktısını verelim, zamanla dolsun.
    currentWord[length] = '\0'; // string sonu işareti

    while (1) {
        printf("\nilk kelime için ipucu: 'uçabilen bir şey' :\n");
        writeWord(0);
        scanf("%s", inputWord);
        checkWord(0);
        printStatus(0);
    }


    printf("Döngüden çıktın.\n");

    return 0;
}

