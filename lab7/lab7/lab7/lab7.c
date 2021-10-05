#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct node{
	int accountNumber; 
	char typeOfCapitalization[20];
	char typeOfContribution[20];
	char passportData[20];
	int currentDepositAmount;
	char lastOperationWithAcoount[20];
	struct node* pNext;
	struct node* pPrev;
}Node;
typedef struct informationAboutContributors
{
	Node* head;
	Node* top;
}InformationAboutContributors;

Node* findLateNode(InformationAboutContributors *users, int key) {
	int data1 = 0, data2 = 0;
	Node* currant = users->head;
	Node* laters = NULL;
	while (currant->pNext != NULL)
	{
		if (currant->accountNumber == key) {

			if (data1 == 0) {
				data1 = dataFormat(currant);
				laters = currant;
			}
			else {
				data2 = dataFormat(currant);
			}

			if (data1 != 0 && data2 != 0) {
				if ((data1 - data2) < 0) {
					data1 = data2;
					laters = currant;
				}
			}

		}
		currant = currant->pNext;
	}
	if (currant->accountNumber == key) {

		if (data1 == 0) {
			data1 = dataFormat(currant);
			laters = currant;
		}
		else {
			data2 = dataFormat(currant);
		}

		if (data1 != 0 && data2 != 0) {
			if ((data1 - data2) < 0) {
				data1 = data2;
				laters = currant;
			}

		}
	}
	return laters;
}

int dataFormat(Node* user1) {
	char dayDt[3];
	char monthDt[3];
	char yearDt[3];
	int deltaDay, deltaMonth, deltaYear;
	int k = 0;
	for (int i = 0; i < 8; i++) {
		if (i < 2) {
			dayDt[k] = user1->lastOperationWithAcoount[i];
		}
		if (i < 5 && i>2) {
			monthDt[k] = user1->lastOperationWithAcoount[i];
		}
		if (i < 8 && i>5) {
			yearDt[k] = user1->lastOperationWithAcoount[i];
		}
		if (k == 1) {
			k = -2;
		}
		k++;
	}
	dayDt[2] = '\0';
	monthDt[2] = '\0';
	yearDt[2] = '\0';

	deltaDay = atoi(dayDt);
	deltaMonth = atoi(monthDt);
	deltaYear = atoi(yearDt);
	int result = deltaYear * 365 + deltaMonth * 30 + deltaDay;
	return result;
}

float calculateProcents(int numbersOfYears, Node* user1) {
	float sumThrowYers = user1->currentDepositAmount;
	if (strcmp(user1->typeOfContribution, "savings") == 0)
	{
		if (strcmp(user1->typeOfCapitalization, "withoutC") == 0) {
			for (int i = 0; i < numbersOfYears; i++) {
				sumThrowYers = sumThrowYers + 0.10 * sumThrowYers;
			}
		}
		else if (strcmp(user1->typeOfCapitalization, "withC") == 0)
		{
			for (int i = 0; i < numbersOfYears; i++) {
				sumThrowYers = sumThrowYers + 0.10 * user1->currentDepositAmount;
			}
		}
	}
	else if (strcmp(user1->typeOfContribution, "cumulative") == 0) {

		if (strcmp(user1->typeOfCapitalization, "withoutC") == 0) {
			for (int i = 0; i < numbersOfYears; i++) {
				sumThrowYers = sumThrowYers + 0.05 * sumThrowYers;
			}
		}
		else if (strcmp(user1->typeOfCapitalization, "withC") == 0)
		{
			for (int i = 0; i < numbersOfYears; i++) {
				sumThrowYers = sumThrowYers + 0.05 * user1->currentDepositAmount;
			}
		}
	}
	return sumThrowYers;

}

