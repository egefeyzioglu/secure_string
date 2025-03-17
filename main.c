#include <stdio.h>
#include <termios.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

#define STDIN_FILENO 0

void disable_echo(){
    struct termios tty;
    tcgetattr(STDIN_FILENO,&tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void enable_echo(){
    struct termios tty;
    tcgetattr(STDIN_FILENO,&tty);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}


void handle_exit(int val){
    enable_echo();
    exit(val);
}

void handle_exit_signal(int signal){
    handle_exit(128 + signal);
}

int main(void){
    signal(SIGTERM, &handle_exit_signal);
    signal(SIGABRT, &handle_exit_signal);
    signal(SIGQUIT, &handle_exit_signal);
    signal(SIGSEGV, &handle_exit_signal);
    signal(SIGINT, &handle_exit_signal);
    disable_echo();
    char *input = NULL;
    size_t input_size;
    int num_chars = getline(&input, &input_size, stdin);
    if(num_chars == -1){
        handle_exit(EXIT_FAILURE);
    }
    input[input_size-1] = '\0'; // Remove newline at the end
    printf("%s", input);
    enable_echo();
}


