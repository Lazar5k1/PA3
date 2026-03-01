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



SLLNode* create_node(Cat* cat);
SLLNode* insert_sorted(Queue* qPtr, SLLNode* head, Cat* cat);
SLLNode* DelList(SLLNode* head, Cat* cat);
void freeCat(Cat* cat);
void initQ(Queue* qPtr);
int empty(Queue* qPtr);
int peek(Queue* qPtr);


int main(){

    return 0;
}


 // creates a cat for SLL
SLLNode* create_node(Cat* cat){
    SLLNode* temp = malloc(sizeof(SLLNode));
    temp->cat = cat;
    temp->next = NULL;
    return temp;
}

 // inserts cat into SLL qeue based on arrival time
SLLNode* insert_sorted(Queue* qPtr, SLLNode* head, Cat* cat){ // should work according to rules but check later anyways
    SLLNode* temp = create_node(cat);

    if(head == NULL || head->cat->arrival > cat->arrival){
        temp->next = head;
        if(head == NULL)
            qPtr->back = temp;
        qPtr->front = temp;
        head = temp;
        return head;
    }
    else{
        SLLNode* walker = head;

        while(walker->next && walker->next->cat->arrival < cat->arrival)
            walker = walker->next;
        
        if(walker->next == NULL)
            qPtr->back = temp;
        
        temp->next = walker->next;
        walker->next = temp;

        return head;
    }
}

 // deletes assigned cat in SLL
SLLNode* DelList(SLLNode* head, Cat* cat){
    if(head==NULL)
        return head;
    
    if(head->cat == cat){
        SLLNode* t = head;

        head = head->next;
        freeCat(t->cat);
        free(t);
        return head;
    }
    else{
        SLLNode* walker = head;

        while(walker->next && walker->next->cat != cat)
            walker = walker->next;

        if(walker->next == NULL)
            return head;

        SLLNode* t = walker->next;
        walker->next = walker->next->next;
        freeCat(t->cat);
        free(t);

        return head;
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
 // rn assumes that cat is already made, sorted and its queue is initialized
int enqueue(Queue* qPtr, SLLNode* temp){
    if(empty(qPtr)){
        qPtr->front = temp;
        qPtr->back = temp;
        return 1;
    }
}