#include <stdio.h>

int main(int ac, char **av)
{
	int count = 1;
	av++;
	while(*av)
		printf("cmd[%d]=%s\n",count++,*(av++));

}
