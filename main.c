#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

typedef struct node
{
    int id;
    struct node*next;
} list;

void create_L (list*head)
{
    list*tmp = head ;

    for (int i = 0; i < 6; i++)
    {
        list*p = (list*)malloc(sizeof(list));

        tmp->next = p;
        p->next = NULL;
        p->id = 1 + rand()%20;
        tmp = tmp->next;
    }
}

void push(list**head, int x)
{
    list*tmp = (list*) malloc(sizeof(list));
    tmp->id = x;
    tmp->next = (*head)->next;
    (*head)->next = tmp;
}

int pop(list **head)
{
    list* tmp = NULL;
    int val;
    tmp = (*head);
    val = tmp->id;
    (*head) = (*head)->next;
    free(tmp);
    return val;
}

   void list_print(list*head)
{
list *p;
p = head->next;
do
{
printf("%d ", p->id);
p = p->next;
}
while (p != NULL);
}

void insert_before(list* bef_el, list* prev_bef_el, int znach)
{
    list* new_el = (struct list*)malloc(sizeof(list));
    new_el->id = znach;
    new_el->next=bef_el;
    prev_bef_el->next=new_el;
}
void insert_after(list* af_el, list*next_el, int znach)
{
    list* new_el = (struct list*)malloc(sizeof(list));
    new_el->id = znach;
    new_el->next=next_el;
    af_el->next=new_el;
}
void insert_end(int znach, list* head)
{
    list* tmp =head;
    list* new_el = (struct list*)malloc(sizeof(list));
    new_el->id = znach;

    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_el;
    new_el->next = NULL;
}

void delete_given(list*del_prev)
{
    del_prev->next =del_prev->next->next;
}

void delete_last(list*last_prev)
{
    last_prev->next = NULL;
    free(last_prev->next);
}

list*search(int bef, list* head, int flag)
{
    list* tmp = head;

    while (tmp->next != NULL)
    {
        if (flag == 0)
        {
            if (tmp->id == bef)
            {
                return tmp;
            }
        }
        else if (tmp->next->id == bef)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    if (tmp->id == bef)
        return tmp;
    return NULL;
}

int indiv(list*head)
{
    list* tmp = head;

    int sum_chet= 0, i=0;
    while (tmp->next != NULL)
    {
        i++;
        if (i%2==0)
            sum_chet += tmp->id;
        tmp = tmp->next;
    }
    i++;
   if (i%2==0)
    sum_chet += tmp->id;

    return sum_chet;
}

int main()
{

    setlocale(LC_ALL, "Rus");

    int n,ch2,znach,znach2,c=5;

    list* head =(struct list*)malloc(sizeof(list));
    list* el =(struct list*)malloc(sizeof(list));

    head->id= 0;
    head->next = NULL;

    create_L(head);
    list_print(head);

    while(c!=0)
    {

        printf("\nЧто требуется сделать со списком? 1-добавить элемент, 2-удалить элемент, 3-индивидуальное задание,0-выход\n");
        scanf("%d", &c);

        switch (c)
        {
        case 1:
            printf("Введите id нового элемента\n");
            scanf("%d", &znach);
            printf("1-в начало, 2-до заданного элемента, 3-после заданного элемента, 4-в конец \n");
            scanf("%d", &ch2);

            switch (ch2)
            {

            case 1:
                push(&head, znach);
                list_print(head);
                break;

            case 2:
                if (head->next == NULL)
                {
                    printf("Список пуст, добавьте элемент\n");

                }
                else
                {
                    printf("Введите значение искомого элемента\n");
                    scanf("%d", &znach2);

                    el = search(znach2, head, 1);

                    insert_before(el->next, el, znach);
                    list_print(head);

                }
                break;

            case 3:
                if (head->next == NULL)
                {
                    printf("Список пуст, добавьте элемент \n");

                }
                else
                {
                    printf("Введите значение искомого элемента\n");
                    scanf("%d", &znach2);

                    el = search(znach2, head, 0);

                    insert_after(el, el->next, znach);
                    list_print(head);
                }
                break;
            case 4:
                insert_end(znach, head);
                list_print(head);

                break;
            }
            break;
        case 2:
            if (head->next == NULL)
            {
                printf("Список пуст, добавьте элемент\n");

            }
            else
            {
                printf("1-первый, 2-заданный элемент, 3-последний\n ");
                scanf("%d", &ch2);

                switch (ch2)
                {
                case 1:

                    pop(&head);
                    list_print(head);
                    break;

                case 2:
                    printf("Введите значение искомого элемента\n");
                    scanf("%d", &znach2);

                      el = search(znach2, head, 1);
                    delete_given(el);
                    list_print(head);


                    break;

                case 3:
                    el = head;
                    while (el->next->next != NULL)
                    {
                        el = el->next;
                    }
                    delete_last(el);
                    list_print(head);
                    break;
                }
            }
            break;
        case 3:
            printf("Сумма элементов, стоящих на четных местах:\n");
            printf("%d",indiv(head->next));
            break;
        }

    }

    return 0;
}
