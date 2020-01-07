#include <stdio.h>
#include <stdlib.h>

struct List {
    double v;
    struct List * next;
};

struct List * list_new() {
    struct List * l = malloc(sizeof(struct List)); 
    l->next = NULL;
    return l;
}

struct List * append(struct List * head, double d) {
    struct List * tmp;
    if (head == NULL) {
        head = list_new();
        tmp = head;
    } else {
        tmp = head;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = list_new();
        tmp = tmp->next; 
    }

    tmp->v = d;

    return head; 
}

void wypisz_liste(struct List * h) {
    while (h != NULL) {
        printf("Wartość: %lf\n", h->v);
        h = h->next;
    }
}

int main(int argc, char **argv) {
    struct List * head = NULL;
    head = append(head, 3.0); 
    head = append(head, -1.0); 
    head = append(head, -2.0); 
    head = append(head, -21.0); 

    wypisz_liste(head);
}