float interestCalculation(InformationAboutContributors* users,int key,char *data, char* currantData) {
	Node* user1 = findLateNode(users, key);
	char dayUs[3];
	char monthUs[3];
	char yearUs[3] ;

	char dayDt[3] ;
	char monthDt[3];
	char yearDt[3];
	int deltaDay, deltaMonth, deltaYear;
	int k = 0;
	for (int i = 0; i < 8; i++) {
		if (i < 2) {
			dayUs[k] = data[i];
			dayDt[k] = currantData[i];
		}
		if (i < 5 && i>2) {
			monthUs[k] = data[i];
			monthDt[k] = currantData[i];
		}
		if (i < 8 && i>5) {
			yearUs[k] = data[i];
			yearDt[k] = currantData[i];
		}
		if (k == 1) {
			k = -2;
		}
		k++;
	}
	dayUs[2]='\0';
	monthUs[2] = '\0';
	yearUs[2] = '\0';

	dayDt[2] = '\0';
	monthDt[2] = '\0';
	yearDt[2] = '\0';

	deltaDay = abs(atoi(dayUs)- atoi(dayDt));
	deltaMonth = abs(atoi(monthUs) - atoi(monthDt));
	deltaYear = abs(atoi(yearUs) - atoi(yearDt));
	int result = deltaYear * 365 + deltaMonth * 30 + deltaDay;
	int numbersOfYears = result / 365;
	float sumThrowYers;
	sumThrowYers =calculateProcents(numbersOfYears, user1);
	return sumThrowYers;
}

void printInfoCurrant(Node* user) {
	printf("Account number = %d\t", user->accountNumber);
	printf("Type of capitalization of contribution = %s\t", user->typeOfCapitalization);
	printf("Type of contribution = %s\t", user->typeOfContribution);
	printf("Current deposit amount = %d\t", user->currentDepositAmount);
	printf("Last operation with acoount = %s\t", user->lastOperationWithAcoount);
	printf("Passport data = %s\t", user->passportData);
	printf("\n");
}

void printTable(InformationAboutContributors *users) {
	if (users->head != NULL) {
		Node* currant = users->head;
		while (currant->pNext != NULL)
		{
			printInfoCurrant(currant);
			currant = currant->pNext;
		}
		printInfoCurrant(currant);
	}
	else {
		printf("\nYour table is empty\n");
	}
}

void pushBack(InformationAboutContributors* users,Node* node) {
	node->pNext = NULL;
	node->pPrev = NULL;
	Node* currant = (Node*)malloc(sizeof(Node));
	
	currant->accountNumber = node->accountNumber;
	currant->currentDepositAmount = node->currentDepositAmount;
	strcpy(currant->lastOperationWithAcoount, node->lastOperationWithAcoount);
	strcpy(currant->passportData, node->passportData);
	strcpy(currant->typeOfCapitalization, node->typeOfCapitalization);
	strcpy(currant->typeOfContribution, node->typeOfContribution);

	currant->pNext = NULL;
	currant->pPrev = NULL;
	
	if (users->head == NULL) {
		users->head = currant;
		users->top = currant;
	}
	else
	{
		currant->pPrev = users->top;
		users->top->pNext = currant;
		users->top = currant;
	}
}

void accountStatement(InformationAboutContributors *users, int key) {
	Node* currant = users->head;
	int i = 0;
	while (currant->pNext != NULL)
	{
		if (currant->accountNumber == key) {
			printInfoCurrant(currant);
			i++;
		}
		currant = currant->pNext;
	}
	if (currant->accountNumber == key) {
		printInfoCurrant(currant);
		i++;
	}
	if (i == 0) {
		printf("\nNot find key\n");
	}

}

