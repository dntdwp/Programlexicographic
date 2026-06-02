#include "bintree.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	int pilihan;
	char prefix[31];
	
	do{
		printf("\n1. Mencari Prefix");
		printf("\n2. Mencari Sinonim");
		printf("\n0. Keluar\n");
		printf("Masukan Pilihan: ");
		scanf("%d", &pilihan);
		
		if (pilihan == 1){
			printf("\nMasukan Prefix yang ingin diinput: ");
			scanf("%s", prefix);
		}
		
	}while (pilihan != 0);
	
	return 0;	
}
