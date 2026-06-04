#include "boolean2.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

// Front untuk tempat keluar data (Delete), dan Rear untuk tempat masuk data (Insert).

boolean IsEmptyQ(queue Q) {
    // Antrian dianggap kosong jika Front dan Rear sama-sama menunjuk ke NULL
    if (Front(Q) == NULL && Rear(Q) == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void Initial(queue *Q) {
    // Inisialisasi awal antrian, pastikan kedua pointer bernilai NULL
    Front(*Q) = NULL;
    Rear(*Q) = NULL;
}

void setFront(queue *Q) {
    // Mengosongkan paksa pointer depan (jika diperlukan oleh logika khusus)
    Front(*Q) = NULL;
}

void setRear(queue *Q) {
    // Mengosongkan paksa pointer belakang
    Rear(*Q) = NULL;
}

addressQ Alokasi(infotype X[31]) {
    // Meminta ruang memori untuk satu node list antrian
    addressQ P = (addressQ)malloc(sizeof(ElmtList));
    if (P != NULL) {
        strcpy (Info(P),X);      // Isi node dengan karakter X
        Next(P) = NULL;   // Pointer next default ke NULL
    }
    return P;
}

void Dealokasi(addressQ *P) {
    // Bebaskan memori
    free(*P);
    // Biasakan mengosongkan pointer setelah free agar tidak menjadi "dangling pointer"
    *P = NULL; 
}

void InsertQ(queue *Q, infotype data[31]) {
    // 1. Buat node baru untuk data yang akan antre
    addressQ P = Alokasi(data);
    
    if (P != NULL) { // Pastikan memori tersedia
        if (IsEmptyQ(*Q) == TRUE) {
            // KASUS 1: Antrian Kosong. 
            // Orang pertama yang antre akan menjadi Front sekaligus Rear.
            Front(*Q) = P;
            Rear(*Q) = P;
        } else {
            // KASUS 2: Antrian sudah ada isinya.
            // Sambungkan orang paling belakang (Rear) saat ini ke orang yang baru masuk (P)
            Next(Rear(*Q)) = P;
            // Pindahkan label Rear ke orang yang paling baru tersebut
            Rear(*Q) = P;
        }
    } else {
        printf("Alokasi memori gagal.\n");
    }
}

void Delete(queue *Q, infotype *data[31]) {
    addressQ P; // Variabel sementara untuk memegang node yang akan dihapus
    
    if (IsEmptyQ(*Q) == FALSE) {
        // 1. Pegang elemen paling depan
        P = Front(*Q);
        
        // 2. Salin nilainya untuk dikembalikan ke pemanggil fungsi
        strcpy(data, Info(P));
        
        // 3. Geser antrian depan ke orang di belakangnya
        Front(*Q) = Next(Front(*Q));
        
        // PENTING: Jika setelah digeser ternyata antriannya habis (Front jadi NULL),
        // maka penunjuk belakang (Rear) juga harus dikembalikan ke NULL
        if (Front(*Q) == NULL) {
            Rear(*Q) = NULL;
        }
        
        // 4. Hancurkan node orang yang sudah keluar antrian
        Dealokasi(&P);
    } else {
        printf("Queue Kosong, tidak bisa Delete.\n");
    }
}

void PrintQueue(queue Q) {
    // Penelusuran selalu dimulai dari antrian terdepan (Front)
    addressQ P = Front(Q); 
    
    if (IsEmptyQ(Q) == TRUE) {
        printf("Queue Kosong\n");
    } else {
        printf("[ ");
        while (P != NULL) {
            // Cetak data. Karena infotype di queue.h adalah 'char', gunakan %c
            printf("%s ", Info(P)); 
            P = Next(P);
        }
        printf("]\n");
    }
}
