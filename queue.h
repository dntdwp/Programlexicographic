
#ifndef queue_H
#define queue_H

#include <stdio.h>
#include "boolean2.h"
#define Front(Q) (Q).front
#define Rear(Q) (Q).rear
#define Nil NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)

typedef char infotype;
typedef struct tElmtlist *addressQ; // address menjadi type data pointer yang menunjuk type data tElmtlist                //node
typedef struct tElmtlist
{
	infotype info[31];
	addressQ next;
} ElmtList;

typedef struct
{
	addressQ front;
	addressQ rear;
} queue;

boolean IsEmptyQ(queue Q);
void Initial(queue *Q);
void setFront(queue *Q);
void setRear(queue *Q);
void Delete(queue *Q, infotype *data[31]);
void InsertQ(queue *Q, infotype data[31]);
void PrintQueue(queue Q);
addressQ Alokasi(infotype X[31]);
void Dealokasi(addressQ *P);

#endif
