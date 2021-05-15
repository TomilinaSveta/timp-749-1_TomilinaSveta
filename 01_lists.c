#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node { //узел
    int value; //значение
    struct node *next; //следующий узел
    struct node *prev; //предыдущий узел
} node;

typedef struct list { //список
    struct node *head; //головной узел
    struct node *tail; //хвостовой узел
} list;


void init(list *l)
{
    l->head = NULL;
    l->tail = NULL;
}

bool is_empty(list *l) //проверяет, является ли список пустым
{ //true - является, false - нет
    return l->head == NULL; //если указатель на голову списка равен NULL, вернем true, иначе false
}

int push_front(list *l, int value) //вставить в начало
{
    node *temp = malloc(sizeof(node)); //создаем элемент temp
    temp->value = value; //в него сохраняем значение
    temp->next = l->head; //устанавливаем указатель следующего элемента на тот, что раньше был головным
    temp->prev = NULL; //устанавливаем указатель предыдущего элемента на NULL (никакой элемент не предшествует)
    if (l->head)
        l->head->prev = temp;
    l->head = temp; //делаем созданный элемент головным
    if (l->tail == NULL)
        l->tail = temp;
    return 0; //0 если успешно
}

int push_back(list *l, int value) //вставить в конец
{
    node *temp = malloc(sizeof(node)); //создаем элемент temp
    temp->value = value; //в него сохраняем значение
    temp->next = NULL; //устанавливаем указатель следующего элемента на NULL
    temp->prev = l->tail; //в качестве указателя на предыдущий берем прошлый хвост
    if (l->tail)
        l->tail->next = temp;
    l->tail = temp; //делаем созданный элемент конечным
    if (l->head == NULL)
        l->head = temp;
    return 0;
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

node *find_last(list *l, int value) //поиск последнего элемента по значению
{
    node *temp = l->tail; //сохраняем указатель на хвост самписка
    while (temp != NULL) //пока не добрались до значения NULL
    { //перебираем значения из списка
        if (temp->value == value) //если значение из списка совпало с запрошенным
            return temp; //возвращаем запись
        temp = temp->prev;//переходим на предыдущий элемент
    }
    return NULL; //возвращает NULL, если нужное значение не было найдено
}

int remove_first(list *l, int value) //удалить первый элемент с указанным значением
{
    node *temp = find(l, value); //находим первый элемент с таким значением
    if (temp == NULL) //если не нашли
        return 1; //невозможно удалить элемент
    if (temp->prev != NULL) //если наше значение не находится вначале списка
        temp->prev->next = temp->next; //передаем информацию о предыдущем элементе следующему
    temp->next->prev = temp->prev; //передаем информацию следующему о предыдущем
    free(temp); //освобожадем память
    return 0; //если успешно
}

int remove_last(list *l, int value) //удалиться последний элемент с указанным значением
{
    node *temp = find_last(l, value); //находим последний элемент с таким значением
    if (temp == NULL) //если не нашли
        return 1; //невозможно удалить элемент
    temp->prev->next = temp->next; //передаем информацию о предыдущем элементе следующему
    if (temp->next != NULL) //если наш элемент не находится в конце списка
        temp->next->prev = temp->prev; //передаем информацию следующему о предыдущем
    free(temp); //освобожадем память
    return 0; //если успешно
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

int insert_after(int value, int position, list *l)
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
    newNode->prev = temp; //тогда temp элемент становится предудщим
    if (temp->next != NULL) //если мы вставляем элемент не в самый конец
        temp->next->prev = newNode; //следующему элементу передаем информацию о том, что добавленный элемент становится предыдущим
    else //если в самый конец
        l->tail = newNode; //то узел становится хвостом
    temp->next = newNode; //следующему узлу передаем указатель новой записи
    return 0; //0 если успешно
}

int insert_before(int value, int position, list *l)
{
    if (position > length(l)) //если вставить значение на место большее, чем количество элементов в списке
        return 1;
    node *temp = l->head; //в temp сохраняем указатель на голову списка
    //перемещаемся до нужной позиции
    for (int i = 0; i < position - 1; i++)
        temp = temp->next;
    node *newNode = malloc(sizeof(node)); //создаем новую запись
    newNode->value = value; //вставляем в нее значение из value
    newNode->next = temp; //следующий элементом становится temp
    newNode->prev = temp->prev; //предыдущим тот, что предшествовал temp
    if (temp->prev != NULL) //если мы вставляем не в самое начало
        temp->prev->next = newNode; //для предыдущего у temp следующим становится вставленный узел
    else //иначе
        l->head = newNode; //узел становится головой
    temp->prev = newNode; //предыдущим для temp становится вставленный узел
    return 0;
}

void print(list *l) //метод для вывода списка
{
    node *temp = l->head; //стартуем с head
    while (temp != NULL) {//пока следующий элемент не окажется нулевым
        printf("%d ", temp->value); //выводим текущее значение
        temp = temp->next; //передаем указатель на следующий элемент
    }
    printf("\n"); //перенос строки
}

void print_invers(list *l) //метод для вывода инверсированного списка
{
    node *temp = l->tail; //стартуем с хвоста
    while (temp != NULL) //пока предыдущий элемент не окажется нулевым
    {
        printf("%d ", temp->value); //выводим текущее значение
        temp = temp->prev; //передаем указатель на предыдущий элемент
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
    //1
    int n;
    scanf("%d", &n); //вводим количество элементов
    //2
    list *l = NULL; //создаем список
    l = malloc(sizeof(list));
    init(l); //инициализируем список
    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a); //вводим a
        push_back(l, a); //вставляем в конец списка
    }
    //3
    print(l); //вывод списка
    //4
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
    //5
    int m;
    scanf("%d", &m); //вводим элемент m
    push_back(l, m); //вставляем элемент в конец списка
    //6
    print_invers(l); //выводим список в инвертированном порядке
    //7
    int t;
    scanf("%d", &t); //вводим элемент t
    push_front(l, t); //вставляем элемент в начало списка
    //8
    print(l); //вывод списка
    //9
    int j, x;
    scanf("%d%d", &j, &x); //вводим значение элемента x и место, после которого вставляем
    insert_after(x, j, l); //вставляем значение x после jго элемента
    //10
    print_invers(l); //выводим список в инвертированном порядке
    //11
    int u, y;
    scanf("%d%d", &u, &y); //вводим значение элемента y и место, перед которым вставляем
    insert_before(y, u, l); //вставляем значение y перед uым элементом
    //12
    print(l); //вывод списка
    //13
    int z;
    scanf("%d", &z); //вводим значение, которое хотим удалить
    remove_first(l, z); //удаляет первое значение, равное z
    //14
    print_invers(l); //выводим список в инвертированном порядке
    //15
    int r;
    scanf("%d", &r); //вводим значение, которое хотим удалить
    remove_last(l, r); //удаляет первое значение, равное r
    //16
    print(l); //выводим список
    //17
    clean(l); //очищаем список
    return 0;
}