int putMoney(InformationAboutContributors* users, int key, int transferAmount) {
	Node* user1 = findLateNode(users, key);
	if (user1 != NULL) {
		Node currant = { 0,NULL,"",0,"",NULL,NULL };
		currant.accountNumber = user1->accountNumber;
		currant.currentDepositAmount = user1->currentDepositAmount;
		strcpy(currant.lastOperationWithAcoount, "18.04.21 12:44");
		strcpy(currant.passportData, user1->passportData);
		strcpy(currant.typeOfCapitalization, user1->typeOfCapitalization);
		strcpy(currant.typeOfContribution, user1->typeOfContribution);

		currant.pNext = NULL;
		currant.pPrev = NULL;

		if (dataFormat(user1) != dataFormat(&currant)) {
			pushBack(users, &currant);
			users->top->currentDepositAmount += transferAmount;
		}
		else {
			user1->currentDepositAmount += transferAmount;
		}
	}
	else {
		printf("\nNot find key\n");
	}
	
	return 1;
}

int writeOffMoney(InformationAboutContributors* users, int key, int transferAmount) {
	Node* user1 = findLateNode(users, key);
	if (user1 != NULL) {
		Node currant = { 0,NULL,"",0,"",NULL,NULL };
		currant.accountNumber = user1->accountNumber;
		currant.currentDepositAmount = user1->currentDepositAmount;
		strcpy(currant.lastOperationWithAcoount, "18.04.21 12:44");
		strcpy(currant.passportData, user1->passportData);
		strcpy(currant.typeOfCapitalization, user1->typeOfCapitalization);
		strcpy(currant.typeOfContribution, user1->typeOfContribution);

		currant.pNext = NULL;
		currant.pPrev = NULL;

		if (dataFormat(user1) != dataFormat(&currant)) {
			pushBack(users, &currant);
			users->top->currentDepositAmount -= transferAmount;
		}
		else {
			user1->currentDepositAmount -= transferAmount;
		}
	}
	else {
		printf("\nNot find key\n");
	}
	return 1;
}

int transfersOfDeposits(InformationAboutContributors* users, int key1, int key2, int transferAmount)
{
	Node* user1 = findLateNode(users, key1);
	Node* user2 = findLateNode(users, key2);
	if (user1 != NULL && user2 != NULL) {
		if (transferAmount > user2->currentDepositAmount) {
			printf("There are not enough money on the account from which you are transferring money\n");
			return 0;
		}
		else if (transferAmount < 3) {
			printf("Minimum sum that you can transfer is 3$\n");
			return 0;
		}
		else {
			Node currant1 = { 0,NULL,"",0,"",NULL,NULL };
			currant1.accountNumber = user1->accountNumber;
			currant1.currentDepositAmount = user1->currentDepositAmount;
			strcpy(currant1.lastOperationWithAcoount, "18.04.21 12:44");
			strcpy(currant1.passportData, user1->passportData);
			strcpy(currant1.typeOfCapitalization, user1->typeOfCapitalization);
			strcpy(currant1.typeOfContribution, user1->typeOfContribution);
			currant1.pNext = NULL;
			currant1.pPrev = NULL;

			Node currant2 = { 0,NULL,"",0,"",NULL,NULL };
			currant2.accountNumber = user2->accountNumber;
			currant2.currentDepositAmount = user2->currentDepositAmount;
			strcpy(currant2.lastOperationWithAcoount, "18.04.21 12:44");
			strcpy(currant2.passportData, user2->passportData);
			strcpy(currant2.typeOfCapitalization, user2->typeOfCapitalization);
			strcpy(currant2.typeOfContribution, user2->typeOfContribution);
			currant2.pNext = NULL;
			currant2.pPrev = NULL;

			if (dataFormat(user1) != dataFormat(&currant1)) {
				currant1.currentDepositAmount += transferAmount;
				pushBack(users, &currant1);
			}
			else {
				user1->currentDepositAmount += transferAmount;
			}

			if (dataFormat(user2) != dataFormat(&currant2)) {
				currant2.currentDepositAmount -= transferAmount;
				pushBack(users, &currant2);
			}
			else {
				user2->currentDepositAmount -= transferAmount;
			}
			return 1;
		}
	}
	else {
		printf("\nNot find key\n");
		return 0;
	}
	
}

