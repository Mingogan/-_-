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
    struct Node* left;
    struct Node* right;
} Node;

Node* root = NULL;

Node* createNode(PhoneBook contact) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->contact = contact;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, PhoneBook contact) {
    if (root == NULL) {
        return createNode(contact);
    }
    if (strcmp(contact.lastName, root->contact.lastName) < 0) {
        root->left = insertNode(root->left, contact);
    } else {
        root->right = insertNode(root->right, contact);
    }
    return root;
}

Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, char* lastName) {
    if (root == NULL) return NULL;
    if (strcmp(lastName, root->contact.lastName) < 0) {
        root->left = deleteNode(root->left, lastName);
    } else if (strcmp(lastName, root->contact.lastName) > 0) {
        root->right = deleteNode(root->right, lastName);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMin(root->right);
        root->contact = temp->contact;
        root->right = deleteNode(root->right, temp->contact.lastName);
    }
    return root;
}

Node* findNodeByNumber(Node* root, int number, int* currentNumber) {
    if (root == NULL) return NULL;
    Node* leftResult = findNodeByNumber(root->left, number, currentNumber);
    if (leftResult != NULL) return leftResult;

    (*currentNumber)++;
    if (*currentNumber == number) return root;

    return findNodeByNumber(root->right, number, currentNumber);
}

void printBook(Node* root, int* count) {
    if (root != NULL) {
        printBook(root->left, count);
        (*count)++;
        printf("Номер контакта: %d\n", *count);
        printf("Имя: %s\n", root->contact.firstName);
        printf("Фамилия: %s\n", root->contact.lastName);
        printf("Отчество: %s\n", root->contact.patronymic);
        printf("Место работы: %s\n", root->contact.jobPlace);
        printf("Должность: %s\n", root->contact.post);
        printf("Адрес email: %s\n", root->contact.email);
        printf("Телефоны:\n");
        for (int i = 0; i < root->contact.amountPhone; i++) {
            printf("\tНомер телефона %d: %s\n", i + 1, root->contact.phones[i].number);
        }
        printf("Ссылки:\n");
        for (int i = 0; i < root->contact.amountLinks; i++) {
            printf("\tСсылка %d: %s\n", i + 1, root->contact.links[i].url);
        }
        printf("\n");
        printBook(root->right, count);
    }
}

void addContact() {
    PhoneBook newContact;
    printf("Введи имя: \n");
    scanf("%s", newContact.firstName);
    printf("Введи фамилию: \n");
    scanf("%s", newContact.lastName);
    
    root = insertNode(root, newContact);
}

void editContact() {
    int number;
    printf("Введи номер контакта для изменения: ");
    scanf("%d", &number);

    int currentNumber = 0;
    Node* contactNode = findNodeByNumber(root, number, &currentNumber);

    if (contactNode == NULL) {
        printf("Контакт с таким номером не найден\n");
        return;
    }

    PhoneBook* contact = &contactNode->contact;
    printf("Текущее имя: %s\n", contact->firstName);
    scanf("%s", contact->firstName);
    printf("Текущая фамилия: %s\n", contact->lastName);
    char newLastName[LEN_STR];
    scanf("%s", newLastName);
    if (strcmp(newLastName, contact->lastName) != 0) {
        strcpy(contact->lastName, newLastName);
        root = deleteNode(root, contact->lastName);
        root = insertNode(root, *contact);
    } else {
        strcpy(contact->lastName, newLastName);
    }
    printf("Текущее отчество: %s\n", contact->patronymic);
    scanf("%s", contact->patronymic);
    printf("Текущее место работы: %s\n", contact->jobPlace);
    scanf("%s", contact->jobPlace);
    printf("Текущая должность: %s\n", contact->post);
    scanf("%s", contact->post);
    printf("Текущий email: %s\n", contact->email);
    scanf("%s", contact->email);

    contact->amountPhone = 0;
    int choice = 1;
    while (contact->amountPhone < 5 && choice == 1) {
        printf("Введи номер телефона: ");
        scanf("%s", contact->phones[contact->amountPhone].number);
        contact->amountPhone++;
        choice = 0;
        if (contact->amountPhone < 5) {
            printf("Чтобы добавить ещё номер нажмите 1: ");
            scanf("%d", &choice);
            while (getchar() != '\n');
        }
    }

    contact->amountLinks = 0;
    choice = 1;
    while (contact->amountLinks < 5 && choice == 1) {
        printf("Введи ссылку: ");
        scanf("%s", contact->links[contact->amountLinks].url);
        contact->amountLinks++;
        choice = 0;
        if (contact->amountLinks < 5) {
            printf("Чтобы добавить ещё ссылку нажмите 1: ");
            scanf("%d", &choice);
            while (getchar() != '\n');
        }
    }
}

void deleteContact() {
    int number;
    printf("Введи номер контакта для удаления: ");
    scanf("%d", &number);

    int currentNumber = 0;
    Node* contactNode = findNodeByNumber(root, number, &currentNumber);

    if (contactNode == NULL) {
        printf("Контакт с таким номером не найден\n");
        return;
    }

    root = deleteNode(root, contactNode->contact.lastName);
}

int main() {
    int choice = 0;
    do {
        printf("задание 4.3 - Телефонная книга \n\n");
        printf("1. Вывести список контактов\n");
        printf("2. Добавить контакт\n");
        printf("3. Изменить контакт\n");
        printf("4. Удалить контакт\n");
        printf("0. Выход\n");
        printf("Выбери действие\n\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    int count = 0;
                    printBook(root, &count);
                }
                break;
            case 2:
                addContact();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
                break;
            case 0:
                break;
            default:
                printf("Неверный ввод, введите число от 0 до 4\n");
        }
    } while (choice != 0);

    return 0;
}
