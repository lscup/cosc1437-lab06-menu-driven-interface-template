#include "Assignment.h"
#include <iostream>

Assignment::Assignment() : name(""), points_earned(0), points_possible(0) {}

Assignment::Assignment(const std::string& n, float earned, float possible)
    : name(n), points_earned(earned), points_possible(possible) {}

std::string Assignment::getName() const {
    return name;
}

float Assignment::getPointsEarned() const {
    return points_earned;
}

float Assignment::getPointsPossible() const {
    return points_possible;
}

float Assignment::getPercentage() const {
    if (points_possible == 0) return 0;
    return (points_earned / points_possible) * 100;
}

void Assignment::setName(const std::string& n) {
    name = n;
}

void Assignment::setPointsEarned(float earned) {
    if (earned >= 0) {
        points_earned = earned;
    }
}

void Assignment::setPointsPossible(float possible) {
    if (possible > 0) {
        points_possible = possible;
    }
}

void Assignment::display() const {
    std::cout << name << ": "
              << points_earned << "/" << points_possible
              << " (" << getPercentage() << "%)\n";
}
