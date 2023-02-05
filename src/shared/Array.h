#pragma once

#include "include/Array.h"

typedef struct _Array {
    void **values;
    ArrayValueSize valueSize;
    ArrayCapacity capacity;
} *Array;