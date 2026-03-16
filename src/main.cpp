#include "dynamic-string.h"
#include "heap.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>

// Читаем строку любого формата
bool readLine(DynamicString* string, FILE* file) {
  string_clear(string);
  int ch;
  bool got_any = false;
  while ((ch = std::fgetc(file)) != EOF) {
    got_any = true;
    if (ch == '\n') {
      break;
    }
    if (ch == '\r') {
      int next = std::fgetc(file);
      if (next != '\n' && next != EOF) {
        std::ungetc(next, file);
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

// Выводим строку из вершинки в stdout
// Не используем std::printf() потому что строки не обязательно С - форматные
bool versh_print(HeapNode* versh, FILE* output) {
  if (std::fwrite(versh->string.data, 1, versh->string.size, output) != versh->string.size) {
    std::perror("failed to write string");
    return false;
  }
  return std::fputc('\n', output) != EOF;
}

// Читаем строку из файла и вставляем в кучу с проверкой сортировки файлов
bool read_file_insert_heap(Heap* heap, HeapNode* node, bool check_sort) {
  DynamicString string;
  if (!string_init(&string, node->string.size)) {
    std::fputs("failed to init string\n", stderr);
    return false;
  }

  if (readLine(&string, node->file)) {
    // Смотрим нужно ли проверять на сортировку
    if (check_sort && string_compare(&string, &node->string) < 0) {
      std::fputs(node->file_name, stderr); std::fputs("file not sorted\n", stderr);
      string_free(&string);
      return false;
    }
    std::swap(node->string, string);
    insert_heap(heap, node);
  } else {
    // Если не получилось прочитать файл вполне возможно, что это был и не файл
    // потому что std::fopen() может открыть и директорию и не вернуть nullptr
    if (std::ferror(node->file) != 0) {
      std::fputs(node->file_name, stderr); std::perror("error reading file");
      return false;
    }
    // Почистили вершинку, если не получилось прочитать
    if (!node_free(node)) {
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
  if (argc < 2) {
    std::fputs("provide exactly one file\n", stderr);
    is_ok = false;
    goto error_system;
  }
  Heap heap;
  if (!heap_init(&heap, argc)) {
    std::perror("failed to initialize heap");
    is_ok = false;
    goto error_system;
  }

  for (size_t i = 1; i < static_cast<size_t>(argc); i++) {
    FILE* file = fopen(argv[i], "rb");
    if (file == nullptr) {
      std::fputs(argv[i], stderr); std::perror("failed to open file:");
      is_ok = false;
      goto heap_clean;
    }
    HeapNode node;
    if (!node_init(&node, file, argv[i])) {
      std::perror("failed to init HeapNode");
      is_ok = false;
      goto heap_clean;
    }
    if (!read_file_insert_heap(&heap, &node, false)) {
      is_ok = false;
      goto heap_clean;
    }
  }

  while (heap.size > 0) {
    HeapNode min = extract_heap_min(&heap);
    if (!versh_print(&min, stdout)) {
      std::fputs("failed to write min string\n", stderr);
      is_ok = false;
      goto heap_clean;
    }
    if (!read_file_insert_heap(&heap, &min, true)) {
      is_ok = false;
      goto heap_clean;
    }
  }

heap_clean:
  if (!heap_deinit(&heap)) {
    std::fputs("failed to clean heap\n", stderr);
    return EXIT_FAILURE;
  }
error_system:
  return is_ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
