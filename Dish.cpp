#include "../include/Dish.h"

Dish::Dish(int d_id, std::string d_name, int d_price, DishType d_type):id(d_id),name(d_name),price(d_price),type(d_type){}

///returns Dish ID
int Dish::getId() const
{
    return id;
}

///returns Dish name
std::string Dish::getName() const
{
    return name;
}

///returns Dish price
int Dish::getPrice() const
{
    return price;
}

///returns Dish type
DishType Dish::getType() const 
{
    return type;
}