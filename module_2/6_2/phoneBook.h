#ifndef PHONEBOOK_H
#define PHONEBOOK_H

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

void printBook(Node* head);
Node* addContact(Node* head, Node* tail, int* amountContact);
Node* deleteContact(Node* head, Node* tail, int* amountContact);
Node* editContact(Node* head, Node* tail, int* amountContact);
Node* createNode();
Node* insertSorted(Node* head, Node* tail, Node* newNode);

#endif