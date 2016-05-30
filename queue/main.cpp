//
//  main.cpp
//  queue
//
//  Created by Terwer Green on 16/5/30.
//  Copyright © 2016年 Terwer Green. All rights reserved.
//

#include <assert.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Queue.h"

char *execname = NULL;
int exit_status = EXIT_SUCCESS;

void putinqueue(Queue *the_queue, FILE *input, const char *filename) {
    char buffer[1024];
    for (int linenr = 1; ; ++linenr) {
        char *linepos = fgets(buffer, sizeof buffer, input);
        if (linepos == NULL) break;
        linepos = strchr(buffer, '\n');
        if (linepos == NULL) {
            fflush(NULL);
            fprintf(stderr, "%s: %s[%d]: unterminated line\n",
                    execname, filename, linenr);
            fflush(NULL);
            exit_status = EXIT_FAILURE;
        } else {
            *linepos = '\0';
        }
        linepos = strdup(buffer);
        assert(linepos != NULL);
        queue_insert(the_queue, linepos);
    }
}

void putfileinqueue(Queue *the_queue, const char *filename) {
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        fflush(NULL);
        fprintf(stderr, "%s: %s: %s\n",
                execname, filename, strerror (errno));
        fflush(NULL);
        exit_status = EXIT_FAILURE;
    } else {
        putinqueue(the_queue, input, filename);
        fclose(input);
    }
}

int main (int argc, char **argv) {
    execname = basename(argv[0]);
    Queue *the_queue = queue_new();
    
    if (argc < 2) {
        putinqueue(the_queue, stdin, "-");
    } else {
        for (int argi = 1; argi < argc; ++argi) {
            if (strcmp(argv[argi], "-") == 0) {
                putinqueue(the_queue, stdin, "-");
            } else {
                putfileinqueue(the_queue, argv[argi]);
            }
        }
    }
    
    while (!queue_isempty(the_queue)) {
        printf("%s\n", queue_remove(the_queue));
    }
    
    return 0;
}
