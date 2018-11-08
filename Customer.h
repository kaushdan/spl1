#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
    virtual std::string toString() const = 0;
    virtual Customer* duplicate()=0;
    std::string getName() const;
    int getId() const;
    std::vector<int> getCustomerOrders() const;
protected:
    std::vector<int> customerOrders;
private:
    const std::string name;
    const int id;

};


class VegetarianCustomer : public Customer {
public:
    VegetarianCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    Customer* duplicate();
private:
    int findVeg(const std::vector<Dish> &menu);
    int findMostExpensiveBVG(const std::vector<Dish> &menu);
};


class CheapCustomer : public Customer {
public:
    CheapCustomer(std::string name, int id);
    CheapCustomer(std::string name, int id,bool has_Ordered);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    bool getHasOrdered() const;
    Customer* duplicate();
    bool getOrdered() const;
private:
    bool hasOrdered;
    int findCheapestDish(const std::vector<Dish> &menu);
};


class SpicyCustomer : public Customer {
public:
    SpicyCustomer(std::string name, int id);
    SpicyCustomer(std::string name, int id,bool has_Ordered);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    Customer* duplicate();
    bool getOrdered() const;
private:
    bool hasOrdered;
    int findMostExpensiveSpc(const std::vector<Dish> &menu);
    int findCheapestBvg(const std::vector<Dish> &menu);
};


class AlchoholicCustomer : public Customer {
public:
    AlchoholicCustomer(std::string name, int id);
    AlchoholicCustomer(std::string name, int id,int drink_count,std::vector<std::pair<int,int>> drinks);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    Customer* duplicate();
    int getCount() const;
    std::vector<std::pair<int,int>> getDrinks() const;
private:
    int drink_count;
    std::vector<std::pair<int,int>> drinks;
    void sort(std::vector<std::pair<int,int>>& drinks);
    void swap(std::vector<std::pair<int,int>>& drinks,int a1,int a2);
};


#endif
