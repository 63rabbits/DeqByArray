#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include "DeqByArray.h"

//////////////////////////////////////////////////
void test(void);
Element_t *createElement(int value);
bool destroyElement(Element_t *element);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    
#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    int testCount = 10;
    
    int capacity = 10;
    int numOfValues = 15;
    
    Deq_t *deq = createDeq(capacity);
    
    for (int r=0; r<testCount; r++) {
        printf("*** [Test #%d] ***\n", r+1);
        
        Element_t *element = NULL;
        bool check = false;
        switch (r) {
            case 0:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueDeq(deq, element);
                    if (check) {
                        printf("enqueue : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(deq)) {
                    element = dequeueDeq(deq);
                    printf("dequeue : %10d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 1:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueHeadOnDeq(deq, element);
                    if (check) {
                        printf("enqueue head : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(deq)) {
                    element = dequeueHeadOnDeq(deq);
                    printf("dequeue head : %10d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 2:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueHeadOnDeq(deq, element);
                    if (check) {
                        printf("enqueue head : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(deq)) {
                    element = dequeueTailOnDeq(deq);
                    printf("dequeue tail : %10d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 3:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueTailOnDeq(deq, element);
                    if (check) {
                        printf("enqueue tail : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(deq)) {
                    element = dequeueHeadOnDeq(deq);
                    printf("dequeue head : %10d\n", element->value);
                    destroyElement(element);
                }
                break;
            case 4:
                for (int i=0; i<numOfValues; i++) {
                    element = createElement(i);
                    check = enqueueTailOnDeq(deq, element);
                    if (check) {
                        printf("enqueue tail : %10d\n", element->value);
                    }
                    else {
                        printf("error [%s] : could not enqueue value %d.\n", __func__, element->value);
                        destroyElement(element);
                    }
                }
                printf("\n");
                while (!isEmptyDeq(deq)) {
                    Element_t *element = dequeueTailOnDeq(deq);
                    printf("dequeue tail : %10d\n", element->value);
                    destroyElement(element);
                    
                }
                // *************************************
                r = INT_MAX - 1;        // stop loop.
                // *************************************
                break;
            default:
                break;
        }
    }
    
    destroyDeq(deq, DEQ_OPTION_WITH_ELEMENT);
}

Element_t *createElement(int value) {
    Element_t *e = malloc(sizeof(Element_t));
    if (e == NULL) return NULL;
    e->value = value;
    return e;
}

bool destroyElement(Element_t *element) {
    // Block illegal parameters.
    if (element == NULL) return false;
    free(element);
    return true;
}
