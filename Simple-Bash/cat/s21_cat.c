#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
typedef struct Node Node;
struct Node {
    int bflag, eflag, nflag, sflag, tflag, vflag;
};
void CatNoFlags(int fd);
void ScanFiles(const char *argv[], Node flag);
void CatWFlags(FILE *fp, Node flag);


int main(int argc, char *argv[]) {
    char ch;
    Node flag;
    flag.vflag = flag.nflag = flag.bflag = flag.sflag = flag.eflag = flag.tflag = 0;
    while ((ch = getopt(argc, argv, "benstv")) != -1)
        switch (ch) {
        case 'b':
            flag.bflag = flag.nflag = 1;
            break;
        case 'e':
            flag.eflag = flag.vflag = 1;
            break;
        case 'n':
            flag.nflag = 1;
            break;
        case 's':
            flag.sflag = 1;
            break;
        case 't':
            flag.tflag = flag.vflag = 1;
            break;
        case 'v':
            flag.vflag = 1;
            break;
        default:
            break;
        }
    argv += optind;
    ScanFiles((const char**)argv, flag);
    return 0;
}
void ScanFiles(const char *argv[], Node flag) {
    int i = 0;
    char *path;
    FILE *fp;
    while ((path = (char*)argv[i]) != NULL || i == 0) {
        int fd;
        if (path == NULL || strcmp(path, "-") == 0) {
            fd = STDIN_FILENO;
        } else {
            fd = open(path, O_RDONLY);
        }
        if (fd != -1 && (flag.bflag || flag.eflag || flag.nflag || flag.sflag || flag.tflag || flag.vflag)) {
            if (fd == STDIN_FILENO) {
                CatWFlags(stdin, flag);
            } else {
                fp = fdopen(fd, "r");
                CatWFlags(fp, flag);
                fclose(fp);
            }
        } else {
            CatNoFlags(fd);
            if (fd != STDIN_FILENO) close(fd);
        }
        if (path == NULL) break;
        i++;
    }
}
void CatWFlags(FILE *fp, Node flag) {
    int ch, gobble, line, prev;
    gobble = 0;
    line = 1;
    int flags = 1;
    for (prev = '\n'; (ch = getc(fp)) != EOF; prev = ch) {
        int flagt = 1;
        if (prev == '\n') {
            if (flag.sflag) {
                if (ch == '\n') {
                    if (gobble) {
                        flags = 0;
                    } else {
                        gobble = 1;
                    }
                } else  {
                    gobble = 0;
                    flags = 1;
                }
            }
            if (flags && flag.nflag && (!flag.bflag || ch != '\n')) {
                fprintf(stdout, "%6d\t", line++);
            }
        }
        if (flags && ch == '\n') {
            if (flag.eflag) {
                putchar('$');
            }
        } else if (flags && ch == '\t') {
            if (flag.tflag) {
                printf("%s", "^I");
                flagt = 0;
            }
        } else if (flags && flag.vflag) {
            if (ch >= 0 && ch <= 31 && !((ch == 9) || (ch == 10))) {
                printf("%s", "^");
                ch = ch + 64;
            } else if (ch == 127) {
                printf("%s", "^");
                ch = ch - 64;
            } else if (ch > 127 && ch <= 159) {
                printf("%s", "M-^");
                ch -= 64;
            }
        }
        if (flags && flagt) printf("%c", ch);
    }
}

void CatNoFlags(int fd) {
    FILE* fp = fdopen(fd, "r");
    char c = getc(fp);
    while (!feof(fp)) {
        printf("%c", c);
        c = getc(fp);
    }
  return;
}
