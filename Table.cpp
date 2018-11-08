#include <utility>
#include <array>
#include "../include/Table.h"

Table::Table(int t_capacity):capacity(t_capacity),open(false),customersList(),orderList(){}

///returns Table capacity
int Table::getCapacity() const
{
    return capacity;
}

///adds customer to the table
void Table::addCustomer(Customer* customer)
{
    customersList.push_back(customer);
}

///removes customer from the table
///delets the customer's memory from stack/heap!!!
void Table::removeCustomer(int id)
{
    int index=-1;
    for(int i=0;i<customersList.size() && index==-1;i++)
    {
        if(customersList[i]->getId()==id)
            index=i;
    }
    
    if(index!=-1)
    {
        delete customersList[index];
        customersList.erase(customersList.begin()+index);
    }
}

///returns pointer to specific customer
///if not found - nullptr
Customer* Table::getCustomer(int id)
{
    for(int i = 0; i < customersList.size(); i++)
    {
        if(customersList[i]->getId()==id)
            return customersList[i];
    }
    return nullptr;
}

///returns vector of customers of the table
std::vector<Customer*>& Table::getCustomers()
{
    std::vector<Customer*>& returnCustomers=customersList;
    return returnCustomers;
}

///returns vector of orders of the table
std::vector<OrderPair>& Table::getOrders()
{
    std::vector<OrderPair>& returnOrders=orderList;
    return returnOrders;
}

///order from the customers of the table
void Table::order(const std::vector<Dish> &menu)
{
    ///going over the customers
    for(int i=0;i<customersList.size();i++)
    {
        ///order from the customer in i index
        std::vector<int> ordersOfCustomer=customersList[i]->order(menu);
        ///generates the dishes from the menu by ID
        for(int j=0;j<ordersOfCustomer.size();j++)
        {
            orderList.push_back(OrderPair((*customersList[i]).getId(),menu[ordersOfCustomer[j]]));
        }
    }
}

///opens a table(adding the customers isn't here - on OpenTable action)
void Table::openTable()
{
    open=true;
}

///closes the table - delets all memory
void Table::closeTable()
{
    for(int i=0;i<customersList.size();i++)
    {
        delete customersList[i];
    }
    customersList.clear();
    orderList.clear();
    open=false;
}

///calculates the bill of the table
int Table::getBill()
{
    int acc=0;
    for(int i=0;i<orderList.size();i++)
    {
        acc+=(std::get<1>(orderList[i])).getPrice();
    }

    return acc;
}

///retuens if the is open
bool Table::isOpen()
{
    return open;
}







