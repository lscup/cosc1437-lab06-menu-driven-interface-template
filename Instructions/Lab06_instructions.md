# Lab 16: Building a Menu-Driven Interface

In this lab, you will transform your grade calculator from a sequential program into a menu-driven application. Instead of running straight through once, users will be able to choose what to do — add an assignment, view all assignments, or exit — as many times as they like. You'll also use `<iomanip>` to display assignments in professionally aligned columns, and apply two modern C++ upgrades to your existing code.

## Learning Objectives

- Implement a menu system using a `do-while` loop and `switch` statement
- Use `<iomanip>` for formatted, column-aligned output
- Organize code into focused helper functions
- Update constructors to use initializer lists
- Replace index-based `for` loops with range-based `for` loops

---

## 2. Algorithm/Concept Background

### C++ Upgrade: Constructor Initializer Lists

In Lab 15, your constructors assigned values inside the body:

```cpp
// Lab 15 style
Assignment::Assignment() {
    name = "";
    points_earned = 0;
    points_possible = 0;
}
```

The preferred C++ style uses an **initializer list** — a colon after the constructor signature:

```cpp
// Modern style
Assignment::Assignment() : name(""), points_earned(0), points_possible(0) {}

Assignment::Assignment(const std::string& n, float earned, float possible)
    : name(n), points_earned(earned), points_possible(possible) {}
```

Both produce the same result. Initializer lists are preferred because members are initialized directly in one step rather than default-initialized first and then reassigned.

---

### C++ Upgrade: Range-Based For Loops

When you don't need the index, a range-based for loop is cleaner:

```cpp
// Index-based (Lab 15 style)
for (size_t i = 0; i < assignments.size(); ++i) {
    assignments[i].display();
}

// Range-based (modern style)
for (const auto& assignment : assignments) {
    assignment.display();
}
```

`const auto&` means: don't modify the object (`const`), let the compiler infer the type (`auto`), use a reference to avoid copying (`&`).

---

### The iomanip Library

`<iomanip>` controls output formatting — column widths, decimal places, and alignment:

```cpp
#include <iomanip>

std::cout << std::left  << std::setw(25) << "Name";      // left-aligned, 25 wide
std::cout << std::right << std::setw(10) << "Earned";    // right-aligned, 10 wide
std::cout << std::fixed << std::setprecision(1) << 95.0; // prints: 95.0
```

| Manipulator | Effect | Resets after use? |
|-------------|--------|-------------------|
| `setw(n)` | Field width | Yes — next item only |
| `setprecision(n)` | Decimal places | No — stays until changed |
| `fixed` | Fixed decimal notation | No — stays until changed |
| `left` / `right` | Alignment | No — stays until changed |

---

### Menu Pattern: do-while + switch

A `do-while` loop guarantees the menu appears at least once. A `switch` statement routes each choice to the right function:

```cpp
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
```

The loop exits when the user enters `0`. The `default` case handles any other input gracefully.

---

## 3. Your Coding Environment

| Area | What It Does |
|------|--------------|
| Code Editor (left) | Edit your files using the tabbed editor |
| Terminal (right) | See output when you click **Run** |
| AI Tutor (chat panel) | Ask for help — it knows this lab and can guide you step by step |

### Workflow

1. Edit your code in the editor tabs
2. Click **Run** to compile and test
3. Click **Commit** to save to GitHub and trigger the autograder
4. A ✅ or ❌ will appear showing whether tests passed

Tip: Commit after each working step — don't wait until everything is done.

---

## 4. Project Structure

```
main.cpp        -- YOUR WORK (rewrite from Lab 15)
Assignment.cpp  -- YOUR WORK (update constructors to initializer lists)
Assignment.h    -- carried over from Lab 15, no changes needed
greeting.cpp    -- provided, do not modify
greeting.h      -- provided, do not modify
```

---

## 5. Step-by-Step Implementation

### Step 1: Update Assignment.cpp — Initializer Lists

Open `Assignment.cpp` and replace the constructor bodies with initializer list syntax:

```cpp
Assignment::Assignment() : name(""), points_earned(0), points_possible(0) {}

Assignment::Assignment(const std::string& n, float earned, float possible)
    : name(n), points_earned(earned), points_possible(possible) {}
```

