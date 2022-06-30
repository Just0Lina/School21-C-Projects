#include "s21_math.h"

#include <stdlib.h>

long double s21_int_pow(long double base, int power) {
  long double result = 1.0L;
  for (int i = 0; i < power; i++) {
    result *= base;
  }
  return result;
}

double s21_truncate(double x) { return x < 0 ? s21_ceil(x) : s21_floor(x); }

long double s21_division_by_factorial(long double div, int base) {
  long double result = div;
  for (long double i = 2.0L; i <= base; i += 1.0L) {
    result /= i;
  }
  return result;
}

int s21_is_integer(double number) {
  int result = 0;
  number = s21_fabs(number);
  if (number - (long int)number == 0.0L) {
    result = 1;
  }
  return result;
}

long int s21_abs(int x) { return x < 0 ? -1 * x : x; }

long double s21_acos(double x) {
  long double result;
  if (x != x || s21_fabs(x) > 1) {
    result = S21_NAN;
  } else {
    result = (S21_PI / 2) - s21_asin(x);
  }
  return result;
}

long double s21_asin(double x) {
  long double result = x;
  if (x == 1 || x == -1) {
    result = x * (S21_PI / 2);
  } else if (s21_fabs(x) > 1 || x != x) {
    result = S21_NAN;
  } else if (s21_fabs(x) > 1 / s21_sqrt(2)) {
    result = (S21_PI / 2) - s21_asin(s21_sqrt(1 - x * x));
    if (x < 0.0L) {
      result *= -1;
    }
  } else {
    long double temp = 1.0L;
    for (int i = 1; s21_fabs(temp) >= S21_EPSILON; i++) {
      temp = s21_int_pow(x, 2 * i + 1);
      for (int j = 1; j < 2 * i; j += 2) {
        temp = temp * j / (j + 1);
      }
      temp /= ((2 * i) + 1);
      result += temp;
    }
  }
  return result;
}

long double s21_atan(double x) {
  long double result;
  if (x == S21_POSITIVE_INF) {
    result = S21_PI / 2;
  } else if (x == S21_NEGATIVE_INF) {
    result = -1 * S21_PI / 2;
  } else if (x != x) {
    result = S21_NAN;
  } else {
    result = s21_asin(x / s21_sqrt(1 + x * x));
  }
  return result;
}

long double s21_ceil(double x) {
  long double result;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_NEGATIVE_INF) {
    result = S21_NEGATIVE_INF;
  } else if (x == S21_POSITIVE_INF) {
    result = S21_POSITIVE_INF;
  } else if (x == 0) {
    result = 0;
  } else if (s21_is_integer(x)) {
    result = (long int)x;
  } else if (x > 0.0) {
    result = (long long int)x + 1;
  } else {
    result = (long long int)x;
  }
  return result;
}

long double s21_cos(double x) {
  long double result;
  if (x != x || x == S21_POSITIVE_INF || x == S21_NEGATIVE_INF) {
    result = S21_NAN;
  } else {
    x = s21_fmod(x, 2 * S21_PI);
    result = 0.0L;
    long double temp = 1.0L;
    for (int i = 0; s21_fabs(temp) >= S21_EPSILON; i++) {
      temp = s21_division_by_factorial(
          s21_int_pow(x, 2 * i) * (i % 2 == 1 ? -1 : 1), 2 * i);
      result += temp;
    }
  }
  return result;
}

long double s21_exp(double x) {
  long double result;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_POSITIVE_INF) {
    result = S21_POSITIVE_INF;
  } else if (x == S21_NEGATIVE_INF) {
    result = 0;
  } else if (x == 0) {
    result = 1.0;
  } else if (s21_fabs(x) < 635) {
    result = 1.0L;
    long double temp = 1.0L;
    for (int i = 1; s21_fabs(temp) >= S21_EPSILON; i++) {
      temp = s21_division_by_factorial(s21_int_pow(x, i), i);
      result += temp;
    }
  } else if (x < 0) {
    result = 0.0;
  } else {
    result = S21_POSITIVE_INF;
  }
  return result;
}

long double s21_fabs(double x) { return x < 0 ? -1 * x : x; }

long double s21_floor(double x) {
  long double result;
  if (x != x) {
    result = S21_NAN;
  } else if (x == S21_NEGATIVE_INF) {
    result = S21_NEGATIVE_INF;
  } else if (x == S21_POSITIVE_INF) {
    result = S21_POSITIVE_INF;
  } else if (x == 0) {
    result = 0;
  } else if (s21_is_integer(x)) {
    result = (long int)x;
  } else if (x > 0.0) {
    result = (long int)x;
  } else {
    result = (long long int)x - 1;
  }
  return result;
}

