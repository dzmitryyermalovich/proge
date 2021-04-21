#include<math.h>
#include<stdio.h>

void  pickUpTarif(double comfortLCost,double comfortMCost, double withOutCost)
{
	float arr[3];
	arr[0] = comfortLCost;
	arr[1] = comfortMCost;
	arr[2] = withOutCost;
	float min=arr[0];
	int  k = 0;

	for (int i = 1; i < 3; i++) 
	{
		if (arr[i] < min) 
		{
			
			k = i;
			min = arr[i];
		}
	}

	switch (k)
	{
	case 0:

		printf("Your tarif is comfortL,price is = %.3f", comfortLCost);
		break;

	case 1:

		printf("Your tarif is comfortM,price is = %f.3", comfortMCost);
		break;

	case 2:

		printf("Your tarif is Without Limits,price is = %.3f", withOutCost);
		break;

	}


	
}

float withOut(double incomingCalls, double outLine, int sms)
{
	float inCall = 0.052;
	float outCall = 0.104;
	float smsKof = 0.078;

	float allCalls, cost = 0;
	allCalls = incomingCalls + outLine;

	allCalls -= 500;

	if (allCalls <= 0) 
	{
		cost += 0;
	}
	else
	{
		cost = cost + allCalls * ((0.052 + 0.104) / 2);
	}
	cost = cost + smsKof * sms;
	cost += 25.89;
	return cost;
}

float comfortM(double outLine, int sms)
{
	
	float outCall = 0.104;
	float smsKof = 0.078;

	float cost = 0;
	

	outLine -= 120;

	if (outCall <= 0)
	{
		cost += 0;
	}
	else
	{
		cost = cost + outCall * outLine;
	}
	cost = cost + smsKof * sms;
	cost += 21.73;
	return cost;
}

float comfortL(int sms)
{

	float smsKof = 0.078;
	float cost = 0;
	cost = cost + smsKof * sms;
	cost += 31.09;
	return cost;
}

void showAllTarifs()
{
	printf("1) Without limits: cost is 25.89,incomingCalls = 0.052,outCalls = 0.104,500 free min,sms = 0.078\n2) Comfort M:cost is 21.73 incomingCalls=0,outCalls = 0.104 and free 120 min,sms = 0.078\n3) Comfort L:cost is 31.09,all calls are free\n");
}

void feedBack()
{

	printf("If you have questions call 411\n");

}

int main()
{
	float incomingCalls, outgoingCalls, callsToLandline,outLine;
	int sms;

	int n;

	printf("Feature : \n1) Calculate tarif\n2) Show all tarifs\n3) Feedback\n\n");

	int f=0;

	while (1)
	{
		printf("\nselect feature = ");
		scanf_s("%d", &n);
		switch (n)
		{
		case 1:

			printf("incomingCalls = ");
			scanf_s("%f", &incomingCalls);

			printf("outgoingCalls = ");
			scanf_s("%f", &outgoingCalls);

			printf("callsToLandline = ");
			scanf_s("%f", &callsToLandline);

			printf("sms = ");
			scanf_s("%d", &sms);

			outLine = outgoingCalls + callsToLandline;

			double cost1, cost2, cost3;

			cost1 = comfortL(sms);
			cost2 = comfortM(outLine, sms);
			cost3 = withOut(incomingCalls, outLine, sms);
			pickUpTarif(cost1, cost2, cost3);
			break;

		case 2:
			showAllTarifs();
			break;
		case 3:
			feedBack();
			break;

		}
		printf("\n");
		printf("If you want to exit press 0 : ");

		scanf_s("%d", &f);

		if(f==0)
		{
			break;
		}

	}
	
}