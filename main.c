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
    struct Stack_s *next;
 } Stack;

// function prototypes
void createQueue(Queue* qPtr);
void initializeQueue(Queue *qPtr);
Cat* createCat(int arrival, char* name, int duration);
void enqueue(Queue* qPtr, Cat* cat);
void dequeue(Queue *qPtr);
Cat* peekQueue(Queue* qPtr);
int emptyQueue(Queue* qPtr);
SLLNode* createNode(Cat* cat);
void freeCat(Cat* cat);
void simulateDay(Queue* qPtr);
Stack* createStack();
void initializeStack(Stack **top);
void push(Stack **top, Cat* cat);
void pop(Stack **top);
Cat* peekStack(Stack *sPtr);
int emptyStack(Stack *sPtr);


int main(){
    Queue queue;
    createQueue(&queue);
    simulateDay(&queue);

    return 0;
}

 // takes input and creates the sorted link list queue
void createQueue(Queue* qPtr){
    initializeQueue(qPtr);
    int arrival = 0;
    char name[26];
    int duration;

    // stops input when you enter -1
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
void enqueue(Queue* qPtr, Cat* cat){
    SLLNode* temp = createNode(cat);

    // if there is no head or the cat's arrival time is the smallest, put it into the front and update front and back pointers
    if(qPtr->front == NULL || qPtr->front->cat->arrival > cat->arrival){
        temp->next = qPtr->front;
        if(qPtr->front == NULL)
            qPtr->back = temp;
        qPtr->front = temp;
    }
    // searches list to find correct spot where cat belongs
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

// moves front of queue to the next in line and frees old node. If entire line is deleted set both front and back to NULL
void dequeue(Queue *qPtr){
    if(emptyQueue(qPtr))
        return;
    
    SLLNode *temp = qPtr->front;
    qPtr->front = qPtr->front->next;
    if(qPtr->front == NULL)
        qPtr->back = NULL;
    free(temp);
}

// returns front of queue if not empty otherwise returns NULL if empty
Cat* peekQueue(Queue* qPtr){
    if(qPtr->front)
        return qPtr->front->cat;
    else
        return NULL;
}

// returns 1 if front == NULL and 0 if not
int emptyQueue(Queue* qPtr){
    return qPtr->front == NULL;
}

 // creates a node for the sorted queue using input cat
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

// The heart of the program. Takes sorted queue as input and prints out each cat according to arrival time. Also dequeues, frees, pushes, and pops according to pdff instructions
void simulateDay(Queue* qPtr){
    int unoTime = 0;
    int dosTime = 0;
    Cat* cat = peekQueue(qPtr);

    Stack *top = createStack();

    while(!emptyQueue(qPtr)){
        // get front of queue and dequeue
        cat = peekQueue(qPtr);
        dequeue(qPtr);
        // if cat's duration is 0 it's freed and nothing changes
        if(cat->duration == 0){
            freeCat(cat);
            continue;
        }

        // changes start for edge case where uno should be available twice
        int unoStart, dosStart;
        if(unoTime > cat->arrival)
            unoStart = unoTime;
        else
            unoStart = cat->arrival;
        if(dosTime > cat->arrival)
            dosStart = dosTime;
        else
            dosStart = cat->arrival;

        // if both times match choose uno over dos
        // prints output of cat based on time left and frees cat
        if(unoStart <= dosStart){
            int startTime;
            if(unoTime > cat->arrival)
                startTime = unoTime;
            else
                startTime = cat->arrival;
            
            if(startTime + cat->duration <= 480){
                unoTime = startTime + cat->duration;
                printf("Doctor Uno treated %s at %d\n", cat->name, startTime);
                freeCat(cat);
            }
            else{
                printf("Cannot accommodate %s\n", cat->name);
                freeCat(cat);
            }
        }
        // prints output of cat and pushes cat if treated, if not it's freed
        else{
            int startTime;
            if(dosTime > cat->arrival)
                startTime = dosTime;
            else
                startTime = cat->arrival;

            if(startTime + cat->duration <= 480){
                printf("Doctor Dos treated %s at %d\n", cat->name, startTime);
                dosTime = startTime + cat->duration;
                push(&top, cat);
            }
            else{
                printf("Cannot accommodate %s\n", cat->name);
                freeCat(cat);
            }
        }
    }

    if(emptyStack(top))
        printf("No Exposed Cats\n");
    else{
        printf("Exposed Cats\n");
        // pops top of stack, prints cat, and frees cat
        while(!emptyStack(top)){
        cat = peekStack(top);
        pop(&top);
        printf("%s\n", cat->name);
        freeCat(cat);
        }
    }
}

// Creates the first node of the stack (create and initialize are kind of redudnant here but they get the job done for the pdf)
Stack* createStack(){
    Stack* top = NULL;
    initializeStack(&top);
    return top;
}

// initializes top of the stack
void initializeStack(Stack **top){
    *top = NULL;
}

// pushes an exposed cat onto the stack
void push(Stack **top, Cat* cat){
    Stack* temp = (Stack*)malloc(sizeof(Stack));

    if(temp != NULL){
        temp->cat = cat;
        temp->next = *top;
        *top = temp;
    }
}

// pops an exposed cat off of the stack
void pop(Stack **top){
    if(!(*top))
        return;
    Stack *temp = *top;
    (*top) = (*top)->next;
    free(temp);
}

// returns cat on top of the stack
Cat* peekStack(Stack *sPtr){
    if(sPtr)
        return sPtr->cat;
    else
        return NULL;
}

// returns 1 if stack pointer (the top in this program) is NULL
int emptyStack(Stack *sPtr){
    return sPtr == NULL;
}