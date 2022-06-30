#include "s21_smartCalc.h"

// Обработанные ошибки 7(+3), *3+3, ()
// Надо обработать 2 знака рядом
int SyntaxError(char* input, int* X) {
  int i = 0, bracket = 0, ok = 1, ret = 0;
  while (input[i] != '\0' && ok) {
    int shift = 0;
    if (IsDigit(input, i) || IsBracket(input, i, &bracket) ||
        IsUnaryOp(input, i)) {
      i++;
      continue;
    } else if (input[i] == 'x') {
      if (!i || input[i - 1] == '(' || IsUnaryOp(input, i - 1) ||
          IsSign(input[i - 1]) || input[i - 1] == '^') {
        *X = 1;
        i++;
        continue;
      } else {
        ok = 0;
        break;
      }
    } else if (i > 0 && IsSign(input[i])) {
      if (IsSign(input[i + 1])) {
        ok = 0;
        break;
      }
      shift = 1;
    } else {
      shift = IsTrigan(input, i);
      if (shift) {
        bracket++;
      }
    }
    if (shift) {
      if (input[i] == '/' && input[i + 1] == '0' && input[i + 2] != '.') {
        // printf("division by zero\n");
        ok = 0;
        break;
      }
      if (IsCorrectOperation(shift, input, i)) {
        i += shift;
        continue;
      }
    }
    ok = 0;
    break;
  }
  if (bracket != 0 || !ok) ret = 1;
  return ret;
}

int IsSign(int sign) {
  return (sign == '+' || sign == '-' || sign == '*' || sign == '/' ||
          sign == '%' || sign == '^');
}

int IsBracket(char* input, int i, int* bracket) {
  int ans = 0;
  if (input[i] == '(' && input[i + 1] != ')' &&
      (!i || !IsDigit(input, i - 1))) {
    *bracket += 1;
    ans = 1;
  } else if (input[i] == ')' && *bracket > 0) {
    *bracket -= 1;
    ans = 1;
  }
  return ans;
}

int IsDigit(char* input, int i) {
  int ans = 0;
  if (input[i] <= '9' && input[i] >= '0') {
    ans = 1;
  }
  if (i > 0 && input[i] == '.') {
    if (isdigit(input[i + 1]) && isdigit(input[i - 1])) {
      ans = 1;
    }
  }
  if (i && (input[i - 1] == 'x' || input[i + 1] == 'x')) {
    ans = 0;
  }
  return ans;
}

int IsTrigan(char* input, int i) {
  int shift = 0;
  if (input[i] == 'a') {
    if (!strncmp(&input[i], "acos(", 5) || !strncmp(&input[i], "asin(", 5) ||
        !strncmp(&input[i], "atan(", 5)) {
      shift = 5;
    }
  } else if (input[i] == 's') {
    if (!strncmp(&input[i], "sin(", 4))
      shift = 4;
    else if (!strncmp(&input[i], "sqrt(", 5))
      shift = 5;
  } else if (input[i] == 'l') {
    if (!strncmp(&input[i], "log(", 4))
      shift = 4;
    else if (!strncmp(&input[i], "ln(", 3))
      shift = 3;
  } else if (!strncmp(&input[i], "cos(", 4) || !strncmp(&input[i], "tan(", 4)) {
    shift = 4;
  }
  return shift;
}

int IsTrig(int a) {
  return a == 'c' || a == 't' || a == 's' || a == 'S' || a == 'l' || a == 'L' ||
         a == 'a' || a == 'A' || a == 'T';
}

int IsUnaryOp(char* input, int i) {
  return ((!i || input[i - 1] == '(') && (input[i] == '-' || input[i] == '+') &&
          (IsDigit(input, i + 1) || input[i + 1] == '(' ||
           IsTrigan(input, i + 1) || input[i + 1] == 'x'));
}

int IsCorrectOperation(int shift, char* input, int i) {
  int ans = 0;
  if ((shift == 1 &&
       (isdigit(input[i - 1]) || input[i - 1] == ')' || input[i - 1] == 'x')) ||
      (shift > 1 && (!i || IsSign(input[i - 1]) || input[i - 1] == '('))) {
    if ((isdigit(input[i + shift]) || input[i + shift] == '(' ||
         IsTrigan(input, i + shift) || input[i + shift] == 'x') ||
        (shift > 1 && IsUnaryOp(input, i + shift)))
      ans = 1;
  }
  return ans;
}

int BinSign(const char* input, int i) {
  return ((!i || input[i - 1] == '(') && (input[i] == '-' || input[i] == '+'));
}
