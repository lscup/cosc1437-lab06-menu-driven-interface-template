#include <iostream>
#include <vector>
#include "greeting.h"
#include "Assignment.h"

int main() {
    // Display greeting
    displayGreeting();
    
    // Welcome message
    std::cout << "Welcome to the COSC 1437 Grade Calculator\n\n";

    // Vector for assignments
    std::vector<Assignment> assignments;

    // Initial data
    std::string name;
    float earned, possible;
    char choice;

    do {
        std::cout << "Enter assignment name: ";
        std::cin >> name;
        std::cout << "Enter points earned: ";
        std::cin >> earned;
        std::cout << "Enter points possible: ";
        std::cin >> possible;

        // Create Assignment object and add to vector
        Assignment newAssignment(name, earned, possible);
        assignments.push_back(newAssignment);

        std::cout << "Add another assignment (y/n)? ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    // Calculate and display total points
    float total_earned = 0;
    float total_possible = 0;

    for (const auto& assignment : assignments) {
        total_earned += assignment.getPointsEarned();
        total_possible += assignment.getPointsPossible();
        assignment.display();
    }

    std::cout << "Total earned: " << total_earned << " out of " << total_possible << "\n";

    return 0;
}