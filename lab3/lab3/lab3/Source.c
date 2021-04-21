#include<stdio.h>
#include<math.h>
#include<time.h>
#include <conio.h>
#include<malloc.h>
#include<stdlib.h>

int cheak(int **mainMatrix,int size)
{

	for(int i=0;i<size;i++)
	{
		for (int j = 0; j < size; j++) 
		{
			if (*(*(mainMatrix + i) + i) <= *(*(mainMatrix + i) + j)&&(i!=j)) 
			{
				return 0;
			}
		}
	
	}
	return 1;

}

void inverseMatrix(float** mainMatrix, int size, float** matrixY,float ** inverseMatrix)
{
	float epsilon = 0.0001;;
	float** newMatrix = (float*)calloc(size, sizeof(float*));
	float* res = (float*)calloc(size, sizeof(float));
	float* Xn = (float*)calloc(size, sizeof(float));
	for (int i = 0; i < size; i++)
	{
		newMatrix[i] = (int*)calloc(size, sizeof(int));
	}

	for(int i=0;i<size;i++)
	{
	  for(int j=0;j<size;j++)
	  {
		  if (i == j) 
		  {
			  *(*(newMatrix + i) + j) = 0;
		  }
		  else
		  {
		     *(*(newMatrix + i) + j) = -(*(*(mainMatrix + i) + j) / (*(*(mainMatrix + i) + i)));
		  }
	  }
	}
	int k = 0, kNew = 0;;
	int nomer = 0;
	int column = 0;
	while (1)
	{
		int b = 5;
		for (int i = 0; i < size; i++)
		{
			*(res + i) = *(*(matrixY + i) + column) / (*(*(mainMatrix + i) + i));
		}
		while (1)
		{

			for (int i = 0; i < size; i++)
			{
				*(Xn + i) = *(*(matrixY + i) + column) / (*(*(mainMatrix + i) + i));
				for (int j = 0; j < size; j++)
				{
					*(Xn + i) = *(Xn + i)+ *(*(newMatrix + i) + j) * (*(res + j));
				}
			}
			for (int i = 0; i < size; i++)
			{
				if (fabs(*(Xn + i) - *(res + i)) < epsilon)
				{
					nomer++;
					if (nomer == size)
					{
						nomer = 0;
						k++;
					}
				}

			}

			if(k-kNew!=0)
			{
				for(int i=0;i<size;i++)
				{
					*(*(inverseMatrix + i) + kNew) = *(Xn + i);
				}
				kNew = k;
				break;
			}

			for (int i = 0; i < size; i++)
			{
				*(res + i) = *(Xn + i);
			}

		}
		column++;
		if(column==size)
		{
			
			printf("\n\n");
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					printf("%f ", *(*(inverseMatrix + i) + j));
				}
				printf("\n");
			}
			
			break;
		}
	}
	
	free(res);
	free(Xn);
	for (int i = 0; i < size; i++)
	{
		free(newMatrix[i]);
	}
	free(newMatrix);
	
}

int main()
{
	srand(time(NULL));

	int n;
	printf("n = ");

	scanf_s("%d", &n);

	float** mainMatrix = (float**)calloc(n,sizeof(float*));
	float** matrixY = (float**)calloc(n, sizeof(float*));
	float** inverseMat = (float**)calloc(n, sizeof(int*));
	int r;
	for(int i=0;i<n;i++)
	{
		mainMatrix[i] = (float*)calloc(n,sizeof(float));
		matrixY[i] = (float*)calloc(n, sizeof(float));
		inverseMat[i] = (float*)calloc(n, sizeof(float));
	}
	int buf;
	while (1) {
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				r = rand() % 20 + 1;
				*(*(mainMatrix + i) + j) = r;
				if (i == j)
				{
					*(*(matrixY + i) + j) = 1;
				}
				else
				{
					*(*(matrixY + i) + j) = 0;
				}

			}
		}
		buf=cheak(mainMatrix, n);
		if(buf==1)
		{
			break;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%f ", *(*(mainMatrix + i) + j));
		}
		printf("\n");
	}

	inverseMatrix(mainMatrix, n, matrixY, inverseMat);
	
	for (int i = 0; i < n; i++) 
	{
		free(mainMatrix[i]);
		free(matrixY[i]);
		free(inverseMat[i]);

	}
	free(mainMatrix);
	free(matrixY);
	free(inverseMat);
	

}