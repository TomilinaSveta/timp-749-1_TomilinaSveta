#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node { //узел
    int value; //значение
    struct node *left; //левый потомок
    struct node *right; //правый потомок
    struct node *parent; //предок
} node;

typedef struct tree { //дерево
    int num; //количество узлов
    struct node *head; //корень дерева
} tree;


// Инициализация дерева
void init(tree *t){
    t->head = NULL;
    t->num = 0;
}

// Удалить все элементы из дерева
void clean(tree *t)
{
    while(t->num > 1) //пока не останется только корень
    {
        node *temp = t->head; //в temp указатель на корень
        while(temp->left != NULL || temp->right != NULL) //пока справа или слева есть потомок
        {
            if(temp->left != NULL) //если слева есть потомок
                temp = temp->left; //идем налево
            else
                temp = temp->right; //иначе идем направо
        }
        node *parent = temp->parent; //сохраняем указатель на предка
        if(parent->left == temp) //если temp является левым элементом предка
            parent->left = NULL; //то у parent убираем указатель на левого потомка
        else
            parent->right = NULL; //иначе указатель на правого
        free(temp); //очищаем память
        t->num--; //уменьшаем количество узлов на единицу
    }
    if(t->head != NULL){ //Проверка, не пусто ли дерево изначально
        free(t->head); //очистка памяти
        t->head = NULL; //указываем, что кореня нет
        t->num = 0; //изменяем число узлов
    }
}

// Поиск элемента по значению
node* find(tree *t, int value)
{
    node *temp = t->head; //сохраняем корень в temp
    while(temp != NULL && temp->value != value) //пока не наткнемся на пустой узел или на нужный
    {
        if(value < temp->value) //если нужное значение меньше, чем текущее
            temp = temp->left; //то переходим в левого потомка
        else
            temp = temp->right; //иначе переходим в правого потомка
    }
    return temp; //возвращаем либо  узел с нужным значением, либо NULL, если ничего не найдено
}

// Вставка значения в дерево
int insert(tree *t, int value)
{
    if(t->head == NULL) //если дерево пустое
    {
        t->head = malloc(sizeof(node)); //выделяем память
        t->head->parent = NULL; //задаем пустыми значениями предка
        t->head->left = NULL; //левого потомка
        t->head->right = NULL; //и правого потомка
        t->head->value = value; //сохраняем значение
        t->num++; //увеличиваем количество узелов на единицу
        return 0; //успешно
    }

    node *temp = t->head; //сохраняем в temp корень дерева
    while(temp->value != value) //пока не найдем уже существующее значение
    {
        if(value > temp->value) //если вставляемое значение больше текущего
        {
            if(temp->right != NULL) //если узел существует
            {
                temp = temp->right; //то переходим к правому потомку, а потом к началу цикла
            }
            else //иначе добавляем значение
            {
                temp->right = malloc(sizeof(node)); //выделяем память
                temp->right->value = value; //сохраняем значение
                temp->right->parent = temp; //указываем новому элемента temp как на предка
                temp->right->right = NULL; //задаем пустыми правого потомка
                temp->right->left = NULL; //и левого потомка
                t->num++; //увеличиваем количество узлов на единицу
                return 0; //успешно
            }
        }
        else //если вставляемое значение меньше текущего
        {
            if(temp->left != NULL) //если узел существует
            {
                temp = temp->left; //то переходим к левому потомку, а потом к началу цикла
            }
            else //иначе добавляем значение
            {
                temp->left = malloc(sizeof(node)); //выделяем память
                temp->left->value = value; //сохраняем значение
                temp->left->parent = temp; //указываем новому элемента temp как на предка
                temp->left->right = NULL; //задаем пустыми правого потомка
                temp->left->left = NULL; //и левого потомка
                t->num++; //увеличиваем количество узлов на единицу
                return 0; //успешно
            }
        }
    }
    return 1; //значение уже существует
}

