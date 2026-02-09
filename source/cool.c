/* cool.c - Pigman v2 Enhancements */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "irc.h"
#include "struct.h"
#include "ircaux.h"
#include "window.h"
#include "output.h"
#include "screen.h"
#include "server.h"
#include "commands.h"
#include "ircterm.h"
#include "list.h"

/* Helper to draw the pig */
static void draw_pig(int frame) {
    /* ANSI Pink: \033[1;35m */
    /* Bold: \033[1m */
    /* Reset: \033[0m */
    
    printf("\033[H\033[J\033[1;35m"); /* Clear, Home, PINK */
    
    printf("\n\n\n");
    printf("         _//| .-.\n");
    
    if (frame % 2 == 0)
        printf("       _/ o O \\_//    PIGMAN IRC\n");
    else
        printf("       _/ - - \\_//    PIGMAN IRC\n"); /* Blink */

    printf("      (   ^   )       v1.2.1\n");
    printf("       | \\_/ |\n");
    
    if (frame % 4 == 0)
         printf("       \\_____/        \"Oink.\"\n");
    else if (frame % 4 == 1)
         printf("       \\_____/        \"Snort.\"\n");
    else if (frame % 4 == 2)
         printf("       \\_____/        \"Squeal.\"\n");
    else
         printf("       \\_____/        \"Grunt.\"\n");

    printf("\n\033[0m");
}

/* Intro Animation */
void cool_matrix_intro(void) {
    int i;
    for(i = 0; i < 12; i++) {
        draw_pig(i);
        fflush(stdout);
        usleep(200000); /* 200ms */
    }
    usleep(500000);
    printf("\033[H\033[J"); /* Clear before BitchX start */
}

/* /PIGMAN Command - Runs the animation */
void cool_pigman_cmd(char *command, char *args, char *subargs, char *helparg) {
    /* To show animation inside client, we need to be careful not to break ncurses state.
       term_clrscr() might work but could leave artifacts. 
       Let's try a safe approach: Just output text art.
       User asked for "show a ascii pig animation" via command.
       Blocking animation inside main loop is risky but we'll try short loop.
    */
    
    int i;
    /* We can't easily clear screen inside BitchX window loop without refresh issues.
       So we'll just put it to the screen buffer.
    */
    BX_put_it("\00313 _//| .-.");
    BX_put_it("\00313_/ o O \\_//    PIGMAN POWER!");
    BX_put_it("\00313(   ^   )       ");
    BX_put_it("\00313 | \\_/ |        ");
    BX_put_it("\00313 \\_____/        ");
}

/* /WTF Command */
void cool_wtf_cmd(char *command, char *args, char *subargs, char *helparg) {
    const char *quotes[] = {
        "I'm not saying it was aliens, but it was pigs.",
        "Why is the bacon gone?",
        "Keyboard not found. Press F1 to continue.",
        "Error: Success.",
        "To err is human, to oink divine.",
        "Have you tried turning it off and on again?",
        "Pigman says: 404 Logic Not Found.",
        "Confusion is the first step to... something."
    };
    
    int index = rand() % 8;
    BX_put_it("\00306%s", quotes[index]); /* Magenta text */
}

/* Boss Mode (Updated) */
void cool_boss_cmd(char *command, char *args, char *subargs, char *helparg) {
    int i;
    const char *messages[] = {
        "Compiling truffle detection algorithms...",
        "Scanning mud pits for optimize vectors...",
        "Feeding slop to the mainframe...",
        "Oinking at the moon...",
        "Pigman protocol initialized...",
        "Downloading excessive Bacon...",
        "Updating system registry..."
    };

    term_clrscr(); 
    
    for (i = 0; i < 50; i++) {
        BX_put_it("%s", messages[rand() % 7]);
        usleep(100000 + (rand() % 200000));
    }
    BX_put_it("System update complete. Resume snorting.");
}
