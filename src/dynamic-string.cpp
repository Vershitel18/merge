#include "dynamic-string.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>

bool string_init(DynamicString* string, std::size_t capacity) {
  void* ptr = std::malloc(capacity);
  if (ptr == nullptr) {
    string->data = nullptr;
    return false;
  }
  string->data = static_cast<char*>(ptr);
  string->size = 0;
  string->capasity = capacity;
  return true;
}

void string_free(DynamicString* string) {
  std::free(string->data);
}

bool string_push_back(DynamicString* string, char ch) {
  if (string->size >= string->capasity) {
    size_t new_capacity = string->capasity * 2;
    if (new_capacity == 0) {
      new_capacity = 1;
    }
    char* new_buf = static_cast<char*>(std::realloc(string->data, new_capacity));
    if (new_buf == nullptr) {
      return false;
    }
    string->data = new_buf;
    string->capasity = new_capacity;
  }

  string->data[string->size] = ch;
  string->size += 1;
  return true;
}

bool string_clear(DynamicString* string) {
  string->size = 0;
  return true;
}

int string_compare(DynamicString* a, DynamicString* b) {
  // функция побитового сравнения любых! строк
  if (int cmp = std::memcmp(a->data, b->data, std::min(a->size, b->size)); cmp != 0) {
    return cmp;
  }
  if (a->size < b->size) {
    return -1;
  }
  if (a->size > b->size) {
    return 1;
  }
  return 0;
}
