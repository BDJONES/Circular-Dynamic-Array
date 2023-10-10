# Circular Dynamic Array

---

## Description

The Circular Dynamic Array is a versatile data structure implemented in C++ that provides dynamic resizing capabilities. This data structure is designed to be easily imported into other C++ projects and supports a wide range of operations such as AddFront, AddBack, RemoveFront, RemoveBack, Sort, Select, and more. It efficiently grows and shrinks as needed, making it a valuable addition to your C++ projects. Moreover, this project leverages C++ Templates to ensure compatibility with multiple data types.

---

## Features

- **Dynamic Resizing:** The Circular Dynamic Array dynamically adjusts its size to manage memory efficiently, ensuring optimal space utilization.

- **Template-Based:** The use of C++ Templates allows this data structure to work seamlessly with various data types, making it highly adaptable for different scenarios.

- **Versatile Operations:** This data structure supports numerous operations, including AddFront, AddBack, RemoveFront, RemoveBack, Sort, Select, and more,
providing flexibility for a wide range of use cases.

---

## Usage

To integrate the Circular Dynamic Array into your C++ project, follow these steps:

1. Include the "CircularDynamicArray.h" header file in your project.

2. Create an instance of the CircularDynamicArray class using one of the available constructors, specifying the data type you intend to work with using templates.

3. Utilize the provided methods and operations to manipulate and manage your data efficiently.

--- 

## Constructors
The Circular Dynamic Array provides various constructors to accommodate different scenarios and data types through the use of templates:

CDA(): Default constructor.
CDA(int initialSize): Constructor with an initial size.
CDA(int s, elmtype init): Constructor with an initial size and a value to populate the array.
CDA(const CDA& src): Constructor to be used when copying values from another CDA array.
