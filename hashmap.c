#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

struct node {
    char key[10];
    int value;
    struct node *next;
};

struct node *hash_map[SIZE];

int hash(char *key) {
    int hash = 5381 ; // 5381 daha az çarpýþma veren bir sayý olduðu için kullanýlmýþtýr.
    int c;
 while ((c = *key++))
        hash = ((hash << 5) + hash) + c; 

    return hash % SIZE;
}

void insert(char *key, int value) {
    int index = hash(key);
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    strcpy(new_node->key, key); // key deðerinin deðiþmemesi için kopyalanýr.
    new_node->value = value;
    new_node->next = hash_map[index];
    hash_map[index] = new_node;
}

void delete(char *key) {
    int index = hash(key);
    struct node *current = hash_map[index];
    struct node *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hash_map[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int search(char *key) {
    int index = hash(key);
    struct node *current = hash_map[index];

    while (current) {
        if (strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }

    return -1;
}

void display() {
    int i;

    for (i = 0; i < SIZE; i++) {
        struct node *current = hash_map[i];

        printf("Index %d: ", i);

        while (current) {
            printf("(%s, %d) ", current->key, current->value);
            current = current->next;
        }

        printf("\n");
    }
}

int main() {
    char choice[10];
    char key[10];
    int value;

    while (1) {
        printf("Seciminizi giriniz  (ekleme icin (e), silmek icin (s), arama icin (a), hash mapi goruntulemek icin (g), cikis icin(c)): ");
        scanf("%s", choice);

        switch (choice[0]) {
            case 'e':
                printf("Key giriniz: ");
                scanf("%s", key);
                printf("Degeri giriniz: ");
                scanf("%d", &value);
                insert(key, value);
                break;
            case 's':
                printf("Silenecek elemanýn key degerini giriniz: ");
                scanf("%s", key);
                delete(key);
                break;
            case 'a':
                printf("Aranacak elemanin key degerini giriniz: ");
                scanf("%s", key);
                printf("Deger: %d\n", search(key));
                break;
            case 'g':
                display();
                break;
            case 'c':
                exit(0);
                break;
            default:
                printf("Yanlis secim\n");
                break;
        }
    }

    return 0;
}


