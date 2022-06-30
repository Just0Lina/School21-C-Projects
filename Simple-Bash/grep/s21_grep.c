#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <regex.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLEN 10000
typedef struct Node Node;
struct Node {
    int eflag, iflag, vflag, cflag, lflag, nflag, hflag, sflag, fflag;
    char **pattern;
    char **path;
    int numFiles, numPat;
};
void Grep(FILE *fp, Node flag, char* path);
void WorkWithText(Node flag);
void ArgFunc(Node *flag, char** argv);
int main(int argc, char *argv[]) {
    Node flag;
    flag.nflag = flag.iflag = flag.cflag = flag.lflag =
     flag.eflag = flag.fflag = flag.sflag = flag.hflag = flag.vflag = flag.numPat = flag.numFiles = 0;
    flag.pattern = (char **)malloc(MAXLEN * sizeof(char *));
    flag.path = (char **)malloc(MAXLEN * sizeof(char *));
    for (int i = 0; i < MAXLEN; i++) {
      flag.path[i] = (char *)malloc(MAXLEN * sizeof(char));
      flag.pattern[i] = (char *)malloc(MAXLEN * sizeof(char));
    }
    ArgFunc(&flag, argv);
    WorkWithText(flag);
    for (int j = 0; j < MAXLEN; j++) {
        free(flag.path[j]);
        free(flag.pattern[j]);
      }
      free(flag.path);
      free(flag.pattern);
    return 0;
}

void ArgFunc(Node *flag, char** argv) {
    int i = 0;
    for (i = 1; argv[i]; i++) {
        if (argv[i][0] == '-') {
            int newF = 0;
            for (int j = 1; argv[i][j] != '\0' && !newF; j++) {
                if (argv[i][j] == 'c') {
                    flag->cflag = 1;
                } else if (argv[i][j] == 'i') {
                    flag->iflag = 1;
                } else if (argv[i][j] == 'l') {
                    flag->lflag = 1;
                } else if (argv[i][j] == 'n') {
                    flag->nflag = 1;
                } else if (argv[i][j] == 'v') {
                    flag->vflag = 1;
                } else if (argv[i][j] == 'e') {
                    flag->eflag = 1;
                    i++;
                    newF = 1;
                    snprintf(flag->pattern[flag->numPat], MAXLEN, "%s", argv[i]);
                    flag->numPat += 1;
                } else if (argv[i][j] == 'h') {
                    flag->hflag = 1;
                } else if (argv[i][j] == 's') {
                    flag->sflag = 1;
                } else if (argv[i][j] == 'f') {
                    flag->fflag = 1;
                    char *patternsPath = (char *)malloc(MAXLEN * sizeof(char));
                    i++;
                    newF = 1;
                    snprintf(patternsPath, MAXLEN, "%s", argv[i]);
                    char *str = NULL;
                    int fd;
                    fd = open(patternsPath, O_RDONLY);
                    if (fd != -1) {
                        FILE *fp;
                        fp = fdopen(fd, "r");
                        size_t len;
                        while (getline(&str, &len, fp) != -1) {
                            int tmp_len = strlen(str);
                            int str_len = str[tmp_len - 1] == '\n' && tmp_len != 1 ? tmp_len : tmp_len + 1;
                            snprintf(flag->pattern[flag->numPat], str_len, "%s", str);
                            flag->numPat++;
                        }
                        fclose(fp);
                    } else if (!flag->sflag) {
                        printf("grep: %s: No such file or directory", patternsPath);
                    }
                    free(str);
                    free(patternsPath);
                    close(fd);
                }
            }
        } else if (flag->numPat) {
            snprintf(flag->path[flag->numFiles], MAXLEN, "%s", argv[i]);
            flag->eflag = 1;
            flag->numFiles++;
        } else {
            snprintf(flag->pattern[flag->numPat], MAXLEN, "%s", argv[i]);
            flag->numPat += 1;
        }
    }
}

void WorkWithText(Node flag) {
    for (int i = 0; i < flag.numFiles; i++) {
        int fd;
        fd = open(flag.path[i], O_RDONLY);
        if (fd != -1 && (flag.eflag || flag.iflag || flag.vflag
                         || flag.cflag || flag.lflag || flag.nflag || flag.fflag)) {
            FILE *fp;
            fp = fdopen(fd, "r");
            Grep(fp, flag, flag.path[i]);
            fclose(fp);
        } else if (!flag.sflag) {
            printf("grep: %s: No such file or directory", flag.path[i]);
        }
        close(fd);
    }
}
void Grep(FILE *fp, Node flag, char* path) {
    int line = 1, lineC = 0;
    char *str = NULL;
    size_t len = 0;
    int move;
    while (getline(&str, &len, fp) != -1) {
        int flagC = 0;
        for (int i = 0; i < flag.numPat && !flagC; i++) {
            regex_t preg;
            if (flag.iflag) {
                regcomp(&preg, flag.pattern[i], REG_ICASE);
                move = regexec(&preg, str, 0, 0, 0);
            } else {
                regcomp(&preg, flag.pattern[i], REG_EXTENDED);
                move = regexec(&preg, str, 0, 0, 0);
            }
            if (flag.vflag) move = (move != 0) ? 0 : 1;
            if (!move) {
                flagC = 1;
                if (flag.nflag) {
                    if (flag.numFiles > 1 && !flag.hflag) fprintf(stdout, "%s:", path);
                    fprintf(stdout, "%d:", line);
                }
                lineC++;
                if (!flag.cflag && !flag.lflag) {
                    if (flag.numFiles > 1 && !flag.nflag && !flag.hflag) fprintf(stdout, "%s:", path);
                    fprintf(stdout, "%s", str);
                }
            }
            line++;
            regfree(&preg);
        }
    }
    free(str);
    if (flag.cflag) {
        if (flag.numFiles > 1 && !flag.hflag) fprintf(stdout, "%s:", path);
        fprintf(stdout, "%d\n", lineC);
    }
    if (flag.lflag && lineC != 0) {
        if (flag.numFiles > 1 && !flag.hflag) fprintf(stdout, "%s:", path);
        fprintf(stdout, "%s\n", path);
    }
}
