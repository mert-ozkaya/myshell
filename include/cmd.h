#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUMBER_OF_PARAMS 10

void parseCmd(char* cmd, char** params);
void parseCmdSymbol(char* cmd, char** params);
void input(char* cmd);
void action(char** params);
int executeCmd(char** params);
void sigChild(int signalNo);
int background(char** params);

