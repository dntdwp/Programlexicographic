#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "binTree.h"
#include "boolean2.h"

BinTree InsertT(BinTree P, infotype X, infotype S) {

    if (IsEmptyT(P)) {
        return AlokasiTree(X, S);
    } else {
        
        if (Left(P) == Nil) {
            Left(P) = AlokasiTree(X, S);
        } else if (Right(P) == Nil) {
            Right(P) = AlokasiTree(X, S);
        } else {
            // Jika kedua cabang penuh, rekursif masukkan ke kiri
            Left(P) = InsertT(Left(P), X, S);
        }
        return P;
    }
}

addressT AlokasiTree(infotype X, infotype S){
    addressT P = (addressT)malloc(sizeof(ElmtNode));
    if (P != Nil) {
        strcpy(Info(P), X);
        strcpy(Sinonim(P), S);
        Left(P) = Nil;
        Right(P) = Nil;
        Count(P) = 0;
    }
    return P;
}

boolean IsEmptyT(BinTree P){
    return (P == Nil);
}

void CreateEmpty(BinTree *P){
    *P = Nil;
}

BinTree GetLeft(BinTree P){
    return Left(P);
}

BinTree GetRight(BinTree P){
    return Right(P);
}

/* ******** KONSTRUKTOR ************ */

BinTree Tree(infotype X, infotype S, BinTree L, BinTree R){
    addressT P = AlokasiTree(X, S);
    if (P != Nil) {
        Left(P) = L;
        Right(P) = R;
    }
    return P;
}

void MakeTree(infotype X, infotype S, BinTree L, BinTree R, BinTree *P) {
    *P = Tree(X, S, L, R);
}

void BuildTree(BinTree *P) {
    infotype X;
    infotype S;
    
    printf("Masukkan kata utama (ketik '.' untuk Nil/Kosong): ");
    scanf(" %s", X);
    if (strcmp(X, ".") == 0) {
        *P = Nil;
    } else {
        printf("Masukkan sinonim untuk '%s': ", X);
        scanf(" %s", S);
        *P = AlokasiTree(X, S);
        if (*P != Nil) {
            printf("--- Masuk ke Subpohon KIRI dari '%s' ---\n", X);
            BuildTree(&Left(*P));
            
            printf("--- Masuk ke Subpohon KANAN dari '%s' ---\n", X);
            BuildTree(&Right(*P));
        }
    }
}

/* ********* PREDIKAT PENTING  **************  */

boolean IsUnerLeft(BinTree P) {
    /* Punerleft: hanya mempunyai subpohon kiri */
    return (P != Nil && Left(P) != Nil && Right(P) == Nil);
}

boolean IsUnerRight(BinTree P) {
    /* Punerright: hanya mempunyai subpohon kanan */
    return (P != Nil && Left(P) == Nil && Right(P) != Nil);
}

boolean IsBiner(BinTree P) {
    /* Biner: mempunyai subpohon kiri dan subpohon kanan */
    return (P != Nil && Left(P) != Nil && Right(P) != Nil);
}

/* ************* TRAVERSAL   ************* */

void Preorder(BinTree P) {
    
    if (!IsEmptyT(P)) {
        printf("[%s - %s] ", Info(P), Sinonim(P));   // Proses Akar
        Preorder(Left(P));        // Jelajahi Subpohon Kiri
        Preorder(Right(P));       // Jelajahi Subpohon Kanan
    }
}

void Inorder(BinTree P) {
    if (!IsEmptyT(P)) {
        Inorder(Left(P));         // Jelajahi Subpohon Kiri
        printf("[%s - %s] ", Info(P), Sinonim(P));   // Proses Akar
        Inorder(Right(P));        // Jelajahi Subpohon Kanan
    }
}

void Postorder(BinTree P) {

    if (!IsEmptyT(P)) {
        Postorder(Left(P));        // Jelajahi Subpohon Kiri
        Postorder(Right(P));       // Jelajahi Subpohon Kanan
        printf("[%s - %s] ", Info(P), Sinonim(P));    // Proses Akar
    }
}

