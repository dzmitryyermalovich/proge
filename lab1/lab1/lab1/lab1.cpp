#include <iostream>
#include<math.h>
#include<stdio.h>
using namespace std;

int main()
{

	int n;
	printf("n = ");
	scanf_s("%d", &n);
	int currantDelitel   = 1;
	int sumOfDelitel=0;

	for (int index = 4; index <= n; index++)
	{
		for(int currantDelitel =1; currantDelitel < index; currantDelitel++)
		{
			if (index % currantDelitel == 0)
			{
				sumOfDelitel += currantDelitel;
			}
			
		}

		if (sumOfDelitel == index)
		{
			printf("%d\n", index);
		}
		sumOfDelitel = 0;
	
	}



}
