#include <stdio.h>
#include <stdlib.h>
#include <String.h>

struct Characters_nodes {

    char Data;
    struct District_nodes* Next;

};

struct District_nodes {

       char Name[50];
       struct town_nodes* Towns;
       struct District_nodes* Next;
       struct District_nodes* Previous;
};

struct town_nodes {

       int Population;
       char Name[50];
       struct town_nodes* Next;
       struct town_nodes* Previous;
};

struct District_nodes* MakeEmpty(struct District_nodes*);
struct town_nodes* MakeEmptyTowns(struct town_nodes*);
struct Characters_nodes* MakeCharacterList(char);

int IsEmpty(struct District_nodes*);
int IsEmptyTown(struct town_nodes*);

int IsLast(struct District_nodes*, struct District_nodes*);
int IsLastTown(struct town_nodes*, struct town_nodes*);

struct District_nodes* Find(char*, struct District_nodes*);
struct town_nodes* FindTown(char*, struct town_nodes*);

struct District_nodes* FindPrevious(char*, struct District_nodes*);
struct town_nodes* FindPreviousTown(char*, struct town_nodes*);

void Delete(char*, struct District_nodes*);
void DeleteTown(char*, struct town_nodes*);

void InsertLast(char*, struct District_nodes*);
void InsertNodeLast(struct District_nodes*, struct District_nodes*);
void InsertTownLast(char*, int, struct town_nodes*);
void InsertDistrictLastToCharacter(struct Characters_nodes*, struct District_nodes*);

void PrintList(struct District_nodes*);
void PrintTownList(struct town_nodes*);
void printLoadedInformationAsOutputFile(struct District_nodes*);
void printLoadedInformationAsInputFile(struct District_nodes*);

void DeleteList(struct District_nodes*);
void DeleteListTown(struct town_nodes*);

int size(struct District_nodes*);
int sizeTown(struct town_nodes*);

int maxDistrictLength(struct District_nodes*);
struct District_nodes* makeDistrictsSameLength(struct District_nodes*, int);
void cleanDistricts(struct District_nodes*);
char toLowerCase(char);
void copyDistricts(struct District_nodes*, struct District_nodes*);
void districtRadixSort(struct District_nodes*);
void sortTowns(struct town_nodes*);


