#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iterator>
#include <fstream>
#include <iostream>

#define ash_TOK_BUFSIZE 64
#define ash_TOK_DELIM " \t\r\n\a"

// fn definitions
int ash_cd(char **args);
int ash_help();
int ash_history();
int ash_execute(char **args);
int ash_launch(char **args);
char *ash_read_line();
char **ash_split_line(char *line);

//List of builtin commands
std::vector<std::string> builtin_str;
std::vector<std::string> history;

int main(int argc, char **argv) {
    char *line;
    char **args;
    int status;

    builtin_str = {"cd","help","exit","history"};

    std::ifstream input_file("history.txt");
    std::istream_iterator<std::string> start(input_file), end;
    history = std::vector<std::string>(start,end);

    do {
        printf("> ");
        line = ash_read_line();
        history.emplace_back(line);
        args = ash_split_line(line);
        status = ash_execute(args);

        free(line);
        free(args);
    } while (status);

    std::ofstream output_file("history.txt");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(history.begin(), history.end(), output_iterator);

    return EXIT_SUCCESS;
}


/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int ash_cd(char **args) {
    if (args[1] == nullptr)
        fprintf(stderr, "ash: expected argument to \"cd\"\n");
    else if (chdir(args[1]) != 0)
        perror("ash");
    return 1;
}

/**
   @brief Builtin command: print help.
   @return Always returns 1, to continue executing.
 */
int ash_help() {
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (const std::string &s:builtin_str)
        std::cout<<s<<std::endl;

    printf("Use the man command for information on other programs.\n");
    return 1;
}

/**
   @brief Execute shell built-in or launch program.
   @param args Null terminated list of arguments.
   @return 1 if the shell should continue running, 0 if it should terminate
 */
int ash_execute(char **args) {
    if (args[0] == nullptr) // An empty command was entered.
        return EXIT_FAILURE;

    if (!strcmp(args[0], "cd"))
        return ash_cd(args);
    else if (!strcmp(args[0], "help"))
        return ash_help();
    else if (!strcmp(args[0], "exit"))
        return EXIT_SUCCESS;
    else if (!strcmp(args[0], "history"))
        return ash_history();
    else
        return ash_launch(args);
}

/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *ash_read_line() {
    int bufsize = 1024;
    int position = 0;
    auto *buffer = (char *) malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "ash: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // Read a character
        c = (char) getchar();

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else
            buffer[position] = c;

        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += 1024;
            buffer = (char *) realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "ash: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **ash_split_line(char *line) {
    int bufsize = ash_TOK_BUFSIZE, position = 0;
    char **tokens = (char **) malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "ash: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, ash_TOK_DELIM);
    while (token != nullptr) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += ash_TOK_BUFSIZE;
            tokens = (char **) realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "ash: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(nullptr, ash_TOK_DELIM);
    }
    tokens[position] = nullptr;
    return tokens;
}

int ash_launch(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) { // Child process
        if (execvp(args[0], args) == -1)
            perror("ash");
        exit(EXIT_FAILURE);
    } else if (pid < 0)         // Error forking
        perror("ash");
    else
        do { // Parent process
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    return 1;
}

int ash_history(){
    for (const std::string &s:history)
        std::cout<<s<<"\n";
    return 1;
}