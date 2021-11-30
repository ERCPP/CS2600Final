int main(int argc, char **argv) {
    // Load config files, if any.

    // Run command loop.
    lsh_loop();

  // Perform any shutdown and cleanup.

  return EXIT_SUCCESS;
}

void lsh_loop(void) {
    char *line;
    char **args;
   int status;
    do {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);
        free(line);
        free(args);
    } while (status);
}

//Replaced LSH_RL_BUFFSIZE with one that utilizes getline.
/*
#define LSH_RL_BUFSIZE 1024
char *lsh_read_line(void) {
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();
        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
*/

char *lsh_read_line(void) {
    char *line = NULL;  
    ssize_t bufsize = 0; // Have getline allocate a buffer for us

    if (getline(&line, &bufsize, stdin) == -1){
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);  // We recieved an EOF
        } else  {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}