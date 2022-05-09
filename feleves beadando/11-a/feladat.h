#ifndef FELADAT_H
#define FELADAT_H

#define FIFO_NAME "myfifo"
// Struktúra az egyenlet adataihoz
struct Equation
{
    int a;
    int b;
    int c;
    double x1;
    double x2;
    int solvable;
};

// Egy sor beolvasása fájlból a read segítségével
int readLine(int file, char *buff, int size)
{
    char ch = ' ';
    int i = 0;
    while (ch != '\n' && ch != '\0' && i < size - 1)
    {
        if (read(file, &ch, 1) <= 0)
        {
            return -1;
        }
        else if (ch != '\n')
            buff[i++] = ch;
    }
    buff[i] = '\0';
    return i;
};

#endif