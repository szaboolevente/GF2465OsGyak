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


#define OUTPUT_FILE "output_file"

// Másodfokú egyenlet megoldása
void solve(struct Equation *eq)
{
    double d = (double)(eq->b * eq->b - 4 * eq->a * eq->c);
    if (d < 0 || eq->a == 0)
    {
        eq->x1 = 0;
        eq->x2 = 0;
        eq->solvable = 0;
    }
    else
    {
        eq->x1 = (double)(-eq->b + sqrt(d)) / (2 * eq->a);
        eq->x2 = (double)(-eq->b - sqrt(d)) / (2 * eq->a);
        eq->solvable = 1;
    }
}

int main(void)
{
    // Kinyitjuk az output fájlt
    int output = open(OUTPUT_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    // Nevesített csővezeték megnyitása
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0)
    {
        perror("open fifo");
        exit(EXIT_FAILURE);
    }

    if (output < 0)
    {
        printf("Fail to open output file\n");
        exit(1);
    }

    // Soronként kiolvassuk a csővezeték tartalmát
    int i = 0;
    char buff[1024];

    while (readLine(fd, buff, sizeof(buff)) > 0 )
    {
        // Ha a csővezeték végére érünk kilépünk a cikluból
        if (buff[0] == '\0')
            break;

        // Számmá konvertáljuk a kiolvasott sort
        struct Equation readFromPipe;
        sscanf(buff, "%d %d %d %lf %lf %d", &readFromPipe.a, &readFromPipe.b, &readFromPipe.c, &readFromPipe.x1, &readFromPipe.x2, &readFromPipe.solvable);
        solve(&readFromPipe);

        if (readFromPipe.solvable)
        {
            // Ha megoldható az egyenlet, akkor kiírjuk az output fájlba
            sprintf(buff, "%d %d %d %lf %lf\n", readFromPipe.a, readFromPipe.b, readFromPipe.c, readFromPipe.x1, readFromPipe.x2);
        }
        else
        {
            // Ha nem megoldható, akkor hibaüzenetet írunk ki
            sprintf(buff, "%d %d %d No solution\n", readFromPipe.a, readFromPipe.b, readFromPipe.c);
        }

        // Kiírjuk az adatokat az output fájlba
        write(output, buff, strlen(buff));
        printf("%s", buff);
        i++;
    }


    // Bezárjuk az output fájlt
    close(output);
     // Bezárjuk az nevesített csővezetéket
    close(fd);
    unlink(FIFO_NAME);
}