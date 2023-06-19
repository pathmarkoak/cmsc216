#include <assert.h>
#include <ctype.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void *word_count(void *arg);

static void *word_count(void *arg) {
    char ch, next_ch;
    int line_count, words, chars;
    char *filename = (char *)arg;
    int *return_array = malloc(sizeof(int) * 3);
    FILE *fp = fopen(filename, "r");

    if (fp != NULL) {
        line_count = words = chars = 0;
        ch = fgetc(fp);
        while (!feof(fp)) {
            next_ch = fgetc(fp);
            ungetc(next_ch, fp);

            if (ch == '\n')
                line_count++;
            if (!isspace(ch) && (isspace(next_ch) || feof(fp)))
                words++;

            chars++;

            ch = fgetc(fp);
        }
        fclose(fp);
    }
    return_array[0] = line_count; 
    return_array[1] = words; 
    return_array[2] = chars;
    pthread_exit(return_array);
}

int main(int argc, char *argv[]) {
    char *filename;
    int arg_num = 0, total_lines = 0, total_words = 0, total_chars = 0;
    pthread_t *tids = malloc(sizeof(pthread_t) * (argc - 1));
    int **thread_results = malloc(sizeof(int *) * (argc - 1));

    for (arg_num = 0; arg_num < argc - 1; arg_num++) {
        filename = argv[arg_num + 1];

        assert(pthread_create(&tids[arg_num], NULL, word_count,
                              (void*) filename) == 0);
    }

    for (arg_num = 0; arg_num < argc - 1; arg_num++) {
        assert(pthread_join(tids[arg_num],
                            (void **)&thread_results[arg_num]) == 0);
    }

    for (arg_num = 0; arg_num < argc - 1; arg_num++) {
        total_lines += thread_results[arg_num][0];
        total_words += thread_results[arg_num][1];
        total_chars += thread_results[arg_num][2];
    }

    printf("%4d %4d %4d\n", total_lines, total_words, total_chars);

    free(tids);
    for (arg_num = 0; arg_num < argc - 1; arg_num++) {
        free(thread_results[arg_num]);
    }
    free(thread_results);

    return 0;
}
