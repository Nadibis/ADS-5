// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}
int getPriority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}
std::string infx2pstfx(const std::string& inf) {
  std::string result;
  TStack<char, 100> opStack;
  for (size_t i = 0; i < inf.length(); ++i) {
    char c = inf[i];
    if (c == ' ') continue;
    if (isdigit(c)) {
      std::string number;
      while (i < inf.length() && isdigit(inf[i])) {
        number += inf[i];
        ++i;
      }
      --i;
      if (!result.empty()) result += ' ';
      result += number;
    } else if (c == '(') {
      opStack.push(c);
    } else if (c == ')') {
      while (!opStack.isEmpty() && opStack.get() != '(') {
        result += ' ';
        result += opStack.pop();
      }
      if (!opStack.isEmpty()) {
        opStack.pop();
      }
    } else if (isOperator(c)) {
      while (!opStack.isEmpty() && opStack.get() != '(' &&
             getPriority(opStack.get()) >= getPriority(c)) {
        result += ' ';
        result += opStack.pop();
      }
      opStack.push(c);
    }
  }
  while (!opStack.isEmpty()) {
    result += ' ';
    result += opStack.pop();
  }
  if (!result.empty() && result[0] == ' ') {
    result.erase(0, 1);
  }
  return result;
}
int eval(const std::string& post) {
  TStack<int, 100> valStack;
  for (size_t i = 0; i < post.length(); ++i) {
    char c = post[i];
    if (c == ' ') continue;
    if (isdigit(c)) {
      int number = 0;
      while (i < post.length() && isdigit(post[i])) {
        number = number * 10 + (post[i] - '0');
        ++i;
      }
      --i;
      valStack.push(number);
    } else if (isOperator(c)) {
      int b = valStack.pop();
      int a = valStack.pop();
      int res;
      switch (c) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
        default: throw std::string("Unknown operator");
      }
      valStack.push(res);
    }
  }
  return valStack.pop();
}
