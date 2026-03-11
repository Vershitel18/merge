#pragma once

#include <cstddef>
#include <cstdio>

struct DynamicString {
  char* data;
  std::size_t capacity;
  std::size_t size;
};

[[nodiscard]] bool string_init(DynamicString* string, std::size_t capacity);
void string_free(DynamicString* string);

[[nodiscard]] bool string_push_back(DynamicString* string, char ch);

bool string_clear(DynamicString* string);

int string_compare(DynamicString* a, DynamicString* b);
