#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROPERTIES 100
#define FILE_NAME "properties.dat"

// Property structure
typedef struct
{
    int id;
    char address[100];
    int num_rooms;
    int floor;
    double price;
} Property;

// Function prototypes
void menu();
void addProperty(Property properties[], int *numProperties);
void viewProperties(Property properties[], int numProperties);
void updateProperty(Property properties[], int numProperties);
void deleteProperty(Property properties[], int *numProperties);
void savePropertiesToFile(Property properties[], int numProperties);
void loadPropertiesFromFile(Property properties[], int *numProperties);

//main function
int main()
{
    Property properties[MAX_PROPERTIES];
    int numProperties = 0;
    int choice;

    loadPropertiesFromFile(properties, &numProperties);

    do
    {
        menu();

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            addProperty(properties, &numProperties);
            break;
        case 2:
            viewProperties(properties, numProperties);
            break;
        case 3:
            updateProperty(properties, numProperties);
            break;
        case 4:
            deleteProperty(properties, &numProperties);
            break;
        case 5:
            savePropertiesToFile(properties, numProperties);
            break;
        case 6:
            printf("Exiting program.\nThanks you.\nSee ya!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
    while(choice != 6);

    return 0;
}

// Display menu
void menu()
{
    printf("\nWELCOME TO GRAY PANTHERS, A WELL-KNOWNED REAL ESTATE COMPANY IN BANGLADESH\n\n");
    printf("Would you like to work with us? Here we go!\n");
    printf("\n====== REAL ESTATE PROPERTY MANAGEMENT ======\n\n");
    printf("1. Add Property\n");
    printf("2. View Properties\n");
    printf("3. Update Property\n");
    printf("4. Delete Property\n");
    printf("5. Save Properties\n");
    printf("6. Exit Program\n");
}

// Add a property to the array
void addProperty(Property properties[], int *numProperties)
{
    if(*numProperties >= MAX_PROPERTIES)
    {
        printf("Maximum number of properties reached.\n");
    }

    Property property;

    printf("Enter property ID: ");
    scanf("%d", &property.id);

    printf("Enter property address: ");
    fflush(stdin);
    gets(property.address);

    printf("Enter number of rooms: ");
    scanf("%d", &property.num_rooms);

    printf("Enter number of floor: ");
    scanf("%d", &property.floor);

    printf("Enter property price in $ : ");
    scanf("%lf", &property.price);

    properties[*numProperties] = property;
    (*numProperties)++;

    printf("Property added successfully.\n");
}

// View all properties in the array
void viewProperties(Property properties[], int numProperties)
{
    if(numProperties == 0)
    {
        printf("No properties to display.\n");

        return;
    }

    printf("\n========== ALL PROPERTIES ==========\n");

    for(int i = 0; i < numProperties; i++)
    {
        printf("Property ID: %d\n", properties[i].id);
        printf("Address: %s\n", properties[i].address);
        printf("Number of rooms: %d\n", properties[i].num_rooms);
        printf("Number of floor: %d\n", properties[i].floor);
        printf("Price in $ : %.3lf$\n", properties[i].price);
        printf("====================================\n");
    }
}

// Update an existing property
void updateProperty(Property properties[], int numProperties)
{
    if(numProperties == 0)
    {
        printf("No properties available to update.\n");

        return;
    }
    int propertyId;

    printf("Enter the ID of the property to update: ");
    scanf("%d", &propertyId);

    int propertyIndex = -1;
    for(int i = 0; i < numProperties; i++)
    {
        if(properties[i].id == propertyId)
        {
            propertyIndex = i;
            break;
        }
    }

    if(propertyIndex == -1)
    {
        printf("Property with ID %d not found.\n", propertyId);

        return;
    }

    printf("Enter the new address: ");
    fflush(stdin);
    gets(properties[propertyIndex].address);

    printf("Enter the new number of rooms: ");
    scanf("%d", &properties[propertyIndex].num_rooms);

    printf("Enter the new number of floor: ");
    scanf("%d", &properties[propertyIndex].floor);

    printf("Enter the new price in $ : ");
    scanf("%lf", &properties[propertyIndex].price);


    printf("Property updated successfully.\n");
}
// Delete a property from the array
void deleteProperty(Property properties[], int *numProperties)
{
    if(*numProperties == 0)
    {
        printf("No properties available to delete.\n");

        return;
    }
    int propertyId;

    printf("Enter the ID of the property to delete: ");
    scanf("%d", &propertyId);

    int propertyIndex = -1;
    for(int i = 0; i < *numProperties; i++)
    {
        if(properties[i].id == propertyId)
        {
            propertyIndex = i;
            break;
        }
    }

    if(propertyIndex == -1)
    {
        printf("Property with ID %d not found.\n", propertyId);

        return;
    }

// Shift remaining properties to fill the gap
    for(int i = propertyIndex; i < *numProperties - 1; i++)
    {
        properties[i] = properties[i + 1];
    }

    (*numProperties)--;

    printf("Property deleted successfully.\n");
}

// Save properties to a file
void savePropertiesToFile(Property properties[], int numProperties)
{
    FILE *file = fopen(FILE_NAME, "wb");
    if(file == NULL)
    {
        printf("Error opening file.\n");

        return;
    }
    fwrite(properties, sizeof(Property), numProperties, file);

    fclose(file);

    printf("Properties saved to file.\n");
}

// Load properties from a file
void loadPropertiesFromFile(Property properties[], int *numProperties)
{
    FILE *file = fopen(FILE_NAME, "rb");
    if(file == NULL)
    {
        printf("File not found. Creating a new file.\n");

        return;
    }
    *numProperties = fread(properties, sizeof(Property), MAX_PROPERTIES, file);

    fclose(file);

    printf("Properties loaded from file.\n");
}
