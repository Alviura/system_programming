#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a struct for traffic sensors
typedef struct TrafficSensor {
    int sensorID;        
    char location[50];   
    int status;          // 1 = Active, 0 = Inactive
    struct TrafficSensor *next; // Pointer to the next sensor in the linked list
} TrafficSensor;

// Function prototypes
TrafficSensor* addSensor(TrafficSensor *head, int id, const char *location, int status);
void displaySensors(TrafficSensor *head);
TrafficSensor* removeSensor(TrafficSensor *head, int id);
void freeSensors(TrafficSensor *head);
void menu();
int validateSensorData(int id, int status);
void detectMemoryCorruption(TrafficSensor *head);

int main() {
    TrafficSensor *head = NULL;  // Initialize head pointer to NULL
    int choice, id, status;
    char location[50];

    while (1) {
        menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter Sensor ID (positive integer): ");
                if (scanf("%d", &id) != 1 || id <= 0) {
                    printf("Invalid Sensor ID. Must be a positive number.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    continue;
                }
                getchar();
                
                printf("Enter Location: ");
                fgets(location, sizeof(location), stdin);
                location[strcspn(location, "\n")] = 0; // Remove newline character
                
                printf("Enter Status (1 = Active, 0 = Inactive): ");
                if (scanf("%d", &status) != 1 || (status != 0 && status != 1)) {
                    printf("Invalid Status. Must be 0 or 1.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    continue;
                }
                
                if (validateSensorData(id, status)) {
                    head = addSensor(head, id, location, status);
                } else {
                    printf("Sensor data validation failed. Sensor not added.\n");
                }
                break;

            case 2:
                detectMemoryCorruption(head); // Detects corrupted memory before displaying sensors
                displaySensors(head);
                break;

            case 3:
                printf("Enter Sensor ID to remove: ");
                if (scanf("%d", &id) != 1 || id <= 0) {
                    printf("Invalid Sensor ID. Must be a positive number.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    continue;
                }
                head = removeSensor(head, id);
                break;

            case 4:
                freeSensors(head); // Ensure all allocated memory is freed before exiting
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Function to display the menu options
void menu() {
    printf("\nTraffic Sensor System\n");
    printf("1. Add a sensor\n");
    printf("2. Display all sensors\n");
    printf("3. Remove a sensor\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Function to add a new sensor to the linked list
TrafficSensor* addSensor(TrafficSensor *head, int id, const char *location, int status) {
    TrafficSensor *newSensor = (TrafficSensor*)malloc(sizeof(TrafficSensor));
    if (!newSensor) {
        printf("Memory allocation failed!\n");
        return head;
    }

    // Initialize sensor attributes safely
    newSensor->sensorID = id;
    strncpy(newSensor->location, location, sizeof(newSensor->location) - 1); // Prevent buffer overflow
    newSensor->location[sizeof(newSensor->location) - 1] = '\0'; // Ensure null-termination
    newSensor->status = status;
    newSensor->next = head; // Insert at the beginning

    printf("Sensor %d added successfully.\n", id);
    return newSensor;
}

// Function to display all sensors in the system
void displaySensors(TrafficSensor *head) {
    if (!head) {
        printf("No sensors in the system.\n");
        return;
    }

    printf("\nTraffic Sensors:\n");
    while (head) {
        printf("ID: %d | Location: %s | Status: %s\n", 
               head->sensorID, 
               head->location, 
               head->status ? "Active" : "Inactive");
        head = head->next;
    }
}

// Function to remove a sensor by ID from the linked list
TrafficSensor* removeSensor(TrafficSensor *head, int id) {
    if (!head) {
        printf("No sensors to remove.\n");
        return NULL;
    }

    TrafficSensor *temp = head, *prev = NULL;
    if (temp && temp->sensorID == id) {
        head = temp->next;
        free(temp);
        printf("Sensor %d removed successfully.\n", id);
        return head;
    }

    while (temp && temp->sensorID != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Sensor %d not found.\n", id);
        return head;
    }

    prev->next = temp->next;
    free(temp);
    printf("Sensor %d removed successfully.\n", id);
    return head;
}

// Function to free all allocated memory before exiting
void freeSensors(TrafficSensor *head) {
    TrafficSensor *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Memory freed. Exiting program.\n");
}

// Function to validate sensor data
int validateSensorData(int id, int status) {
    if (id <= 0) {
        printf("Error: Sensor ID must be a positive integer.\n");
        return 0;
    }
    if (status != 0 && status != 1) {
        printf("Error: Sensor status must be 0 (Inactive) or 1 (Active).\n");
        return 0;
    }
    return 1;
}

// Function to detect memory corruption
void detectMemoryCorruption(TrafficSensor *head) {
    TrafficSensor *current = head;
    while (current) {
        if (current->sensorID <= 0 || (current->status != 0 && current->status != 1)) {
            printf("Warning: Possible memory corruption detected in Sensor ID %d!\n", current->sensorID);
        }
        current = current->next;
    }
}