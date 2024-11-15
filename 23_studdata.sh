#!/bin/bash
DB_FILE="student_database.txt"
show_menu() {
    echo "Select an operation:"
    echo "a) Insert a record"
    echo "b) Delete a record"
    echo "c) Update a record"
    echo "d) Search for a record"
    echo "e) Exit"
    read -p "Enter your choice: " choice
}
insert_record() {
    read -p "Enter Student ID: " id
    read -p "Enter Student Name: " name
    read -p "Enter Student Grade: " grade
    echo "$id,$name,$grade" >> "$DB_FILE"
    echo "Record inserted successfully."
}
delete_record() {
    read -p "Enter Student ID to delete: " id
    if grep -q "^$id," "$DB_FILE"; then
        grep -v "^$id," "$DB_FILE" > temp_file && mv temp_file "$DB_FILE"
        echo "Record with ID $id deleted successfully."
    else
        echo "Record with ID $id not found."
    fi
}
update_record() {
    read -p "Enter Student ID to update: " id
    if grep -q "^$id," "$DB_FILE"; then
        read -p "Enter new Student Name: " name
        read -p "Enter new Student Grade: " grade
        grep -v "^$id," "$DB_FILE" > temp_file
        echo "$id,$name,$grade" >> temp_file
        mv temp_file "$DB_FILE"
        echo "Record with ID $id updated successfully."
    else
        echo "Record with ID $id not found."
    fi
}
search_record() {
    read -p "Enter Student ID to search: " id
    if grep -q "^$id," "$DB_FILE"; then
        echo "Record found:"
        grep "^$id," "$DB_FILE"
    else
        echo "Record with ID $id not found."
    fi
}
while true; do
    show_menu
    case $choice in
        a|A) insert_record ;;
        b|B) delete_record ;;
        c|C) update_record ;;
        d|D) search_record ;;
        e|E) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid option. Please try again." ;;
    esac
done






























# Sure, let's break down the code for this shell script that implements a simple student database system with CRUD operations.

# 1. Concept, Uses, and Purpose
# Concept: This script represents a basic file-based database system for managing student records. It allows for inserting, deleting, updating, and searching student information. It demonstrates CRUD operations (Create, Read, Update, Delete) and how shell scripting can manipulate data stored in a text file (student_database.txt).

# Uses: File-based databases are useful in lightweight applications, demos, or scenarios where installing a complex database system is unnecessary. Here, a shell script offers an easy way to demonstrate database management without external dependencies.

# Purpose: This code helps in understanding shell scripting basics for database operations, string handling, pattern matching, and file redirection.

# 2. Logic and Algorithm
# Insert a Record: Prompt for student ID, name, and grade, then append this information to the database file.
# Delete a Record: Check for the ID in the file. If found, filter out that line using grep and update the file.
# Update a Record: Locate the student by ID, delete the old entry, and append the updated information.
# Search for a Record: Search by student ID, and if the ID exists, display the information.
# This approach is based on simple pattern matching (grep), file manipulation (redirecting output), and appending data.

# 3. Line-by-Line Code Explanation
# bash
# Copy code
# #!/bin/bash
# DB_FILE="student_database.txt"  # Define the file that stores student records.

# show_menu() {  # Display options to the user.
#     echo "Select an operation:"
#     echo "a) Insert a record"
#     echo "b) Delete a record"
#     echo "c) Update a record"
#     echo "d) Search for a record"
#     echo "e) Exit"
#     read -p "Enter your choice: " choice  # Capture the user's choice.
# }

# insert_record() {  # Function to insert a new student record.
#     read -p "Enter Student ID: " id
#     read -p "Enter Student Name: " name
#     read -p "Enter Student Grade: " grade
#     echo "$id,$name,$grade" >> "$DB_FILE"  # Append data to the database file.
#     echo "Record inserted successfully."
# }

