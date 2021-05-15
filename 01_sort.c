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

void quicksort(int a[], int l, int r, int n) //быстрая сортировка
{
    if (r - l < 1) //если левая граница больше или равна правой
        return;
    int center = a[l + (r - l) / 2]; //установка центрального элемента как опорного
    int i = l; //запоминаем левую границу
    int j = r; //запоминаем правую границу
    int t; //переменная для замены
    while(i < j) //пока левая граница меньше правой
    {
        while(a[i] < center) //находим слева элемент не меньше центрального
            i++;
        while(a[j] > center) //находим справа элемент не больше центрального
            j--;
        if(i <= j) //если левая не больше правой границы, то происходит замена
        {
            t = a[i];
            a[i++] = a[j];
            a[j--] = t;
            logger("quicksort.log", a, n, 0); //логгирование без создания нового файла
        }
    }
    quicksort(a, l, j, n); //рекурсивный вызов левой оставшейся части
    quicksort(a, i, r, n); //рекурсивный вызов правой оставшейся части
}

// Функция "просеивания" через кучу - формирование кучи
void heapify(int a[], int top, int bottom, int n)
{
    int maxChild; // индекс максимального потомка
    int done = 0; // флаг того, что куча сформирована
    while ((top * 2 <= bottom) && (!done)) // Пока не дошли до последнего ряда
    {
        if (top * 2 == bottom)    // если мы в последнем ряду,
            maxChild = top * 2;    // запоминаем левый потомок
        else if (a[top * 2] > a[top * 2 + 1]) // иначе запоминаем больший потомок из двух
            maxChild = top * 2;
        else
            maxChild = top * 2 + 1;
        // если элемент вершины меньше максимального потомка
        if (a[top] < a[maxChild])
        {
            int temp = a[top]; // меняем их местами
            a[top] = a[maxChild];
            a[maxChild] = temp;
            top = maxChild;
        }
        else // иначе
            done = 1; // пирамида сформирована
        logger("heapsort.log", a, n, 0);
    }
}

void heapsort(int a[], int n)
    {
    // Формируем нижний ряд пирамиды
    for (int i = n / 2; i >= 0; i--)
        heapify(a, i, n - 1, n);
    // Просеиваем через пирамиду остальные элементы
    for (int i = n - 1; i >= 1; i--)
    {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapify(a, 0, i - 1, n);
    }
}

int main(){
    //1
    int n;
    scanf("%d", &n);
    int a[n], b[n];
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    logger("quicksort.log", a, n, 1); //логгирование с созданием файла
    quicksort(a, 0, n - 1, n);

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");

    //2
    logger("heapsort.log", a, n, 1); //логгирование с созданием файла
    heapsort(b, n);
    
    for (int i = 0; i < n; i++)
        printf("%d ", b[i]);
    return 0;
}
