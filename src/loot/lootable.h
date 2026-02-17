
#pragma once 
class Lootable {
public:
    virtual ~Lootable() = default;

    virtual int weight() const = 0;
    virtual bool isUnique() const = 0;
    virtual bool isAlways() const = 0;
};