#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define StringLength 55

typedef struct node
{
    char category[StringLength];
    char place[StringLength];
    char street[2 * StringLength];
    int area;
    int price;
    char description[4 * StringLength];
    struct node* next;
} NODE;

void freeList(NODE** firstNode)
{
    if (*firstNode != NULL) {
        NODE* deleteNode = *firstNode;
        while (deleteNode != NULL) {
            *firstNode = (*firstNode)->next;
            free(deleteNode);
            deleteNode = *firstNode;
        }
    }
}

void loadFile(NODE** first) // n
{
    freeList(first);

    FILE* file = NULL;
    if ((file = fopen("reality.txt", "r")) == NULL) {
        printf("Zaznamy neboli nacitane\n");
        return;
    }

    int charFromFile;
    int numberOfNodes = 0;
    NODE* current = NULL;

    while ((charFromFile = fgetc(file)) != EOF) {
        if (charFromFile == '&') {
            getc(file);     /* scans the enter behind '&' */
            if (numberOfNodes == 0) {
                *first = (NODE*)malloc(sizeof(NODE));
                current = *first;
                current->next = NULL;
            }
            else {
                current->next = (NODE*)malloc(sizeof(NODE));
                current = current->next;
                current->next = NULL;
            }
            /* fscanf() scans a string with spaces until '\n' without it and getc() scans the '\n' */
            fscanf(file, "%[^\n]s", current->category);     getc(file);
            fscanf(file, "%[^\n]s", current->place);        getc(file);
            fscanf(file, "%[^\n]s", current->street);       getc(file);
            fscanf(file, "%d", &current->area);             getc(file);
            fscanf(file, "%d", &current->price);            getc(file);
            fscanf(file, "%[^\n]s", current->description);
            numberOfNodes++;
        }
    }

    if (file != NULL)
        fclose(file);

    printf("Nacitalo sa %d zaznamov\n", numberOfNodes);
}

void printNode(NODE* currentNode)
{
    printf("kategoria ponuky: %s\n", currentNode->category);
    printf("miesto ponuky: %s\n", currentNode->place);
    printf("ulica: %s\n", currentNode->street);
    printf("rozloha v m2: %d\n", currentNode->area);
    printf("cena: %d\n", currentNode->price);
    printf("popis: %s\n", currentNode->description);
}

void printOutList(NODE* first)  // v
{
    if (first == NULL)
        return;

    NODE* current = first;
    int serialNumber = 1;

    while (current != NULL) {
        printf("%d.\n", serialNumber++);
        printNode(current);
        current = current->next;
    }
}

NODE* scanNode()
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));        /* writes the new items into a new node */
    scanf("%[^\n]s", newNode->category);        getchar();
    scanf("%[^\n]s", newNode->place);           getchar();
    scanf("%[^\n]s", newNode->street);          getchar();
    scanf("%d", &newNode->area);                getchar();
    scanf("%d", &newNode->price);               getchar();
    scanf("%[^\n]s", newNode->description);     getchar();
    newNode->next = NULL;
    return newNode;
}

void addNode(NODE** first)  // p
{
    int newNodePosition;
    scanf("%d", &newNodePosition);
    getchar();

    NODE* newNode = scanNode();

    if (newNodePosition <= 1 || *first == NULL) {       /* insert at the beginning of the list */
        if (*first != NULL) {
            newNode->next = *first;
            *first = newNode;
        }
        else *first = newNode;
    }
    else {                                              /* insert somewhere into the list */
        NODE* current = *first;
        int currentPosition = 1;
        while (current->next != NULL) {
            if (newNodePosition == currentPosition + 1) {
                newNode->next = current->next;
                current->next = newNode;
                return;
            }
            current = current->next;
            currentPosition++;
        }
        current->next = newNode;                        /* insert behind the last position if not inserted yet */
    }
}

void stringToLower(char buffer[])
{
    for (int i = 0; i < strlen(buffer); i++)
        buffer[i] = tolower(buffer[i]);
}

void copyString(char original[], char copy[])
{
    for (int i = 0; i < strlen(original); i++)
        copy[i] = original[i];
}

void deleteNode(NODE** first)  // z
{
    getchar();
    char deletePlace[StringLength];
    gets_s(deletePlace, StringLength);

    if (*first == NULL)                         /* end the function if the list is empty */
        return;

    int deletions = 0;
    char nodePlace[StringLength];
    NODE* current = *first;
    NODE* following = current->next;

    stringToLower(deletePlace);
    while (following != NULL) {                 /* deleting all nodes if necessary except the first node */
        copyString(following->place, nodePlace);
        stringToLower(nodePlace);
        if (strstr(nodePlace, deletePlace) != NULL) {
            current->next = current->next->next;
            free(following);
            deletions++;
            following = current->next;
            continue;
        }
        current = current->next;
        following = current->next;
    }

    current = *first;                           /* deleting the first node if necessary */
    copyString(current->place, nodePlace);
    stringToLower(nodePlace);
    if (strstr(nodePlace, deletePlace) != NULL) {
        *first = current->next;
        free(current);
        deletions++;
    }

    printf("Vymazalo sa %d zaznamov\n", deletions);
}