void PrintTree(BinTree P, char tab[]) {

    char tempTab[255];

    if (!IsEmptyT(P)) {
        // Cetak identasi saat ini diikuti data dari akar/node
        printf("%s[%s - %s]\n", tab, Info(P), Sinonim(P));

        strcpy(tempTab, tab);
        strcat(tempTab, "---");

        // Rekursif cetak anak kiri dan anak kanan menggunakan tabulasi baru
        PrintTree(Left(P), tempTab);
        PrintTree(Right(P), tempTab);
    }
}

/* ************ SEARCH **************** */

boolean Search(BinTree P, infotype X) {
    /* Mengirimkan true jika ada node dari P yang bernilai X */
    if (IsEmptyT(P)) {
        return FALSE;
    }
    if (strcmp(Info(P), X) == 0) {
        return TRUE;
    }
    // Cari di subpohon kiri ATAU subpohon kanan
    return (Search(Left(P), X) || Search(Right(P), X));
}

/* ************* FUNGSI LAIN *************** */

int NbElmt(BinTree P) {

    if (IsEmptyT(P)) {
        return 0;
    } else {
        // Total elemen = 1 (akar) + elemen di kiri + elemen di kanan
        return 1 + NbElmt(Left(P)) + NbElmt(Right(P));
    }
}

int NbDaun(BinTree P) {
    /* Mengirimkan banyaknya daun */
    if (IsEmptyT(P)) {
        return 0;
    }
    // Jika sebuah node tidak punya anak kiri DAN tidak punya anak kanan, berarti dia daun
    if (Left(P) == Nil && Right(P) == Nil) {
        return 1;
    }
    // Jika bukan daun, terus cari ke bawah (kiri dan kanan)
    return NbDaun(Left(P)) + NbDaun(Right(P));
}

boolean IsSkewLeft(BinTree P) {
    /* Mengirimkan true jika P adalah pohon condong kiri (semua node hanya punya anak kiri) */
    if (IsEmptyT(P)) {
        return TRUE; // Pohon kosong dianggap condong kiri secara default
    }
    if (Right(P) != Nil) {
        return FALSE;
    }
    // Cek rekursif ke bawah sepanjang jalur kiri
    return IsSkewLeft(Left(P));
}

boolean IsSkewRight(BinTree P) {
    /* Mengirimkan true jika P adalah pohon condong kanan (semua node hanya punya anak kanan) */
    if (IsEmptyT(P)) {
        return TRUE; // Pohon kosong dianggap condong kanan secara default
    }
    if (Left(P) != Nil) {
        return FALSE;
    }
    // Cek rekursif ke bawah sepanjang jalur kanan
    return IsSkewRight(Right(P));
}

int Level(BinTree P, infotype X) {

    if (IsEmptyT(P)) {
        return 0;
    }

    if (strcmp(Info(P), X) == 0) {
        return 1;
    }
    
    // Cari di subpohon kiri
    int leftLevel = Level(Left(P), X);
    if (leftLevel != 0) {
        return 1 + leftLevel; // Tambah 1 level setiap kali naik ke parent
    }
    
    // Cari di subpohon kanan
    int rightLevel = Level(Right(P), X);
    if (rightLevel != 0) {
        return 1 + rightLevel; // Tambah 1 level setiap kali naik ke parent
    }
    
    return 0; // Jika tidak ditemukan di manapun
}

/* ********* OPERASI LAIN ********* */

void AddDaunTerkiri(BinTree *P, infotype X, infotype S) {

    if (IsEmptyT(*P)) {
        *P = AlokasiTree(X, S);
    } else {
        AddDaunTerkiri(&Left(*P), X, S);
    }
}

void AddDaun(BinTree *P, infotype X, infotype Y, infotype SY, boolean InputKiri) {

    if (IsEmptyT(*P)) {
        return; // Jika pohon kosong, tidak ada parent X yang bisa dicari
    }

    // Jika ketemu node parent-nya (X)
    if (strcmp(Info(*P), X) == 0) {
        if (InputKiri) {
            if (Left(*P) == Nil) {
                Left(*P) = AlokasiTree(Y, SY);
            } else {
                printf("Gagal: Anak kiri dari %s sudah terisi!\n", X);
            }
        } else {
            if (Right(*P) == Nil) {
                Right(*P) = AlokasiTree(Y, SY);
            } else {
                printf("Gagal: Anak kanan dari %s sudah terisi!\n", X);
            }
        }
        return;
    }

    // Jika belum ketemu, cari ke cabang kiri dan kanan
    AddDaun(&Left(*P), X, Y, SY, InputKiri);
    AddDaun(&Right(*P), X, Y, SY, InputKiri);
}

