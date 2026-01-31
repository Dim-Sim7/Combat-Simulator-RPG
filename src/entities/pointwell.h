#pragma once
#include <cstdint>

//Type alias for pointwell type

/**
 * @brief holds pointwell mechanics for an entity.
 * 
 * A well can be emptied but never hold more than its max.
 * Implements a number management system that is similar to this.
 * Useful for HP, MP
 */
class PointWell {
public:
    //default constructor
    PointWell();

    //parameter constructor
    explicit PointWell (int inMax, int inCurrent);
    // ----- Getters -----
    [[nodiscard]] int getMax() const; //const means this function won't change any member variables
    [[nodiscard]] int getCurrent() const;

    //// ----- Setters -----
    bool setMax(const int& newMax);

    bool setCurrent(const int& newCurrent);

    // ----- Utility -----

    //reduce current point, returns 0 if reduction is more than current
    void reduceCurrent(const int& amount);

    //increase current point, returns max points if increase + current is more than max
    void increaseCurrent(const int& amount);

private:
    int pointMax; //maximum of th well
    int pointCurrent; //current points

};
