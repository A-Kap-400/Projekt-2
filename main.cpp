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
            fscanf(file, "%[^\n]s", current->category);	    getc(file);
            fscanf(file, "%[^\n]s", current->place);		getc(file);
            fscanf(file, "%[^\n]s", current->street);		getc(file);
            fscanf(file, "%d", &current->area);		        getc(file);
            fscanf(file, "%d", &current->price);			getc(file);
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

NODE* z(NODE* first, int* number_of_nodes)  // z
{
    NODE* current = first;
    int number_of_deleted_nodes = 0;

    char delete_these_places[StringLength];
    getchar();
    gets_s(delete_these_places, StringLength);

    if (current == NULL)
        return NULL;

    unsigned int i;
    NODE* current_next = current->next;

    for (i = 0; i < strlen(delete_these_places); i++)	// zmeni zadany text na male pismena
        delete_these_places[i] = tolower(delete_these_places[i]);

    char place_from_node[StringLength];
    while (current_next != NULL) {
        for (i = 0; i < strlen(current_next->place); i++)	// zmeni nazov miesta v zazname na male pismena
            place_from_node[i] = tolower(current_next->place[i]);
        place_from_node[i] = '\0';

        if (strstr(place_from_node, delete_these_places) != NULL) {	// vymazavanie vsetkych zaznamov, ktore sa zhoduju, okrem prveho
            current->next = current->next->next;
            free(current_next);
            number_of_deleted_nodes++;
            current_next = current->next;
            continue;
        }
        current = current->next;
        current_next = current->next;
    }

    current = first;
    for (i = 0; i < strlen(current->place); i++)
        place_from_node[i] = tolower(current->place[i]);
    place_from_node[i] = '\0';

    if (strstr(place_from_node, delete_these_places) != NULL) {	// vymazanie prveho zaznamu, ak sa zhoduje
        current_next = current->next;
        free(current);
        number_of_deleted_nodes++;
        *number_of_nodes -= number_of_deleted_nodes;
        printf("Vymazalo sa %d zaznamov\n", number_of_deleted_nodes);
        return current_next;
    }
    else {
        *number_of_nodes -= number_of_deleted_nodes;
        printf("Vymazalo sa %d zaznamov\n", number_of_deleted_nodes);
        return current;
    }
}

void h(NODE* first) // h
{
    int insertedPrice;
    scanf("%d", &insertedPrice);

    if (first == NULL)	                    /* end the function if the list is empty */
        return;

    int nodeExists = 0;	                    /* flag describing whether a node with a smaller price was found */
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

void a(NODE* first) // a
{
    NODE* current = first;
    int number_of_updated_nodes = 0;

    char update_these_places[StringLength];
    getchar();
    gets_s(update_these_places, StringLength);

    NODE* updated_node = (NODE*)malloc(sizeof(NODE));
    scanf("%[^\n]s", updated_node->category);	getchar();
    scanf("%[^\n]s", updated_node->place);		getchar();
    scanf("%[^\n]s", updated_node->street);
    scanf("%d", &updated_node->area);
    scanf("%d", &updated_node->price);				getchar();
    scanf("%[^\n]s", updated_node->description);		getchar();
    updated_node->next = NULL;

    if (current == NULL)	// ak je zoznam prazdny, neaktualizuje sa nic
        return;

    unsigned int i;
    for (i = 0; i < strlen(update_these_places); i++)
        update_these_places[i] = tolower(update_these_places[i]);

    char place_from_node[StringLength];
    while (current != NULL) {
        for (i = 0; i < strlen(current->place); i++)
            place_from_node[i] = tolower(current->place[i]);
        place_from_node[i] = '\0';

        if (strstr(place_from_node, update_these_places) != NULL) {
            strcpy(current->category, updated_node->category);
            strcpy(current->place, updated_node->place);
            strcpy(current->street, updated_node->street);
            current->area = updated_node->area;
            current->price = updated_node->price;
            strcpy(current->description, updated_node->description);
            number_of_updated_nodes++;
        }
        current = current->next;
    }
    printf("Aktualizovalo sa %d zaznamov\n", number_of_updated_nodes);
    free(updated_node);
}

NODE* u(NODE* first)    // u
{
    NODE* sorted_list = NULL;	// novy usporiadany zoznam
    NODE* current = first;

    if (current == NULL) {
        printf("Zoznam nie je mozne usporiadat\n");
        return NULL;
    }

    while (current != NULL) {
        NODE* currnet_next = current->next;		// krokuje po povodnom zozname a pamata si miesto pre 'aktualny'
        //	umiestnenie na prvu poziciu:
        if (sorted_list == NULL || (strcmp(sorted_list->place, current->place) > 0) || (strcmp(sorted_list->place, current->place) == 0 && sorted_list->price >= current->price)) {
            current->next = sorted_list;
            sorted_list = current;
        }
            //	umiestnenie na ostatne pozicie:
        else {
            NODE* sorted_current = sorted_list;		// urci, za ktory zaznam v zozname 'usporiadane' sa vklada aktualny zaznam
            while (sorted_current->next != NULL && (strcmp(sorted_current->next->place, current->place) <= 0)) {
                if (strcmp(sorted_current->next->place, current->place) == 0 && sorted_current->next->price > current->price)
                    break;
                sorted_current = sorted_current->next;
            }
            current->next = sorted_current->next;
            sorted_current->next = current;
        }
        current = currnet_next;		// pokracuje na dalsiu polozku v povodnom zozname
    }

    printf("Zaznamy boli usporiadane\n");
    return sorted_list;
}

int main()
{
    int input;
    int number_of_nodes = 0;
    NODE* head = NULL;

    while (1) {
        input = getchar();
        if (input == 'n')           loadFile(&head);
        else if (input == 'v')      printOutList(head);
        else if (input == 'p')      addNode(&head);
        else if (input == 'z')      head = z(head, &number_of_nodes);
        else if (input == 'h')		h(head);
        else if (input == 'a')		a(head);
        else if (input == 'k')		break;
        else if (input == 'u')      head = u(head);
    }

    freeList(&head);
    return 0;
}