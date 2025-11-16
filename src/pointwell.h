#pragma once
#include <cstdint>

//Type alias for pointwell type
typedef std::uint32_t point_t;

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
    explicit PointWell (point_t inMax, point_t inCurrent);
    // ----- Getters -----
    [[nodiscard]] point_t getMax() const; //const means this function won't change any member variables
    [[nodiscard]] point_t getCurrent() const;

    //// ----- Setters -----
    bool setMax(const point_t& newMax);

    bool setCurrent(const point_t& newCurrent);

    // ----- Utility -----

    //reduce current point, returns 0 if reduction is more than current
    void reduceCurrent(const point_t& amount);

    //increase current point, returns max points if increase + current is more than max
    void increaseCurrent(const point_t& amount);

private:
    point_t pointMax; //maximum of th well
    point_t pointCurrent; //current points

};
