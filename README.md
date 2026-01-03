# 📇 Person Directory Application (C)

A simple **console-based Person Directory application written in C**.  
This program allows users to **add, delete, search, list, and permanently store people information** using file operations.

The project is designed to practice **structs, enums, typedefs, functions, and file I/O** in C.

---

## 🚀 Features

- Add a new person
- Delete a selected person (even if multiple people share the same name)
- Search people by first name
- List all stored people
- Save data permanently to a file (`people.txt`)
- Load data automatically when the program starts

---

## 🧠 Concepts Used

- **Struct** – To represent a person  
- **Typedef** – To simplify struct usage  
- **Enum** – For menu options  
- **Functions** – Modular program design  
- **File I/O** – Persistent data storage using `fopen`, `fprintf`, `fscanf`

---

## 🧱 Data Structure

```c
typedef struct {
    char firstName[50];
    char lastName[50];
    char phoneNumber[15];
    int age;
} Person;

##Menu Options
1. Add Person
2. Delete Person
3. Search Person
4. List People
5. Exit

##File Format (people.txt)
FirstName LastName PhoneNumber Age

























