#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "DeqByArray.h"

//////////////////////////////////////////////////
Deq_t *createDeq(int capacity) {
    // Block illegal parameters.
    if (capacity <= 0) return NULL;
    
    Deq_t *deq = malloc(sizeof(Deq_t));
    if (deq == NULL) return NULL;
    deq->array = malloc(capacity * sizeof(void*));
    if (deq->array == NULL) {
        free(deq);
        return NULL;
    }
    deq->capacity = capacity;
    deq->head = -1;
    deq->tail = -1;
    
    return deq;
}

bool destroyDeq(Deq_t *Deq, DEQ_OPTION_e option) {
    // Block illegal parameters.
    if (Deq == NULL) return false;
    
    bool result = clearDeq(Deq, option);
    if (!result) {
        return false;
    }
    if (Deq->array != NULL) {
        free(Deq->array);
    }
    free(Deq);
    
    return true;
}

bool clearDeq(Deq_t *Deq, DEQ_OPTION_e option) {
    // Block illegal parameters.
    if (Deq == NULL) return false;
    
    while (!isEmptyDeq(Deq)) {
        Element_t *element = dequeueDeq(Deq);
        if ((option == DEQ_OPTION_WITH_ELEMENT) &&
            (element != NULL)) {
            free(element);
        }
    }
    
    return true;
}

bool enqueueDeq(Deq_t *Deq, Element_t *element) {
    return enqueueTailOnDeq(Deq, element);
}

bool enqueueHeadOnDeq(Deq_t *Deq, Element_t *element) {
    // Block illegal parameters.
    if (Deq == NULL) return false;
    if (element == NULL) return false;
    
    // for 1st enqueue
    if (Deq->head < 0) {
        Deq->array[0] = element;
        Deq->head = 0;
        Deq->tail = 0;
        return true;
    }
    
    int prev = Deq->head - 1;
    if (prev < 0) {
        prev = Deq->capacity - 1;
    }
    
    if (prev != Deq->tail) {
        Deq->array[prev] = element;
        Deq->head = prev;
        return true;
    }
    
    return false;
}

bool enqueueTailOnDeq(Deq_t *Deq, Element_t *element) {
    // Block illegal parameters.
    if (Deq == NULL) return false;
    if (element == NULL) return false;
    
    // for 1st enqueue
    if (Deq->tail < 0) {
        Deq->array[0] = element;
        Deq->head = 0;
        Deq->tail = 0;
        return true;
    }
    
    int next = (Deq->tail + 1) % Deq->capacity;
    if (next != Deq->head) {
        Deq->array[next] = element;
        Deq->tail = next;
        return true;
    }
    
    return false;
}

Element_t *dequeueDeq(Deq_t *Deq) {
    return dequeueHeadOnDeq(Deq);
}

Element_t *dequeueHeadOnDeq(Deq_t *Deq) {
    if (isEmptyDeq(Deq)) return NULL;
    
    Element_t *element = NULL;
    element = Deq->array[Deq->head];
    if (Deq->head == Deq->tail) {   // for dequeue last elemet.
        Deq->head = -1;
        Deq->tail = -1;
        return element;
    }
    Deq->head = (Deq->head + 1) % Deq->capacity;
    
    return element;
}

Element_t *dequeueTailOnDeq(Deq_t *Deq) {
    if (isEmptyDeq(Deq)) return NULL;
    
    Element_t *element = NULL;
    element = Deq->array[Deq->tail];
    if (Deq->tail == Deq->head) {   // for dequeue last elemet.
        Deq->head = -1;
        Deq->tail = -1;
        return element;
    }
    
    Deq->tail--;
    if (Deq->tail < 0) {
        Deq->tail = Deq->capacity - 1;
    }
    
    return element;
}

bool isEmptyDeq(Deq_t *Deq) {
    if (Deq == NULL) return true;
    if (Deq->head < 0) return true;
    return false;
}
