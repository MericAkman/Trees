#include <stdio.h>
#include <stdlib.h>


struct Heap{
    void** arr;
    int index;
    int maxSize;
};

struct Heap* heapCreator(int maxSize){
    struct Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));

    if(heap){
        heap->index=-1;
        heap->maxSize = maxSize;
        heap->arr = calloc(maxSize,sizeof(void*));
            if(heap->arr){
                return heap;
            }
            else{
                free(heap);
            }
    }

    return NULL;
};

void swapVal(void** val1, void** val2){
    void* temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}


void siftUp(struct Heap* heap,int childIndex){
    while(childIndex > 0){
        int parentIndex = (childIndex-1)/2;

        int* childVal = (int*)heap->arr[childIndex];
        int* parentVal = (int*)heap->arr[parentIndex];

        if(*childVal > *parentVal){
            swapVal(&heap->arr[childIndex],&heap->arr[parentIndex]);
            childIndex = parentIndex;
        }
        else{
            break;
        }
    }
}

void InsertHeap(struct Heap* heap,void* val){
    if(heap->maxSize == heap->index+1){
        return;
    }

    heap->arr[++heap->index]=val;

    siftUp(heap,heap->index);
}


void heapDown(struct Heap* heap , int parentIndex){
    while(1){
        int leftIndex = parentIndex*2 +1;
        int rightIndex = parentIndex*2 +2;
        int largestIndex = parentIndex;

        if(heap->index >= leftIndex){
            int* leftVal = (int*)heap->arr[leftIndex];
            int* largestVal = (int*)heap->arr[largestIndex];

            if(*leftVal > *largestVal){
                largestIndex = leftIndex;
            }
        }

        if(heap->index >= rightIndex){
            int* rightVal = (int*)heap->arr[rightIndex];
            int* largestVal = (int*)heap->arr[largestIndex];

            if(*rightVal > *largestVal){
                largestIndex = rightIndex;
            }
        }

        if(parentIndex!=largestIndex){
            swapVal(&heap->arr[largestIndex],&heap->arr[parentIndex]);
            parentIndex = largestIndex;
        }

        else{
            break;
        }
    }
}

int DeleteHeap(struct Heap* heap){
    if(heap->index == -1){
        return 0;
    }

    int dataOut = *(int*)heap->arr[0];

    free(heap->arr[0]);
    heap->arr[0]=heap->arr[heap->index];
    heap->index--;

    if (heap->index >= 0) {
        heapDown(heap, 0);
    }

    return dataOut;
}
