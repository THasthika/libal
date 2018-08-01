#include <stdio.h>
#include "dynamic.h"

int comp_char(void *key1, void *key2)
{
	if(*(char *)key1 > *(char *)key2)
		return 1;
	else if(*(char *)key1 < *(char *)key2)
		return -1;
	else
		return 0;
}

int main(int argc, char const *argv[])
{

    char arr1[] = "abcc";
    char arr2[] = "acbc";

    char *ret;

    int i = AL_longest_common_subsequence(sizeof(char), (void*)arr1, 4, (void*)arr2, 4, comp_char, (void**)&ret);

	printf("%s\n", ret);

    return 0;
}
