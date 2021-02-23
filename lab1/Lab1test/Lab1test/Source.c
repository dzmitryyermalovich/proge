#include<math.h>
#include<stdio.h>

int main()
{

	long long int n;
	printf("n = ");
	scanf_s("%lld", &n);
	long long int currantValue = 2;
	long long int newValue = 2;
	int metka = 0;

	for (int index = 2; index <= 1000; index++)
	{
		newValue = pow(2, index) - 1;

		for (long long int j = 2; j <= (newValue / 2); j++)
		{
			if (newValue % j == 0)
			{
				metka = 1;
				break;
			}
		}


		if (metka != 1)
		{
			currantValue = pow(2, (index - 1)) * (pow(2, index) - 1);

			if (n >= currantValue)
			{
				printf("%lld\n", currantValue);
			}
			else
			{
				break;
			}
		}



		metka = 0;
	}



}