#ifndef MINITALK_H
#define MINITALK_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

enum{
    READY,
    BUSY,
};

void    handler(int signo, siginfo_t *info, void *more_info);

void   my_signal(int signo, void *handler, bool use_sigi);
#endif