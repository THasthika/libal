#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "rbt.h"

void fn(void *data)
{
	int a = *(int*)data;
	printf("%d\n", a);
}

int main(int argc, char **argv)
{
	return 0;
}
