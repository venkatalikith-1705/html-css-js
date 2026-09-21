#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "nurses.dat"

typedef struct {
    int id;
    char name[50];
    char department[50];
    char shift[20];
} Nurse;

void addNurse() {
    Nurse n;
    FILE *fp = fopen(FILE_NAME, "ab");

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Nurse ID: ");
    scanf("%d", &n.id);

    printf("Enter Name: ");
    getchar(); 
    fgets(n.name, sizeof(n.name), stdin);
    n.name[strcspn(n.name, "\n")] = 0;

    printf("Enter Department: ");
    fgets(n.department, sizeof(n.department), stdin);
    n.department[strcspn(n.department, "\n")] = 0;

    printf("Enter Shift: ");
    fgets(n.shift, sizeof(n.shift), stdin);
    n.shift[strcspn(n.shift, "\n")] = 0;

    fwrite(&n, sizeof(Nurse), 1, fp);
    fclose(fp);

    printf("\nNurse added successfully!\n");
}

void listNurses() {
    Nurse n;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (!fp) {
        printf("No records found.\n");
        return;
    }

    printf("\n--- Nurse Records ---\n");
    while (fread(&n, sizeof(Nurse), 1, fp)) {
        printf("ID: %d\nName: %s\nDepartment: %s\nShift: %s\n\n",
               n.id, n.name, n.department, n.shift);
    }

    fclose(fp);
}

void searchNurse() {
    int id;
    Nurse n;
    int found = 0;

    printf("\nEnter Nurse ID to search: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb");

    if (!fp) {
        printf("File error.\n");
        return;
    }

    while (fread(&n, sizeof(Nurse), 1, fp)) {
        if (n.id == id) {
            printf("\nRecord Found:\n");
            printf("ID: %d\nName: %s\nDepartment: %s\nShift: %s\n",
                   n.id, n.name, n.department, n.shift);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No nurse found with ID %d.\n", id);

    fclose(fp);
}

void deleteNurse() {
    int id, found = 0;
    Nurse n;

    printf("\nEnter Nurse ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        printf("File error.\n");
        return;
    }

    while (fread(&n, sizeof(Nurse), 1, fp)) {
        if (n.id == id) {
            found = 1;
            continue;
        }
        fwrite(&n, sizeof(Nurse), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Nurse deleted successfully.\n");
    else
        printf("Nurse with ID %d not found.\n", id);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Nurse Management System ---\n");
        printf("1. Add Nurse\n");
        printf("2. List Nurses\n");
        printf("3. Search Nurse\n");
        printf("4. Delete Nurse\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addNurse(); break;
            case 2: listNurses(); break;
            case 3: searchNurse(); break;
            case 4: deleteNurse(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
