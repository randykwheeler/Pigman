/* cool.c - Pigman Enhancements */

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

/* Animated Pig Intro */
void cool_matrix_intro(void) {
    int i;
    
    printf("\033[H\033[J"); /* Clear screen */
    
    /* Animation loop: Move ears/snout */
    for(i = 0; i < 20; i++) {
        printf("\033[H"); /* Reset cursor to top-left */
        
        printf("\n\n");
        printf("           (____)\n");
        if (i % 2 == 0)
            printf("    (____) ( oo )   PIGMAN IRC\n");
        else
            printf("    (____) (-oo-)   PIGMAN IRC\n"); /* Blink */
            
        printf("      ||----\\/ \n");
        printf("      ||     ||      Initializing...\n");
        printf("      ||__||_||\n");
        printf("      \"\"  \"\" \"\" \n");
        
        fflush(stdout);
        usleep(250000); /* 250ms delay */
    }
    usleep(500000);
    printf("\033[H\033[J"); 
}

/* Rainbow Command (Unchanged but improved for Pigman) */
static int get_rainbow_color(int i) {
    int colors[] = { 13, 5, 4, 7, 8, 3, 12, 2, 6 }; /* Pink first for pig! */
    return colors[i % 9];
}

void cool_rainbow_cmd(char *command, char *args, char *subargs, char *helparg) {
    char buffer[2048];
    char *p = buffer;
    int i = 0;
    
    if (!args || !*args) {
        BX_put_it("Usage: /RAINBOW <text>");
        return;
    }

    *p = 0;
    while (*args && (p - buffer < 2000)) {
        if (*args != ' ') {
            p += sprintf(p, "\003%02d%c", get_rainbow_color(i++), *args);
        } else {
            *p++ = ' ';
        }
        args++;
    }
    *p = 0;
    
    if (BX_get_server_channels(from_server))
        BX_send_text(((ChannelList *)BX_get_server_channels(from_server))->channel, buffer, NULL, 0, 0);
    else if (current_window && current_window->current_channel)
        BX_send_text(current_window->current_channel, buffer, NULL, 0, 0);
    else
        BX_put_it("You are not in a channel!");
}

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

    /* term_clear_screen() macro from ircterm.h */
    term_clrscr(); 
    
    for (i = 0; i < 50; i++) {
        BX_put_it("%s", messages[rand() % 7]);
        usleep(100000 + (rand() % 200000));
        if (i % 5 == 0) {
             BX_put_it("Swine Process [PID %d]: %d%% complete...", getpid(), i*2);
        }
    }
    BX_put_it("Pigman Update Complete. Resume snorting.");
}
