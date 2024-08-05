#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int priority;
    int data;
} Element;

typedef struct {
    Element elements[20];
    int size;
} PriorityQueue;


void add(PriorityQueue *queue, int data, int priority) {
    if (queue->size >= 20) {
        printf("Очередь переполнена!\n");
        return;
    }

    int i;
    for (i = queue->size - 1; i >= 0; i--) {
        if (queue->elements[i].priority > priority) {
            queue->elements[i + 1] = queue->elements[i];
        } else {
            break;
        }
    }
    queue->elements[i + 1].data = data;
    queue->elements[i + 1].priority = priority;
    queue->size++;
}

int extraction(PriorityQueue *queue) {
    if (queue->size == 0) {
        printf("Очередь пуста!\n");
        return 0; 
    }
    int data = queue->elements[0].data;
    for (int i = 0; i < queue->size - 1; i++) {
        queue->elements[i] = queue->elements[i + 1];
    }
    queue->size--;
    return data;
}

int extractionByPriority(PriorityQueue *queue, int priority) {
    for (int i = 0; i < queue->size; i++) {
        if (queue->elements[i].priority == priority) {
            int data = queue->elements[i].data;
            for (int j = i; j < queue->size - 1; j++) {
                queue->elements[j] = queue->elements[j + 1];
            }
            queue->size--;
            return data;
            }
        }
    printf("Элемент с приоритетом %d не найден!\n", priority);
    return 0; 
}

int extractionBelowPriority(PriorityQueue *queue, int belowPriority) {
    for (int i = 0; i < queue->size; i++) {
        if (queue->elements[i].priority >= belowPriority) {
            int data = queue->elements[i].data;
            for (int j = i; j < queue->size - 1; j++) {
                queue->elements[j] = queue->elements[j + 1];
            }
            queue->size--;
            return data;
        }
    }
    printf("Элемент с приоритетом не ниже %d не найден!\n", belowPriority);
    return 0; 
} 

int main() {
    PriorityQueue queue;
    queue.size = 0;

    add(&queue, 10, 5);
    add(&queue, 20, 1);
    add(&queue, 30, 10);
    add(&queue, 40, 8);
    add(&queue, 50, 3);

    printf("Извлечение элемента с самым высоким приоритетом: %d\n", extraction(&queue));
    printf("Извлечение элемента с приоритетом 3: %d\n", extractionByPriority(&queue, 3));
    printf("Извлечение элемента с приоритетом не ниже 6: %d\n", extractionBelowPriority(&queue, 6));

    return 1;
}