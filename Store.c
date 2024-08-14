#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 100

typedef struct {
    char *name;
    int quantity;
    float price;
} Product;

void free_product(Product* product) {
    free(product->name);
}

void add_product_to_file(const char* file_name) {
    Product new_product;

    printf("Enter product name: \n");
    char product_name[MAX_STRING_LENGTH];
    fgets(product_name, sizeof(product_name), stdin);
    product_name[strcspn(product_name, "\n")] = '\0';

    new_product.name = (char*)malloc(strlen(product_name) + 1);
    if (new_product.name == NULL) {
        printf("Memory allocation error.\n");
        return;
    }
    strcpy(new_product.name, product_name);

    printf("Enter quantity: \n");
    scanf("%d", &new_product.quantity);
    printf("Enter price: \n");
    scanf("%f", &new_product.price);
    getchar(); 

    FILE* file = fopen(file_name, "a");
    if (file == NULL) {
        printf("Error opening file for adding product.\n");
        free_product(&new_product);
        return;
    }

    fprintf(file, "%s, %d, %.2f\n", new_product.name, new_product.quantity, new_product.price);

    fclose(file);
    free_product(&new_product);

    printf("Product successfully added to file.\n");
}

void display_products_from_file(const char* file_name) {
    FILE* file = fopen(file_name, "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    Product read_product;
    read_product.name = (char*)malloc(MAX_STRING_LENGTH);
    if (read_product.name == NULL) {
        printf("Memory allocation error.\n");
        fclose(file);
        return;
    }

    printf("\nAll products from the file:\n");
    printf("---------------------------------\n");

    char line[MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^,], %d, %f", read_product.name, &read_product.quantity, &read_product.price);
        printf("Name: %s\n", read_product.name);
        printf("Quantity: %d\n", read_product.quantity);
        printf("Price: %.2f\n", read_product.price);
        printf("---------------------------------\n");
    }

    free(read_product.name);
    fclose(file);
}

void delete_product(const char* file_name, const char* product_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    Product read_product;
    read_product.name = (char*)malloc(MAX_STRING_LENGTH);
    if (read_product.name == NULL) {
        printf("Memory allocation error.\n");
        fclose(file);
        fclose(temp_file);
        return;
    }

    char line[MAX_STRING_LENGTH];
    int deleted = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^,], %d, %f", read_product.name, &read_product.quantity, &read_product.price);
        if (strcmp(read_product.name, product_name) != 0) {
            fprintf(temp_file, "%s, %d, %.2f\n", read_product.name, read_product.quantity, read_product.price);
        } else {
            deleted = 1;
        }
    }

    free(read_product.name);
    fclose(file);
    fclose(temp_file);

    if (remove(file_name) != 0) {
        printf("Error deleting the original file.\n");
        return;
    }
    if (rename("temp.txt", file_name) != 0) {
        printf("Error renaming the temporary file.\n");
        return;
    }

    if (deleted) {
        printf("Product \"%s\" was successfully deleted from the file.\n", product_name);
    } else {
        printf("Product \"%s\" not found in the file.\n", product_name);
    }
}

void edit_product_data(const char* file_name, const char* product_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    Product read_product;
    read_product.name = (char*)malloc(MAX_STRING_LENGTH);
    if (read_product.name == NULL) {
        printf("Memory allocation error.\n");
        fclose(file);
        fclose(temp_file);
        return;
    }

    char line[MAX_STRING_LENGTH];
    int edited = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%[^,], %d, %f", read_product.name, &read_product.quantity, &read_product.price);
        if (strcmp(read_product.name, product_name) == 0) {
            printf("Product \"%s\" found.\n", product_name);
            printf("Enter new quantity: ");
            scanf("%d", &read_product.quantity);
            printf("Enter new price: ");
            scanf("%f", &read_product.price);
            edited = 1;
        }
        fprintf(temp_file, "%s, %d, %.2f\n", read_product.name, read_product.quantity, read_product.price);
    }

    free(read_product.name);
    fclose(file);
    fclose(temp_file);

    if (!edited) {
        printf("Product \"%s\" not found in the file.\n", product_name);
        remove("temp.txt");
        return;
    }

    if (remove(file_name) != 0) {
        printf("Error deleting the original file.\n");
        return;
    }
    if (rename("temp.txt", file_name) != 0) {
        printf("Error renaming the temporary file.\n");
        return;
    }

    printf("Product data for \"%s\" successfully edited.\n", product_name);
}

int main() {
    int option;

    do {
        printf("\nChoose an option:\n");
        printf("1. Add product to file\n");
        printf("2. Display all products from file\n");
        printf("3. Delete product from file\n");
        printf("4. Edit product data\n");
        printf("5. Exit (0)\n");
        scanf("%d", &option);
        getchar(); 

        switch (option) {
        case 0:
            printf("Exiting program.\n");
            break;
        case 1:
            add_product_to_file("file.txt");
            break;
        case 2:
            display_products_from_file("file.txt");
            break;
        case 3: {
            char product_name[MAX_STRING_LENGTH];
            printf("Enter the name of the product you want to delete: ");
            fgets(product_name, sizeof(product_name), stdin);
            product_name[strcspn(product_name, "\n")] = '\0';
            delete_product("file.txt", product_name);
            break;
        }
        case 4: {
            char product_name[MAX_STRING_LENGTH];
            printf("Enter the name of the product whose data you want to edit: ");
            fgets(product_name, sizeof(product_name), stdin);
            product_name[strcspn(product_name, "\n")] = '\0';
            edit_product_data("file.txt", product_name);
            break;
        }
        default:
            printf("Unknown option.\n");
            break;
        }
    } while (option != 0);

    return 0;
}
