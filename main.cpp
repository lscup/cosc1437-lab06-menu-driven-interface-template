#include <iostream>
#include <vector>
#include <iomanip>
#include "greeting.h"
#include "Assignment.h"

void displayHeader(const std::string& title) {
    std::cout << "\n";
    std::cout << std::string(50, '=') << '\n';
    std::cout << "  " << title << '\n';
    std::cout << std::string(50, '=') << '\n';
}

void displaySeparator() {
    std::cout << std::string(50, '-') << '\n';
}

void displayMenu() {
    displayHeader("GRADE CALCULATOR - MAIN MENU");
    std::cout << "1. Add Assignment\n";
    std::cout << "2. View All Assignments\n";
    std::cout << "0. Exit\n";
    displaySeparator();
}

void viewAssignments(const std::vector<Assignment>& assignments) {
    displayHeader("ALL ASSIGNMENTS");
    if (assignments.empty()) {
        std::cout << "No assignments entered yet.\n";
        return;
    }
    std::cout << std::left  << std::setw(25) << "Name"
              << std::right << std::setw(10) << "Earned"
                            << std::setw(10) << "Possible"
                            << std::setw(10) << "Percent" << '\n';
    displaySeparator();
    std::cout << std::fixed << std::setprecision(1);
    for (const auto& assignment : assignments) {
        std::cout << std::left  << std::setw(25) << assignment.getName()
                  << std::right << std::setw(10) << assignment.getPointsEarned()
                                << std::setw(10) << assignment.getPointsPossible()
                                << std::setw(9)  << assignment.getPercentage() << "%\n";
    }
}

void addAssignment(std::vector<Assignment>& assignments) {
    std::string name;
    float earned, possible;
    std::cout << "Enter assignment name: ";
    std::cin >> name;
    std::cout << "Enter points earned: ";
    std::cin >> earned;
    std::cout << "Enter points possible: ";
    std::cin >> possible;
    Assignment newAssignment(name, earned, possible);
    assignments.push_back(newAssignment);
}

int main() {
    std::vector<Assignment> assignments;
    displayGreeting();

    int choice = 0;
    do {
        displayMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addAssignment(assignments);
                break;
            case 2:
                viewAssignments(assignments);
                break;
            case 0:
                displayHeader("GOODBYE");
                std::cout << "Thank you for using Grade Calculator!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}