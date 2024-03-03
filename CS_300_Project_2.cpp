#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Define the Course structure
struct Course {
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prerequisites;
};

// Data structure to store courses as a vector
std::vector<Course> courseVector;

// Function prototypes
void loadDataStructure(const std::string& ABCU_Program);
void printCourseList();
void printCourse(const std::string& userInput);
void printError();

// Utility function to convert a string to lowercase
std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Main Function 
int main() {
    // Print a welcome message to the user
    std::cout << "Welcome to the course planner.\n";

    // Declare a variable to store the user's choice
    int choice;

    // Use a do-while loop to present the menu and handle user input
    do {
        // Print the menu options
        std::cout << "\n1. Load Data Structure.\n"
            << "2. Print Course List.\n"
            << "3. Print Course.\n"
            << "4. Exit\n";

        // Prompt user for their choice
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        // Use a switch statement to perform actions based on the user's choice 
        switch (choice) {

        case 1:
            // Option 1: Load Data Structure
        {
            // Declare a variable to store the file name (ABCU_Program)
            std::string ABCU_Program;
            // Prompt user to enter file name (ABCU_Program.txt)
            std::cout << "Enter the file name: ";
            std::cin >> ABCU_Program;
            loadDataStructure(ABCU_Program);
        }
        break;
        case 2:
            // Option 2: Print Course List
            printCourseList();
            break;
        case 3:
            // Option 3: Print Course
        {
            // Declare a variable to store the user input (course number or title)
            std::string userInput;
            // Prompt the user to enter the course number or title
            std::cout << "Enter the course number or title: ";
            std::cin >> userInput;
            // Call the function to print information about the specified course
            printCourse(userInput);
        }
        break;
        case 4:
            // Option 4: Exit the program
            std::cout << "Thank you for using the course planner!\n";
            break;
        default:
            // Handle invalid input by calling a function to display an error message
            printError();
        }

    } while (choice != 4); // Continue the loop until the user chooses to exit

    return 0; // Return 0 to indicate successful program execution
}

// Function to load data from the file into the data structure
void loadDataStructure(const std::string& ABCU_Program) {
    // Open the file with the provided file name (ABCU_Program.txt)
    std::ifstream file(ABCU_Program);
    // Check if the file is successfully opened
    if (!file.is_open()) {
        // Print error message if the file fails to open 
        std::cerr << "Error opening file: " << ABCU_Program << "\n";
        return;
    }
    // Read each line from the file
    std::string line;
    while (std::getline(file, line)) {
        // Create a stringstream to process each line
        std::stringstream ss(line);
        Course course;

        // Read course information from the line
        std::getline(ss, course.courseNumber, ',');
        std::getline(ss, course.courseTitle, ',');

        // Read prerequisites from the line and add them to the course 
        std::string prerequisite;
        while (std::getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        // Insert the course into the vector
        courseVector.push_back(course);
    }
    // Print a success message after loading data into the data structure
    std::cout << "Data structure loaded successfully.\n";
}

// Function to print course list
void printCourseList() {
    // Iterate over the vector and print each course
    for (const Course& course : courseVector) {
        // Display the course information using the DisplayCourse method
        std::cout << course.courseNumber << ", " << course.courseTitle << std::endl;
    }
}

// Function to print course information
void printCourse(const std::string& userInput) {
    // Convert the user input to lowercase for case-insensitive comparison
    std::string userInputLower = toLower(userInput);

    // Search for the course in the vector based on the provided user input
    auto it = std::find_if(courseVector.begin(), courseVector.end(),
        [&userInputLower](const Course& course) {
            return toLower(course.courseNumber) == userInputLower ||
                toLower(course.courseTitle) == userInputLower;
        });

    // Check if the course was found
    if (it != courseVector.end()) {
        // Display the course information using the DisplayCourse method
        std::cout << it->courseNumber << ", " << it->courseTitle << std::endl;
        // Print prerequisites
        std::cout << "Prerequisites: ";
        for (const std::string& prereq : it->prerequisites) {
            std::cout << prereq << ", ";
        }
        std::cout << std::endl;
    }
    // If the course was not found, print an error message
    else {
        std::cout << "Course not found.\n";
    }
}

// Function to display an error message for invalid input
void printError() {
    std::cout << "Invalid option. Please try again.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
