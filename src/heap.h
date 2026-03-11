
#include "dynamic-string.h"
#pragma once

struct versh {
  DynamicString string;
  FILE* file;
};

[[nodiscard]] bool versh_free(versh* versh);

[[nodiscard]] bool versh_init(versh* versh, FILE* file);

struct Heap {
  versh* array;
  size_t size;
};

void siftUp(Heap *heap, size_t index);

void siftDown(Heap* heap, size_t id);

void insertHeap(Heap *heap, versh* versh);

[[nodiscard]] bool insertVersh(versh* current, DynamicString* next);

[[nodiscard]] bool heapInit(Heap* heap, size_t size);

[[nodiscard]] bool heapDeinit(Heap* heap);

[[nodiscard]] versh extractHeapMin(Heap *heap);