// Удалить элемент из дерева
int remove_node(tree *t, int value)
{
    node *temp = find(t, value); //находим элемент в дереве по значению
    if(temp == NULL) //если такого элемента не существует
        return 1;
    if(temp->left == NULL && temp->right == NULL) //если у удаляемого элемента нет потомков
    {
        node *parent = temp->parent; //запоминаем предка
        if(parent == NULL) //если удаляемый элемент является корнем
            t->head = NULL; //указываем, что корня нет
        else //иначе
        {
            if(parent->left == temp) //если удаляемый элемент является левым элементом предка
                parent->left = NULL; //указываем, что левого потомка больше нет
            else
                parent->right = NULL; //указываем, что правого потомка больше нет
        }
        free(temp); //очищаем память
        t->num--; //уменьшаем количество узлов на единицу
        return 0; //успешно
    }
    else if(temp->right != NULL && temp->left == NULL) //если есть только правый потомок
    {
        node *parent = temp->parent; //запоминаем родителя
        if(parent == NULL)  //если удаляемый элемент является корнем дерева
        {
            t->head = temp->right; //корнем теперь является правый потомок
            t->head->parent = NULL; //устанавливаем предка пустым для нового корня
        }
        else //иначе
        {
            if(parent->left == temp) //если удаляемый элемент является  левым элементом предка
                parent->left = temp->right; //указываем на новый левый элемент
            else
                parent->right = temp->right; //указываем на новый правый элемент
        }
        temp->right->parent = parent; //указываем у нового элемента родителя
        free(temp); //очищаем память
        t->num--; //уменьшаем количество узлов на единицу
        return 0; //успешно
    }
    else if(temp->right == NULL && temp->left != NULL) //если есть только левый потомок
    {
        node *parent = temp->parent; //запоминаем родителя
        if(parent == NULL) //если удаляемый элемент является корнем дерева
        {
            t->head = temp->left; //корнем теперь является левый потомок
            t->head->parent = NULL; //устанавливаем предка пустым для нового корня
        }
        else //иначе
        {
            if(parent->left == temp) //если удаляемый элемент является  левым элементом предка
                parent->left = temp->left; //указываем на новый левый элемент
            else
                parent->right = temp->left; //указываем на новый правый элемент
        }
        temp->left->parent = parent; //указываем у нового элемента родителя
        free(temp); //очищаем память
        t->num--; //уменьшаем количество узлов на единицу
        return 0; //успешно
    }
    else //если есть оба потомка
    {
        node *max = temp->left; //запоминаем левый элемент у удаляемого
        while(max->right != NULL) //пока не найдем самый большой (правый) элемент
            max = max->right; //переходим направо
        if (max->parent == temp) //если левый элемент и есть максимальным
            temp->left = max->left; //сохраняем левого потомка у max как левого потомка для удаляемого
        else
            max->parent->right = max->left; //переводим левого потомка у max как правого у его родителя
        //правого потомка незачем перемещать, так как max и есть самый правый

        node *parent = temp->parent; //сохраняем родителя удаляемого элемента
        if(parent == NULL) //если удаляемый элемент является корнем
            t->head = max; //то заменяем на максимальный элемент левого поддерева
        else //иначе
        {
            if(parent->left == temp) //если удаляемый элемент является левым элементом предка
                parent->left = max; //указываем на новый левый элемент
            else
                parent->right = max; //указываем на новый правый элемент
        }
        max->parent = parent; //устанавливаем у нового элемента родителя, а также
        max->right = temp->right; //правый элемент
        max->left = temp->left; //левый элемент
        max->right->parent = max; //меняем у правого элемента родителя на новый
        if(max->left != NULL) //если существует левый элемент
            max->left->parent = max; //устанавливаем у него родителя
        free(temp); //очищаем память
        t->num--; //уменьшаем количество узлов на единицу
        return 0; //успешно
    }
}

// Выполнить правое вращение поддерева, корнем которого является temp
int rotate_right(tree *t, node *temp)
{
    if(temp == NULL || temp-> left == NULL) //если элемент пустой или левого потомка нет
        return 1; //то вращение невозможно

    node *rightofnew = temp->left->right; //запоминаем правого потомка у левого потомка
    node *parent = temp->parent; //запоминаем родителя
    if(parent == NULL) //если поворачиваемый элемент является корнем
    {
        t->head = temp->left; //изменяем корневой элемент на левого потомка
        t->head->parent = NULL; //устанавливаем предка пустым для нового корня
        temp->parent = t->head; //изменяем родителя для прошлого корня
    }
    else //иначе
    {
        if(parent->left == temp) //если поворачиваемый элемент является левым элементом предка
            parent->left = temp->left; //изменяем левый элемент у предка
        else //иначе
            parent->right = temp->left; //изменяем правый элемент у предка
        temp->left->parent = temp->parent; //меняем родителя у нового корня поддерева
        temp->parent = parent; //меняем родителя у поворачиваемого элемента
    }
    temp->left->right = temp; //помещаем поворачиваемый элемент как правый для нового корня поддерева
    temp->left = rightofnew; //помещение этого узла как левого потомка для повернутого
    if(rightofnew != NULL) //если новый левый потомок не пустой
        rightofnew->parent = temp; //то устанавливаем у него предка
    return 0; //успешно
}