# delete_record() {  # Function to delete a student record.
#     read -p "Enter Student ID to delete: " id
#     if grep -q "^$id," "$DB_FILE"; then  # Check if the ID exists in the file.
#         grep -v "^$id," "$DB_FILE" > temp_file && mv temp_file "$DB_FILE"  # Filter out the record and update the file.
#         echo "Record with ID $id deleted successfully."
#     else
#         echo "Record with ID $id not found."
#     fi
# }

# update_record() {  # Function to update a student's record.
#     read -p "Enter Student ID to update: " id
#     if grep -q "^$id," "$DB_FILE"; then  # Check if the record exists.
#         read -p "Enter new Student Name: " name
#         read -p "Enter new Student Grade: " grade
#         grep -v "^$id," "$DB_FILE" > temp_file  # Remove old record.
#         echo "$id,$name,$grade" >> temp_file  # Add updated record.
#         mv temp_file "$DB_FILE"  # Replace the original file.
#         echo "Record with ID $id updated successfully."
#     else
#         echo "Record with ID $id not found."
#     fi
# }

# search_record() {  # Function to search for a student's record.
#     read -p "Enter Student ID to search: " id
#     if grep -q "^$id," "$DB_FILE"; then  # Check if the record exists.
#         echo "Record found:"
#         grep "^$id," "$DB_FILE"  # Display the record.
#     else
#         echo "Record with ID $id not found."
#     fi
# }

# while true; do
#     show_menu  # Display the menu in a loop.
#     case $choice in
#         a|A) insert_record ;;  # Call insert function if 'a' is selected.
#         b|B) delete_record ;;  # Call delete function if 'b' is selected.
#         c|C) update_record ;;  # Call update function if 'c' is selected.
#         d|D) search_record ;;  # Call search function if 'd' is selected.
#         e|E) echo "Exiting..."; exit 0 ;;  # Exit the script if 'e' is selected.
#         *) echo "Invalid option. Please try again." ;;  # Handle invalid input.
#     esac
# done
# 4. Potential External Examiner Questions and Answers
# What is the purpose of the DB_FILE variable?

# The DB_FILE variable stores the filename for the database, making it easier to manage file operations in a single location within the script.
# How does the script check if a student ID exists before performing operations like delete or update?

# It uses grep -q "^$id," "$DB_FILE", which checks if a line beginning with the ID exists in the file.
# Why does the update_record function use temp_file?

# temp_file is used as a temporary file to store updated records without modifying the original file directly, ensuring atomicity.
# Can this script handle cases where multiple students have the same ID?

# No, the script assumes unique IDs for each student, as it uses IDs to identify records.
# How does the script calculate the average seek time?

# This code does not involve seek time calculation, as it's a database script, not related to disk scheduling.



















# Step 1: Script Overview
# This script is a simple student database management system written in Bash. It allows the user to perform the following operations on a file-based database (student_database.txt):

# Insert a record (adding new student information)
# Delete a record (removing student information by ID)
# Update a record (modifying student information by ID)
# Search for a record (retrieving student information by ID)
# Exit the program
# Each student record is stored in the format ID,Name,Grade, with each field separated by a comma.

# Step 2: Key Components of the Script
# 1. show_menu Function
# Displays a menu of options for the user to choose from. This function asks the user to select an operation:

# bash
# Copy code
# show_menu() {
#     echo "Select an operation:"
#     echo "a) Insert a record"
#     echo "b) Delete a record"
#     echo "c) Update a record"
#     echo "d) Search for a record"
#     echo "e) Exit"
#     read -p "Enter your choice: " choice
# }
# The function prompts the user for their choice and stores it in the choice variable.
# 2. insert_record Function
# Adds a new student record to student_database.txt:

