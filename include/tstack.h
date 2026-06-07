// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_
#include <string>

template<typename T, int size>
class TStack {
 private:
  T data[size]; // NOLINT
  int top;
 public:
  TStack() : top(-1) {}
  void push(T value) {
    if (top < size - 1) {
      data[++top] = value;
    }
  }
  T pop() {
    if (top < 0) throw std::string("Stack is empty");
    return data[top--];
  }
  T get() const {
    if (top < 0) throw std::string("Stack is empty");
    return data[top];
  }
  bool isEmpty() const {
    return top == -1;
  }
};
#endif  // INCLUDE_TSTACK_H_
