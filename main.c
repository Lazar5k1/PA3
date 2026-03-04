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

 // struct for queue of sorted cats
 typedef struct Queue_s {
    SLLNode* front;
    SLLNode* back;
 } Queue;

 //struct for node of exposed cat
 typedef struct Stack_s {
    Cat *cat;
    Stack *next;
 } Stack;


void createQueue(Queue* qPtr);
void initializeQueue(Queue *qPtr);
Cat* createCat(int arrival, char* name, int duration);
SLLNode* createNode(Cat* cat);
void enqueue(Queue* qPtr, Cat* cat);
void freeCat(Cat* cat);
int empty(Queue* qPtr);
int peek(Queue* qPtr);


int main(){
    Queue queue;
    createQueue(&queue);
    simulateDay(&queue);

    return 0;
}

 // takes input and creates the sorted link list queue
void createQueue(Queue* qPtr){
    int arrival = 0;
    char name[26];
    int duration;

    while(arrival != -1){
        scanf("%d", &arrival);
        
        if(arrival == -1)
            break;
        
        scanf("%s %d", name, &duration);
        Cat* cat = createCat(arrival, name, duration);
        enqueue(qPtr, cat);
    }
}

// initializes queue values to NULL
void initializeQueue(Queue *qPtr){
    qPtr->front = NULL;
    qPtr->back = NULL;
}

// creates and initializes a cat's values based on input (also perfectly sizes string)
Cat* createCat(int arrival, char* name, int duration){
    Cat* cat = (Cat*)malloc(sizeof(Cat));

    cat->arrival = arrival;
    cat->duration = duration;

    cat->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(cat->name, name);

    return cat;
}

 // inserts cat into SLL qeue based on arrival time
void enqueue(Queue* qPtr, Cat* cat){ // should work according to rules but check later anyways
    SLLNode* temp = createNode(cat);

    if(qPtr->front == NULL || qPtr->front->cat->arrival > cat->arrival){
        temp->next = qPtr->front;
        if(qPtr->front == NULL)
            qPtr->back = temp;
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

// 
Cat* dequeue(){

}

// returns front of queue if not empty otherwise returns NULL if empty
Cat* peekQueue(Queue* qPtr){
    if(qPtr->front)
        return qPtr->front;
    else
        return NULL;
}

// returns 1 if front == NULL and 0 if not
int emptyQueue(Queue* qPtr){
    return qPtr->front == NULL;
}

 // creates a cat for SLL
SLLNode* createNode(Cat* cat){
    SLLNode* temp = malloc(sizeof(SLLNode));
    temp->cat = cat;
    temp->next = NULL;
    return temp;
}

 // frees a cat's memory
void freeCat(Cat* cat){
    free(cat->name);
    free(cat);
}

//
void simulateDay(Queue* qPtr){
    int dayTime = 0;
    int unoTime = 0;
    int dosTime = 0;
    Cat* cat = peekQueue(qPtr);
    if(cat != NULL)
        unoTime = cat->arrival;

    cat = peekQueue(qPtr->front->next);
    if(cat != NULL)
        dosTime = cat->arrival;

    Stack *top = (Stack*)malloc(sizeof(Stack));
    top->next = NULL;
    top->cat = NULL;

    while(!emptyQueue(qPtr)){
        cat = dequeue(qPtr);
        if(unoTime <= dosTime && unoTime <= 480){
            unoTime += cat->duration;
            dayTime += unoTime;

            printf("Doctor Uno treated %s at %d\n", cat->name, cat->arrival);
            freeCat(cat);
        }
        else if (dosTime <= 480){
            dosTime += cat->duration;
            dayTime += dosTime;

            printf("Doctor Dos treated %s at %d\n", cat->name, cat->arrival);
            push(&top, cat);
            //free stuff later
        }
        else{
            printf("Cannot accommodate %s\n", cat->name);
            freeCat(cat);
        }
    }
}
// pushes an exposed cat onto the stack
void push(Stack **top, Cat* cat){
    Stack* temp = (Stack*)malloc(sizeof(Stack));
    temp->cat = cat;

    if(temp){
        if(!(*top))
            temp->next = *top;
        *top = temp;
    }
}

// pops an exposed cat off of the stack
void pop(Stack **top){
    if(!(*top))
        return;
    Stack *temp = *top;
    (*top)->next = (*top)->next->next;
    free(temp);
}