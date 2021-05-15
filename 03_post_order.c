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

void post_order(node *temp) //Вывод обратным обходом с помощью рекурсии
{
    if(temp == NULL) //если этого элемента не существует
        return;
    post_order(temp->left); //запускаем рекурсию для левого поддерева
    post_order(temp->right); //запускаем рекурсию для правого поддерева
    printf("%d ", temp->value); //выводим значение текущего элемента
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
    post_order(t->head);
    return 0;
}
