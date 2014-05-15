#include <stdio.h>
#include <stdlib.h>
# include <math.h>
# include <string.h>
#include <ctype.h>
#include <conio.h>

#define N 1000

int isPowOfTwo(int);
void mainMenu();

int main(int argc, char **argv)
{
	mainMenu(); // Вывод главного меню.
	char user = '1';
	
	while (1)
	{
		scanf("%c", &user);
		int count = 0; // Количество лишних символов.
		while (getchar()!='\n') count++;
		
		while (!isdigit(user) || user - '0' < 1 || user - '0' > 3 || count > 0)
		{
			printf("Select an item: ");
			scanf("%c", &user);
			count = 0;
			while (getchar()!='\n') count++;
		}
	
		switch (user - '0')
		{
			case 1:
				printf("-------------------------\n");
				printf(" Hamming Code Simulation\n");
				printf("-------------------------\n");
				printf("Input a word: ");
				char data[N]; // Входные данные.
				gets(data); 

				int j = 0;	// Основной счетчик.
				int correct = 1; // Флаг корректности введенных данных (0 - имеется ошибка, 1 - данные корректны).
				
				while (j < strlen(data) && correct) // Проверка корректности введенных данных (может быть только 0/1).
				{
					if (!isdigit(data[j]) || (data[j] - '0' != 0 && data[j] - '0' != 1)) correct = 0;
					j++;
				}
				
				while (!correct)
				{
					printf("ERROR: Incorrect word.\n");
					printf("Input a word: ");
					gets(data); 
					
					j = 0;
					correct = 1;
					
					while (j < strlen(data) && correct) // Проверка корректности введенных данных (может быть только 0/1).
					{
						if (!isdigit(data[j]) || (data[j] - '0' != 0 && data[j] - '0' != 1)) correct = 0;
						j++;
					}
				}
				
				int i = strlen(data); // Число информационных разрядов.
				int r = 0; // Число проверочных разрядов.
				while (pow(2, r) < r + i + 1) r++;
				int n = i + r; // Общее число разрядов.
				
				int *res = (int *)malloc(n*sizeof(int)); // Результирующее кодовое слово.
				
				int jData = 0; // Счетчик для прохода по массиву исходных данных.

				// Первичное заполнение данными результирующего массива.
				j = 0;
				while (j < n) 
				{
					if (isPowOfTwo(j+1)) res[j] = 0; // Заполнение проверочных разрядов нулями.
					else // Перенос информационных разрядов в результирующий код.
					{
						res[j] = data[jData] - '0';
						jData++;
					}
					j++;
				}
				
				// Расчет значений проверочных разрядов.
				int num = 1; // Номер проверочного разряда. 
				for (j=0; j<n; j++)
				{
					if (isPowOfTwo(j+1)) // Если текущий бит - проверочный.
					{
						int sum = 0; // Сумма бит, контролируемых этим проверочным разрядом.
						int k;
						for (k = j; k < n; k += pow(2, num)) // Вычисление суммы.
						{
							int q;
							for (q = k; q < n && q < k + pow(2, num-1); q++)
								sum = sum + res[q];
						}
						res[j] = sum % 2;
						num++;
					}
				}
				
				printf("Hamming code: ");
				for (j=0; j<n; j++)
					printf("%d", res[j]);
				printf("\n");
				
				char err;
				printf("\nInput the index of error: ");
				scanf("%c", &err);
				count = 0;
				while (getchar()!='\n') count++;
				
				while (!isdigit(err) || count > 0)
				{
					count = 0;
					printf ("ERROR: Index must be a natural number.\n");
					printf("Input the index of error: ");
					scanf("%c", &err);
					while (getchar()!='\n') count++;
				}
				while (err - '0' < 0 || err - '0' >= n)
				{
					while (getchar()!='\n');
					printf ("%d\n", n);
					printf ("ERROR: The index must be included in the interval [%d; %d].\n", 0, n-1);
					printf("Input the index of error: ");
					scanf("%c", &err);
				}

				if (res[err -'0']) res[err -'0'] = 0; else res[err -'0'] = 1; // Генерация ошибки в коде.
				
				printf("\nIncorrect code: ");
				for (j=0; j<n; j++)
					printf("%d", res[j]);
				printf("\n");
				
				int syndrome = 0;
				int index = 0;
				num = 1;
				for (j=0; j<n; j++)
				{
					if (isPowOfTwo(j+1)) // Если текущий бит - проверочный.
					{
						syndrome = 0;
						int k;
						for (k = j; k < n; k += pow(2, num)) // Вычисление суммы.
						{
							int q;
							for (q = k; q < n && q < k + pow(2, num-1); q++)
							{
								syndrome += res[q];
							}
						}
						syndrome %= 2;
						if (syndrome != 0) index += (j+1);
						num++;
					}
				}
				
				index--;	
				printf("Error was found. Index: %d\n", index);
				if (res[index]) res[index] = 0; else res[index] = 1; // Исправление ошибки.
				
				printf("Correct code: ");
				for (j=0; j<n; j++)
					printf("%d", res[j]);
				printf("\n");
				
				free(res);
				
				printf("\nInput any symbol to exit to main menu: ");
				getch();
				while (getchar()!='\n');
				system("cls");
				mainMenu();
			
				break;
			
			case 2:
				printf("-------------------------\n");
				printf("   About the program\n");
				printf("-------------------------\n");
				printf("Authors:\n");
				printf("\tIvashkova K.P.,\n");
				printf("\tIgnatova U.A.,\n");
				printf("\tOsadchaya T.S.,\n");
				printf("\tPutintseva A.A..\n");
				printf("University ITMO, Department of Instrumentation Technology, Group 2652.\n");
				printf("Saint-Petersburg, 2014\n");
				
				printf("\nInput any symbol to exit to main menu: ");
				while (getchar()!='\n');
				getch();
				while (getchar()!='\n');
				system("cls");
				mainMenu();
				
				break;
				
			case 3:
				printf("-------------------------\n");
				printf("  Program was finished\n");
				printf("-------------------------\n");
				return 0;
			
		}
	}
	return 0;
}

int isPowOfTwo(int a)
{
	return (fmod(log2(a), 1) == 0);
}

void mainMenu()
{
	printf("*** Welcome to Hamming Code Simulation! ***\n");
	printf("1 - Begin the simulation\n");
	printf("2 - About the program\n");
	printf("3 - Exit\n");
	printf("Select an item: ");
}