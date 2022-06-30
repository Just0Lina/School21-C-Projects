#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define H 25
#define W 80
#define E 10000
#define MAGENTA "\x1b[35m"
#define BLACK "\x1b[30m"

int readi(int generation1[H][W]);
void futuregeneration(int future[H][W], int generation1[H][W]);
int game(int future[H][W], int generation1[H][W], int generation2[H][W]);
int getch();
void invert(int future[H][W], int generation1[H][W]);
int compare(int future[H][W], int generation1[H][W], int generation2[H][W]);
void copy_gen(int generation1[H][W], int generation2[H][W]);
void output(int future[H][W]);

int main() {
    int generation1[H][W], future[H][W], generation2[H][W];

    if (readi(generation1) == 0) {
//    output(generation1);
//    sleep(1);
    printf("\033[H\033[J");
        if (game(future, generation1, generation2) == 0) {
            printf("Жизнь кончена");
        } else {
            printf("Выход через q\n");
        }
    } else {
        printf("Некорректный ввод\n");
    }

    return 0;
}
// Считывает файл из текстового документа в зависимости от выбранного mode.
int readi(int generation1[H][W]) {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                // Считываем элементы матрицы
                if (scanf("%d", &generation1[i][j]) !=  1) {
                    return 1;
                }
            }
        }
    return 0;
}
// Генерирует новое поколение
void futuregeneration(int future[H][W], int generation1[H][W]) {
    for (int i = 0; i < H  ; i++) {
        for (int j = 0; j < W  ; j++) {
            int neighboors, need1, need2;
            neighboors = 0;
            for (int ln =  -1; ln < 2; ln++) {
                for (int st = -1; st < 2; st++) {
                    // Проверяем не выодим ли мы за верхний предел
                    if (ln < 0  && i == 0)
                        need1 = (H + ln + i) % H;
                    else
                        need1 = (ln + i) % H;
                    // Проверяем не выходим ли мы левый предел
                    if (st < 0 && j == 0)
                        need2 = (W + st + j) % W;
                    else
                        need2 = (st + j) % W;
                    // Проверяем потому, что значение координаты отрицательное
                    // и остаток от деления будет отрицательным соответсятвенно
                    neighboors += generation1[need1][need2];
                    }
                }
            neighboors -= generation1[i][j];
            if (generation1[i][j] == 1 && (neighboors < 2 || neighboors > 3)) {
                future[i][j] = 0;
            } else if (generation1[i][j] == 0 && (neighboors == 3)) {
                future[i][j] = 1;
            } else {
                future[i][j] = generation1[i][j];
            }
        }
    }
}

// Управление
int game(int future[H][W], int generation1[H][W], int generation2[H][W]) {
    int keydoard = 0;
    futuregeneration(future, generation1);
    freopen("/dev/tty", "r", stdin);
    while (keydoard != 'q') {
        printf("\033[H\033[J");
        copy_gen(generation1, generation2);
        output(generation1);
        invert(future, generation1);
        if (keydoard == ' ') {
        futuregeneration(future, generation1);
            if (compare(future, generation1, generation2) == 0) {
                break;
            }
        }
        keydoard = getch();
    }
    if (keydoard == 'q')
        keydoard = 1;
    else
        keydoard = 0;
    return keydoard;
}
//  Читает символы с клавиатуры
int getch() {
    struct termios oldt, newt;  // переменные для запоминания исходных атрибутов терминала
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    // переход в некаконический режим
    // после этого терминал не ожидает нажатия Enter
    // сразу обрабтатывает переданные символы
    // STDIN_FILENO означает дескриптор (инф единицу) потока ввода, с которым мы работаем
    // (по умолчанию он равен 0)
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // ICANON — флаг включения того самого канонического ввода
    // ECHO — флаг отображения вводимых символов на экранe
    // TCSANOW и TCSAFLUSH — определенные библиотекой макросы.
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
// Продолжает род
void invert(int future[H][W], int generation1[H][W]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            generation1[i][j] = future[i][j];
        }
    }
}

// Сохраняет предыдущее поколение
void copy_gen(int generation1[H][W], int generation2[H][W]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            generation2[i][j] = generation1[i][j];
        }
    }
}
// Сравнивает поколения
int compare(int future[H][W], int generation1[H][W], int generation2[H][W]) {
    int res;
    res = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (future[i][j] != generation2[i][j]) {
                res = -1;
                break;
            }
        }
    }
    if (res == -1) {
        res = 0;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (future[i][j] != generation1[i][j]) {
                    res = -1;
                    break;
                }
            }
        }
    }
    return res;
}
// Вывод на экран
void output(int future[H][W]) {
    // пробегаем по всем строкам
    for (int i = 0; i < H; i++) {
        // пробегаем по всем столбцам для данной строки i
        for (int j = 0; j < W; j++) {
            if (future[i][j] == 0) {
                printf(BLACK "*");
            } else if (future[i][j] == 1) {
                printf(MAGENTA "•");
            }
        }
        printf("\n");
    }
    printf(MAGENTA "--------------------------ДЛЯ ВЫХОДА ИЗ ИГРЫ НАЖМИТЕ q--------------------------");
    printf("\n");
}