int main(){

    struct District_nodes* unsortedDistrictList = MakeEmpty(NULL);
    struct District_nodes* sortedDistrictList = MakeEmpty(NULL);
    int isDistrictsSorted = 0;
    int isTownsSorted = 0;

    int choice;

    struct District_nodes* districtPointer;
    struct town_nodes* townPointer;
    char line[50];
    char districtName[50];
    char townName[50];
    int population;
    int lineCount = 0;
    char *token;

    FILE* input = fopen("districts.txt","r");

    do{

        printf("Please Select one of the option you want:\n");
        printf("1. Load the input file\n");
        printf("2. Print the loaded information before sorting\n");
        printf("3. Sort the districts alphabetically\n");
        printf("4. Sort the towns for each district based on population in ascending order\n");
        printf("5. Print the sorted information\n");
        printf("6. Add a new district to the list of sorted districts (and sort the list)\n");
        printf("7. Add a new town to a certain district\n");
        printf("8. Delete a town from a specific district\n");
        printf("9. Delete a complete district\n");
        printf("10.Calculate the population of Palestine, the max and min town population\n");
        printf("11.Print the districts and their total population\n");
        printf("12.Change the population of a town, after prompting the user to enter the district name\n");
        printf("13.Save to output file\n");
        printf("14.Exit\n\n");
        printf("Enter the option: ");

      scanf("%d", &choice);

      switch(choice){

        case 1:

            while (fgets(line, sizeof(line), input)) {
                lineCount++;
                token = strtok(line, "|");

                if(token != NULL) {
                    strcpy(districtName, token);
                    token = strtok(NULL, "|");
                }

                if(token != NULL) {
                    strcpy(townName, token);
                    token = strtok(NULL, "|");
                }

                if(token != NULL) {
                    population = atoi(token);

                }

                districtPointer = Find(districtName, unsortedDistrictList);

                if(districtPointer == NULL){
                    InsertLast(districtName, unsortedDistrictList);
                    districtPointer = Find(districtName, unsortedDistrictList);
                    InsertTownLast(townName, population, districtPointer->Towns);


                }else{
                    InsertTownLast(townName, population, districtPointer->Towns);

                }

            }

            copyDistricts(sortedDistrictList, unsortedDistrictList);

            fclose(input);
            printf("\nThe information loaded successfully\n\n");
            break;

        case 2:

            if(IsEmpty(unsortedDistrictList)){
                printf("\nYou must load the information first!\n\n");
            } else {
                printf("\n");
                printLoadedInformationAsInputFile(unsortedDistrictList);
            }
            break;


        case 3:

            if(IsEmpty(sortedDistrictList)){
                printf("\nYou must load the information first!\n\n");
            } else {
                districtRadixSort(sortedDistrictList);
                printf("\nThe districts list has been sorted!\n\n");
                isDistrictsSorted = 1;

            }
            break;

        case 4:

            if(IsEmpty(sortedDistrictList)){
                printf("\nYou must load the information first!\n\n");
            } else {

                struct District_nodes* district = sortedDistrictList->Next;
                while (district->Next != NULL) {
                    sortTowns(district->Towns);
                    district = district->Next;

                }

            printf("\nThe towns lists has been sorted!\n\n");
            isTownsSorted = 1;

            }
            break;

        case 5:
            if(IsEmpty(sortedDistrictList)){
                printf("\nYou must load the information first!\n\n");

            } else {
                if(isDistrictsSorted == 1 || isTownsSorted == 1){
                    printf("\n");
                    printLoadedInformationAsOutputFile(sortedDistrictList);
                } else {
                    printf("\nYou must sort the information first!\n\n");
                }
            }

            break;

        case 6:

            if(IsEmpty(sortedDistrictList)){
                printf("\nYou must load the information first!\n\n");

            } else {
                printf("\nPlease Enter the district's Name:\n");
                scanf("%s", districtName);
                districtPointer = Find(districtName, sortedDistrictList);

                if(districtPointer == NULL){
                    InsertLast(districtName, sortedDistrictList);
                    districtRadixSort(sortedDistrictList);
                    isDistrictsSorted = 1;

                    printf("\nThe district name you entered has been added!\n\n");

                } else {
                    printf("\nThe district name you entered is already in the list!\n\n");

                }
            }
            break;

        case 7:

            if(IsEmpty(sortedDistrictList)){
                printf("\nYou must load the information first!\n\n");

            } else {
                printf("\nPlease Enter the Town's Name, population and district's Name:\n");
                scanf("%s %d %s", townName, &population, districtName);
                districtPointer = Find(districtName, sortedDistrictList);

                if(districtPointer == NULL){
                    printf("\nThe district name you entered not found!\n\n");

                } else {
                    InsertTownLast(townName, population, districtPointer->Towns);
                    printf("\nThe town you entered has been added!\n\n");

                }
            }
            break;


        case 8:

            if(IsEmpty(sortedDistrictList)){
                printf("\nYou must load the information first!\n\n");

            } else {
                printf("\nPlease Enter the Town's Name and district's Name:\n");
                scanf("%s %s", townName, districtName);

                districtPointer = Find(districtName, sortedDistrictList);

                if(districtPointer == NULL){
                    printf("\nThe District's Name you entered not found!\n\n");

                } else {
                    townPointer = FindTown(townName, districtPointer->Towns);

                    if(townPointer == NULL){
                        printf("\nThe Town's Name you entered not found!\n\n");

                    } else {
                        DeleteTown(townPointer->Name, districtPointer->Towns);
                        printf("\nThe Town's Name entered has been deleted!\n\n");
                    }
                }
            }
            break;

        case 9:

            if(IsEmpty(sortedDistrictList)){
                printf("\nYou must load the information first!\n\n");

            } else {
                printf("\nPlease Enter the district's Name:\n");
                scanf("%s", districtName);

                districtPointer = Find(districtName, sortedDistrictList);

                if(districtPointer == NULL){
                    printf("\nThe district name you entered not found!\n\n");

                } else {
                    DeleteListTown(districtPointer->Towns);
                    Delete(districtName, sortedDistrictList);
                    printf("\nThe district you entered has been deleted!\n\n");

                }
            }
            break;

        case 10:

            if (IsEmpty(sortedDistrictList)) {
                 printf("\nYou must load the information first!\n\n");

            } else {
                int totalPopulation = 0;
                int maxPopulation = 0;
                char maxTown[50];
                int minPopulation = 100000000;
                char minTown[50];

                districtPointer = sortedDistrictList->Next;

                while (districtPointer->Next != NULL) {
                    townPointer = districtPointer->Towns->Next;

                    while (townPointer->Next != NULL) {
                        totalPopulation += townPointer->Population;

                        if (townPointer->Population > maxPopulation) {
                           maxPopulation = townPointer->Population;
                           strcpy(maxTown, townPointer->Name);

                        }

                        if (townPointer->Population < minPopulation) {
                           minPopulation = townPointer->Population;
                           strcpy(minTown, townPointer->Name);

                        }

                        townPointer = townPointer->Next;
                    }
                    districtPointer = districtPointer->Next;
                 }

                 printf("\nThe total population is %d\n", totalPopulation);
                 printf("The maximum town population is %s with %d\n", maxTown, maxPopulation);
                 printf("The minimum town population is %s with %d\n\n", minTown, minPopulation);
            }
            break;

        case 11:

            if (IsEmpty(sortedDistrictList)) {
                 printf("\nYou must load the information first!\n\n");

            } else {
                printf("\nThe population for each district:\n\n");
                districtPointer = sortedDistrictList->Next;
                while (districtPointer->Next != NULL) {
                     int totalPopulation = 0;
                     townPointer = districtPointer->Towns->Next;

                    while (townPointer->Next != NULL) {
                         totalPopulation += townPointer->Population;
                         townPointer = townPointer->Next;
                    }

               printf("%s District, Population = %d\n", districtPointer->Name, totalPopulation);
               districtPointer = districtPointer->Next;

                }
            }
            printf("\n");
            break;

        case 12:

            if (IsEmpty(sortedDistrictList)) {
                 printf("\nYou must load the information first!\n\n");

            } else {
                printf("\nPlease enter the district's Name of the town:\n");
                scanf("%s", districtName);
                printf("\nPlease now enter the Towns's Name and the new population for it:\n");
                scanf("%s %d", townName, &population);

                districtPointer = Find(districtName, sortedDistrictList);

                if(districtPointer == NULL){
                      printf("\nThe district's name you entered not found!\n\n");

                }else{
                   townPointer = FindTown(townName, districtPointer->Towns);
                   if(townPointer == NULL){
                        printf("\nThe town's name you entered not found!\n\n");

                    }else{
                       townPointer->Population = population;
                       printf("\nThe number of population has been updated\n\n");

                    }

                }
            }
            break;

        case 13:

            if (IsEmpty(sortedDistrictList)) {
               printf("\nYou must load the information first!\n\n");

            } else {

               FILE* output = fopen("sorted_districts.txt", "w");

               districtRadixSort(sortedDistrictList);
               struct District_nodes* district = sortedDistrictList->Next;
                while (district->Next != NULL) {
                    sortTowns(district->Towns);
                    district = district->Next;

                }
                isDistrictsSorted = 1;
                isTownsSorted = 1;

               districtPointer = sortedDistrictList->Next;
               while (districtPointer->Next != NULL) {
                  int totalPopulation = 0;
                  townPointer = districtPointer->Towns->Next;

                  while (townPointer->Next != NULL) {
                      totalPopulation += townPointer->Population;
                      townPointer = townPointer->Next;
                  }

                  fprintf(output, "%s District, Population = %d\n", districtPointer->Name, totalPopulation);

                  townPointer = districtPointer->Towns->Next;
                  while (townPointer->Next != NULL) {
                      fprintf(output, "%s, %d\n", townPointer->Name, townPointer->Population);
                      townPointer = townPointer->Next;
                  }

                  districtPointer = districtPointer->Next;

               }

              fclose(output);
              printf("\nThe information has been saved!\n\n");
            }
            break;

        case 14:

            printf("\nWe are gonna miss you <3\n");
            break;

        default:

            printf("\nAre you sure you entered the number between 1 - 14 :/\n\n");

      }

   }while(choice != 14);

    return 0;

}

