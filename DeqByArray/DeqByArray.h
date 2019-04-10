#ifndef DeqByArray_h
#define DeqByArray_h

#include <stdbool.h>

//////////////////////////////////////////////////
typedef enum DeqOption {
    DEQ_OPTION_NONE,
    DEQ_OPTION_WITH_ELEMENT
} DEQ_OPTION_e;

typedef struct Element {
    int value;
} Element_t;

typedef struct Deq {
    int capacity;
    int head;
    int tail;
    void **array;
} Deq_t;

//////////////////////////////////////////////////
Deq_t *createDeq(int capacity);
bool destroyDeq(Deq_t *Deq, DEQ_OPTION_e option);
bool clearDeq(Deq_t *Deq, DEQ_OPTION_e option);
bool enqueueDeq(Deq_t *Deq, Element_t *element);
bool enqueueHeadOnDeq(Deq_t *Deq, Element_t *element);
bool enqueueTailOnDeq(Deq_t *Deq, Element_t *element);
Element_t *dequeueDeq(Deq_t *Deq);
Element_t *dequeueHeadOnDeq(Deq_t *Deq);
Element_t *dequeueTailOnDeq(Deq_t *Deq);
bool isEmptyDeq(Deq_t *Deq);

#endif
