#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char cheak[100];
    while (1) 
    {
        char str1[100];
        char str2[100];
        gets(str1);
        int b, capacity;
        int k;
        double n = strlen(str1);
        b = round((n / 2));
        capacity = round(n);

        if (b >= 41) {
            b = 41;
        }

        for (int i = 0; i < 41 - b; i++)
        {
            str2[i] = ' ';
        }

        k = 0;

        for (int i = 41 - b; i < 41 - b + capacity; i++)
        {
            str2[i] = str1[k];
            k++;
        }

        int u = 41 - b + capacity;
        str2[u] = '\0';
        printf("%s", str2);
        printf("\nEnter operation ");
        gets(cheak);
        if (!strcmp(cheak, "exit")) {
            break;
        }
    }
}