// Выполнить левое вращение поддерева, корнем которого является n
int rotate_left(tree *t, node *temp)
{
    if(temp == NULL || temp->right == NULL)//если элемент пустой или правого потомка нет
        return 1; //то вращение невозможно
    node *leftofnew = temp->right->left; //запоминаем левого потомка у правого потомка
    node *parent = temp->parent; //запоминаем родителя
    if(parent == NULL) //если поворачиваемый элемент является корнем
    {
        t->head = temp->right; //изменяем корневой элемент на правого потомка
        t->head->parent = NULL; //устанавливаем предка пустым для нового корня
        temp->parent = t->head; //изменяем родителя для прошлого корня
    }
    else //иначе
    {
        if(parent->left == temp) //если поворачиваемый элемент является левым элементом предка
            parent->left = temp->right; //изменяем левый элемент у предка
        else //иначе
            parent->right = temp->right; //изменяем правый элемент у предка
        temp->right->parent = temp->parent; //меняем родителя у нового корня поддерева
        temp->parent = parent; //меняем родителя у поворачиваемого элемента
    }
    temp->right->left = temp; //помещаем поворачиваемый элемент как левый для нового корня поддерева
    temp->right = leftofnew; //помещение этого узла как правого потомка для повернутого
    if(leftofnew != NULL) //если новый левый потомок не пустой
        leftofnew->parent = temp; //то устанавливаем у него предка
    return 0; //успешно
}


// Для вывода нужно обходить в ширину, а значит нужна очередь
// Двусвязный список
typedef struct node_list { //узел
    node *value; //значение
    struct node_list *next; //следующий узел
    struct node_list *prev; //предыдущий узел
} node_list;

typedef struct list { //список
    struct node_list *head; //головной узел
    struct node_list *tail; //хвостовой узел
} list;

void init_list(list *l)
{
    l->head = NULL;
    l->tail = NULL;
}

int push_front(list *l, node *value) //вставить в начало
{
    node_list *temp = malloc(sizeof(node_list)); //создаем элемент temp
    temp->value = value; //в него сохраняем значение
    temp->next = l->head; //устанавливаем указатель следующего элемента на тот, что раньше был головным
    temp->prev = NULL; //устанавливаем указатель предыдущего элемента на NULL (никакой элемент не предшествует)
    if (l->head)
        l->head->prev = temp;
    l->head = temp; //делаем созданный элемент головным
    if (l->tail == NULL)
        l->tail = temp;
    return 0; //успешно
}

int remove_last(list *l) //будет выведен и удален последний элемент
{
    node_list *temp = l->tail;
    if (temp == NULL) //если очередь пуста
        return -1; //то невозможно удалить элемент
    if (temp->prev != NULL) //если это не единственный элемент в очереди
        temp->prev->next = NULL; //передаем информацию о конце к предыдущему элементу
    else //иначе
        l->head = NULL; //передаем информацию о конце к списку
    l->tail = temp->prev; //передаем информацию о предыдущем элементе к списку
    if (temp->value != NULL)
    {
        printf("%d ", temp->value->value); //вывод значения
        free(temp); //освобождаем память
    }
    else //иначе
    {
        int numNULL = 0; //запоминаем число NULL, которое было встречено
        while (temp->value == NULL){ //пока не наткнемся на значащий элемент
            numNULL++; //прибавляем количество встреченных NULL
            free(temp); //освобождаем память
            temp = l->tail; //переходим к следующему элементу в очереди
            if (temp == NULL || temp->value != NULL) //если очередь пуста или если есть значещие элементы
                break; //то выходим из цикла
            if (temp->prev != NULL) //если это не единственный элемент в очереди
                temp->prev->next = NULL; //передаем информацию о конце к предыдущему элементу
            else //иначе
                l->head = NULL; //передаем информацию о конце к списку
            l->tail = temp->prev; //передаем информацию о предыдущем элементе к списку
        }
        return numNULL; //возвращает количество выведенных элементов
    }
    return 0; //успешно
}


// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке.
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _.
// Если дерево пусто, вывести -
void print(node *n)
{
    if (n == NULL) //если корень поддерева пустой
    {
        printf("-\n"); //то вывести "-"
    }
    else //иначе
    {
        int counter = 0; //счетчик выведенных элементов на уровне
        int max = 1; //максимум элементов на текущем уровне
        list *l = NULL; //создаем очередь
        l = malloc(sizeof(list)); //выделяем память
        init_list(l); //инициализируем очередь
        push_front(l, n); //добавляем корень
        while (l->tail != NULL) //пока очередь не пуста
        {
            node *temp = l->tail->value; //сохраняем значение об элементе в очереди
            if (temp != NULL) //если элемент не пуст
            {
                push_front(l, temp->left); //то добавляем его в очередь
                push_front(l, temp->right); //то добавляем его в очередь
                remove_last(l); //выводим и удаляем потомка из очереди
                counter++; //увеличиваем счетчик на единицу
            }
            else //иначе
            {
                int number = remove_last(l); //удаляем пустой элемент и узнаем, сколько вывелось
                if (counter != 0 || l->tail != NULL) //если счетчик не равен нулю или если очередь не пуста
                {
                    for(int i = 0; i < number && i + counter < max; i++) //для каждого встреченного пустого элемента
                    {
                        push_front(l, NULL); //вставляем два пустых на следующем уровне
                        push_front(l, NULL);
                        printf("_ "); //выводим пустой элемент
                    }
                    if (l->tail != NULL && l->tail->value != NULL && number + counter > max) //если очередь не пуста, а пустые элементы были не все выведены
                    {
                        printf("\n"); //переходим на пустую строку
                        for (int i = max; number + counter > i; i++) //продолжаем для каждого встреченного пустого
                        {
                            push_front(l, NULL); //вставляем два пустых на следующем уровне
                            push_front(l, NULL);
                            printf("_ "); //выводим пустой элемент
                        }
                        counter -= max; //обновляем счетчик
                        max *= 2; //обновляем максимальное число, так как уже перешли на нвоый уровень
                    }
                    counter += number; //то прибавляем это значение к счетчику
                }
            }
            if (counter >= max) //если вывели все элементы на уровне, то переходим на следующий
            {
                max *= 2; //количество максимальных элементов на уровне увеличивается в два раза
                counter = 0; //счетчик элементов обнуляется
                printf("\n"); //переход на новую строку
            }
        }
    }
    printf("\n"); //вывод пустой строки, как окончания вывода
}

// Вывести все значения дерева t
void print_tree(tree *t)
{
    print(t->head);
}

//Вывод предка и потомков
void print_about(tree *t, int value)
{
    node *n = find(t, value); //находим элемент по значению
    if(n == NULL) //если элемента нет
        printf("-\n\n"); //то печатаем "-"
    else //иначе
    {
        if(n->parent != NULL) //если предок не пустой
            printf("%d ", n->parent->value); //то печатаем его
        else //иначе
            printf("_ "); //печатаем "_" вместо предка

        if(n->left != NULL) //если левый потомок не пустой
            printf("%d ", n->left->value); //то печатаем его
        else //иначе
            printf("_ "); //печатаем "_" вместо предка

        if(n->right != NULL) //если левый потомок не пустой
            printf("%d\n\n", n->right->value); //то печатаем его
        else //иначе
            printf("_\n\n"); //печатаем "_" вместо предка
    }
}

int main() {
    //1
    int a[4];
    scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);

    tree *t = NULL;
    t = malloc(sizeof(tree));
    init(t);
    for(int i = 0; i < 4; i++)
        insert(t, a[i]);
    //2
    print_tree(t);
    //3
    scanf("%d %d %d", &a[0], &a[1], &a[2]);
    for(int i = 0; i < 3; i++)
        insert(t, a[i]);
    //4
    print_tree(t);
    //5
    int m;
    scanf("%d", &m);
    print_about(t, m);
    //6
    scanf("%d", &m);
    print_about(t, m);
    //7
    scanf("%d", &m);
    remove_node(t, m);
    //8
    print_tree(t);
    //9
    while(rotate_left(t, t->head) != 1);
    //10
    print_tree(t);
    //11
    while(rotate_right(t, t->head) != 1);
    //12
    print_tree(t);
    //13
    printf("%d\n\n", t->num);
    //14
    clean(t);
    //15
    print_tree(t);
    return 0;
}
