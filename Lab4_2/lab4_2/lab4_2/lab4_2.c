#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS

void process(char str[]){
	for (int i = 65; i <= 90; i++) {
		for (int j = 0; j < strlen(str); j++) {
			if ((int)str[j] == i) {
				str[j] = (char)i + 32;
			}
		}
	}
}

int main()
{
	FILE* fp;
	char str[255];
	int index = 0;
	fp = fopen("C:\\Education\\Rubish\\data.txt", "r");
	char buf;
	while (!feof(fp))
	{
		buf = fgetc(fp);
		str[index] = buf;
		index++;
	}
	str[index] = '\0';
	index++;

	int arr[30];
	int k = 0;
	int l = 0;
	process(str);
	for (int i = 97; i < 123; i++) 
	{
	   for(int j=0;j<strlen(str);j++)
	   {
		   if ((int)str[j] == i) 
		   {
			   k++;
		   }
	   }
	   arr[l] = k+1;
	   l++;
	   k = 0;
	}

	int lin = 0;
	for (int i = 0; i < l; i++) 
	{
		printf("%d", (arr[i]-1));
		printf("\n");
	}
	printf("\n");
	for(int i=0;i<l;i++)
	{

		if(arr[i-1]>arr[i]&&(i!=0))
		{
			lin = arr[i-1];
		}
		else 
		{
			lin = arr[i];
		}
		for (int j = 0; j < lin; j++)
		{
			printf("-");
		}
		printf("\n");

		for (int j = 0; j < arr[i]; j++)
		{
			if (j == (arr[i] - 1))
			{
				printf("|");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}

	for (int j = 0; j < arr[l-1]; j++)
	{
		printf("-");
	}

	fclose(fp);
	return 0;
}