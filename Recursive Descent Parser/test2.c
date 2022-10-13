#include<stdio.h>
#include<stdlib.h>

main () 
{
	int a, ar[10];
	char c;
	int i, j, counter, flag;
    counter = 0;
    flag = 0;
	for(i = 0 ; i < 10 ; i = i + 1)
	{
		for(j = 0; j < 10; j = j + 1)
		{
			if(j<2)
			{
				counter = 1;
			}
		}
		if(counter == 1)
		{
			flag = 1;
        }
	}
}