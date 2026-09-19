#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef RESERVATION_MANAGER_H

#define RESERVATION_MANAGER_H
#define MAX_NAME_LEN 50
#define MAX_RESOURCES 10

// --- Data Structures ---

typedef struct Reservation
{
    int reservationId;
    int resourceId;
    char studentName[MAX_NAME_LEN];
    struct Reservation* next;
}
Reservation;

typedef struct WaitNode
{
    int resourceId;
    char studentName[MAX_NAME_LEN];
    struct WaitNode* next;
}
WaitNode;

typedef struct
{
    WaitNode* front;
    WaitNode* rear;
}
WaitQueue;


// --- Global System ---
int resourceCount = 0;
Reservation* activeListHead = NULL;



// --- Functions ---

// Linked List: Active Reservation (One List Only)

void initActiveList(Reservation** head);
void insertActiveReservation (Reservation** head, int resID, int ResourceId, const char* studentName);
int removeActiveReservation(Reservation** head, int resourceId, Reservation* removedOut);
void traverseActiveReservations (Reservation* head);
int findActiveReservationByResource(Reservation* head, int resourceId);

// Queue: Waiting List
void initWaitQueue(WaitQueue* q);
void enqueueWaitList(WaitQueue* q, int resourceId, const char* studentName);
int dequeueWaitlistForResources(WaitQueue* q, int resourceId, char * studentNameOut);
void displayWaitlist(WaitQueue* q);

#endif