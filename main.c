#include "binTree.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void isiBST(const char *FILENAME, BinTree *KAMUS);
void carisuggestion(BinTree P, char PREFIX[], queue *Q);
int TampilSuggestion(queue Q, char daftar[100][31]);

int main(){
	int pilihan;
	const char *filename = "kamus.txt";
	char prefix[31];
	BinTree kamus;
	queue hasil;
	CreateEmpty(&kamus);
		
	isiBST(filename,&kamus);
	
	do{
		printf("\n1. Mencari Prefix");
		printf("\n2. Mencari Sinonim");
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


void isiBST(const char *FILENAME, BinTree *KAMUS){
	infotype kata[31];
	FILE *f = fopen(FILENAME,"r");
	if (f == NULL) {
        printf("Kamus Tidak di Temukan.\n");
        return;
    }	
    while (fscanf(f, "%s", kata)!= EOF){
    	InsSearch(KAMUS, kata);
	}
}

void carisuggestion(BinTree P, char PREFIX[31], queue *Q) {
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

	

