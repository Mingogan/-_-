
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

Node* createNode();
void printBook(Node* head);
Node* addContact(Node* head, Node* tail, int* amountContact);
Node* deleteContact(Node* head, Node* tail, int* amountContact);
Node* editContact(Node* head, Node* tail, int* amountContact);
Node* insertSorted(Node* head, Node* tail, Node* newNode);

Node* head = NULL;
Node* tail = NULL;
int amountContact = 0;

int main() {
    
    int choice = 0;
    do {
        printf("Телефонная книга\n\n");
        printf("1. Вывести список контактов\n");
        printf("2. Добавить контакт\n");
        printf("3. Изменить контакт\n");
        printf("4. Удалить контакт\n");
        printf("0. Выход\n");
        printf("Выбери действие \n\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printBook(head);
                break;
            case 2:
                head = addContact(head, tail, &amountContact);
                break;
            case 3:
                head = editContact(head, tail, &amountContact);
                break;
            case 4:
                head = deleteContact(head, tail, &amountContact);
                break;
            case 0:
                break;
            default:
                printf("Неверный ввод, введи число от 0 до 4\n");
                break;
        }
    } while (choice != 0);

    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
