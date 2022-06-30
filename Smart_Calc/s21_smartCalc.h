#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRLEN 255
#define S21_PI 3.141592653589793
#define STRINGIFY(a) STRINGIFy(a)
#define STRINGIFy(a) #a
#define HERE fprintf(stderr, " HERE %i\n", __LINE__);
#define MAXDOUBLE 255
// sin s
// tan t
// acos a
// asin A
// atan T
// sqrt S
// ln l
// log L
// u - унарный минус

typedef struct Notation Notation;
struct Notation {
  double value;
  Notation* next;
};
//  Main functions
int SyntaxError(char* input, int* X);
double Calculate(char* output, int length, double val);
int ConvertToRPN(char* input, char* output);

// Add functuons
void SendToStack(double a, Notation** head);
void PopNoValue(Notation** head);
double Pop(Notation** head);
void Destroy(Notation* head);

double Calculator(char* input, double X);

// Convert tot RPN
int SendTrig(int val, int nextVal, Notation** head);
void SendSign(int val, Notation** head, char* output, int* j);
void SendBracket(int val, Notation** head, char* output, int* j);
void AddDidigit(char* input, char* output, int* i, int* j, Notation** head);
int BinSign(const char* input, int i);

// Calculate extra fuctions
double CalculateSign(int val, Notation* signStack);
double SignCase(int sign, Notation** signStack, double one, double two);
double TrigCase(int sign, double one);
double GetDigit(char* output, int* i);

// Syntax functions
int IsTrigan(char* input, int i);
int IsDigit(char* input, int i);
int IsBracket(char* input, int i, int* bracket);
int IsSign(int sign);
int IsTrig(int a);
int IsUnaryOp(char* input, int i);
int IsCorrectOperation(int shift, char* input, int i);
void AddOutput(char* output, int value, int* j);