// MakeEmpty Methods
struct District_nodes* MakeEmpty(struct District_nodes* head) {
    struct District_nodes* tail;
    if (head != NULL)
        DeleteList(head);

     head = (struct District_nodes*)malloc(sizeof(struct District_nodes));
     tail = (struct District_nodes*)malloc(sizeof(struct District_nodes));

    if (head == NULL || tail == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    head->Next = tail;
    head->Previous = NULL;

    tail->Next = NULL;
    tail->Previous = head;

    return head;
}

struct town_nodes* MakeEmptyTowns(struct town_nodes* head) {
    struct town_nodes* tail;
    if (head != NULL)
        DeleteListTown(head);

     head = (struct town_nodes*)malloc(sizeof(struct town_nodes));
     tail = (struct town_nodes*)malloc(sizeof(struct town_nodes));

    if (head == NULL || tail == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    head->Next = tail;
    head->Previous = NULL;

    tail->Next = NULL;
    tail->Previous = head;

    return head;
}

struct Characters_nodes* MakeCharacterList(char character) {
    struct Characters_nodes* head;

     head = (struct Characters_nodes*)malloc(sizeof(struct Characters_nodes));

    if (head == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    head->Data = character;
    head->Next = NULL;

    return head;
}

// isEmpty Methods
int IsEmpty(struct District_nodes* L) {
    return L->Next->Next == NULL;
}

int IsEmptyTown(struct town_nodes* L) {
    return L->Next->Next == NULL;
}

// isLast Methods
int IsLast(struct District_nodes* P, struct District_nodes* L) {
    return P->Next->Next == NULL;
}

int IsLastTown(struct town_nodes* P, struct town_nodes* L) {
    return P->Next->Next == NULL;
}

// Find Methods
struct District_nodes* Find(char* districtName, struct District_nodes* L){
    struct District_nodes* P = L->Next;
    while (P != NULL && strcasecmp(P->Name, districtName) != 0) {
        P = P->Next;
    }

