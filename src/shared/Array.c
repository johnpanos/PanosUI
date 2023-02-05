#include <stdlib.h>
#include "Array.h"

Array ArrayCreate(ArrayValueSize valueSize)
{
    Array array = malloc(sizeof(struct _Array));

    array->valueSize = valueSize;
    array->values = NULL;
    array->capacity = 0;

    return array;
}

void ArrayDestroy(Array array)
{
    free(array->values);
    free(array);
}

ArrayCapacity ArrayGetCapacity(Array array)
{
    return array->capacity;
}

void ArrayAddValue(Array array, ArrayValue value)
{
    if (array->capacity < 1)
    {
        array->capacity = 1;
        array->values = calloc(array->capacity, array->valueSize);
        array->values[0] = value;
    }
    else
    {
        array->capacity += 1;
        array->values = realloc(array->values, array->capacity * array->valueSize);
        array->values[array->capacity - 1] = value;
    }
}

ArrayValue ArrayGetValueAtIndex(Array array, ArrayIndex index)
{
    return array->values[index];
}

void ArrayRemoveValueByIndex(Array array, ArrayIndex index)
{
    void ***values = &array->values;

    array->capacity -= 1;

    memcpy(&(*values)[index], &(*values)[index + 1], (array->capacity - index) * array->valueSize);

    (*values) = realloc(*values, (array->capacity) * array->valueSize);
}

void ArrayRemoveValueByRef(Array array, ArrayValue value)
{
    int i = -1;
    for (int j = 0; j < array->capacity; j++)
    {
        printf("array %p\n", array->values[j]);
        printf("value %p\n", value);
        if ((array->values)[j] == value)
        {
            i = j;
            break;
        }
    }

    if (i == -1)
    {
        return;
    }

    ArrayRemoveValueByIndex(array, i);
}