void DelDaunTerkiri(BinTree *P, infotype X) {

    if (IsEmptyT(*P)) {
        return;
    }

    // Kondisi dasar: Jika ini adalah daun (tidak punya anak sama sekali)
    if (Left(*P) == Nil && Right(*P) == Nil) {
        strcpy(X, Info(*P)); // Ambil infonya sebelum dihapus
        free(*P);      // DeAlokasiTree memori
        *P = Nil;      // Set pointer parent-nya menjadi Nil
        return;
    }

    // Jika cabang kiri masih ada, prioritaskan jalan ke kiri terus
    if (Left(*P) != Nil) {
        DelDaunTerkiri(&Left(*P), X);
    } else {
        // Jika kiri kosong tapi kanan ada, maka daun terkiri berada di jalur kanan
        DelDaunTerkiri(&Right(*P), X);
    }
}

void DelDaun(BinTree *P, infotype X) {
    /* I.S   : P tidak kosong; X adalah salah satu daun */
    /* F.S   : Node X dihapus dari P jika terbukti dia adalah daun */
    if (IsEmptyT(*P)) {
        return;
    }

    // Cek apakah node saat ini mengandung info X DAN dia beneran daun
    if (strcmp(Info(*P), X) == 0) {
        if (Left(*P) == Nil && Right(*P) == Nil) {
            free(*P);
            *P = Nil;
        } else {
            printf("Gagal: %s bukan sebuah simpul daun!\n", X);
        }
        return;
    }

    // Cari ke cabang kiri dan kanan secara rekursif
    DelDaun(&Left(*P), X);
    DelDaun(&Right(*P), X);
}

ListOfNode MakeListDaun(BinTree P) {
    /* Jika P adalah pohon kosong, maka menghasilkan list kosong (Nil) */
    /* Jika P bukan pohon kosong, menghasilkan list yang elemennya adalah semua daun pohon P */
    if (IsEmptyT(P)) {
        return Nil;
    }

    // Jika ketemu daun, buat node list baru dengan cabang kiri dan kanan diset Nil
    if (Left(P) == Nil && Right(P) == Nil) {
        addressT nodeBaru = AlokasiTree(Info(P), Sinonim(P));
        return nodeBaru; 
    }

    // Rekursif cari daun di kiri dan kanan
    ListOfNode leftList = MakeListDaun(Left(P));
    ListOfNode rightList = MakeListDaun(Right(P));

    // Gabungkan list kiri dan list kanan (sambungkan ekor list kiri ke kepala list kanan)
    if (leftList == Nil) {
        return rightList;
    } else {
        addressT temp = leftList;
        while (Right(temp) != Nil) { // Geser sampai ke ujung "list" kiri
            temp = Right(temp);
        }
        Right(temp) = rightList; // Sambungkan ke list kanan
        return leftList;
    }
}

ListOfNode MakeListPreoder(BinTree P) {
    /* Jika P adalah pohon kosong, maka menghasilkan list kosong (Nil) */
    /* Jika P bukan pohon kosong, menghasilkan list yang elemennya adalah semua elemen pohon P */
    /* dengan urutan Preorder (Akar -> Kiri -> Kanan) */
    if (IsEmptyT(P)) {
        return Nil;
    }

    // 1. AlokasiTree untuk Akar saat ini
    addressT akarList = AlokasiTree(Info(P), Sinonim(P));
    
    // 2. Rekursif buat list dari subpohon kiri dan kanan
    ListOfNode leftList = MakeListPreoder(Left(P));
    ListOfNode rightList = MakeListPreoder(Right(P));

    // 3. Sambungkan: Akar -> Kiri -> Kanan
    Right(akarList) = leftList;
    
    // Cari ujung dari list kiri untuk menyambungkan list kanan
    addressT temp = akarList;
    while (Right(temp) != Nil) {
        temp = Right(temp);
    }
    Right(temp) = rightList;

    return akarList;
}

