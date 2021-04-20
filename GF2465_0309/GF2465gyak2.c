#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){

	char valtozo[10];
	printf("Adjon meg egy parancsot:");
	scanf("%s", valtozo);
	system(valtozo);

return 0;
}
