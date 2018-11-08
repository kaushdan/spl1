#include "Customer.h"

///class Customer
Customer::Customer(std::string c_name, int c_id):name(c_name), id(c_id), customerOrders(){}
///get for name
std::string Customer::getName() const
{
    return name;
}
///get for id
int Customer::getId() const
{
    return id;
}
///get for customers orders
std::vector<int> Customer::getCustomerOrders() const
{
    return customerOrders;
}

///class VegetarianCustomer that inherits from class Customer
VegetarianCustomer::VegetarianCustomer(std::string name, int id): Customer(name, id){}
///returns a vector of orders of the customer
std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu)
{
    std::vector<int> orders;
    int veg_Location=VegetarianCustomer::findVeg(menu);
    int bvg_Location=VegetarianCustomer::findMostExpensiveBVG(menu);
    if(veg_Location == -1 | bvg_Location == -1) return orders;
    orders.push_back(veg_Location);
    orders.push_back(bvg_Location);
    customerOrders.push_back(veg_Location);
    customerOrders.push_back(bvg_Location);
    return orders;
}
///a private function that returns the location in the vector of the veg dish with smallest id
int VegetarianCustomer::findVeg(const std::vector<Dish> &menu)
{
    for(int i=0;i<menu.size();i++)
        if(menu[i].getType()==VEG) return i;
    return -1;
}
///a private function that returns the location in the vector of the most expensive bvg dish with smallest id
int VegetarianCustomer::findMostExpensiveBVG(const std::vector<Dish> &menu)
{
    int max=-1,max_price=0;
    for(int i=0;i<menu.size();i++)
        if(menu[i].getType()==BVG && menu[i].getPrice()>max_price)
        {
            max_price=menu[i].getPrice();
            max=i;
        }
    return max;
}
///toString of the vegetarian customer
std::string VegetarianCustomer::toString() const
{
    return VegetarianCustomer::getId()+" "+VegetarianCustomer::getName();
}
///creates a new copy of the customer
Customer* VegetarianCustomer::duplicate()
{
    return new VegetarianCustomer(VegetarianCustomer::getName(),VegetarianCustomer::getId());
}
///class CheapCustomer that inherits from class Customer
CheapCustomer::CheapCustomer(std::string name, int id):Customer(name,id),hasOrdered(false) {};

CheapCustomer::CheapCustomer(std::string name, int id,bool has_Ordered):Customer(name,id),hasOrdered(has_Ordered){}
///returns a vector of customers order
std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu)
{
    std::vector<int> orders;
    if (hasOrdered) return orders;
    int cheapest_Location=findCheapestDish(menu);
    orders.push_back(cheapest_Location);
    customerOrders.push_back(cheapest_Location);
    hasOrdered=true;
    return orders;
}
///a private function that returns the location in the vector of the cheapest dish with smallest id
int CheapCustomer::findCheapestDish(const std::vector<Dish> &menu)
{
    int loc=0;
    for(int i=1;i<menu.size();i++)
        if(menu[i].getPrice()<menu[loc].getPrice())
            loc=i;
    return loc;
}
///toString of a cheap customer
std::string CheapCustomer::toString() const
{
    return CheapCustomer::getId()+" "+CheapCustomer::getName();
}
///get for hasOrdered
bool CheapCustomer::getOrdered() const
{
    return CheapCustomer::hasOrdered;
}
///creates a copy of the customer
Customer* CheapCustomer::duplicate()
{
    return new CheapCustomer(CheapCustomer::getName(),CheapCustomer::getId(),CheapCustomer::hasOrdered);
}
///class SpicyCustomer that inherits from class Customer
SpicyCustomer::SpicyCustomer(std::string name, int id):Customer(name,id),hasOrdered(false) {};

