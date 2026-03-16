
#include "dynamic-string.h"
#pragma once

struct HeapNode {
  DynamicString string;
  FILE* file;
  char* file_name;
};

[[nodiscard]] bool node_free(HeapNode* node);

[[nodiscard]] bool node_init(HeapNode* node, FILE* file, char* file_name);

struct Heap {
  HeapNode* array;
  size_t size;
};

void sift_up(Heap* heap, size_t index);

void sift_down(Heap* heap, size_t id);

void insert_heap(Heap* heap, HeapNode* versh);

[[nodiscard]] bool heap_init(Heap* heap, size_t size);

[[nodiscard]] bool heap_deinit(Heap* heap);

[[nodiscard]] HeapNode extract_heap_min(Heap* heap);
