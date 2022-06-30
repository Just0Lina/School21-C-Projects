#include "s21_matrix.h"

matrix_t s21_create_matrix(int rows, int columns) {
  matrix_t matrix = {NULL, 0, 0, INCORRECT_MATRIX};
  if (rows > 0 && columns > 0) {
    matrix.matrix = (double **)calloc(rows, sizeof(double *));
    matrix.columns = columns;
    matrix.rows = rows;
    for (int i = 0; i < rows; i++) {
      matrix.matrix[i] = (double *)calloc(columns, sizeof(double));
    }
    matrix.matrix_type = ZERO_MATRIX;
  }
  return matrix;
}

void s21_remove_matrix(matrix_t *A) {
  double **tmp = A->matrix;
  for (int i = 0; i < A->rows; i++) {
    free(tmp[i]);
  }
  if (A->rows && A->columns) free(tmp);
  A->columns = 0;
  A->rows = 0;
  A->matrix_type = INCORRECT_MATRIX;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A->matrix_type == INCORRECT_MATRIX ||
      B->matrix_type == INCORRECT_MATRIX || A->columns != B->columns ||
      A->rows != B->rows) {
    res = FAILURE;
  } else {
    double **tmpA = A->matrix, **tmpB = B->matrix;
    for (int i = 0; i < A->rows && res; i++) {
      for (int j = 0; j < A->columns && res; j++) {
        if (fabs(tmpA[i][j] - tmpB[i][j]) >= 1e-7) {
          res = FAILURE;
        }
      }
    }
  }
  return res;
}

matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
  matrix_t tmp = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type == INCORRECT_MATRIX ||
      B->matrix_type == INCORRECT_MATRIX) {
    tmp.matrix_type = INCORRECT_MATRIX;
  } else {
    if (A->columns != B->columns || A->rows != B->rows) {
      tmp.matrix_type = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          tmp.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
      Set_matrix_type(&tmp);
    }
  }
  return tmp;
}

matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
  matrix_t tmp = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type == INCORRECT_MATRIX ||
      B->matrix_type == INCORRECT_MATRIX) {
    tmp.matrix_type = INCORRECT_MATRIX;
  } else {
    if (A->columns != B->columns || A->rows != B->rows) {
      tmp.matrix_type = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          tmp.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
      Set_matrix_type(&tmp);
    }
  }
  return tmp;
}

void Set_matrix_type(matrix_t *A) {  // Добавить сравнение с Е
  int allZeroes = 1, identity = (A->rows == A->columns) ? 1 : 0;
  matrix_type_t type = CORRECT_MATRIX;
  double **tmp = A->matrix;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if ((i == j && tmp[i][j] != 1) || (i != j && tmp[i][j] != 0)) {
        identity = 0;
      }
      if (tmp[i][j] != 0) allZeroes = 0;
    }
  }
  if (allZeroes)
    type = ZERO_MATRIX;
  else if (identity)
    type = IDENTITY_MATRIX;
  A->matrix_type = type;
}

matrix_t s21_mult_number(matrix_t *A, double number) {
  matrix_t tmp = s21_create_matrix(A->rows, A->columns);
  if (A->matrix_type == INCORRECT_MATRIX) {
    tmp.matrix_type = INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        tmp.matrix[i][j] = number * A->matrix[i][j];
      }
    }
    Set_matrix_type(&tmp);
    Set_matrix_type(&tmp);
  }
  return tmp;
}

matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
  matrix_t tmp = s21_create_matrix(A->rows, B->columns);
  if (A->matrix_type == INCORRECT_MATRIX ||
      B->matrix_type == INCORRECT_MATRIX || A->columns != B->rows) {
    tmp.matrix_type = INCORRECT_MATRIX;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < B->columns; k++) {
        double sum = 0;
        for (int j = 0; j < A->columns; j++) {
          sum += A->matrix[i][j] * B->matrix[j][k];
        }
        tmp.matrix[i][k] = sum;
      }
      Set_matrix_type(&tmp);
    }
  }
  return tmp;
}

