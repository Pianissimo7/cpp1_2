#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

typedef struct AdptArray_ {
    PElement* data;
    int size;
    COPY_FUNC CF;
    DEL_FUNC DF;
    PRINT_FUNC PF;
} *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC CF, DEL_FUNC DF,PRINT_FUNC PF) {
    PAdptArray PAA = (PAdptArray)malloc(sizeof(struct AdptArray_));
    if (PAA == NULL) {
        return FAIL;
    }
    PAA->data = (PElement*)malloc(sizeof(PElement));
    PAA->data[0] = NULL;
    if (PAA->data == NULL) {
        free(PAA);
        return FAIL;
    }
    PAA->size = 0;
    PAA->DF = DF;
    PAA->PF = PF;
    PAA->CF = CF;
    return PAA;
}
void DeleteAdptArray(PAdptArray PAA) {
    for (int i = 0 ; i < PAA->size ; i++) {
        if (PAA->data[i]) {
            PAA->DF(PAA->data[i]);
        }
    }
    free(PAA->data);
    free(PAA);
}
Result SetAdptArrayAt(PAdptArray PAA, int index, PElement PE) {
    if (index < 0) {
        return FAIL;
    }
    if (index >= PAA->size) {
        PAA->data = (PElement*)realloc(PAA->data, (index + 1) * sizeof(PElement));
        if (PAA->data == NULL) {
            return FAIL;
        }
        
        for (int i = PAA->size ; i <= index ; i++) {
            PAA->data[i] = NULL;
        }
        
        PAA->size = index + 1;
    }
    
    if (PAA->data[index] != NULL) {
        PAA->DF(PAA->data[index]);
    }
    PAA->data[index] = PAA->CF(PE);
    return SUCCESS;
}
PElement GetAdptArrayAt(PAdptArray PAA, int index) {
    if (index < 0 || index >= PAA->size) {
        return NULL;
    }
    if(PAA->data[index])
        return PAA->CF(PAA->data[index]);
    return NULL;
}
int GetAdptArraySize(PAdptArray PAA) {
    return PAA->size;
}
void PrintDB(PAdptArray PAA) {
    for (int i = 0 ; i < PAA->size ; i++) {
        if (PAA->data[i]) {
            PAA->PF(PAA->data[i]);
        }
    }
}