# bash
# Copy code
# insert_record() {
#     read -p "Enter Student ID: " id
#     read -p "Enter Student Name: " name
#     read -p "Enter Student Grade: " grade
#     echo "$id,$name,$grade" >> "$DB_FILE"
#     echo "Record inserted successfully."
# }
# Prompts the user to enter Student ID, Student Name, and Student Grade.
# Appends the record in the format ID,Name,Grade to the database file.
# 3. delete_record Function
# Deletes an existing record by matching the student ID:

# bash
# Copy code
# delete_record() {
#     read -p "Enter Student ID to delete: " id
#     if grep -q "^$id," "$DB_FILE"; then
#         grep -v "^$id," "$DB_FILE" > temp_file && mv temp_file "$DB_FILE"
#         echo "Record with ID $id deleted successfully."
#     else
#         echo "Record with ID $id not found."
#     fi
# }
# Prompts for a Student ID to delete.
# If the ID is found, it uses grep -v to exclude the line from student_database.txt, temporarily storing the result in temp_file before overwriting student_database.txt.
# If the ID is not found, it informs the user.
# 4. update_record Function
# Updates an existing record by student ID:

# bash
# Copy code
# update_record() {
#     read -p "Enter Student ID to update: " id
#     if grep -q "^$id," "$DB_FILE"; then
#         read -p "Enter new Student Name: " name
#         read -p "Enter new Student Grade: " grade
#         grep -v "^$id," "$DB_FILE" > temp_file
#         echo "$id,$name,$grade" >> temp_file
#         mv temp_file "$DB_FILE"
#         echo "Record with ID $id updated successfully."
#     else
#         echo "Record with ID $id not found."
#     fi
# }
# Prompts for Student ID, new Student Name, and new Student Grade.
# If the ID exists, it removes the old entry, adds the updated record to temp_file, and moves temp_file back to student_database.txt.
# 5. search_record Function
# Searches for a record by student ID and displays it if found:

# bash
# Copy code
# search_record() {
#     read -p "Enter Student ID to search: " id
#     if grep -q "^$id," "$DB_FILE"; then
#         echo "Record found:"
#         grep "^$id," "$DB_FILE"
#     else
#         echo "Record with ID $id not found."
#     fi
# }
# Prompts for a Student ID.
# If found, the record is displayed; otherwise, it informs the user the ID was not found.
# Step 3: Main Program Flow
# The main program loop continues until the user chooses to exit:

# bash
# Copy code
# while true; do
#     show_menu
#     case $choice in
#         a|A) insert_record ;;
#         b|B) delete_record ;;
#         c|C) update_record ;;
#         d|D) search_record ;;
#         e|E) echo "Exiting..."; exit 0 ;;
#         *) echo "Invalid option. Please try again." ;;
#     esac
# done
# Loop: The while true loop continuously displays the menu and processes the user’s choice.
# Case Statement:
# Matches the choice (a|A, b|B, etc.) with the appropriate function (insert_record, delete_record, etc.).
# Invalid Input: If the input doesn’t match any options, it prompts the user to try again.
# Exit: Choosing e or E exits the loop and ends the program.
# Step 4: Sample Execution
# Insert a Record: Adds a student’s data.

# plaintext
# Copy code
# Enter Student ID: 101
# Enter Student Name: John Doe
# Enter Student Grade: A
# Record inserted successfully.
# Delete a Record: Removes a student’s data by ID.

# plaintext
# Copy code
# Enter Student ID to delete: 101
# Record with ID 101 deleted successfully.
# Update a Record: Modifies a student’s information by ID.

# plaintext
# Copy code
# Enter Student ID to update: 102
# Enter new Student Name: Jane Smith
# Enter new Student Grade: B+
# Record with ID 102 updated successfully.
# Search for a Record: Looks up a student by ID.

# plaintext
# Copy code
# Enter Student ID to search: 103
# Record found:
# 103,Anna Lee,A
# Exit: Ends the program.

# plaintext
# Copy code
# Exiting...
# This script provides a basic text-based interface for managing a student database, demonstrating file manipulation, conditional logic, and loops in Bash. Let me know if you need any more details or modifications!