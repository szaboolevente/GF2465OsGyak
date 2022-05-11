#include <stdio.h>
#include <stdlib.h>

int main() {
    int return_value = system("ls");
    printf("Visszatérési érték: %d\n", return_value);

    return_value = system("cm");
    printf("Visszatérési érték: %d\n", return_value);
    
    return 0;
}
