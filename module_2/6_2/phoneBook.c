#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_STR 50

typedef struct Phones {
    char number[LEN_STR];
} Phones;

typedef struct Links {
    char url[LEN_STR];
} Links;

typedef struct PhoneBook {
    char firstName[LEN_STR];
    char lastName[LEN_STR];
    char patronymic[LEN_STR];
    char jobPlace[LEN_STR];
    char post[LEN_STR];
    char email[LEN_STR];
    Phones phones[5];
    int amountPhone;
    Links links[5];
    int amountLinks;
} PhoneBook;

typedef struct Node {
    PhoneBook contact;
    struct Node* next;
    struct Node* prev;
} Node;

void printBook(Node* head) {
    if (head == NULL) {
        printf("Книга пуста\n");
        return;
    }
    Node* current = head;
    int i = 1;
    while (current != NULL) {
        printf("\n\nНомер контакта: %d\n", i++);
        printf("Имя: %s\n", current->contact.firstName);
        printf("Фамилия: %s\n", current->contact.lastName);
        printf("Отчество: %s\n", current->contact.patronymic);
        printf("Место работы: %s\n", current->contact.jobPlace);
        printf("Должность: %s\n", current->contact.post);
        printf("Адрес email: %s\n", current->contact.email);
        printf("Телефоны:\n");
        for (int j = 0; j < current->contact.amountPhone; j++) {
            printf("\tНомер телефона %d: %s\n", j + 1, current->contact.phones[j].number);
        }
        printf("Ссылки:\n");
        for (int j = 0; j < current->contact.amountLinks; j++) {
            printf("\tСсылка %d: %s\n", j + 1, current->contact.links[j].url);
        }
        current = current->next;
    }
}

Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }
    return newNode;
}

Node* insertSorted(Node* head, Node* tail, Node* newNode) {
    if (head == NULL) {
        newNode->next = NULL;
        newNode->prev = NULL;
        head = newNode;
        tail = newNode;
    } else {
        Node* current = head;
        while (current != NULL && strcmp(current->contact.lastName, newNode->contact.lastName) < 0) {
            current = current->next;
        }
        if (current == NULL) {
            newNode->prev = tail;
            newNode->next = NULL;
            tail->next = newNode;
            tail = newNode;
        } else if (current == head) {
            newNode->next = head;
            newNode->prev = NULL;
            head->prev = newNode;
            head = newNode;
        } else {
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }
    return head;
}

Node* addContact(Node* head, Node* tail, int* amountContact) {
    if (*amountContact == 50) {
        printf("Переполнение телефонной книги\n");
        return head;
    }

    Node* newNode = createNode();
    if (newNode == NULL) {
        return head;
    }

    printf("Введи имя: ");
    scanf("%s", newNode->contact.firstName);
    printf("Введи фамилию: ");
    scanf("%s", newNode->contact.lastName);

    head = insertSorted(head, tail, newNode);
    (*amountContact)++;
    return head;
}

Node* deleteContact(Node* head, Node* tail, int* amountContact) {
    int id;

    printf("Введи номер контакта для удаления: ");
    scanf("%d", &id);
    id--;
    if (id < 0 || id >= *amountContact) {
        printf("Введён неверный номер\n");
        return head;
    }

    Node* current = head;
    for (int i = 0; i < id; i++) {
        current = current->next;
    }

    if (current == head) {
        head = current->next;
        if (head != NULL) {
            head->prev = NULL;
        } else {
            tail = NULL;
        }
    } else {
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
    }

    free(current);
    (*amountContact)--;
    return head;
}

Node* editContact(Node* head, Node* tail, int* amountContact) {
    int id;
    printf("Введи номер контакта для изменения: ");
    scanf("%d", &id);
    id--;

    if (id < 0 || id >= *amountContact) {
        printf("Введён неверный номер\n");
        return head;
    }

    Node* current = head;
    for (int i = 0; i < id; i++) {
        current = current->next;
    }

    char oldLastName[LEN_STR];
    strcpy(oldLastName, current->contact.lastName);

    printf("Текущее имя: %s\n", current->contact.firstName);
    scanf("%s", current->contact.firstName);
    printf("Текущая фамилия: %s\n", current->contact.lastName);
    scanf("%s", current->contact.lastName);
    printf("Текущее отчество: %s\n", current->contact.patronymic);
    scanf("%s", current->contact.patronymic);
    printf("Текущее место работы: %s\n", current->contact.jobPlace);
    scanf("%s", current->contact.jobPlace);
    printf("Текущая должность: %s\n", current->contact.post);
    scanf("%s", current->contact.post);
    printf("Текущий email: %s\n", current->contact.email);
    scanf("%s", current->contact.email);

    current->contact.amountPhone = 0;
    int choice = 1;
    while (current->contact.amountPhone < 5 && choice == 1) {
        printf("Введи номер телефона: ");
        scanf("%s", current->contact.phones[current->contact.amountPhone].number);
        current->contact.amountPhone++;
        choice = 0;
        if (current->contact.amountPhone < 5) {
            printf("Чтобы добавить ещё номер нажмите 1: ");
            scanf("%d", &choice);
            while (getchar() != '\n');
        }
    }

    current->contact.amountLinks = 0;
    choice = 1;
    while (current->contact.amountLinks < 5 && choice == 1) {
        printf("Введи ссылку: ");
        scanf("%s", current->contact.links[current->contact.amountLinks].url);
        current->contact.amountLinks++;
        choice = 0;
        if (current->contact.amountLinks < 5) {
            printf("Чтобы добавить ещё ссылку нажмите 1: ");
            scanf("%d", &choice);
            while (getchar() != '\n');
        }
    }

    if (strcmp(oldLastName, current->contact.lastName) != 0) {
        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }
        if (current->next != NULL) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        head = insertSorted(head, tail, current);
    }
    return head;
}