#include <stdio.h>
#include <stdlib.h>

int main() {

    char command[128];

    while (1) {
        printf("Adjon egy olyan parancsot, amely vegrehajthato!\n");
        scanf("%s", command);
        printf("A %s parancs eredménye:\n", command);
        system(command);
    }

    return 0;
}
