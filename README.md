# Mini-Store-Menagment-Program
This project is a C application designed to manage a store's inventory.

## Introduction
This project represents a mini program for managing a store, allowing the seller to add products to a file (i.e., the store), view all products, modify product details, and delete products. By selecting the appropriate options, the seller can efficiently manage the store.

### Program Objective
The objective of this program is to enable the user to check the inventory of their store, add new products, and manage existing ones. Products are stored in a file, providing a permanent record of all products in the store.

### Program Components
The program consists of four classes, one structure, and the main class.

**Structure `Product`:**  
The `Product` structure stores all relevant product data, including the name, quantity in stock, and price per unit.

**Function `add_product_to_file`:**  
This function is used to add a newly created product to the product storage file. The seller enters the product name, quantity, and price, and the data is then written to the file.

**Function `display_products_from_file`:**  
This function displays all products that have been added to the file up to the point of reading.

**Function `delete_product`:**  
This function allows the deletion of a product from the file based on the product name.

**Function `modify_product_data`:**  
This function allows the seller to modify the quantity and price of a product in the file based on the product's name.

### Program Development
The program begins by defining the `Product` structure, which forms the basis of the project. Key functions for adding, modifying, reading, and deleting data are implemented.

### Program Functionality and Screenshots
When the program is executed, the user is presented with various options for managing products. The options include:

1. **Add a product:** Enter the product name, quantity, and price.
2. **View all products:** Display all products stored in the file.
3. **Delete a product:** Enter the name of the product to be deleted from the file.
4. **Modify a product:** Enter the name of the product to modify its details.
5. **Exit the program:** Close the application.

## Conclusion
This program is designed for sellers who want to manage their store inventory. Through this project, I learned how to input, display, delete, and modify data in a file, which are the core functionalities of this program.