int* InfoAboutVisitors(InformationAboutContributors* users,int arr[]) {
	int cheak = 0;
	for (int i = 0; i < 100; i++) {
		arr[i] = -1;
	}
	Node* currant = users->head;
	Node* p;
	int k = 0;
	while (currant->pNext != NULL)
	{
		p=findLateNode(users, currant->accountNumber);
		for (int i = 0; i < 100; i++) {
			if (arr[i] == p->accountNumber) {
				cheak = 1;
				break;
			}
		}
		if (cheak != 1) {
			arr[k] = p->accountNumber;
			k++;
		}
		cheak = 0;
		currant = currant->pNext;
	}
	p = findLateNode(users, currant->accountNumber);
	for (int i = 0; i < 100; i++) {
		if (arr[i] == p->accountNumber) {
			cheak = 1;
			break;
		}
	}
	if (cheak != 1) {
		arr[k] = p->accountNumber;
		k++;
	}
	return arr;
}

void sumOfBalances(InformationAboutContributors* users) {
	int arr[100];
	InfoAboutVisitors(users, arr);
	Node* p;
	int sum = 0;
	for (int i = 0; i < 100; i++) {
		if (arr[i] == -1) {
			break;
		}
		else {
			p = findLateNode(users,arr[i]);
			sum=sum+p->currentDepositAmount;
		}
	}
	printf("%d", sum);
}

void printKeys(InformationAboutContributors* users, int arr[]) {
	Node* p;

		for (int i = 0; i < 100; i++) {
			if (arr[i] == -1) {
				break;
			}
			else {
				p = findLateNode(users, arr[i]);
				printInfoCurrant(p);
			}
		}
}

void sortingByDeposits(InformationAboutContributors* users) {
	int arr[100];
	InfoAboutVisitors(users, arr);
	int deposits[100];
	Node* p;
	int k = 0;
		for (int i = 0; i < 100; i++) {
			if (arr[i] == -1) {
				break;
			}
			else {
				p = findLateNode(users, arr[i]);
				deposits[k] = p->currentDepositAmount;
				k++;
			}
		}

	int buf = 0;
	
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k - i - 1; j++) {
			if (deposits[j] < deposits[j + 1]) {
				buf = deposits[j];
				deposits[j] = deposits[j + 1];
				deposits[j + 1] = buf;

				buf = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = buf;

			}
		}
	}
	printKeys(users,arr);
}

void printInfoAboutVisitors(InformationAboutContributors* users) {
	int arr[100];
	InfoAboutVisitors(users, arr);
	printKeys(users, arr);
}

void rewind() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void menu() {
	rewind();
	printf("Menu card :\n");
	printf("1)Information about contributors\n2)Operations\n3)Reports\n4)Edit\n5)Exit\n");
}

void operation() {
	rewind();
	printf("Operations :\n");
	printf("1)Transfer money to account\n2)Count money from an account\n3)Transfers between clients\n4)Calculate procents\n5)Memu\n");
}

void informationAboutContributors() {
	rewind();
	printf("Information about contributors :\n");
	printf("1)Dump the entire table\n2)Memu\n");
}

void reports() {
	rewind();
	printf(" Reports :\n");
	printf("1)Statement of the count\n2)List of all clients\n3)Find a client by identification key\n4)Sorting by deposit balances\n5)Sum of all deposits\n6)Memu\n");
}

void edit() {
	rewind();
	printf("Edit :\n");
	printf("1)Push\n2)Remove\n3)Change\n4)Menu\n");
}

