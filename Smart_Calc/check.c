#include "s21_smartCalc.h"
double Calculator(char *input, double X);

double Calculator(char *input, double X) {
  if (input[0] == '\0') {
    return -1;
  }
  int x = 0;
  int syntax = SyntaxError(input, &x);
  if (syntax) {
    return -1;
  }
  double val = 0.0;
  if (x) val = X;
  char output[MAXSTRLEN * 2] = {' '};
  int length = ConvertToRPN(input, output);
  double ans = Calculate(output, length, val);
  if (ans != ans) {
    return -2;
  }
  return ans;
}
