#include <iostream>
#include <cstdlib> 
#include <ctime>
using namespace std; 

struct Stack {
    int info;
    Stack* next;
} *begin;

Stack* InStack(Stack* p, int in) {
    Stack* t = new Stack;			
    t->info = in;			
    t->next = p;			
    return t;
}

void View(Stack* p) {
    Stack* t = p;
    while (t != NULL) {
        cout << t->info << " ";
        t = t->next;
    }
    cout << endl;
}
void Del_All(Stack** p) {
    Stack* t;
    while (*p != NULL) {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}
void Sort_p(Stack** p) {
    Stack* t = NULL, * t1, * r;
    if ((*p)->next->next == NULL) return;
    do {
        for (t1 = *p; t1->next->next != t; t1 = t1->next)
            if (t1->next->info > t1->next->next->info) {
                r = t1->next->next;
                t1->next->next = r->next;
                r->next = t1->next;
                t1->next = r;
            }
        t = t1->next;
    } while ((*p)->next->next != t);
}
void Sort_info(Stack* p) {
    Stack* t = NULL, * t1;
    int r;
    do {
        for (t1 = p; t1->next != t; t1 = t1->next)
            if (t1->info > t1->next->info) {
                r = t1->info;
                t1->info = t1->next->info;
                t1->next->info = r;
            }
        t = t1;
    } while (p->next != t);
}
int LessAvg(Stack* p) {
    if (p == NULL)
        return 0;
    int sum = 0;
    int count = 0;
    Stack* cur = p;

    while (cur != NULL) {
        sum += cur->info;
        count++;
        cur = cur->next;
    }

    double avg = static_cast<double>(sum) / count;
    cout <<"Среднее: " << avg << endl;
    int lessAvg = 0;
    cur = p;
    while (cur != NULL) {
        if (cur->info < avg)
            lessAvg++;
        cur = cur->next;
    }

    return lessAvg;
}

Stack* RemLessAvg(Stack** p) {
    if (*p == NULL)
        return NULL;

    int sum = 0;
    int count = 0;
    Stack* a = *p;

    while (a != NULL) {
        sum += a->info;
        count++;
        a = a->next;
    }

    double avg = static_cast<double>(sum) / count;

    Stack* prev = NULL;
    Stack* newStack = NULL;
    a = *p;
    while (a != NULL) {
        if (a->info < avg) {
            Stack* temp = a;
            if (prev == NULL) {
                *p = a->next;
                a = a->next;
                temp->next = newStack;
                newStack = temp;
            }
            else {
                prev->next = a->next;
                a = a->next;
                temp->next = newStack;
                newStack = temp;
            }
        }
        else {
            prev = a;
            a = a->next;
        }
    }
    return newStack;
}

int main()
{
    srand(time(NULL));
    Stack* stack = NULL;
    for (int i = 0; i < 10; i++) {
        int value = rand() % 101 - 50;
        stack = InStack(stack, value);
    }
    cout << "Начальный стек: ";
    View(stack);

    cout << "Cтек после 1 сортировки: ";
    Sort_p(&stack);
    View(stack);
    cout << "Cтек после 2 сортировки: ";
    Sort_info(stack);
    View(stack);
    int lessavg = LessAvg(stack);
    cout << "Количество элементов, меньших среднего: " << lessavg << endl;
    Stack* removedStack = RemLessAvg(&stack);
    cout << "Стек после удаления элементов, меньших среднего: ";
    View(stack);
    cout << "Удаленные элементы: ";
    View(removedStack);
    Del_All(&stack);
    Del_All(&removedStack); 
}