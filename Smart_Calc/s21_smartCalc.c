#include "s21_smartCalc.h"

double Calculate(char* output, int length, double val) {
  int i = 0;
  Notation* signStack = NULL;
  while (i < length) {
    if (isdigit(output[i])) {
      double count = GetDigit(output, &i);
      SendToStack(count, &signStack);
      i++;
      continue;
    } else if (output[i] == 'x') {
      SendToStack(val, &signStack);
      i += 2;
      continue;
    }
    double one = 0, two = 0;
    if (signStack != NULL) one = signStack->value;
    if (IsSign(output[i]) && signStack && signStack->next)
      two = (signStack->next)->value;
    if (IsSign(output[i]) || output[i] == 'u') {
      if (!(one = SignCase(output[i], &signStack, one, two))) {
        Destroy(signStack);
        return NAN;
      }
    } else if (IsTrig(output[i])) {
      one = TrigCase(output[i], one);
    }
    i += 2;
    if (signStack) signStack->value = one;
  }
  double result = -1;
  if (signStack) result = signStack->value;
  Destroy(signStack);
  return result;
}

int ConvertToRPN(char* input, char* output) {
  int i = 0, j = 0;
  Notation* head = NULL;
  for (; input[i] != '\0'; i++) {
    if (isdigit(input[i])) {
      AddDidigit(input, output, &i, &j, &head);
    }
    if (BinSign(input, i)) {
      if (input[i] == '-') {
        SendToStack('u', &head);
      }
    } else if (input[i] == 'x') {
      output[j] = 'x';
      output[j + 1] = ' ';
      j += 2;
    } else if (IsSign(input[i])) {
      SendSign(input[i], &head, output, &j);
    } else if (IsTrig(input[i])) {
      i += SendTrig(input[i], input[i + 1], &head);
    } else {
      SendBracket(input[i], &head, output, &j);
    }
  }
  while (head != NULL) {
    AddOutput(output, Pop(&head), &j);
  }
  j -= 2;
  return j + 1;
}
