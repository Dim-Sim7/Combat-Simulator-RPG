#pragma once
#include <cstdint>

typedef std::uint32_t point_t;

class PointWell {
    public:

        PointWell() 
            : pointMax(1u), pointCurrent(1u) {}


        explicit PointWell (point_t inMax, point_t inCurrent)
            : pointMax(1u), pointCurrent(1u)
        {
            setMax(inMax);
            setCurrent(inCurrent);

            if(pointCurrent > pointMax)
                pointCurrent = pointMax;
        }

        point_t getMax() const { return pointMax; } //const means this function won't change any member variables
        point_t getCurrent() const { return pointCurrent; }

        bool setMax(const point_t& newMax)
        {
            if (newMax < 1)
                return false;

            pointMax = newMax;

            if (pointCurrent > newMax)
                pointCurrent = newMax;

            return true;
        }

        bool setCurrent(const point_t& newCurrent)
        {
            if (newCurrent < 1)
                return false;
            
            pointCurrent = (newCurrent > pointMax) ? pointMax : newCurrent;
            return true;
        }

        void reduceCurrent(const point_t& amount)
        {
            pointCurrent = (amount > pointCurrent) ? 0 : pointCurrent -= amount;
        }

        void increaseCurrent(const point_t& amount)
        {
            if ((pointCurrent + amount) > pointMax)
                pointCurrent = pointMax;
            else
                pointCurrent += amount;
        }

    private:
        point_t pointMax;
        point_t pointCurrent;

};