All other methods (getters, setters, `display()`) stay exactly the same.

---

### Step 2: Set Up main.cpp Includes

Start `main.cpp` with these includes:

```cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include "greeting.h"
#include "Assignment.h"
```

---

### Step 3: Add Display Helper Functions

These two functions draw the visual separators used throughout the UI. Add them before `main()`:

```cpp
void displayHeader(const std::string& title) {
    std::cout << "\n";
    std::cout << std::string(50, '=') << '\n';
    std::cout << "  " << title << '\n';
    std::cout << std::string(50, '=') << '\n';
}

void displaySeparator() {
    std::cout << std::string(50, '-') << '\n';
}
```

`std::string(50, '=')` creates a string of 50 `=` characters — a compact way to draw a divider line.

---

### Step 4: Add the Menu Function

```cpp
void displayMenu() {
    displayHeader("GRADE CALCULATOR - MAIN MENU");
    std::cout << "1. Add Assignment\n";
    std::cout << "2. View All Assignments\n";
    std::cout << "0. Exit\n";
    displaySeparator();
}
```

---

### Step 5: Add the viewAssignments Function

This function uses `<iomanip>` to display assignments in aligned columns. Note the range-based for loop:

```cpp
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
```

---

### Step 6: Add the addAssignment Function

```cpp
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
```

Note: `std::cin >> name` reads a single word — assignment names should not contain spaces.

---

### Step 7: Write main()

```cpp
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
```

---

### Step 8: Compile and Test

```bash
g++ -std=c++17 -o grade_calc main.cpp greeting.cpp Assignment.cpp
```

---

## 6. Expected Output

```
Good morning!

==================================================
  GRADE CALCULATOR - MAIN MENU
==================================================
1. Add Assignment
2. View All Assignments
0. Exit
--------------------------------------------------
Enter choice: 1
Enter assignment name: Homework1
Enter points earned: 95
Enter points possible: 100

==================================================
  GRADE CALCULATOR - MAIN MENU
==================================================
1. Add Assignment
2. View All Assignments
0. Exit
--------------------------------------------------
Enter choice: 2

==================================================
  ALL ASSIGNMENTS
==================================================
Name                      Earned  Possible   Percent
--------------------------------------------------
Homework1                   95.0     100.0     95.0%

Enter choice: 0

==================================================
  GOODBYE
==================================================
Thank you for using Grade Calculator!
```

---

## 7. Autograding

| Test | Points | What It Checks |
|------|--------|----------------|
| Compilation | 10 | Code compiles without errors |
| Menu displays correctly | 20 | Correct title, all 3 options, `=` and `-` separator lines, GOODBYE on exit |
| Empty assignment list | 15 | "No assignments entered yet." when list is empty |
| Add and view one assignment | 25 | Correct name, points, and percentage in aligned columns |
| Add and view multiple assignments | 20 | Both assignments displayed with correct values |
| Invalid menu input handled | 10 | "Invalid choice. Please try again." on bad input |

---

## 8. Submission Checklist

- [ ] `Assignment.cpp` constructors use initializer lists
- [ ] `<iomanip>` included and used for column-aligned output
- [ ] `displayHeader()` and `displaySeparator()` implemented
- [ ] `displayMenu()` shows exactly: `1. Add Assignment`, `2. View All Assignments`, `0. Exit`
- [ ] `viewAssignments()` uses range-based for loop and correct column widths (25/10/10/9)
- [ ] `addAssignment()` reads name, earned, possible and pushes to vector
- [ ] `main()` uses `do-while` + `switch`, exits cleanly on `0`
- [ ] Click **Run** — output matches expected
- [ ] Click **Commit** — autograder shows green check

---

## What You Learned

- ✅ Updated constructors to use initializer lists
- ✅ Used range-based for loops in place of index-based loops
- ✅ Used `<iomanip>` for professional column-aligned output
- ✅ Built a menu-driven interface with `do-while` + `switch`
- ✅ Organized code into focused, reusable helper functions

---

## Next Steps

In **Lab 17**, you'll add inheritance to create different types of graded items with weighted categories!