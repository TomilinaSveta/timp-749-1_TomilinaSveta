#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node { //создаем структуру node и определяем ее как новый тип данных
    int value; //значение элемента
    struct node *next; //ссылка на следующий элемент
} node; //даем этому типу данных имя node

typedef struct list { //создаем структуру list и определяем ее как новый тип
    struct node *head; //начало списка
} list; //даем этому типу название list

//инициализация пустого списка
void init(list *l)
{
    l->head = NULL;
}

bool is_empty(list *l) //проверяет, является ли список пустым
{ //true - является, false - нет
    return l->head == NULL; //если указатель на голову списка равен NULL, вернем true, иначе false
}

node *find(list *l, int value) //поиск элемента по значению
{
    node *temp = l->head; //в temp сохраняем указатель на голову списка
    while (temp != NULL) //пока не добрались до значения NULL
    { //перебираем значения из списка
        if (temp->value == value) //если значение из списка совпало с запрошенным
            return temp; //возвращаем запись
        temp = temp->next; //переходим на следующий элемент
    }
    return NULL; //возвращает NULL, если нужное значение не было найдено
}

int insert_after(node *n, int value) //вставляет значение value после узла n
{
    if (n == NULL) //если узла не сущетсвует
        return 1; //возвращает 1

    node *newNode = malloc(sizeof(node)); //создаем новую запись
    newNode->value = value; //вставляем в нее значение из value
    newNode->next = n->next; //передаем указатель из прошлого узла
    n->next = newNode; //следующему узлу передаем указатель новой записи
    return 0; //0 если успешно
}

int length(list *l) //определяет длину списка
{
    int len = 0; //задаем начальную длину, равную 0
    node *temp = l->head; //определяем указатель на головной элемент
    while (temp != NULL) //пока не дойдем до NULL
    {
        len++; //увеличиваем счетчик элементов
        temp = temp->next; //переходим на следующий
    }
    return len; //возвращаем длину списка
}

int insert_after_position(int position, int value, list *l) //вставляем значение value на позицию position в списке l
{
    if (position > length(l)) //если вставить значение на место большее, чем количество элементов в списке
        return 1;
    node *temp = l->head; //в temp сохраняем указатель на голову списка
    //перемещаемся до нужной позиции
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;
    node *newNode = malloc(sizeof(node)); //создаем новую запись
    newNode->value = value; //вставляем в нее значение из value
    newNode->next = temp->next; //передаем указатель из прошлого узла
    temp->next = newNode; //следующему узлу передаем указатель новой записи
    return 0; //0 если успешно
}

int remove_node(list *l, int value) //удаляет первое значение, равное value
{
    if (is_empty(l)) //если список пуст
        return 1; //1 - если не успешно
    if (l->head->next == NULL) //если указатель на следующий элемент равен NULL
    { //т.е. всего один элемент в списке
        if (l->head->value == value) //если текущий элемент равен требуемому
        {
            free(l->head); //освобождаем память
            l->head = NULL; //устанавливаем указатель на голову списка равный NULL
            return 0; //0 если успешно
        }
        else
        {
            return 1; //1 если не успешно
        }
    }
    node *temp = l->head; //в temp сохраняем указатель на голову списка
    while (temp->next != NULL) //пока указатель на следующий элемент не равен NULL
    {
        if (temp->next->value == value) //если значение в следующем элементе равно требуемому
        {
            node *oldNode = temp->next; //запоминаем указатель на следующий элемент
            temp->next = temp->next->next; //в указатель на следуюший элемент передаем указатель на следующий следующий
            free(oldNode); //освобождаем память под текущий
            return 0; //0 - если успешно
        }
        temp = temp->next; //переходим на следующий элемент
    }
    return 1; //1 - если не успешно
}

//вставка значения в начало списка, вернуть 0, если успешно
int push_front(list *l, int value)
{
    node *temp = l->head; //сохраняем в temp указатель на голову списка
    l->head = malloc(sizeof(node)); //выделяем память
    l->head->value = value; //передаем значение
    l->head->next = temp; //делаем указатель на предыдущий элемент, который становится следующим
    return 0; //0 если успешно
}

//вставка значения в конец списка
int push_back(list *l, int value)
{
    if (is_empty(l)) //если список пуст
    {
        l->head = malloc(sizeof(node)); //выделяем память
        l->head->value = value; //вставляем значение
        l->head->next = NULL; //делаем указатель на NULL
        return 0; //0 если успешно
    }
    //если список не пуст
    node *temp = l->head; //получаем указатель на голову списка
    while (temp->next != NULL) //перебираем все элементы, пока не дойдем до конца
        temp = temp->next; //перебор указателей
    temp->next = malloc(sizeof(node)); //выделяем память
    temp->next->value = value; //вставляем значение
    temp->next->next = NULL; //делаем указатель на NULL
    return 0; //0 если успешно
}

//вывести все значения из списка в прямом порядке через пробел,
//после окончания вывода перейти на новую строку
void print(list *l) //метод для вывода списка
{
    node *temp = l->head; //стартуем с head
    while (temp != NULL) {//пока следующий элемент не окажется нулевым
        printf("%d ", temp->value); //выводим текущее значение
        temp = temp->next; //передаем указатель на следующий элемент
    }
    printf("\n"); //перенос строки
}

//удалить все элементы из списка
void clean(list *l)
{
    node* temp = NULL; //создаем пустую запись
    while (l->head->next != NULL) //пока следующий элемент не равен NULL
    {
        temp = l->head; //сохарянем в temp указатель на голову списка
        l->head = l->head->next; //в указатель на голову списка заносим указатель на следующий элемент
        free(temp); //освобождаем память под текущий
    }
    free(l->head); //освобождаем память под последний элемент
    l->head = NULL; //устанавливаем указатель на голову списка равный NULL
}


int main()
{
    int n;
    scanf("%d", &n); //вводим количество элементов
    list *l = NULL; //создаем список
    l = malloc(sizeof(list));
    l->head = NULL;
    init(l);
    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a); //вводим a
        push_back(l, a); //вставляем в конец списка
    }
    print(l); //вывод списка
    int k1, k2, k3;
    scanf("%d%d%d", &k1, &k2, &k3); //вводим три элемента
    if (find(l, k1) == NULL) //проверяем первый элемент k1
        printf("%d ", 0); //если нет в списке, выводим 0
    else
        printf("%d ", 1); //если есть в списке - выводим 1
    if (find(l, k2) == NULL) //проверяем второй элемент k2
        printf("%d ", 0); //если нет в списке, выводим 0
    else
        printf("%d ", 1); //если есть в списке - выводим 1
    if (find(l, k3) == NULL) //проверяем третий элемент k3
        printf("%d\n", 0); //если нет в списке, выводим 0
    else
        printf("%d\n", 1); //если есть в списке - выводим 1
    int m;
    scanf("%d", &m); //вводим элемент m
    push_back(l, m); //вставляем элемент в конец списка
    print(l); //выводим список
    int t;
    scanf("%d", &t); //вводим элемент t
    push_front(l, t); //вставляем элемент в начало списка
    print(l);
    int j, x;
    scanf("%d%d", &j, &x); //вводим значение элемента x и место, после которого вставляем
    insert_after_position(j, x, l); //вставляем значение x на позицию j в списке l
    print(l); //выводим список
    int z;
    scanf("%d", &z); //вводим значение элемента
    remove_node(l, z); //удаляет из списка значение z
    print(l); //выводим список
    clean(l); //очищаем список
    return 0;
}