void removeNode(InformationAboutContributors* users, int key) {
	Node* currant = users->head;
	Node* prev = NULL;
	while (currant->pNext != NULL) {
		if ((currant->accountNumber == key)&&(currant==users->head)) {
			currant->pNext->pPrev = NULL;
			users->head = currant->pNext;
			free(currant);
			currant = users->head;
		}
		else if ((currant->accountNumber == key) && (currant == users->top)) {
			users->top->pPrev->pNext = NULL;
			users->top = users->top->pPrev;
			free(currant);
			currant = users->head;
		}
		else if ((currant->accountNumber == key) && (currant != users->head) && (currant != users->top)) {
			currant->pNext->pPrev = currant->pPrev;
			currant->pPrev->pNext = currant->pNext;
			free(currant);
			currant = users->head;
		}
		else {
			currant = currant->pNext;
		}
	}
	if ((currant->accountNumber == key) && (currant == users->top) && (currant == users->head)) {
		users->head = NULL;
		users->top = NULL;
	}
	if ((currant->accountNumber == key) && (currant == users->top)&& (currant != users->head)) {
		users->top->pPrev->pNext = NULL;
		users->top = users->top->pPrev;
	}
}

int cheakContriburion1(char str[]) {
	int c = 0;
	if ((strcmp(str, "savings") == 0)|| (strcmp(str, "cumulative") == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

int cheakContriburion2(char str[]) {
	int c = 0;
	if ((strcmp(str, "withC") == 0) || (strcmp(str, "withoutC") == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

int cheakData(char str[]) {

	int deltaDay, deltaMonth, deltaYear;
	int k = 0;
	if (strlen(str) < 8) {
		return 0;
	}
	for (int i = 0; i < 8; i++) {
		if (i < 2) {
			if ((int)str[i] > 57 || (int)str[i] < 48) {
				return 0;
			}
		}
		else if (i < 5 && i>2) {
			if ((int)str[i] > 57 || (int)str[i] < 48) {
				return 0;
			}
		}
		else if (i < 8 && i>5) {
			if ((int)str[i] > 57 || (int)str[i] < 48) {
				return 0;
			}
		}
		else {
			if ((int)str[i] != 46) {
				return 0;
			}
		}
	}
	return 1;
}

int cheakNumber(char str[]) {
	
	for (int i = 0; i < strlen(str); i++) {
		if ((int)str[i] > 57 || (int)str[i] < 48) {
			return 0;
		}
	}
	
	return 1;
}

int main()
{ 	
	InformationAboutContributors users = { NULL,NULL };
	FILE* fp;
	FILE* fwr;
	int k=1;
	int kof = 1;
	char str[255];
	char s[255];
	char fullStr[255];
	char convStr[255];
	char* next = 0;
	fp = fopen("C:\\Education\\IT\\C\\lab7.txt", "r");
	fwr = fopen("C:\\Education\\IT\\C\\output.txt", "w");
	int c = 0;
	char inputStr[255];
	int buf1=0;
	char buf2[255];
	Node* currant1;
	while (!feof(fp))
	{

		fgets(str, 255, fp);
		char* s = strtok_s(str, ",", &next);
		Node currant = { 0,NULL,"",0,"",NULL,NULL };
		do {
			switch (c)
			{
				case 0:
					currant.accountNumber = atoi(s);
				    break;
				case 1:
					strcat(currant.typeOfCapitalization, s);
					break;
				case 2:
					strcat(currant.typeOfContribution, s);
					break;
				case 3:
					strcat(currant.passportData, s);
					break;
				case 4:
					currant.currentDepositAmount = atoi(s);
					break;
				case 5:
					strcat(currant.lastOperationWithAcoount, s);
					break;
			}

			c++;
		} while (s = strtok_s(0, ",", &next));
		c = 0;
		pushBack(&users,&currant);
	}
	int button;
	int button2;
	int button3;
	int key1, key2;
	int money;
	char a;
	int ex = 0;
	menu();
	char s2[255];
	char data[255];
	char currantData[255];
	char* next2 = 0;
	char q;
	while (1)
	{ 
		ex = 0;
		printf("Choose operation = ");
		scanf("%d", &button);
		switch (button)
		{
		case 1:
			while (1)
			{ 
				informationAboutContributors();
				printf("Enter button = ");
				scanf("%d", &button2);
				switch (button2)
				{
				case 1:
					printTable(&users);
					break;
				case 2:
					menu();
					ex=1;
					break;
				default:
					printf("Cheak input");
				}
				if (ex == 1) {
					break;
				}
				scanf(" %s", &a);
			}
			break;
		case 2:
			while (1)
			{
				operation();
				printf("Enter button = ");
				scanf("%d", &button2);
				switch (button2)
				{
				case 1:
					printf("Enter identification key = ");
					scanf("%d", &key1);
					printf("Transfer amount = ");
					scanf("%d", &money);
					putMoney(&users, key1, money);
					break;
				case 2:
					printf("Enter identification key = ");
					scanf("%d", &key1);
					printf("How much do we wwrite off = ");
					scanf("%d", &money);
					writeOffMoney(&users, key1, money);
					break;
				case 3:
					printf("Enter identification key1 = ");
					scanf("%d", &key1);
					printf("Enter identification key2 = ");
					scanf("%d", &key2);
					printf("Transfer amount = ");
					scanf("%d", &money);
					transfersOfDeposits(&users, key1, key2, money);
					break;
				case 4:
					printf("Enter identification key1 = ");
					scanf(" %d", &key1);
					printf("Enter currant data = ");
					scanf(" %s", &currantData);
					printf("Enter data = ");
					scanf(" %s", &data);
					printf("%f",interestCalculation(&users, key1, data, currantData));
					printf("\n");
					break;
				case 5:
					menu();
					ex = 1;
					break;
				default:
					printf("Cheak input");
				}
				if (ex == 1) {
					break;
				}
				scanf(" %s", &a);
			}
			break;
		case 3:
			while (1)
			{
				reports();
				printf("Enter button = ");
				scanf("%d", &button2);
				switch (button2)
				{
				case 1:
					printf("Enter identification key = ");
					scanf("%d", &key1);
					accountStatement(&users, key1);
					break;
				case 2:
					printInfoAboutVisitors(&users);
					break;
				case 3:
					printf("Enter identification key = ");
					scanf("%d", &key1);
					Node* p=findLateNode(&users, key1);
					if (p != NULL) {
						printInfoCurrant(p);
					}
					else {
						printf("\nNot find key\n");
					}
					break;
				case 4:
					sortingByDeposits(&users);
					break;
				case 5:
					sumOfBalances(&users);
					break;
				case 6:
					menu();
					ex = 1;
					break;
				default:
					printf("Cheak input\n");
				}
				if (ex == 1) {
					break;
				}
				scanf(" %s", &a);
			}
			break;
		case 4:
			while (1)
			{
				edit();
				kof = 1;
				printf("Enter button = ");
				scanf("%d", &button2);
				switch (button2)
				{
				case 1:
					printf("Enter str = ");
					scanf(" %s", &inputStr);
					inputStr[strlen(inputStr)] = '\0';
					char *s2 = strtok_s(inputStr, ",", &next2);
					Node currant = { 0,NULL,"",0,"",NULL,NULL };
					do {
						switch (c)
						{
						case 0:
							k = cheakNumber(s2);
							if (k == 0) {
								kof = 0;
							}
							currant.accountNumber = atoi(s2);
							break;
						case 1:
							k = cheakContriburion2(s2);
							if (k == 0) {
								kof = 0;
							}
							strcat(currant.typeOfCapitalization, s2);
							break;
						case 2:
							k = cheakContriburion1(s2);
							if (k == 0) {
								kof = 0;
							}
							strcat(currant.typeOfContribution, s2);
							break;
						case 3:
							strcat(currant.passportData, s2);
							break;
						case 4:
							k = cheakNumber(s2);
							if (k == 0) {
								kof = 0;
							}
							currant.currentDepositAmount = atoi(s2);
							break;
						case 5:
							k=cheakData(s2);
							if (k == 0) {
								kof = 0;
							}
							strcat(currant.lastOperationWithAcoount, s2);
							break;
						}

						c++;
					} while (s2 = strtok_s(0, ",", &next2));
					if (kof != 0) {
						c = 0;
						Node* cheak = findLateNode(&users, currant.accountNumber);
						if (cheak == NULL) {
							pushBack(&users, &currant);
						}
						else {
							printf("We have this person \n");
						}
					}
					else
					{
						c = 0;
						printf("Isnt correct input \n");
					}
					break;
				case 2:
					printf("Enter identification key = ");
					scanf(" %d", &key1);
					removeNode(&users, key1);
					break;
				case 3:
					rewind();
					printf("Enter identification key = ");
					scanf(" %d", &key1);
					Node* p = findLateNode(&users, key1);
					if (p != NULL) {
						Node currant = { 0,NULL,"",0,"",NULL,NULL };

						currant.accountNumber = p->accountNumber;
						currant.currentDepositAmount = p->currentDepositAmount;
						strcpy(currant.lastOperationWithAcoount,"18.04.21 12:44");
						strcpy(currant.passportData, p->passportData);
						strcpy(currant.typeOfCapitalization, p->typeOfCapitalization);
						strcpy(currant.typeOfContribution, p->typeOfContribution);
						currant.pNext = NULL;
						currant.pPrev = NULL;

						printf("1)Type of capitalization of contribution\n2)Type of contribution\n3)Current deposit amount\n4)Passport data\n");
						printf("Select operation = ");
						scanf(" %d", &key2);
						switch (key2)
						{
						case 1:
							scanf(" %s", &buf2);
							k=cheakContriburion2(buf2);
							if (k == 0) {
								kof = 0;
							}
							strcpy(currant.typeOfCapitalization, buf2);
							break;
						case 2:
							scanf(" %s", &buf2);
							k=cheakContriburion1(buf2);
							if (k == 0) {
								kof = 0;
							}
							strcpy(currant.typeOfContribution, buf2);
							break;
						case 3:
							scanf(" %s", &buf2);
							k = cheakNumber(buf2);
							if (k == 0) {
								kof = 0;
							}
							currant.currentDepositAmount = atoi(buf2);
							break;
						case 4:
							scanf("%s", &buf2);
							strcpy(currant.passportData, buf2);
							break;
						default:
							printf("Cheak input\n");
							break;
						}
						if (kof != 0) {
							if (dataFormat(&currant) != dataFormat(p)) {
								pushBack(&users, &currant);
							}
							else {
								p->currentDepositAmount = currant.currentDepositAmount;
								strcpy(p->passportData, currant.passportData);
								strcpy(p->typeOfCapitalization, currant.typeOfCapitalization);
								strcpy(p->typeOfContribution, currant.typeOfContribution);
							}
						}
						else {
							printf("Isnt correct input\n");
						}
					}
					else {
						printf("NotFind key\n");
					}
					
					break;
				case 4:
					menu();
					ex = 1;
					break;
				default:
				
                	printf("Cheak input\n");
				}
				if (ex == 1) {
					break;
				}
				scanf(" %s", &q);
			}
			break;
		case 5:
			currant1 = users.head;
			while (currant1!=NULL)
			{
				strcpy(fullStr, "");
				strcpy(convStr, "");
				_itoa(currant1->accountNumber, convStr, 10);
				strcat(fullStr, convStr);
				strcat(fullStr,"  ");
				strcat(fullStr, currant1->typeOfCapitalization);
				strcat(fullStr, "  ");
				strcat(fullStr, currant1->typeOfContribution);
				strcat(fullStr, "  ");
				strcat(fullStr, currant1->passportData);
				strcat(fullStr, "  ");
				strcpy(convStr, "");
				_itoa(currant1->currentDepositAmount, convStr, 10);
				strcat(fullStr, convStr);
				strcat(fullStr, "  ");
				strcat(fullStr, currant1->lastOperationWithAcoount);
				fprintf(fwr, fullStr);
				fprintf(fwr, "\n");
				currant1 = currant1->pNext;
			}
			fclose(fwr);
			fclose(fp);
			exit(0);
		default:
			printf("Cheak input");
		}

	}
	return 0;
}