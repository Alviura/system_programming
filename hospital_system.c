#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Patient structure
struct Patient {
    char *name;
    int id;
    char *medicalHistory;
    struct Patient *next; // pointer to link each patient record to the next one
};

// Function prototypes
typedef struct Patient Patient;
Patient* addPatient(Patient *head, char *name, int id, char *history);
void updateMedicalHistory(Patient *head, int id, char *newHistory);
Patient* removePatient(Patient *head, int id);
void displayPatients(Patient *head);
void freeAllPatients(Patient *head);

// Main function with menu
int main() {
    Patient *head = NULL;
    int choice, id;
    char name[50], history[100];

    do {
        printf("\nPATIENT RECORDS SYSTEM\n");
        printf("1. Add Patient\n");
        printf("2. Update Medical History\n");
        printf("3. Remove Patient\n");
        printf("4. Display All Patients\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume newline character after entering choice

        switch (choice) {
            case 1:
                printf("Enter Patient Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0; // Remove newline
                printf("Enter Patient ID: ");
                scanf("%d", &id);
                getchar(); // Consume newline
                printf("Enter Medical History: ");
                fgets(history, sizeof(history), stdin);
                history[strcspn(history, "\n")] = 0; // Remove newline

                head = addPatient(head, name, id, history);
                break;

            case 2:
                printf("Enter Patient ID to update: ");
                scanf("%d", &id);
                getchar();
                printf("Enter new Medical History: ");
                fgets(history, sizeof(history), stdin);
                history[strcspn(history, "\n")] = 0; // Remove newline

                updateMedicalHistory(head, id, history);
                break;

            case 3:
                printf("Enter Patient ID to remove: ");
                scanf("%d", &id);
                head = removePatient(head, id);
                break;

            case 4:
                displayPatients(head);
                break;

            case 5:
                freeAllPatients(head);
                printf("Exiting program. Memory freed.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to add a new patient
Patient* addPatient(Patient *head, char *name, int id, char *history){
    Patient *newPatient = (Patient*) malloc(sizeof(Patient));
    if (!newPatient){
        printf("Memory allocation failed!\n");
        return head;
    }

    newPatient->name = strdup(name); // strdup - to duplicate the strings(to avoid pointer issues)
    newPatient->id = id;
    newPatient->medicalHistory = strdup(history);
    newPatient->next = head; // insert at the beginning of the list

    printf("Patient added successfully!\n");
    return newPatient; // Return new head of the list
}

// Function to update medical history of a patient
void updateMedicalHistory(Patient *head, int id, char *newHistory) {
    Patient *temp = head;
    while (temp) {
        if (temp->id == id) {
            free(temp->medicalHistory); // free old history
            temp->medicalHistory = strdup(newHistory); //Allocate and copy new history
            printf("Medical history updated!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Patient not found!\n");
}

// Function to remove a patient
Patient* removePatient(Patient *head, int id) {
    Patient *temp = head, *prev = NULL;

    while (temp) {
        if (temp->id == id) {
            if (prev){
                prev->next = temp->next; // Skip the node
            } else{
                head = temp->next; // update head if removing first patient
            }

            free(temp->name);
            free(temp->medicalHistory);
            free(temp);
            printf("Patient removed!\n");
            return head;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Patient not found!\n");
    return head;
}

// Function to display all patients
void displayPatients(Patient *head) {
    Patient *temp = head;
    if (!temp) {
        printf("No patients found!\n");
        return;
    }
    while (temp) {
        printf("ID: %d, Name: %s, History: %s\n", temp->id, temp->name, temp->medicalHistory);
        temp = temp->next;
    }
}

// Function to free all allocated memory before exiting
void freeAllPatients(Patient *head) {
    Patient *temp;
    while (head) {
        temp = head;
        head = head->next;

        free(temp->name);
        free(temp->medicalHistory);
        free(temp);
    }
}
