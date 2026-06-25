
#ifndef queue_H
#define queue_H

#include <stdio.h>
#include "boolean2.h"
#define Front(Q) (Q).front
#define Rear(Q) (Q).rear
#define Nil NULL
#define InfoQ(P) (P)->info
#define Next(P) (P)->next
#define First(L) ((L).First)

typedef char infotypeQ[31];
typedef struct tElmtlist *addressQ; // address menjadi type data pointer yang menunjuk type data tElmtlist                //node
typedef struct tElmtlist
{
	infotypeQ info;
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
void Delete(queue *Q, infotypeQ data);
void InsertQ(queue *Q, infotypeQ data);
void PrintQueue(queue Q);
addressQ Alokasi(infotypeQ X);
void Dealokasi(addressQ *P);

#endif
