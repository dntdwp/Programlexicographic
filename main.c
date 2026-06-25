#include "binTree.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====== DEKLARASI FUNGSI ======
void carisuggestion(BinTree P, char PREFIX[31], queue *Q);
void CariSinonim(BinTree P, char kata[31]);
void clearBuffer();

// ====== MAIN ======
int main(){
	int pilihan;
	const char *filename = "Tesaurus-BahasaIndonesia.txt";
	BinTree kamus;
	CreateEmpty(&kamus);
	isiBST(filename, &kamus);
	
	do {
		printf("\n=================================\n");
		printf("   KAMUS LEKSIKOGRAFIS (BST)\n");
		printf("=================================\n");
		printf("1. Mencari Prefix (Auto-Suggestion)\n");
		printf("2. Mencari Sinonim\n");
		printf("3. Cetak Pohon\n");
		printf("0. Keluar\n");
		printf("Masukan Pilihan: ");
		
		if (scanf("%d", &pilihan) != 1) {
			clearBuffer();
			printf("Input tidak valid.\n");
			continue;
		}
		clearBuffer();
		
		if (pilihan == 1) {
			// --- AUTO-SUGGESTION ---
			char prefix[31];
			printf("\nMasukkan prefix: ");
			scanf("%s", prefix);
			clearBuffer();
			
			// Cari semua kata yang cocok dengan prefix
			queue hasil;
			Initial(&hasil);
			carisuggestion(kamus, prefix, &hasil);
			
			if (IsEmptyQ(hasil)) {
				printf("Tidak ditemukan kata dengan prefix \"%s\".\n", prefix);
			} else {
				// Tampilkan daftar suggestion bernomor + simpan ke array
				char daftar[100][31];
				int jumlah = 0;
				addressQ cur = Front(hasil);
				
				printf("\n--- Suggestion untuk \"%s\" ---\n", prefix);
				while (cur != NULL && jumlah < 100) {
					strcpy(daftar[jumlah], InfoQ(cur));
					printf("  %d. %s\n", jumlah + 1, daftar[jumlah]);
					cur = Next(cur);
					jumlah++;
				}
				printf("Total: %d kata ditemukan.\n", jumlah);
				
				// Pilih kata untuk melihat sinonim
				int pick;
				printf("\nPilih nomor (1-%d) untuk lihat sinonim, 0 batal: ", jumlah);
				if (scanf("%d", &pick) == 1 && pick >= 1 && pick <= jumlah) {
					CariSinonim(kamus, daftar[pick - 1]);
				}
				clearBuffer();
			}
		}
		
		else if (pilihan == 2) {
			// --- MENCARI SINONIM (untuk rekan) ---
			printf("\n[Fitur ini belum diimplementasi]\n");
		}
		
		else if (pilihan == 3) {
			printf("\n--- Isi Pohon BST ---\n");
			PrintTree(kamus, "");
		}
		
	} while (pilihan != 0);
	
	printf("\nTerima kasih!\n");
	return 0;
}

// ====== IMPLEMENTASI FUNGSI ======

void clearBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void carisuggestion(BinTree P, char PREFIX[31], queue *Q) {
	if (IsEmptyT(P)) return;

	// Inorder traversal: kiri -> proses -> kanan
	carisuggestion(Left(P), PREFIX, Q);

	// Cek apakah kata cocok dengan prefix
	if (strncmp(Info(P), PREFIX, strlen(PREFIX)) == 0) {
		InsertQ(Q, Info(P));
	}

	// Optimasi: stop jika sudah melewati range prefix di BST
	if (strcmp(Info(P), PREFIX) > 0 &&
		strncmp(Info(P), PREFIX, strlen(PREFIX)) != 0) {
		return;
	}

	carisuggestion(Right(P), PREFIX, Q);
}

void CariSinonim(BinTree P, char kata[31]) {
	if (IsEmptyT(P)) {
		printf("Kata \"%s\" tidak ditemukan.\n", kata);
		return;
	}
	int cmp = strcmp(kata, Info(P));
	if (cmp == 0) {
		printf("Kata    : %s\n", Info(P));
		printf("Sinonim : %s\n", Sinonim(P));
	} else if (cmp < 0) {
		CariSinonim(Left(P), kata);
	} else {
		CariSinonim(Right(P), kata);
	}
}
