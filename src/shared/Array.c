#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Array ArrayCreate(ArrayValueSize valueSize)
{
	Array array = malloc(sizeof(struct _Array));

	// printf("Making array with size: %ld\n", valueSize);

	array->valueSize = valueSize;
	array->values = NULL;
	array->capacity = 0;

	return array;
}

void ArrayDestroy(Array array)
{
	if (array->values != NULL)
	{
		free(array->values);
	}

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
