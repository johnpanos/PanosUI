#pragma once

#include <stdlib.h>

typedef struct _Array *Array;
typedef void* ArrayValue;
typedef int ArrayIndex;
typedef size_t ArrayCapacity;
typedef size_t ArrayValueSize;

Array ArrayCreate(ArrayValueSize valueSize);
void ArrayDestroy(Array array);

ArrayCapacity ArrayGetCapacity(Array array);

void ArrayAddValue(Array array, ArrayValue value);
void ArrayAddValueAtIndex(Array array, ArrayIndex index);

ArrayIndex ArrayGetIndexByRef(Array array, ArrayValue value);

ArrayValue ArrayGetValueAtIndex(Array array, ArrayIndex index);

void ArrayRemoveValueByRef(Array array, ArrayValue item);
void ArrayRemoveValueByIndex(Array array, ArrayIndex index);