void searchByPrice(NODE* first) // h
{
    int insertedPrice;
    scanf("%d", &insertedPrice);

    if (first == NULL)	                        /* end the function if the list is empty */
        return;

    int nodeExists = 0;	                        /* flag describing whether a node with a smaller price was found */
    int serialNumber = 1;
    NODE* current = first;

    while (current != NULL) {
        if (insertedPrice >= current->price) {
            printf("%d.\n", serialNumber++);
            printNode(current);
            nodeExists = 1;
        }
        current = current->next;
    }

    if (nodeExists == 0)
        printf("V ponuke su len reality s vyssou cenou\n");
}

void rewriteNode(NODE* original, NODE* updated)
{
    strcpy(original->category, updated->category);
    strcpy(original->place, updated->place);
    strcpy(original->street, updated->street);
    original->area = updated->area;
    original->price = updated->price;
    strcpy(original->description, updated->description);
}

void updateNode(NODE* first) // a
{
    getchar();
    char updatePlace[StringLength];
    gets_s(updatePlace, StringLength);
    NODE* updatedNode = scanNode();             /* scan the updated items */

    if (first == NULL)                          /* end the function if the list is empty */
        return;

    int updates = 0;
    char nodePlace[StringLength];
    NODE* current = first;

    stringToLower(updatePlace);
    while (current != NULL) {
        copyString(current->place, nodePlace);
        stringToLower(nodePlace);
        if (strstr(nodePlace, updatePlace) != NULL) {
            rewriteNode(current, updatedNode);
            updates++;
        }
        current = current->next;
    }

    printf("Aktualizovalo sa %d zaznamov\n", updates);
    free(updatedNode);
}

void sortedInsert(NODE** sortedHead, NODE* inserting)
{                                               /* inserting to first position */
    if (*sortedHead == NULL ||
    (strcmp((*sortedHead)->place, inserting->place) > 0) ||
    (strcmp((*sortedHead)->place, inserting->place) == 0 && (*sortedHead)->price >= inserting->price)) {
        inserting->next = *sortedHead;
        *sortedHead = inserting;
    }
    else {                                      /* inserting to the other places */
        NODE* sortedCurrent = *sortedHead;
        while (sortedCurrent->next != NULL && (strcmp(sortedCurrent->next->place, inserting->place) <= 0)) {
            if (strcmp(sortedCurrent->next->place, inserting->place) == 0 && sortedCurrent->next->price > inserting->price)
                break;                          /* find the node, after which to insert */
            sortedCurrent = sortedCurrent->next;
        }
        inserting->next = sortedCurrent->next;
        sortedCurrent->next = inserting;        /* insert the new node to its place */
    }
}

void insertionSort(NODE** first)    // u
{
    if (*first == NULL) {
        printf("Zoznam nie je mozne usporiadat\n");
        return;                                 /* end the function if the list is empty */
    }

    NODE* sortedList = NULL;	                /* new sorted list */
    NODE* current = *first;

    while (current != NULL) {
        NODE* following = current->next;        /* remembers which node is going to be sorted next in the original list, */
        sortedInsert(&sortedList, current);     /* inserting the current node to its new position into the sorted list */
        current = following;                    /* go to the next node */
    }

    *first = sortedList;
    printf("Zaznamy boli usporiadane\n");
}

void reverseList(NODE** first)  // o
{
    if (*first == NULL)
        return;

    NODE* previous = NULL;
    NODE* current = *first;
    NODE* following = NULL;

    while (current != NULL) {
        following = current->next;
        current->next = previous;
        previous = current;
        current = following;
    }

    *first = previous;
    printOutList(*first);
}

int main()
{
    int input;
    NODE* head = NULL;

    while (1) {
        input = getchar();
        if (input == 'n')           loadFile(&head);
        else if (input == 'v')      printOutList(head);
        else if (input == 'p')      addNode(&head);
        else if (input == 'z')      deleteNode(&head);
        else if (input == 'h')      searchByPrice(head);
        else if (input == 'a')      updateNode(head);
        else if (input == 'k')      break;
        else if (input == 'u')      insertionSort(&head);
        else if (input == 'o')      reverseList(&head);
    }

    freeList(&head);
    return 0;
}