ListOfNode MakeListLevel(BinTree P, int N) {
    /* Jika P adalah pohon kosong, maka menghasilkan list kosong */
    /* Jika P bukan pohon kosong, menghasilkan list yang elemennya adalah semua elemen pohon P yang levelnya N */
    if (IsEmptyT(P) || N < 1) {
        return Nil;
    }

    // Kondisi dasar: Jika sudah mencapai level target (N == 1 karena akar dimulai dari level 1)
    if (N == 1) {
        return AlokasiTree(Info(P), Sinonim(P));
    }

    // Rekursif cari ke level bawahnya (N dikurangi 1)
    ListOfNode leftList = MakeListLevel(Left(P), N - 1);
    ListOfNode rightList = MakeListLevel(Right(P), N - 1);

    // Gabungkan list kiri dan kanan hasil buruan di level N
    if (leftList == Nil) {
        return rightList;
    } else {
        addressT temp = leftList;
        while (Right(temp) != Nil) {
            temp = Right(temp);
        }
        Right(temp) = rightList;
        return leftList;
    }
}

/* *********** MEMBENTUK BALANCE TREE ************* */

BinTree BuildBalanceTree(int n) {
    /* Menghasilkan sebuah balance tree dengan n node, nilai setiap node dibaca */
    if (n <= 0) {
        return Nil;
    } else {
        infotype X;
        infotype S;
        int nL, nR;
        addressT P;

        // 1. Hitung pembagian node agar seimbang
        nL = n / 2;       // Jumlah node untuk subpohon kiri
        nR = n - nL - 1;  // Sisa node untuk subpohon kanan (dikurangi 1 untuk akar)

        // 2. Baca input data dari user untuk node/akar saat ini
        printf("Masukkan kata utama untuk Balance Tree: ");
        scanf(" %s", X);
        printf("Masukkan sinonim untuk '%s': ", X);
        scanf(" %s", S);

        // 3. AlokasiTreekan akar saat ini
        P = AlokasiTree(X, S);
        if (P != Nil) {
            // 4. Bangun subpohon kiri dan kanan secara rekursif sesuai jatah nL dan nR
            Left(P) = BuildBalanceTree(nL);
            Right(P) = BuildBalanceTree(nR);
        }
        
        return P;
    }
}

/* ************** TERHADAP BINARY SEARCH TREE *************** */

boolean BSearch(BinTree P, infotype X) {
    /* Mengirimkan true jika ada node dari P yang bernilai X pada BST */
    if (IsEmptyT(P)) {
        return FALSE;
    }
    if (strcmp(Info(P), X) == 0) {
        return TRUE;
    }
    
    // Memanfaatkan sifat BST untuk mempercepat pencarian (efisien O(log n))
    if (strcmp(X, Info(P)) < 0) {
        return BSearch(Left(P), X);  // Sesuai aturan, nilai kecil pasti di kiri
    } else {
        return BSearch(Right(P), X); // Nilai besar pasti di kanan
    }
}

BinTree InsSearch(BinTree *P, infotype X, infotype S) {
    /* Menghasilkan sebuah pohon Binary Search Tree P dengan tambahan X. */
    /* Belum ada simpul P yang bernilai X. */
    if (IsEmptyT(*P)) {
        *P = AlokasiTree(X, S);
        return *P;
    }
    
    if (strcmp(X, Info(*P)) < 0){
    	InsSearch(&Left(*P), X, S);
	}
	else if (strcmp(X, Info(*P)) > 0){
		InsSearch(&Right(*P), X, S);
	}
    
    return *P; // Jika ternyata X sudah ada (tidak boleh duplikat di BST)
}

