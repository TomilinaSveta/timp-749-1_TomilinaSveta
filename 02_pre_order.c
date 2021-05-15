#include <stdio.h>
#include <stdlib.h>

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

// Для вывода нужен прямой обход, а значит нужен стек
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

node_list* pop_first(list *l) //вернуть последнее значение списка
{
    node_list *temp = l->head; //начинаем с начала списка
    if (temp == NULL) //если список пуст
        return NULL; //то вернуть NULL
    if (temp->next != NULL) //если это не последний элемент в списке
        temp->next->prev = NULL; //обновляем предыдущий элемент у следующего
    l->head = temp->next; //обновляем начало списка
    return temp; //возвращаем первый элемент
}

void pre_order(tree *t) //Вывод прямым обходом с помощью стека
{
    list *l = NULL; //создаю очередь
    l = malloc(sizeof(list)); //выделяю память очереди
    init_list(l); //инициализирую
    node *temp; //создаем хранилище текущего узла дерева
    push_front(l, t->head); //вставляем корень дерева в стек
    while(l->head != NULL) //пока список не пуст
    {
        node_list* temp_list = pop_first(l); //забираем первое значение в списке
        temp = temp_list->value; //сохраняем узел от него
        free(temp_list); //очищаем память от записи списка
        while(temp != NULL) //пока текущий узел не будет пуст
        {
            printf("%d ", temp->value); //выводим значение узла
            if(temp->right) //если есть правый потомок
                push_front(l, temp->right); //то вставляем его в стек
            temp = temp->left;  //переходим в левому потомку
        }
    }
}


int main() {
    //1
    tree *t = NULL;
    t = malloc(sizeof(tree));
    init(t);
    int a;
    for (int i = 0; i < 7; i++){
        scanf("%d",&a);
        insert(t, a);
    }
    //2
    pre_order(t);
    return 0;
}
