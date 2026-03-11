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

// Выводим строку из вершинки в stdout
// Не используем std::printf() потому что строки не обязательно С - форматные
bool versh_print(versh* versh, FILE* output) {
  if (std::fwrite(versh->string.data, 1, versh->string.capacity, output) != versh->string.capacity) {
    std::perror("failed to write string");
    return false;
  }
  return std::fputc('\n', output) != EOF;
}

// Читаем строку из файла и вставляем в кучу с проверкой сортировки файлов
bool read_file_insert_heap(Heap* heap, versh* node, bool check_sort) {
  DynamicString string;
  if (!string_init(&string, node->string.capacity)) {
    std::fputs("failed to init string", stderr);
    return false;
  }

  if (readLine(&string, node->file)) {
    // Смотрим нужно ли проверять на сортировку
    if (check_sort && string_compare(&string, &node->string) < 0) {
      std::fputs("file not sorted\n", stderr);
      string_free(&string);
      return false;
    }
    std::swap(node->string, string);
    insert_heap(heap, node);
  } else {
    // Если не получилось прочитать файл вполне возможно, что это был и не файл
    // потому что std::fopen() может открыть и директорию и не вернуть nullptr
    if (std::ferror(node->file) != 0) {
      std::perror("error reading file");
      return false;
    }
    // Почистили вершинку, если не получилось прочитать
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
  if (argc < 2) {
    std::perror("provide exactly one file\n");
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
      std::perror("failed to open file");
      is_ok = false;
      goto heap_clean;
    }
    versh node;
    if (!versh_init(&node, file)) {
      std::perror("failed to init versh");
      is_ok = false;
      goto heap_clean;
    }
    if (!read_file_insert_heap(&heap, &node, false)) {
      is_ok = false;
      goto heap_clean;
    }
  }

  while (heap.size > 0) {
    versh min = extract_heap_min(&heap);
    if (!versh_print(&min, stdout)) {
      std::perror("failed to write min string");
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
    std::perror("failed to clean heap\n");
    return EXIT_FAILURE;
  }
error_system:
  return is_ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