    return P;
}

struct town_nodes* FindTown(char* townName, struct town_nodes* L){
    struct town_nodes* P = L->Next;
    while (P != NULL && strcasecmp(P->Name, townName) != 0) {
        P = P->Next;
    }

    return P;
}

// FindPrevious Methods
struct District_nodes* FindPrevious(char* districtName, struct District_nodes* L){
    struct District_nodes* P = L;

    while (P->Next != NULL && strcasecmp(P->Next->Name, districtName) != 0) {
        P = P->Next;
    }

    return P;
}

struct town_nodes* FindPreviousTown(char* townName, struct town_nodes* L){
    struct town_nodes* P = L;

    while (P->Next != NULL && strcasecmp(P->Next->Name, townName) != 0) {
        P = P->Next;
    }

    return P;
}

// Delete Methods
void Delete(char* districtName, struct District_nodes* L){
     struct District_nodes* P;
     struct District_nodes* temp;

     P = FindPrevious(districtName, L);


     if(!IsLast(P, L) ){
         temp = P->Next;
         P->Next = temp->Next;
         free(temp);
     }
}

void DeleteTown(char* townName, struct town_nodes* L){
     struct town_nodes* P;
     struct town_nodes* temp;

     P = FindPreviousTown(townName, L);


     if(!IsLastTown(P, L) ){
         temp = P->Next;
         P->Next = temp->Next;
         free(temp);
     }
}

// InsertLast Methods
void InsertLast(char* districtName, struct District_nodes* L) {
    struct District_nodes* temp;
    struct District_nodes* P = L;
    temp = (struct District_nodes*)malloc(sizeof(struct District_nodes));

    if (temp == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    strcpy(temp->Name, districtName);

    struct town_nodes* townsList = MakeEmptyTowns(NULL);
    temp->Towns = townsList;

    while(P->Next != NULL){
        P = P->Next;
    }

    temp->Next = P;
    temp->Previous = P->Previous;
    P->Previous->Next = temp;
    P->Previous = temp;
}

void InsertTownLast(char* townName,int population, struct town_nodes* L) {
    struct town_nodes* temp;
    struct town_nodes* P;
    P = L;

    temp = (struct town_nodes*)malloc(sizeof(struct town_nodes));

    if (temp == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    strcpy(temp->Name, townName);
    temp->Population = population;

    while(P->Next != NULL){
        P = P->Next;
    }

    temp->Next = P;
    temp->Previous = P->Previous;
    P->Previous->Next = temp;
    P->Previous = temp;
}

void InsertNodeLast(struct District_nodes* district, struct District_nodes* L) {
    struct District_nodes* P = L;

    while(P->Next != NULL){
        P = P->Next;
    }

    district->Next = P;
    district->Previous = P->Previous;
    P->Previous->Next = district;
    P->Previous = district;
}

void InsertDistrictLastToCharacter(struct Characters_nodes* charList, struct District_nodes* districtNode) {
    struct District_nodes* P = charList->Next;
    struct District_nodes* newNode = (struct District_nodes*)malloc(sizeof(struct District_nodes));

    if (newNode == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    strcpy(newNode->Name, districtNode->Name);
    newNode->Towns = districtNode->Towns;
    newNode->Next = NULL;


    if (P == NULL) {
        charList->Next = newNode;

    } else {
        while (P->Next != NULL) {
            P = P->Next;
        }
        P->Next = newNode;
    }
}

// PrintList Methods
void PrintList(struct District_nodes* L) {
    struct District_nodes* P = L->Next;
    if(IsEmpty(L)){
      printf("Empty list\n\n");

    } else {
    while (P->Next != NULL) {
        printf("%s\t", P->Name);
        P = P->Next;
    }
    printf("\n");
  }
}

void PrintTownList(struct town_nodes* L) {
    struct town_nodes* P = L->Next;
    if(IsEmptyTown(L)){
      printf("Empty list\n\n");

    } else {
    while (P->Next != NULL) {
        printf(" %s, %d\n", P->Name, P->Population);
        P = P->Next;
    }
    printf("\n");
  }
}

void printLoadedInformationAsOutputFile(struct District_nodes* L) {
    struct District_nodes* P = L->Next;

    while (P->Next != NULL) {
        int totalPopulation = 0;
        struct town_nodes* townPointer = P->Towns->Next;

        while (townPointer->Next != NULL) {
            totalPopulation += townPointer->Population;
            townPointer = townPointer->Next;
        }

        printf("%s District, Population = %d: \n", P->Name, totalPopulation);
        PrintTownList(P->Towns);
        P = P->Next;
    }
}

void printLoadedInformationAsInputFile(struct District_nodes* L) {
    struct District_nodes* P = L->Next;

    while (P != NULL && P->Next != NULL) {
        struct town_nodes* townPointer = P->Towns->Next;

        while (townPointer != NULL && townPointer->Next != NULL) {
            printf("%s | %s | %d\n", P->Name, townPointer->Name, townPointer->Population);
            townPointer = townPointer->Next;
        }
        P = P->Next;
    }
    printf("\n");
}

// DeleteList Methods
void DeleteList(struct District_nodes* L) {
    struct District_nodes* P;
    struct District_nodes* tail;
    struct District_nodes* temp;

    P = L->Next;

    while (P->Next != NULL)
        P = P->Next;


    tail = P;
    P = L->Next;

    L->Next = tail;
    tail->Previous = L;


    while (P != NULL && P->Next != NULL) {
        temp = P->Next;
        free(P);
        P = temp;
    }
}

void DeleteListTown(struct town_nodes* L) {
    struct town_nodes* P;
    struct town_nodes* tail;
    struct town_nodes* temp;

    P = L->Next;

    while (P->Next != NULL)
        P = P->Next;

    tail = P;
    P = L->Next;

    L->Next = tail;
    tail->Previous = L;

    while (P != NULL && P->Next != NULL) {
        temp = P->Next;
        free(P);
        P = temp;
    }
}


// Size Methods
int size(struct District_nodes* L) {
    struct District_nodes* P = L->Next;
    int count = 0;

    while (P != NULL && P->Next != NULL) {
        count += 1;
        P = P->Next;
    }

    return count;
}

int sizeTown(struct town_nodes* L) {
    struct town_nodes* P = L->Next;
    int count = 0;

    while (P != NULL && P->Next != NULL) {
        count += 1;
        P = P->Next;
    }

    return count;
}

// RadixSort Methods
int maxDistrictLength(struct District_nodes* L) {
    int maxLength = 0;
    struct District_nodes* P = L->Next;

    while (P != NULL && P->Next != NULL) {
        int length = strlen(P->Name);

        if (length > maxLength) {
            maxLength = length;
        }

        P = P->Next;
    }

    return maxLength;
}


struct District_nodes* makeDistrictsSameLength(struct District_nodes* L, int maxLength) {
    struct District_nodes* P = L->Next;

    while (P != NULL && P->Next != NULL) {
        int length = strlen(P->Name);

        if (length < maxLength) {
            int padding = maxLength - length;

            for (int i = 0; i < padding; i++) {
                strcat(P->Name, "$");
            }

        }
        P = P->Next;
    }

    return L;
}

void cleanDistricts(struct District_nodes* L) {
    struct District_nodes* P = L->Next;

    while (P != NULL) {
        int length = strlen(P->Name);
        int i = length - 1;
        while (i >= 0 && P->Name[i] == '$') {
            P->Name[i] = '\0';
            i--;
        }
        P = P->Next;
    }
}

char toLowerCase(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        letter = (char)(letter + 32);
    }

    return letter;
}

void copyDistricts(struct District_nodes* Destination, struct District_nodes* Source){

   struct District_nodes* node = Source->Next;

      while (node != NULL && node->Next != NULL) {

            struct District_nodes* newNode = (struct District_nodes*)malloc(sizeof(struct District_nodes));

            if (newNode == NULL) {
                printf("Out of memory!\n");
                break;
            }

            strcpy(newNode->Name, node->Name);
            newNode->Towns = MakeEmptyTowns(NULL);

            struct town_nodes* P = node->Towns->Next;
            while (P != NULL && P->Next != NULL) {

                    InsertTownLast(P->Name, P->Population, newNode->Towns);
                    P = P->Next;

            }

            InsertNodeLast(newNode, Destination);
            node = node->Next;

     }
}

void districtRadixSort(struct District_nodes* L){

    int maxLength = maxDistrictLength(L);

    makeDistrictsSameLength(L, maxLength);

    struct Characters_nodes* characters[27];
    characters[0] = MakeCharacterList('$');

    char digit = 'a';
    for(int i=1; i <= 26; i++){
        characters[i] = MakeCharacterList(digit);
        digit++;
    }

    int location = 0;
    char readChar;

    for (int i = maxLength - 1; i >= 0; i--) {

        struct District_nodes* P = L->Next;

        for(int j = 1; j <= size(L); j++){
            readChar = P->Name[i];

            while(toLowerCase(readChar) != characters[location]->Data){
                location++;
            }

            InsertDistrictLastToCharacter(characters[location], P);
            location = 0;
            P = P->Next;

        }
        DeleteList(L);

        for (int i = 0; i <= 26 ; i++) {
        struct District_nodes* node = characters[i]->Next;
        struct District_nodes* temp;

            while (node != NULL) {

                struct District_nodes* newNode = (struct District_nodes*)malloc(sizeof(struct District_nodes));

                if (newNode == NULL) {
                  printf("Out of memory!\n");
                  break;
                }

                strcpy(newNode->Name, node->Name);
                newNode->Towns = node->Towns;


                InsertNodeLast(newNode, L);
                temp = node;
                node = node->Next;
                free(temp);

            }
        }

        for(int i = 0; i <= 26; i++){
           characters[i]->Next = NULL;
        }
    }


    cleanDistricts(L);

    for (int i = 0; i <= 26; i++) {
        free(characters[i]);
    }

}

// TownsSort Methods
void swap(struct town_nodes* a, struct town_nodes* b) {
    int tempPopulation;
    char tempName[50];

    strcpy(tempName, a->Name);
    tempPopulation = a->Population;

    a->Population = b->Population;
    strcpy(a->Name, b->Name);

    b->Population = tempPopulation;
    strcpy(b->Name, tempName);
}

void sortTowns(struct town_nodes* L) {
    int size = sizeTown(L);

    if (size <= 1)
        return;

    struct town_nodes* town;
    struct town_nodes* nextTown;

    for (int i = 0; i < size - 1; i++) {
        town = L->Next;
        nextTown = town->Next;

        for (int j = 0; j < size - 1; j++) {
            if (town->Population > nextTown->Population) {
                swap(town, nextTown);

            }
            town = nextTown;
            nextTown = nextTown->Next;
        }

    }
}
