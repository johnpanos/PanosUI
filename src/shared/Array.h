#pragma once

#include "include/Array.h"

typedef struct _Array
{
	void **values;
	ArrayValueSize valueSize;
	ArrayCapacity capacity;
} *Array;

#define ArrayForEach(item, array)                                                                                      \
	for (int keep = 1, i = 0, size = ArrayGetCapacity(array); keep && i != size; keep = !keep, i++)                    \
		for (item = ArrayGetValueAtIndex(array, i); keep; keep = !keep)