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

versh extract_heap_min(Heap* heap) {
  versh min = heap->array[0];
  heap->size--;
  if (heap->size > 0) {
    heap->array[0] = heap->array[heap->size];
    sift_down(heap, 0);
  }
  return min;
}

void insert_heap(Heap* heap, versh* node) {
  heap->array[heap->size] = *node;
  heap->size++;
  sift_up(heap, heap->size - 1);
}

bool heap_init(Heap* heap, std::size_t size) {
  heap->size = 0;
  void* ptr = std::malloc(sizeof(*heap->array) * size);
  if (ptr == nullptr) {
    std::free(heap->array);
    return false;
  }
  heap->array = static_cast<versh*>(ptr);
  return true;
}

bool heap_deinit(Heap* heap) {
  for (size_t i = 0; i < heap->size; i++) {
    versh node = extract_heap_min(heap);
    if (!versh_free(&node)) {
      return false;
    }
  }
  std::free(heap->array);
  return true;
}

bool versh_free(versh* versh) {
  string_free(&versh->string);
  if (fclose(versh->file) != 0) {
    std::perror("failed flose file");
    return false;
  }
  return true;
}

bool versh_init(versh* versh, FILE* file) {
  versh->file = file;
  return string_init(&versh->string, 1);
}
