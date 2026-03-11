#include "dynamic-string.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>

bool string_init(DynamicString* string, std::size_t capacity) {
  void* ptr = std::malloc(sizeof(*string->data) * capacity);
  if (ptr == nullptr) {
    string->data = nullptr;
    return false;
  }
  string->data = static_cast<char*>(ptr);
  string->capacity = 0;
  string->size = capacity;
  return true;
}

void string_free(DynamicString* string) {
  std::free(string->data);
}

bool string_push_back(DynamicString* string, char ch) {
  if (string->capacity >= string->size) {
    size_t new_capacity = string->size * 2;
    if (new_capacity == 0) {
      new_capacity = 1;
    }
    char* new_buf = static_cast<char*>(std::realloc(string->data, new_capacity * sizeof(char)));
    if (new_buf == nullptr) {
      return false;
    }
    string->data = new_buf;
    string->size = new_capacity;
  }

  string->data[string->capacity] = ch;
  string->capacity += 1;
  return true;
}

bool string_clear(DynamicString* string) {
  string->capacity = 0;
  return true;
}

int string_compare(DynamicString* a, DynamicString* b) {
  // функция побитового сравнения любых! строк
  if (int cmp = std::memcmp(a->data, b->data, std::min(a->capacity, b->capacity)); cmp != 0) {
    return cmp;
  }
  if (a->capacity < b->capacity) {
    return -1;
  }
  if (a->capacity > b->capacity) {
    return 1;
  }
  return 0;
}
