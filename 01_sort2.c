#include <stdio.h>
#include <stdlib.h>

void logger(char tag[], int message[], int n, int creating) //логгирование действий
{
    FILE *fp; //создание
    if (creating) //если файл нужно создать
        fp = fopen(tag, "w"); //то он создается
    else //иначе
        fp = fopen(tag, "a"); //он записывается
    for (int i = 0; i < n; i++) //для каждого числа в массиве
    { 
        fprintf(fp, "%d", message[i]); //вывести его
        fprintf(fp, " ");
    }
    fprintf(fp, "\n"); //перейти на новую строку
    fclose(fp); //закрыть поток
}

//Сортировка Шелла
void Shellsort(int a[], int n)
{
    int step = n / 2; //шаг для разделения массива на группы
    while (step > 0) //пока шаг не стал нулевым
    {
        for (int i = 0; i < n - step; i++) //пока проверка текущего со следующим возможна
        {
            int j = i; //запоминаем номер текущего элемента
            while (j >= 0 && a[j] > a[j + step]) //если следующий элемент меньше, то используем метод вставок
            {
                int temp = a[j]; //замена переменных
                a[j] = a[j + step];
                a[j + step] = temp;
                j-= step; //смотрим предыдущий элемент для вставки
                logger("Shellsort.log", a, n, 0); //логгирование
            }
        }
        step = step / 2; //уменьшение шага в два раза
    }
}

//Сортировка "Расчёской"
void combsort(int a[], int n)
{
    double factor = 1.2473309; //универсальный фактор уменьшения
	int step = n - 1; //задание шага размером с массив
	while (step > 0) //пока шаг не стал нулевым
	{
		for (int i = 0; i < n - step; i++) //пока сравнение текущего со следующим возможна
		{
			if (a[i] > a[i + step]) //метод пузырька - самый большой элемент всплывает
			{
			    int temp = a[i]; //замена переменных
			    a[i] = a[i + step];
			    a[i + step] = temp;
			    logger("combsort.log", a, n, 0); //логгирование 
			}
		}
		step /= factor; //уменьшение шага
	}
}

int main(){
    int n; //ввод количества элементов массива
    scanf("%d", &n);
    int a[n], b[n];
    for (int i = 0; i < n; i++) //заполнение массива
    { 
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    //Сортировка Шелла
    logger("Shellsort.log", a, n, 1); //логгирование с созданием файла
    Shellsort(a, n);

    for (int i = 0; i < n; i++) //вывод сортированного массива
        printf("%d ", a[i]);

    printf("\n");

    //Сортировка "Расчёской"
    logger("combsort.log", a, n, 1); //логгирование с созданием файла
    combsort(b, n);
    
    for (int i = 0; i < n; i++) //вывод сортированного массива
        printf("%d ", b[i]);
    return 0;
}