matrix_t s21_transpose(matrix_t *A) {
  matrix_t tmp = {NULL, 0, 0, INCORRECT_MATRIX};
  if (A->matrix_type == INCORRECT_MATRIX) {
    tmp.matrix_type = INCORRECT_MATRIX;
  } else {
    tmp = s21_create_matrix(A->columns, A->rows);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        tmp.matrix[j][i] = A->matrix[i][j];
      }
    }
    tmp.matrix_type = A->matrix_type;
  }
  return tmp;
}

double s21_determinant(matrix_t *A) {
  double ans = 0;
  if (A->matrix_type != INCORRECT_MATRIX) {
    double **tmp = A->matrix;
    if (!IsSquare(A)) {
      ans = 0 / 0.0;
    } else {
      if (A->rows == 1) {
        ans = tmp[0][0];
      } else if (A->rows == 2) {
        ans = tmp[0][0] * tmp[1][1] - tmp[1][0] * tmp[0][1];
      } else {
        for (int i = 0; i < A->rows; i++) {
          matrix_t lilTmp = FindLilMAtrix(A, 0, i);
          int sign = ((i) % 2 == 0) ? 1 : -1;
          ans += tmp[0][i] * s21_determinant(&lilTmp) * sign;
          s21_remove_matrix(&lilTmp);
        }
      }
    }
  }
  return ans;
}

matrix_t s21_calc_complements(matrix_t *A) {
  matrix_t tmp;
  if (A->matrix_type == INCORRECT_MATRIX) {
    tmp.matrix_type = INCORRECT_MATRIX;
  } else {
    tmp = s21_create_matrix(A->columns, A->rows);
    if (!IsSquare(A)) {
      tmp.matrix_type = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->rows; j++) {
          matrix_t lilTmp = FindLilMAtrix(A, i, j);
          int sign = ((i + j) % 2 == 0) ? 1 : -1;
          tmp.matrix[i][j] = s21_determinant(&lilTmp) * sign;
          s21_remove_matrix(&lilTmp);
        }
      }
      Set_matrix_type(&tmp);
    }
  }
  return tmp;
}

int IsSquare(matrix_t *A) { return (A->rows == A->columns); }

matrix_t FindLilMAtrix(matrix_t *A, int ir, int jr) {
  matrix_t tmp;
  if (A->rows == 1 && A->columns == 1) {
    tmp = s21_create_matrix(1, 1);
    tmp.matrix[0][0] = A->matrix[0][0];
  } else {
    tmp = s21_create_matrix(A->rows - 1, A->rows - 1);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->rows; j++) {
        if (i < ir && j < jr) {
          tmp.matrix[i][j] = A->matrix[i][j];
        } else if (i > ir && j < jr) {
          tmp.matrix[i - 1][j] = A->matrix[i][j];
        } else if (i < ir && j > jr) {
          tmp.matrix[i][j - 1] = A->matrix[i][j];
        } else if (i > ir && j > jr) {
          tmp.matrix[i - 1][j - 1] = A->matrix[i][j];
        }
      }
    }
  }
  Set_matrix_type(&tmp);
  return tmp;
}

matrix_t s21_inverse_matrix(matrix_t *A) {
  matrix_t tmp = {NULL, 0, 0, INCORRECT_MATRIX};
  if (A->matrix_type == INCORRECT_MATRIX || !IsSquare(A)) {
    tmp.matrix_type = INCORRECT_MATRIX;
  } else {
    matrix_t calc = s21_calc_complements(A);
    tmp = s21_transpose(&calc);
    s21_remove_matrix(&calc);
    double det = s21_determinant(A);
    if (det) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          tmp.matrix[i][j] = 1 / det * tmp.matrix[i][j];
        }
      }
      Set_matrix_type(&tmp);
    } else {
      tmp.matrix_type = INCORRECT_MATRIX;
    }
  }
  return tmp;
}

void init_matrix(matrix_t *A, char *string) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      int n = 0;
      sscanf(string, "%lf%n", &A->matrix[i][j], &n);
      string += n;
    }
  }
  Set_matrix_type(A);
}
