

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation_manager.h"

// Linked List Implementation (Onyl One linked list)

void initActiveList(Reservation** head)
{
    *head = NULL;
}

// insert new reservation into linked list
void insertActiveReservation(Reservation** head, int resId, int resourceId, const char* studentName)
{
    Reservation* newNode = (Reservation*)malloc(sizeof(Reservation));
    if(!newNode)
    {
        printf("(Error) Memory failed for active reservation.\n");
        return;
    }

    newNode->reservationId = resId;
    newNode-> resourceId = resourceId;
    strncpy(newNode->studentName, studentName, MAX_NAME_LEN -1);
    newNode-> studentName[MAX_NAME_LEN -1] = '\0';

    // insert at head for O(1) efficiency
    newNode->next = *head;
    *head = newNode;
}

// Removed reservation from active list with matching resource ID

int removeActiveReservation(Reservation** head, int resourcedId, Reservation* removedOut)
{
    Reservation* current = *head;
    Reservation* prev = NULL;

    // Go through the single linked list to find the resource booking
    while (current != NULL && current->resourceId != resourcedId)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return 0; // not found in list
    }

    if (removedOut != NULL)
    {
        removedOut->reservationId = current->reservationId;
        removedOut->resourceId = current->resourceId;
        strcpy(removedOut->studentName, current->studentName);
    }

    // Unlink node from list
    if(prev == NULL)
    {
        *head = current->next;
    } else
    {
        prev->next = current->next;
    }

    free(current);
    return 1;
}
    // traverses and prints all records across all recousrces from single linked list
    void traverseActiveReservations(Reservation* head)
    {
        printf("\n-- Active Reservations ---\n");
        if(head == NULL)
        {
            printf("No active Reservations in the system.\n");
            return;
        }

        Reservation* current = head;
        while (current != NULL)
        {
            printf("Reservation ID: %d  | Resource ID: %d  | Student: %s\n",
                    current->reservationId, current->resourceId, current->studentName);
            current = current->next;
        }
    }

    int findActiveReservationByResource(Reservation* head, int resourceId)
    {
        Reservation* current = head;
        while(current != NULL)
        {
            if (current->resourceId == resourceId)
            return 1;
            current = current->next;
        }
        return 0;
    }

// Waiting List Management

void initWaitQueue(WaitQueue* q)
{
    q->front = NULL;
    q->rear = NULL;
}

// FIFO Queue when student is added
void enqueueWaitList(WaitQueue* q,int resourceId, const char* studentName)
{
   WaitNode* newNode = (WaitNode*) malloc (sizeof(WaitNode));
   if (!newNode)
   {
        printf("(Error) Memory failed for waitlist queue.\n");
        return;
   }

   newNode->resourceId = resourceId;
   strncpy(newNode-studentName, studentName, MAX_NAME_LEN -1);
   newNode->studentName[MAX_NAME_LEN -1] = '\0';
   newNode->next = NULL;

   if (q->rear == NULL)
   {
    q->front = q->rear = newNode;
   } else
   {
    q->rear->next = newNode;
    q->rear = newNode;
   }
}

// Dequeues the first student waiting for a new resource

int dequeueWaitlistForResource(WaitQueue* q, int resourceId, char* studentNameOut)
{
    if (q->front == NULL)
    return 0;

    WaitNode* current = q->front;
    WaitNode* prev = NULL;

    // Scan queue to maintain FIFO order
    while (current != NULL && current->resourceId != resourceId)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return 0; 
    }

    // extract student name

    strcpy(studentNameOut, current->studentName);

    // unlink from queue
    if(prev == NULL)
    {
        q->front = current->next;
    } else
    {
        prev->next = current->next;
    }

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(current);
    return 1;
}

void displayWaitlist(WaitQueue* q)
{
    printf("\n--- Waiting List Queue ---\n");
    if(q->front == NULL)
    {
        printf("Waiting list is empty.\n");
        return;
    }

    WaitNode* current = q->front;
    while (current != NULL)
    {
        printf("Resource ID: %d | Student %s\n", current->resourceId, current->studentName);
        current = current->next;
    }
}


