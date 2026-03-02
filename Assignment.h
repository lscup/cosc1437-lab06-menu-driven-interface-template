#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include <string>

class Assignment {
private:
    std::string name;
    float points_earned;
    float points_possible;

public:
    Assignment();
    Assignment(const std::string& n, float earned, float possible);

    std::string getName() const;
    float getPointsEarned() const;
    float getPointsPossible() const;
    float getPercentage() const;

    void setName(const std::string& n);
    void setPointsEarned(float earned);
    void setPointsPossible(float possible);

    void display() const;
};

#endif