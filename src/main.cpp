#include "dynamic-string.h"
#include "heap.h"
#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>

bool readLine(DynamicString* string, FILE* file) {
  string_clear(string);

  int ch;
  bool got_any = false;

  while ((ch = std::fgetc(file)) != EOF) {
    got_any = true;

    if (ch == '\n') break;

    if (ch == '\r') {
      int next = std::fgetc(file);
      if (next != '\n' && next != EOF) {
        ungetc(next, file);
      }
      break;
    }
    if (!string_push_back(string, static_cast<char>(ch))) {
      std::perror("failed to read line");
      std::exit(EXIT_FAILURE);
    }
  }

  return got_any;
}

bool versh_print(versh* versh, FILE *output) {
  if (std::fwrite(versh->string.data, 1, versh->string.size, output) != versh->string.size) {
    std::perror("failed to write string");
    return false;
  }
  return std::fputc('\n', output) != EOF;
}

bool read_file_insert_heap(Heap* heap, versh* node, bool check_sort) {
  DynamicString string;
  if (!string_init(&string, node->string.size)) {
    std::fputs("failed to init string", stderr);
    return false;
  }

  if (readLine(&string, node->file)) {
    if (check_sort && string_compare(&string, &node->string) < 0) {
      std::fputs("file not sorted\n", stderr);
      string_free(&string);
      return false;
    }
    std::swap(node->string, string);
    insertHeap(heap, node);
  } else {
    if (!versh_free(node)) {
      std::perror("failed to free node");
      string_free(&string);
      return false;
    }
  }
  string_free(&string);
  return true;
}


int main(int argc, char** argv) {
  bool is_ok = true;
  // Блок кода где мы добавляем первые строчки всех файлов в кучу
  // далее мы будем работать с этой кучей, но больше элементов в ней будет всегда <= количеству файлов
  if (argc < 2) {
    std::perror("provide exactly one file\n");
    is_ok = false;
    goto error_system;
  }
  Heap heap;
  if (!heapInit(&heap, argc)) {
    std::perror("failed to initialize heap");
    is_ok = false;
    goto error_system;
  }

  for (size_t i = 1; i < static_cast<size_t>(argc); i++) {

    FILE* file = fopen(argv[i], "rb");
    if (file == nullptr) {
      std::perror("failed to open file");
      is_ok = false;
      goto heap_clean;
    }
    versh node;
    if (!versh_init(&node, file)) {
      std::perror("failed to init file");
      is_ok = false;
      goto heap_clean;
    }
    if (!read_file_insert_heap(&heap, &node, false)) {
      std::perror("failed to init file");
      is_ok = false;
      goto heap_clean;
    }
  }

  while (heap.size > 0) {
    versh min = extractHeapMin(&heap);
    if (!versh_print(&min, stdout)) {
      std::perror("failed to write min string");
      is_ok = false;
      goto heap_clean;
    }
    if (!read_file_insert_heap(&heap, &min, true)) {
      std::perror("failed to init file");
      is_ok = false;
      goto heap_clean;
    }
  }

heap_clean:
  if (!heapDeinit(&heap)) {
    std::fputs("failed to clean heap\n", stderr);
    return EXIT_FAILURE;
  }
error_system:
  return is_ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
