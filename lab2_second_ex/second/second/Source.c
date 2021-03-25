#include<stdio.h>
#include<math.h>
#include < stdlib.h >

 int calculateCyclicaly(float x,float epsilon)
{
    long float row = 0;

    int temp = 0;
    int i = 1;
    long long int fact = 1;
    float kof=0;
    
    do
     {

         temp = 2 * i - 1;
         for(int j=1;j<=temp;j++)
         {
             fact *= j;
         }

         row = row + pow(-1, (i - 1)) * (pow(x, (2 * i - 1)) / fact);
         fact = 1;
         i++;
         kof = fabs(row - sin(x));

    } while (kof > epsilon);
    printf("result of row in cucle = %f", row);

     return --i;
}

long long int countFact(int temp)
{
 
    if (temp == 1) 
    {
        return 1;
    }
    
    return temp * countFact(temp-1);

}

long double calculateRecurcivno(float x, float epsilon,int i,int numOfIteration)
{
 

    int temp ;
     
    long long int fact;

    temp = 2 * i - 1;

    fact = countFact(temp);
    
    if (i == numOfIteration)
    {
        return pow(-1, (i - 1)) * (pow(x, (2 * i - 1)) / fact);
    }

        return pow(-1, (i - 1)) * (pow(x, (2 * i - 1)) / fact) + calculateRecurcivno(x, epsilon, i + 1, numOfIteration);  
    
}

float decreaseX(long float x)
{

    long float xInGradus;
    xInGradus = (x * 180) / 3.141592653589793238462643;

    if (x > 0) 
    {
        while (xInGradus > 0)
        {

            xInGradus -= 360;


        }
        xInGradus += 360;
    }
    else
    {
        while (xInGradus < 0)
        {

            xInGradus += 360;


        }
        xInGradus -= 360;
    }
    double alpha;
    alpha = (3.14 * xInGradus) / 180;

    return alpha;

    


}

int main()
{

    float p;
    long float x;
    float epsilon;

    printf("x = ");
    scanf_s("%lf", &x);

    printf("epsilon = ");
    scanf_s("%f", &epsilon);


    float rezRecurs;
    int rezCucl;
    int numOfIteration=1;
    double reduceGradus;
    reduceGradus = decreaseX(x);
    printf("\n");

    do
    {
        rezRecurs = calculateRecurcivno(reduceGradus, epsilon, 1, numOfIteration);
        numOfIteration++;

    } while (fabs(sin(reduceGradus)- rezRecurs) > epsilon);


    printf("Result of row recursivno =  %f", rezRecurs);
    printf("\n");
    printf("Num of iteration recursivno %d", --numOfIteration);
    printf("\n\n");
    
    rezCucl = calculateCyclicaly(reduceGradus, epsilon);
    printf("\n");
    printf("Num of iteration cucl %d", rezCucl);
    printf("\n");
}