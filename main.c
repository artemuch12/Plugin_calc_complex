/*Программа модульного комплексного калькулятора*/
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

#define LOT 10		// Отвечает за максимальное количество модулей
#define NUM_SYM 50	// Длина входной строки

struct complex
{
	int real;
    int im;
};

/*Структура необходимая для формирования порядка библиотек подключенных 
 * к программе. Включает в себя порядковый номер подключения, пути к 
 * библиотеке, а также указатель на функции из библиотек. */
struct number_lib	
{
	int count;
	char name_file[NUM_SYM];
	void (*pointers_func)(struct complex *, struct complex *, struct complex *);
};


void enter_number (struct complex *n1, struct complex *n2)
{
	puts("Enter real number 1");
    scanf("%d", &n1->real);
    puts("Enter image number 1");
    scanf("%d", &n1->im);
    puts("Enter real number 2");
    scanf("%d", &n2->real);
    puts("Enter image number 2");
    scanf("%d", &n2->im);
}

void res_print(struct complex *result)
{
	if (result->im > 0)
	{
		printf("Result: %d+%dj\n", result->real,result->im);
	}
	if (result->im < 0)
	{
		printf("Result: %d%dj\n", result->real, result->im);
	}
	if (result->im == 0)
	{
		printf("Result: %d\n", result->real);
	}
}

int main()
{
	int i = 0, j = 0, num_link_lib = 0;
	char directory[NUM_SYM];
	char buffer[NUM_SYM-12];
	int menu;
	void *pointers_lib[LOT];
	struct number_lib spisok[LOT];
	struct complex num1, num2, res;
	
	
	while((i < LOT) && (strcmp(directory,"exit")))
	{
		puts("Enter the directory with the library (Maximum 10 libraries): ");
		fgets(directory, NUM_SYM, stdin);
		for(j = 0; j < NUM_SYM; j++)
		{
			if(directory[j] =='\n')
			{
				directory[j] = '\0';
			} 
		}
		pointers_lib[i] = dlopen(directory, RTLD_NOW);
		if(pointers_lib[i] == NULL)
		{
			puts("Error");
			dlerror();
		}
		else
		{
			puts("Library added");
			spisok[i].count = i+1;
			for(j = 0; j < NUM_SYM; j++)
			{
				spisok[i].name_file[j] = directory[j];
			}
			for(j = 0; j < (NUM_SYM-9); j++)
			{
				buffer[j] = spisok[i].name_file[j+9];
			}
			for(j = 0; j < (NUM_SYM-12); j++)
			{
				if((buffer[j] == '.') && (buffer[j+1] == 's') && (buffer[j+2] == 'o'))
				{
					buffer[j] = '\0';
					buffer[j+1] = '\0';
					buffer[j+2] = '\0';
				}
			}
			spisok[i].pointers_func = dlsym(pointers_lib[i], buffer);
			i++;
			
		}
	}
	num_link_lib = i;
	if(num_link_lib > 0)
	{
		printf("%d libraries connected\n", num_link_lib);
		while (menu != (num_link_lib+1))
		{
			puts("Command: ");
			for(i = 0; i < num_link_lib; i++)
			{
				printf("%d %s\n", spisok[i].count, spisok[i].name_file);
			}
			printf("%d exit\n", num_link_lib+1);
			puts("Enter number command: ");
			scanf("%d", &menu);
			if(menu != num_link_lib+1)
			{
				for(i = 0; i < num_link_lib; i++)
				{
					if(menu == spisok[i].count)
					{
					enter_number(&num1, &num2);
					spisok[i].pointers_func(&num1, &num2, &res);
					res_print(&res);
					}
				}
			}
			else
			{
				puts("The programm is closing!");
				for(i = 0; i < num_link_lib; i++)
				{
					dlclose(pointers_lib[i]);
				}
			}
		}
	}
	else
	{
		puts("Libraries were not connected! The program is closing!");
	}
	
}
