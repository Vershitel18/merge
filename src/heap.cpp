#include "heap.h"
#include<algorithm>
#include "dynamic-string.h"
#include<cstdlib>
#include<cstring>

void siftUp(Heap *heap, size_t index) {
  while (index > 0 &&
         string_compare(&heap->array[index].string, &heap->array[(index - 1) / 2].string) < 0) {
    std::swap(heap->array[index], heap->array[(index - 1) / 2]);
    index = (index - 1) / 2;
         }
}

void siftDown(Heap* heap, size_t id) {
  while (2 * id + 1 < heap->size) {
    size_t child = 2 * id + 1;

    // выбрать меньшего из двух детей
    if (child + 1 < heap->size &&
        string_compare(&heap->array[child + 1].string, &heap->array[child].string) < 0) {
      child++;
        }

    // если родитель больше выбранного ребенка, меняем местами
    if (string_compare(&heap->array[child].string, &heap->array[id].string) < 0) {
      std::swap(heap->array[child], heap->array[id]);
      id = child;
    } else {
      break;
    }
  }
}

versh extractHeapMin(Heap *heap) {
  versh min = heap->array[0];
  heap->size--;
  if (heap->size > 0) {
    heap->array[0] = heap->array[heap->size];
    siftDown(heap, 0);
  }
  return min;
}

void insertHeap(Heap* heap, versh* node) {
    heap->array[heap->size] = *node;
    heap->size++;
    siftUp(heap, heap->size - 1);
}

bool heapInit(Heap* heap,  std::size_t size) {
    heap->size = 0;
    void *ptr = std::malloc(sizeof(*heap->array) * size);
    if (ptr == nullptr) {
        std::free(heap->array);
        return false;
    }
    heap->array = static_cast<versh *>(ptr);
    return true;
}

bool heapDeinit(Heap *heap) {
  for (size_t i = 0; i < heap->size; i++) {
    versh node = extractHeapMin(heap);
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