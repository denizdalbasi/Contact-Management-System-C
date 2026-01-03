#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 1000

/*
 * Enum: Menu
 * -------------------------
 * Represents menu options shown to the user.
 * Each value corresponds to an action in the program.
 */
enum Menu {
    ADD = 1,
    DELETE,
    SEARCH,
    LIST,
    EXIT
};

/*
 * Struct: Person
 * -------------------------
 * Holds personal information for a single person.
 *
 * firstName    : Person's first name
 * lastName     : Person's last name
 * phoneNumber  : Person's phone number
 * age          : Person's age
 */
typedef struct {
    char firstName[50];
    char lastName[50];
    char phoneNumber[15];
    int age;
} Person;

/*
 * Function: load_people
 * -------------------------
 * Loads people information from a text file into an array.
 *
 * filename : Name of the file to read from
 * people   : Array of Person structs to be filled
 * max      : Maximum number of people that can be loaded
 *
 * returns  : Number of people successfully loaded from the file
 */
int load_people(const char *filename, Person people[], int max) {
    FILE *file = fopen(filename, "r");
    int count = 0;

    if (file == NULL) {
        return 0;
    }

    while (count < max &&
           fscanf(file, "%s %s %s %d",
                  people[count].firstName,
                  people[count].lastName,
                  people[count].phoneNumber,
                  &people[count].age) == 4) {
        count++;
    }

    fclose(file);
    return count;
}

/*
 * Function: save_people
 * -------------------------
 * Saves all people information from memory into a file.
 *
 * filename : Name of the file to write to
 * people   : Array of Person structs to save
 * count    : Number of people currently stored
 *
 * returns  : void
 */
void save_people(const char *filename, Person people[], int count) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s %d\n",
                people[i].firstName,
                people[i].lastName,
                people[i].phoneNumber,
                people[i].age);
    }

    fclose(file);
}

/*
 * Function: add_person
 * -------------------------
 * Adds a new person to the list by asking the user for input.
 *
 * people : Array of Person structs
 * count  : Pointer to current number of people
 *
 * returns: void
 */
void add_person(Person people[], int *count) {
    if (*count >= MAX_PEOPLE) {
        printf("List is full\n");
        return;
    }

    printf("Enter first name: ");
    scanf("%s", people[*count].firstName);

    printf("Enter last name: ");
    scanf("%s", people[*count].lastName);

    printf("Enter phone number: ");
    scanf("%s", people[*count].phoneNumber);

    printf("Enter age: ");
    scanf("%d", &people[*count].age);

    (*count)++;
    printf("Person added successfully\n");
}

/*
 * Function: list_people
 * -------------------------
 * Prints all people currently stored in memory.
 *
 * people : Array of Person structs
 * count  : Number of people in the list
 *
 * returns: Nothing void
 */
void list_people(Person people[], int count) {
    if (count == 0) {
        printf("No people found\n");
        return;
    }

    printf("\n--- People List ---\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s %s | Phone: %s | Age: %d\n",
               people[i].firstName,
               people[i].lastName,
               people[i].phoneNumber,
               people[i].age);
    }
}

/*
 * Function: search_person
 * -------------------------
 * Searches for people by first name and displays all matches.
 *
 * people : Array of Person structs
 * count  : Number of people in the list
 *
 * returns: void
 */
void search_person(Person people[], int count) {
    char searchName[50];
    int found = 0;

    if (count == 0) {
        printf("No people to search\n");
        return;
    }

    printf("Enter first name to search: ");
    scanf("%s", searchName);

    printf("\n--- Search Results ---\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(people[i].firstName, searchName) == 0) {
            printf("%d) %s %s | Phone: %s | Age: %d\n",
                   i + 1,
                   people[i].firstName,
                   people[i].lastName,
                   people[i].phoneNumber,
                   people[i].age);
            found = 1;
        }
    }

    if (!found) {
        printf("No person found with that name\n");
    }
}

/*
 * Function: delete_person
 * -------------------------
 * Deletes a selected person by first name.
 * If multiple people have the same name, user selects one.
 *
 * people : Array of Person structs
 * count  : Pointer to number of people in the list
 *
 * returns: void
 */
void delete_person(Person people[], int *count) {
    char deleteName[50];
    int indexes[MAX_PEOPLE];
    int foundCount = 0;
    int choice;

    if (*count == 0) {
        printf("No people to delete\n");
        return;
    }

    printf("Enter first name to delete: ");
    scanf("%s", deleteName);

    for (int i = 0; i < *count; i++) {
        if (strcmp(people[i].firstName, deleteName) == 0) {
            indexes[foundCount++] = i;
            printf("%d) %s %s | Phone: %s | Age: %d\n",
                   foundCount,
                   people[i].firstName,
                   people[i].lastName,
                   people[i].phoneNumber,
                   people[i].age);
        }
    }

    if (foundCount == 0) {
        printf("No person found with that name\n");
        return;
    }

    printf("Choose a person to delete (1-%d): ", foundCount);
    scanf("%d", &choice);

    if (choice < 1 || choice > foundCount) {
        printf("Invalid choice\n");
        return;
    }

    int deleteIndex = indexes[choice - 1];

    for (int i = deleteIndex; i < *count - 1; i++) {
        people[i] = people[i + 1];
    }

    (*count)--;
    printf("Person deleted successfully\n");
}

/*
 * Function: main
 * -------------------------
 * Program entry point.
 * Displays menu, handles user input, and calls related functions.
 *
 * returns: 0 on successful program termination
 */
int main(void) {
    Person people[MAX_PEOPLE];
    int count = load_people("people.txt", people, MAX_PEOPLE);
    int answer;

    printf("Welcome to our project\n");

    while (1) {
        printf("\n1.Add 2.Delete 3.Search 4.List 5.Exit\n");
        printf("Your choice: ");

        if (scanf("%d", &answer) != 1) {
            while (getchar() != '\n');
            printf("Invalid input, please enter a number\n");
            continue;
        }

        switch (answer) {
            case ADD:
                add_person(people, &count);
                break;
            case DELETE:
                delete_person(people, &count);
                break;
            case SEARCH:
                search_person(people, count);
                break;
            case LIST:
                list_people(people, count);
                break;
            case EXIT:
                save_people("people.txt", people, count);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
