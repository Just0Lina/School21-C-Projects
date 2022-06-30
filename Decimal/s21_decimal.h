#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

typedef enum {
  s21_NORMAL_VALUE = 0,
  s21_INFINITY = 1,
  s21_NEGATIVE_INFINITY = 2,
  s21_NAN = 3,
} value_type_t;

typedef struct {
  unsigned int bits[4];
  value_type_t value_type;
} s21_decimal;

typedef struct {
  unsigned int bits[7];
  value_type_t value_type;
} s21_superdecimal;

// MAIN FUNCTIONS
int s21_is_equal(s21_decimal s1, s21_decimal s2);
int s21_is_not_equal(s21_decimal s1, s21_decimal s2);
int s21_is_less(s21_decimal s1, s21_decimal s2);
int s21_is_greater(s21_decimal s1, s21_decimal s2);
int s21_is_less_or_equal(s21_decimal s1, s21_decimal s2);
int s21_is_greater_or_equal(s21_decimal s1, s21_decimal s2);
s21_decimal s21_add(s21_decimal s1, s21_decimal s2);
s21_decimal s21_sub(s21_decimal s1, s21_decimal s2);
s21_decimal s21_mul(s21_decimal mul1, s21_decimal mul2);
s21_decimal s21_div(s21_decimal s1, s21_decimal s2);
s21_decimal s21_mod(s21_decimal dec1, s21_decimal dec2);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);
s21_decimal s21_truncate(s21_decimal decimal);
s21_decimal s21_floor(s21_decimal decimal);
s21_decimal s21_round(s21_decimal dec);
s21_decimal s21_negate(s21_decimal);

// SUPPORT FUNCTIONS  // AFTER COMPLETION DELETE THEM AND DO CONST IN .c FILE!!!

unsigned getscale(s21_decimal* decimal);
s21_decimal mul10(s21_decimal decimal);
s21_decimal div10(s21_decimal* decimal);
unsigned int getbit(s21_decimal* decimal, int bitn);
void setbit(s21_decimal* decimal, int bitn, unsigned int value);
s21_decimal inversion(s21_decimal decimal);
s21_decimal minisub(s21_decimal decimal, s21_decimal dst);
s21_decimal minisum(s21_decimal s1, s21_decimal s2);
void BitSetValue(s21_decimal* decimal, unsigned value);
void lshift(s21_decimal* decimal, int shift);
void rshift(s21_decimal* decimal, int shift);
// int s21_from_decimal_to_int(s21_decimal src, int* dst);
unsigned binarytouns(s21_decimal* decimal, unsigned bitn, unsigned num);
void norm(s21_decimal* decimal, s21_decimal* dec2);
unsigned is_zero(s21_decimal* decimal);
int GetFirstOne(s21_decimal* sd1);
unsigned FirstDigit(s21_decimal* s1);
unsigned CheckSpecialValue(s21_decimal* s1, float f1);

// SUPER DECIMAL FUNCTIONS // AFTER COMPLETION DELETE THEM AND
// DO CONST IN .c FILE!!!
int sdGetFirstOne(s21_superdecimal* sd1);
void decimal_to_sdecimal(s21_decimal* decimal, s21_superdecimal* sdecimal);
void sdecimal_to_decimal(s21_superdecimal* sdecimal, s21_decimal* decimal);
unsigned int sdgetbit(s21_superdecimal* decimal, int bitn);
void sdsetbit(s21_superdecimal* decimal, int bitn, unsigned int value);
unsigned sdgetscale(s21_superdecimal* decimal);
void sdBitSetValue(s21_superdecimal* decimal, unsigned value);
void sdlshift(s21_superdecimal* decimal, int shift);
void sdrshift(s21_superdecimal* decimal, int shift);
unsigned sdbinarytouns(s21_superdecimal* decimal, unsigned bitn, unsigned num);
s21_superdecimal sdmul10(s21_superdecimal decimal);
s21_superdecimal sdminisum(s21_superdecimal s1, s21_superdecimal s2);
s21_superdecimal sddiv10(s21_superdecimal* decimal);
void sdnorm(s21_superdecimal* decimal, s21_superdecimal* dec2);
s21_superdecimal sdinversion(s21_superdecimal decimal);
s21_superdecimal sdminisub(s21_superdecimal decimal, s21_superdecimal dst);
int sd_is_equal(s21_superdecimal sd1, s21_superdecimal sd2);
unsigned sdFirstDigit(s21_superdecimal* sd1);
int sdFindBiggest(s21_superdecimal* sd1, s21_superdecimal* sd2);
s21_superdecimal sdnormsum(s21_superdecimal s1, s21_superdecimal s2);
s21_superdecimal sdDopCode(s21_superdecimal dec1);
unsigned sdis_zero(s21_superdecimal* decimal);
void Special_Decimal(s21_decimal* s1, unsigned value);

#endif
