#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

struct termios savetty;//termios структура для сохранения предыдущего состояния терминала
struct termios tty;//termios структура для перевода терминала в режим неканонического ввода
int ppid, pid0, pid1, pid2, pid3;
void readString(char *buf) {//функция считывания строки
    char ch;
    int i = 0;
    write(1, "Enter the string:\n", 18);
    tcsetattr (0, TCSAFLUSH, &savetty);
    while(read(0, &ch, 1)>0)
        if(ch == '\n')
            break;
        else
            buf[i++] = ch;
            buf[i] = '\n';
            buf[i+1] = '\0';
            tcsetattr (0, TCSAFLUSH, &tty);
    }
void changeRegister(int sig) {//функция смены регистра
    int i = 0;
    char str[100];
    char c;
    write(1, "Option 0:\n", 10);
    readString(str);
    while((c = str[i]) != '\0') {
        if(c <= (int)'Z' && c >= (int)'A') {
            str[i] = c + 32;
            i++;
            continue;
        }
        else 
            if(c <= (int)'z' && c >= (int)'a') {
                str[i] = c - 32;
                i++;
                continue;
            } else {
                str[i] = c;
                i++;
                continue;
            }
    }
    write(1, str, i+1);
    sigset(SIGUSR1, changeRegister);
    kill(ppid, SIGUSR1);
    pause();
}
void invertString(int sig) { //функция инвертирования строки
    int i = 0;
    int len;
    char str[100];
    char c;
    write(1, "Option 1:\n", 10);
    readString(str);
    len = strlen(str) - 2;
    for(i = 0; i <= len / 2; i++) {
        c = str[i];
        str[i] = str[len - i];
        str[len - i] = c;
    }
    write(1, str, len + 2);
    sigset(SIGUSR1, invertString);
    kill(ppid, SIGUSR1);
    pause();
}

void swapNeighbor(int sig) {//функция замены соседних элементов строки
    int i = 0;
    char str[100];
    char c;
    write(1, "Option 2:\n", 10);
    readString(str);
    while(str[i+1] != '\n'){
        if(str[i] == '\n'){
            i--;
            break;
        }
        c = str[i];
        str[i] = str[i+1];
        str[i+1] = c;
        i+=2;
    }
    
    write(1, str, i + 2);
    sigset(SIGUSR1, swapNeighbor);
    kill(ppid, SIGUSR1);
    pause();
}
void convertToKOI(int sig) {//функция перевода в KOI8
    int i = 0;
    char str[100];
    char c = (char)128;
    write(1, "Option 3:\n", 10);
    readString(str);
    while(str[i] != '\n'){
        str[i] |= c;
        i++;
    }
    write(1, str, i + 1);
    sigset(SIGUSR1, convertToKOI);
    kill(ppid, SIGUSR1);
    pause();
}

void emptySig(int sig){}//функция-обработчик корневого процесса

int main (int argc, char** argv){
    char ch;
    if ( !isatty(0) ) {//проверка устройства ввода
        fprintf (stderr, "stdin not terminal\n");
        exit (1);
    };
    sigset(SIGUSR1, emptySig);//регистрация функции-обработчика корневого процесса
    tcgetattr (0, &tty);
    savetty = tty;//сохранение состояния терминала
    tty.c_lflag &= ~(ICANON|ECHO|ISIG);//установка флагов для неканонического ввода
    tty.c_cc[VMIN] = 1;
    tcsetattr (0, TCSAFLUSH, &tty);
    write(1, "\nEnter number of string transformation option:\n", 47);
    write(1, " 0) Change case of symbols\n", 28);
    write(1, " 1) Inverting string\n", 22);
    write(1, " 2) Transposition of neighbor symbols\n", 39);
    write(1, " 3) Convert string to KOI8\n", 28);
    ppid = getpid();
    if(!(pid0 = fork())) {//регистрация обработчика 1 сигнала
        sigset(SIGUSR1, changeRegister);
        pause();
    }
    if(!(pid1 = fork())) {//регистрация обработчика 2 сигнала
        sigset(SIGUSR1, invertString);
        pause();
    }
    if(!(pid2 = fork())) {//регистрация обработчика 3 сигнала
        sigset(SIGUSR1, swapNeighbor);
        pause();
    }
    if(!(pid3 = fork())) {//регистрация обработчика 3 сигнала
        sigset(SIGUSR1, convertToKOI);
        pause();
    }
    if(getpid() == ppid) {
        for(;;) {
            read (0, &ch, 1);
            if (ch == 'q')
                break;
            switch (ch) {
            case '0':
                kill(pid0, SIGUSR1);
                pause();
                break;
            case '1':
                kill(pid1, SIGUSR1);
                pause();
                break;
            case '2':
                kill(pid2, SIGUSR1);
                pause();
                break;
            case '3':
                kill(pid3, SIGUSR1);
                pause();
                break;
            }
        }
    }
    tcsetattr (0, TCSAFLUSH, &savetty);//возврат терминала к режиму канонического ввода
    exit (0);
}
