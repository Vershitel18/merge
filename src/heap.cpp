#include "heap.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>

void sift_up(Heap* heap, size_t index) {
  while (index > 0 && string_compare(&heap->array[index].string, &heap->array[(index - 1) / 2].string) < 0) {
    std::swap(heap->array[index], heap->array[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}

void sift_down(Heap* heap, size_t id) {
  while (2 * id + 1 < heap->size) {
    size_t child = 2 * id + 1;

    if (child + 1 < heap->size && string_compare(&heap->array[child + 1].string, &heap->array[child].string) < 0) {
      child++;
    }
    if (string_compare(&heap->array[child].string, &heap->array[id].string) < 0) {
      std::swap(heap->array[child], heap->array[id]);
      id = child;
    } else {
      break;
    }
  }
}

HeapNode extract_heap_min(Heap* heap) {
  HeapNode min = heap->array[0];
  heap->size--;
  if (heap->size > 0) {
    heap->array[0] = heap->array[heap->size];
    sift_down(heap, 0);
  }
  return min;
}

void insert_heap(Heap* heap, HeapNode* node) {
  heap->array[heap->size] = *node;
  heap->size++;
  sift_up(heap, heap->size - 1);
}

bool heap_init(Heap* heap, std::size_t size) {
  heap->size = 0;
  void* ptr = std::malloc(sizeof(HeapNode) * size);
  if (ptr == nullptr) {
    return false;
  }
  heap->array = static_cast<HeapNode*>(ptr);
  return true;
}

bool heap_deinit(Heap* heap) {
  bool is_ok = true;
  for (size_t i = 0; i < heap->size; i++) {
    HeapNode node = extract_heap_min(heap);
    if (!node_free(&node)) {
      is_ok = false;
    }
  }
  std::free(heap->array);
  return is_ok;
}

bool node_free(HeapNode* node) {
  string_free(&node->string);
  if (fclose(node->file) != 0) {
    std::fprintf(stderr, "filed flose file: %s/n", node->file_name);
    return false;
  }
  node->file_name = nullptr;
  return true;
}

bool node_init(HeapNode* node, FILE* file, char* file_name) {
  node->file_name = file_name;
  node->file = file;
  return string_init(&node->string, 1);
}
