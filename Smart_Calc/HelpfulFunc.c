
#include "s21_smartCalc.h"

void SendToStack(double a, Notation **head) {
  Notation *tmp = calloc(1, sizeof(Notation));
  tmp->next = *head;
  tmp->value = a;
  *head = tmp;
}

void PopNoValue(Notation **head) {
  if (*head) {
    Notation *tmp = *head;
    *head = (*head)->next;
    free(tmp);
  }
}

void Destroy(Notation *head) {
  if (head != NULL) {
    Notation *tmp;
    tmp = head->next;
    free(head);
    Destroy(tmp);
  }
}

void AddOutput(char *output, int value, int *j) {
  output[*j] = value;
  output[*j + 1] = ' ';
  *j = *j + 2;
}

double Pop(Notation **head) {
  double res = 0;
  if (*head) {
    Notation *tmp = *head;
    res = tmp->value;
    *head = (*head)->next;
    free(tmp);
  }
  return res;
}

int SendTrig(int val, int nextVal, Notation **head) {
  int shift = 0;
  switch (val) {
    case 'c':
      SendToStack('c', head);
      shift = 3;
      break;
    case 't':
      SendToStack('t', head);
      shift = 3;
      break;
    case 's':
      if (nextVal == 'i') {
        SendToStack('s', head);  // sin
        shift = 3;
      } else {
        SendToStack('S', head);  // Sqrt
        shift = 4;
      }
      break;
    case 'l':
      if (nextVal == 'o') {
        SendToStack('L', head);  // log
        shift = 3;
      } else {
        SendToStack('l', head);  // ln
        shift = 2;
      }
      break;
    case 'a':
      if (nextVal == 's') {
        SendToStack('A', head);  // asin
      } else if (nextVal == 'c') {
        SendToStack('a', head);  // acos
      } else {
        SendToStack('T', head);  // atan
      }
      shift = 4;
      break;
  }
  return shift - 1;
}

void SendSign(int val, Notation **head, char *output, int *j) {
  if (val == '+' || val == '-') {
    if ((*head != NULL) && (IsSign((*head)->value))) {
      while (*head != NULL && (*head)->value != '(') {
        AddOutput(output, Pop(head), j);
      }
    }
  } else if (val == '*' || val == '/' || val == '%') {
    if ((*head != NULL) && ((*head)->value == '*' || (*head)->value == '/' ||
                            (*head)->value == '^' || (*head)->value == '%')) {
      AddOutput(output, Pop(head), j);
    }
  } else {
    if ((*head != NULL) && ((*head)->value == '^')) {
      AddOutput(output, Pop(head), j);
    }
  }
  SendToStack(val, head);
}

void SendBracket(int val, Notation **head, char *output, int *j) {
  if (val == '(') {
    SendToStack(val, head);
  } else if (val == ')') {
    if ((*head != NULL) && (IsSign((*head)->value) || (*head)->value == 'u')) {
      while ((*head)->value != '(') {
        AddOutput(output, Pop(head), j);
      }
    }
    if ((*head != NULL) && ((*head)->value == '(')) {
      if (((*head)->next != NULL) && IsTrig((*head)->next->value)) {
        PopNoValue(head);
        AddOutput(output, (*head)->value, j);
      }
    }
    PopNoValue(head);  //  deleting '(' bracket
  }
}

void AddDidigit(char *input, char *output, int *i, int *j, Notation **head) {
  for (; isdigit(input[*i]) || input[*i] == '.';
       output[*j] = input[*i], *i += 1, *j += 1) {
  }
  output[*j] = ' ';
  *j += 1;
  while (*head && (*head)->value == 'u' && !(input[*i] == '^')) {
    AddOutput(output, Pop(head), j);
  }
}

double SignCase(int sign, Notation **signStack, double one, double two) {
  double ans = one;
  if (sign == 'u') {
    ans *= -1;
  } else {
    switch (sign) {
      case '+':
        ans += two;
        break;
      case '-':
        ans = two - one;
        break;
      case '/':
        if (one == 0) {
          Destroy(*signStack);
          return NAN;
        } else {
          ans = two / one;
        }
        break;
      case '*':
        ans *= two;
        break;
      case '%':
        ans = fmod(two, one);
        break;
      case '^':
        ans = pow(two, one);
        break;
    }
    PopNoValue(signStack);
  }
  return ans;
}

double TrigCase(int sign, double one) {
  double ans = 0;
  switch (sign) {
    case 'c':
      ans = cos(one);
      break;
    case 't':
      ans = tan(one);
      break;
    case 's':
      ans = sin(one);
      break;
    case 'S':
      ans = sqrt(one);
      break;
    case 'l':
      ans = log(one);
      break;
    case 'L':
      ans = log10(one);
      break;
    case 'T':
      ans = atan(one);
      break;
    case 'A':
      ans = asin(one);
      break;
    case 'a':
      ans = acos(one);
      break;
  }
  return ans;
}

double GetDigit(char *output, int *i) {
  double ans = output[*i] - '0';
  int flag = 0;
  *i += 1;
  while (isdigit(output[*i]) || output[*i] == '.') {
    if (flag) flag++;
    if (output[*i] == '.') {
      flag = 1;
    } else {
      ans *= 10;
      ans += output[*i] - '0';
    }
    *i += 1;
  }
  if (flag) ans /= pow(10, flag - 1);
  return ans;
}
