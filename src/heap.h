
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

void sift_up(Heap* heap, size_t index);

void sift_down(Heap* heap, size_t id);

void insert_heap(Heap* heap, versh* versh);

[[nodiscard]] bool heap_init(Heap* heap, size_t size);

[[nodiscard]] bool heap_deinit(Heap* heap);

[[nodiscard]] versh extract_heap_min(Heap* heap);