long double s21_fmod(double x, double y) {
  long double result;
  if (x != x || y != y) {
    result = S21_NAN;
  } else if (x == 0) {
    result = 0;
  } else if (x == S21_POSITIVE_INF || x == S21_NEGATIVE_INF) {
    result = S21_NAN;
  } else if (y == S21_NEGATIVE_INF || y == S21_POSITIVE_INF) {
    result = x;
  } else {
    result = x - s21_truncate(x / y) * y;
  }
  return result;
}

long double s21_log(double x) {
  long double result = 0.0L;
  if (x == 0) {
    result = S21_NEGATIVE_INF;
  } else if (x < 0) {
    result = S21_NAN;
  } else if (x == S21_POSITIVE_INF) {
    result = S21_POSITIVE_INF;
  } else if (x != x || x == S21_NEGATIVE_INF) {
    result = S21_NAN;
  } else if (x > 1000.0L) {
    result = s21_log(x / 10) + s21_log(10);
  } else {
    double z = (x - 1) / (x + 1);
    long double temp = 1.0L;
    for (int i = 1; s21_fabs(temp) >= S21_EPSILON; i += 2) {
      temp = s21_int_pow(z, i) / i;
      result += temp;
    }
    result *= 2;
  }
  return result;
}

long double s21_pow(double base, double exp) {
  long double result = 0.0L;
  if (exp == 0.0L) {
    result = 1.0L;
  } else if (exp == 1.0L) {
    result = base;
  } else if (exp != exp) {
    result = S21_NAN;
  } else if (exp == S21_POSITIVE_INF) {
    if (s21_fabs(base) > 1.0L) {
      result = S21_POSITIVE_INF;
    } else if (s21_fabs(base) < 1.0L) {
      result = +0.0L;
    } else if (s21_fabs(base) == 1) {
      result = S21_NAN;
    }
  } else if (exp == S21_NEGATIVE_INF) {
    if (s21_fabs(base) > 1.0L) {
      result = +0.0L;
    } else if (s21_fabs(base) < 1.0L) {
      result = S21_POSITIVE_INF;
    } else if (s21_fabs(base) == 1) {
      result = S21_NAN;
    }
  } else {
    if (base == 0.0) {
      if (exp > 0.0L) {
        result = 0.0;
      } else {
        result = S21_POSITIVE_INF;
      }
    } else if (s21_fabs(base) < 0.001) {
      long double count = 1;
      while (s21_fabs(base) < 0.001) {
        base *= 10;
        count /= 10;
      }
      result = s21_pow(base, exp) * s21_pow(count, exp);
    } else if (base == S21_POSITIVE_INF) {
      if (exp > 0.0L) {
        result = S21_POSITIVE_INF;
      } else {
        result = +0.0;
      }
    } else if (base == S21_NEGATIVE_INF) {
      result = s21_pow(-0.0, -1 * exp);
    } else if (base < 0.0L && s21_is_integer(exp)) {
      result = s21_int_pow(-1.0, exp) * s21_pow(s21_fabs(base), exp);
    } else {
      result = s21_exp(exp * s21_log(base));
    }
  }
  return result;
}

long double s21_sin(double x) {
  long double result;
  if (x == 0) {
    result = 0.0;
  } else if (x != x || x == S21_POSITIVE_INF || x == S21_NEGATIVE_INF) {
    result = S21_NAN;
  } else {
    x = s21_fmod(x, 2 * S21_PI);
    result = 0.0L;
    long double temp = 1.0L;
    for (int i = 0; s21_fabs(temp) >= S21_EPSILON; i++) {
      temp = s21_division_by_factorial(
          s21_int_pow(x, 2 * i + 1) * (i % 2 == 1 ? -1 : 1), 2 * i + 1);
      result += temp;
    }
  }
  return result;
}

long double s21_sqrt(double x) {
  long double result;
  if (x != x || x == S21_NEGATIVE_INF || x < 0.0) {
    result = S21_NAN;
  } else if (x == S21_POSITIVE_INF) {
    result = S21_POSITIVE_INF;
  } else if (x == 0.0) {
    result = 0;
  } else {
    double sqrt = x / 3, diff = 1;
    do {
      double last = sqrt;
      sqrt = (sqrt + x / sqrt) / 2;
      diff = sqrt - last;
    } while (diff > MINDIFF || diff < -MINDIFF);
    result = sqrt;
  }
  return result;
}

long double s21_tan(double x) {
  long double result;
  if (x != x || x == S21_POSITIVE_INF || x == S21_NEGATIVE_INF) {
    result = S21_NAN;
  } else {
    result = s21_sin(x) / s21_cos(x);
  }
  return result;
}
