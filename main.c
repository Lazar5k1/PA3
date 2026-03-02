/*COP 3502C PA3
This program is written by: Nicholas Gill*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 // struct for cat information
typedef struct Cat_s {
 int arrival; // Minutes since clinic opened (Unique)
 char *name; // Unique cat name
 int duration; // Required treatment time in minutes
} Cat;

 // struct for node for sorted link list of each cat
typedef struct SLLNode_s {
 Cat *cat; // Pointer to a cat
 struct SLLNode_s *next;
} SLLNode;

 // struct for queue of sorted cats... (might change later)
 typedef struct Queue_s {
    SLLNode* front;
    SLLNode* back;
 } Queue;


void createSortedQueue(Queue* qPtr);
void createCat(int* arrival, char* name, int* duration);
SLLNode* createNode(Cat* cat);
void insert_sorted(Queue* qPtr, Cat* cat);
void freeCat(Cat* cat);
void initQ(Queue* qPtr);
int empty(Queue* qPtr);
int peek(Queue* qPtr);


int main(){
    Queue queue;
    createSortedQueue(&queue);

    return 0;
}

 // takes input and creates the sorted link list queue
void createSortedQueue(Queue* qPtr){
    initQ(qPtr);
    int arrival = 0;
    char name[26];
    int duration;
    while(arrival != -1){
        scanf("%d", &arrival);
        if(arrival == -1)
            break;
        
        scanf("%s %d", name, &duration);
        createCat(&arrival, name, &duration);
    }
}

void createCat(int* arrival, char* name, int* duration){

}

 // creates a cat for SLL
SLLNode* createNode(Cat* cat){
    SLLNode* temp = malloc(sizeof(SLLNode));
    temp->cat = cat;
    temp->next = NULL;
    return temp;
}

 // inserts cat into SLL qeue based on arrival time
void insert_sorted(Queue* qPtr, Cat* cat){ // should work according to rules but check later anyways
    SLLNode* temp = createNode(cat);

    if(qPtr->front == NULL || qPtr->front->cat->arrival > cat->arrival){
        temp->next = qPtr->front;
        if(qPtr->front == NULL)
            qPtr->back = temp;
        qPtr->front = temp;
        qPtr->front = temp;
    }
    else{
        SLLNode* walker = qPtr->front;

        while(walker->next && walker->next->cat->arrival < cat->arrival)
            walker = walker->next;
        
        if(walker->next == NULL)
            qPtr->back = temp;
        
        temp->next = walker->next;
        walker->next = temp;
    }
}

 // frees a cat's memory
void freeCat(Cat* cat){
    free(cat->name);
    free(cat);
}

 // initializes queue pointers
void initQ(Queue* qPtr){
    qPtr->front = NULL;
    qPtr->back = NULL;
}

 // returns 1 if front == NULL and 0 if not
int empty(Queue* qPtr){
    return qPtr->front == NULL;
}

 // returns 0 if not empty otherwise returns -1 if empty... (needs to be edited later)
int peek(Queue* qPtr){
    if(qPtr->front != NULL)
        return 0;
    else
        return -1;
}
