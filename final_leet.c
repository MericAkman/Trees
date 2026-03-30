#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Heap{
    void** arr;
    int index;
    int maxSize;
    int(*compare)(void* arg1,void* arg2);
};

struct Heap* heapCreator(int maxSize,int(*compare)(void* arg1, void*arg2)){
    struct Heap* heap =(struct Heap*)malloc(sizeof(struct Heap));

    if(heap){
        heap->index=-1;
        heap->maxSize=maxSize;
        heap->arr=calloc(maxSize,sizeof(void*));
        heap->compare=compare;
    }
    if(heap->arr){
        return heap;
    }
    return NULL;
};

//------------------------------------------------------

void swapVal(void** a, void** b){
    void* temp = *a;
    *a=*b;
    *b=temp;
}

//------------------------------------------------------

void heapUp(struct Heap* heap,int childIndex){

    while(childIndex > 0){
        int parentIndex = (childIndex-1)/2;

        void* parentVal = heap->arr[parentIndex];
        void* childVal = heap->arr[childIndex];

        if(heap->compare(childVal,parentVal) > 0){
            swapVal(&heap->arr[parentIndex],&heap->arr[childIndex]);
            childIndex=parentIndex;
        }
        else{
            break;
        }
    }
}


void InsertHeap(struct Heap* heap, void* val){

    heap->index++;
    heap->arr[heap->index]=val;

    heapUp(heap,heap->index);
}

//------------------------------------------------------

void heapDown(struct Heap* heap,int parentIndex){

    while(1){

    int leftIndex = 2*parentIndex+1;
    int rightIndex = 2*parentIndex+2;
    int largestIndex = parentIndex;



    if(heap->index >= leftIndex){
        void* leftVal = heap->arr[leftIndex];
        void* largestVal = heap->arr[largestIndex];

        if(heap->compare(leftVal,largestVal) > 0){
            largestIndex=leftIndex;
        }
    }

    if(heap->index >= rightIndex){
        void* rightVal = heap->arr[rightIndex];
        void* largestVal = heap->arr[largestIndex];

        if(heap->compare(rightVal,largestVal) > 0){
            largestIndex=rightIndex;
        }
    }

    if(parentIndex!=largestIndex){
        swapVal(&heap->arr[largestIndex],&heap->arr[parentIndex]);
        parentIndex=largestIndex;
    }
    else{
        break;
    }
}
}


void DeleteHeap(struct Heap* heap){
    if(heap->index < 0){
        return;
    }

    free(heap->arr[0]);
    heap->arr[0]=heap->arr[heap->index];
    heap->index--;

    if(heap->index >= 0){
        heapDown(heap,0);
    }
}










