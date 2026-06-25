#include "binTree.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void carisuggestion(BinTree P, char PREFIX[31], queue *Q);
int TampilSuggestion(queue Q, char daftar[100][31]);

int main(){
	int pilihan;
	const char *filename = "Tesaurus-BahasaIndonesia.txt";
	char prefix[31];
	BinTree kamus;
	queue hasil;
	CreateEmpty(&kamus);
		
	isiBST(filename,&kamus);
	
	do{
		printf("\n1. Mencari Prefix");
		printf("\n2. Mencari Sinonim");
		printf("\n3. Cetak Pohon");
		printf("\n0. Keluar\n");
		printf("Masukan Pilihan: ");
		scanf("%d", &pilihan);
		
		if (pilihan == 1){
	    
		}
	    
		
		if (pilihan == 3){
			PrintTree(kamus,"");
		}
		
	}while (pilihan != 0);
	
	return 0;	
}

void carisuggestion(BinTree P, char PREFIX[31], queue *Q) { // buat nyari suggestion yang cocok sama prefix yang diinput
    if (IsEmptyT(P)) {
        return;
    }

    /* kunjungi subtree kiri */
    carisuggestion(Left(P), PREFIX, Q);

    /* cek apakah prefix cocok */
    if (strncmp(Info(P), PREFIX, strlen(PREFIX)) == 0) {
        InsertQ(Q, Info(P));  
    }

    /* jika sudah melewati prefix */
    if (strcmp(Info(P), PREFIX) > 0 &&
        strncmp(Info(P), PREFIX, strlen(PREFIX)) != 0) {
        return;
    }

    /* kunjungi subtree kanan */
    carisuggestion(Right(P), PREFIX, Q);
}

	