void DelBTree(BinTree *P, infotype X) {

    if (IsEmptyT(*P)) {
        return;
    }

    // 1. Cari dulu posisi node X yang mau dihapus
    if (strcmp(X, Info(*P)) < 0) {
        DelBTree(&Left(*P), X);
    } else if (strcmp(X, Info(*P)) > 0) {
        DelBTree(&Right(*P), X);
    } 
    // 2. Jika node X sudah ditemukan (Info(*P) == X)
    else {
        addressT temp;
        
        // Kasus 1: Node adalah daun atau hanya punya 1 anak (anak kanan)
        if (Left(*P) == Nil) {
            temp = *P;
            *P = Right(*P); // Sambungkan langsung ke anak kanannya
            free(temp);
        }
        // Kasus 2: Node hanya punya 1 anak (anak kiri)
        else if (Right(*P) == Nil) {
            temp = *P;
            *P = Left(*P);  // Sambungkan langsung ke anak kirinya
            free(temp);
        }
        // Kasus 3: Node punya 2 anak (Biner murni)
        else {
            // Cari kandidat pengganti dari subpohon kanan yang paling kiri (nilai terkecil di kanan)
            addressT successor = Right(*P);
            while (Left(successor) != Nil) {
                successor = Left(successor);
            }
            
            // Salin nilai successor ke node yang ingin dihapus
            strcpy(Info(*P), Info(successor));
            strcpy(Sinonim(*P), Sinonim(successor));
            
            // Hapus node successor asli yang nilainya baru saja kita salin tadi
            DelBTree(&Right(*P), Info(successor));
        }
    }
}

/*Huffman*/

void CetakKodeHuffman(BinTree root, int jalur[], int kedalaman) {
    if (IsEmptyT(root)) return;

    // Jika belok KIRI, catat '0' di array jalur
    if (Left(root) != Nil) {
        jalur[kedalaman] = 0;
        CetakKodeHuffman(Left(root), jalur, kedalaman + 1);
    }

    // Jika belok KANAN, catat '1' di array jalur
    if (Right(root) != Nil) {
        jalur[kedalaman] = 1;
        CetakKodeHuffman(Right(root), jalur, kedalaman + 1);
    }

    // Jika sampai di DAUN (Leaf), cetak karakter dan kode binernya
    if (Left(root) == Nil && Right(root) == Nil) {
        printf("  Kata '%s' | Frekuensi: %2d | Kode: ", Info(root), Count(root));
        for (int i = 0; i < kedalaman; i++) {
            printf("%d", jalur[i]);
        }
        printf("\n");
    }
}


void isiBST(const char *FILENAME, BinTree *KAMUS){ // ngisi bst pake kamus yang ada
	char line[1024];
	infotype kata;
	infotype sinonim;
	FILE *f = fopen(FILENAME,"r");
	if (f == NULL) {
        printf("Kamus Tidak di Temukan.\n");
        return;
    }
    while (fgets(line, sizeof(line), f) != NULL){
    	// Skip baris kosong
    	if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') continue;

    	// Cari koma pertama sebagai pemisah kata utama dan sinonim
    	char *comma1 = strchr(line, ',');
    	if (comma1 == NULL) continue; // Skip baris tanpa koma

    	// Ambil kata utama: kata pertama saja (sebelum spasi atau koma)
    	char *start = line;
    	while (*start == ' ') start++; // trim spasi depan

    	int i = 0;
    	while (start[i] != '\0' && start[i] != ',' && start[i] != ' '
    	       && start[i] != '\n' && start[i] != '\r' && i < 30) {
    		kata[i] = start[i];
    		i++;
    	}
    	kata[i] = '\0';

    	if (strlen(kata) == 0) continue;

    	// Ambil sinonim: token kedua setelah koma pertama (di-trim)
    	char *afterComma = comma1 + 1;
    	while (*afterComma == ' ') afterComma++; // trim spasi depan

    	i = 0;
    	while (afterComma[i] != '\0' && afterComma[i] != ','
    	       && afterComma[i] != '\n' && afterComma[i] != '\r' && i < 30) {
    		sinonim[i] = afterComma[i];
    		i++;
    	}
    	sinonim[i] = '\0';

    	// Trim spasi belakang dari sinonim
    	int len = strlen(sinonim);
    	while (len > 0 && sinonim[len-1] == ' ') {
    		sinonim[len-1] = '\0';
    		len--;
    	}

    	if (strlen(sinonim) == 0) continue;

    	InsSearch(KAMUS, kata, sinonim);
	}
	fclose(f);
}
