#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "feladat.h"

#define INPUT_FILE "input_file"

int main(void)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // Child process
        system("./solve.o");
    }
    else
    {
        int input, output, numberOfEquations, fd, i;

        // Kinyitjuk az input fájlt
        input = open(INPUT_FILE, O_RDONLY);
        if (input < 0)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Beolvassuk az első sort a fájlból
        char buff[1024];
        readLine(input, buff, sizeof(buff));
        numberOfEquations = atoi(buff);

        printf("Egyenletek száma : %d\n", numberOfEquations);

        // Struktúratömb az adatok tárolására
        struct Equation *equations = malloc(numberOfEquations * sizeof(struct Equation));

        // Nevesített csővezeték létrehozása
        if (mkfifo(FIFO_NAME, 00666) < 0)
        {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }

        // Nevesített csővezeték megnyitása
        fd = open(FIFO_NAME, O_WRONLY);
        if (fd < 0)
        {
            perror("open fifo");
            exit(EXIT_FAILURE);
        }

        // Kiolvassuk az adatotak az input fájlból
        i = 0;
        while (i < numberOfEquations && readLine(input, buff, sizeof(buff)) > 0)
        {
            sscanf(buff, "%d %d %d", &equations[i].a, &equations[i].b, &equations[i].c);

            // Elküldjük a csővezetéken keresztül
            sprintf(buff, "%d %d %d %lf %lf %d\n", equations[i].a, equations[i].b, equations[i].c, 0.0, 0.0, 0);

            write(fd, buff, strlen(buff));
            i++;
        }

        // A csővezeték végére egy \0 karaktert teszünk, ez fogja jelezni a csővezeték végét
        buff[0] = '\0';
        write(fd, buff, strlen(buff) + 1);

        // Bezárjuk az input fájlt
        close(input);

        // Felszabadítjuk a struktúratömböt
        free(equations);

        // Bezárjuk az nevesített csővezetéket
        close(fd);

        unlink(FIFO_NAME);
    }
    return 0;
}