SpicyCustomer::SpicyCustomer(std::string name, int id,bool has_Ordered):Customer(name,id),hasOrdered(has_Ordered){}
///a private function that returns the location in the vector of the most expensive spc dish with smallest id
int SpicyCustomer::findMostExpensiveSpc(const std::vector<Dish> &menu)
{
    int max=-1,max_price=0;
    for(int i=0;i<menu.size();i++)
        if(menu[i].getType()==SPC && menu[i].getPrice()>max_price)
        {
            max_price=menu[i].getPrice();
            max=i;
        }
    return max;
}
///a private function that returns the location in the vector of the cheapest bvg dish with smallest id
int SpicyCustomer::findCheapestBvg(const std::vector<Dish> &menu)
{
    int min=0;
    while(min<menu.size() && menu[min].getType()!=BVG)
        min++;
    if(min==menu.size())return -1;
    for(int i=min+1;i<menu.size();i++)
        if(menu[i].getType()==BVG && menu[i].getPrice()<menu[min].getPrice())
            min=i;
    return min;
}
///returns a vector of the order of the customer
std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu)
{
    std::vector<int> orders;
    if(hasOrdered)
    {
        int order=SpicyCustomer::findCheapestBvg(menu);
        if(order!=-1)
        {
            orders.push_back(order);
            customerOrders.push_back(order);
        }
        return orders;
    }
    hasOrdered= true;
    int order=SpicyCustomer::findMostExpensiveSpc(menu);
    if(order!=-1)
    {
        orders.push_back(order);
        customerOrders.push_back(order);
    }
    return  orders;
}
///creates a copy of the customer
Customer* SpicyCustomer::duplicate()
{
    return new CheapCustomer(SpicyCustomer::getName(),SpicyCustomer::getId(),SpicyCustomer::hasOrdered);
}
///toString of a spicy customer
std::string SpicyCustomer::toString() const
{
    return SpicyCustomer::getId()+" "+SpicyCustomer::getName();
}
///class AlchoholicCustomer that inherits from class Customer
AlchoholicCustomer::AlchoholicCustomer(std::string name, int id): Customer(name,id),drink_count(0),drinks() {}

AlchoholicCustomer::AlchoholicCustomer(std::string name, int id, int drink_count,
                                       std::vector<std::pair<int, int>> drinks)
                                       :Customer(name,id),drink_count(drink_count),drinks(drinks){}
///returns a vector of the orders of the customer
std::vector<int> AlchoholicCustomer::order(const std::vector<Dish>& menu)
{
    std::vector<int> orders;
    if(drink_count==0)
    {
        for(int i=0;i<menu.size();i++)
        {
            if(menu[i].getType()==ALC)
            {
                drinks.push_back(std::make_pair(i,menu[i].getPrice()));
            }
        }
        if(drinks.size()>0)
        {
            sort(drinks);
            orders.push_back(drinks[drink_count].first);
            customerOrders.push_back(drinks[drink_count].first);
            drink_count++;
        }
        return  orders;
    }
    if(drink_count<drinks.size())
    {
        orders.push_back(drinks[drink_count].first);
        customerOrders.push_back(drinks[drink_count].first);
        drink_count++;
    }
    return  orders;
}
///a private function that stably sorts the vector from cheapest to most expensive
void AlchoholicCustomer::sort(std::vector<std::pair<int, int>> &drinks)
{
    int i=1,j;
    while (i<drinks.size())
    {
        j=i;
        while(j>0 && drinks[j-1].second>drinks[j].second)
        {
            AlchoholicCustomer::swap(drinks,j-1,j);
            j=j-1;
        }
        i=i+1;
    }
}
///a private function that swaps between to elemnets of a vector
void AlchoholicCustomer::swap(std::vector<std::pair<int, int>> &drinks,int a1,int a2)
{
    std::pair<int,int> tmp=drinks[a1];
    drinks[a1]=drinks[a2];
    drinks[a2]=tmp;
}
///toString of an alcoholic customer
std::string AlchoholicCustomer::toString() const
{
    return AlchoholicCustomer::getId()+" "+AlchoholicCustomer::getName();
}
///creates a copy of the customer
Customer* AlchoholicCustomer::duplicate()
{
    return new AlchoholicCustomer(AlchoholicCustomer::getName(),AlchoholicCustomer::getId(),
            AlchoholicCustomer::drink_count,AlchoholicCustomer::drinks);
}










