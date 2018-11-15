#include "Action.h"
#include "Table.h"

BaseAction::BaseAction():errorMsg(),status(PENDING) {}
///get for the action status
ActionStatus BaseAction::getStatus() const
{
    return status;
}
///changes the status to completed after a successful action
void BaseAction::complete()
{
    status=COMPLETED;
}
///changes the status to error and updates the error message after an unsuccessful action
void BaseAction::error(std::string errorMsg)
{
    status=ERROR;
    this->errorMsg=errorMsg;
}
///returns the error message
std::string BaseAction::getErrorMsg() const
{
    return errorMsg;
}

///class OpenTable that inherits from BaseAction,responsible for opening a table
OpenTable::OpenTable(int id,std::vector<Customer *> &customersList):BaseAction(),tableId(id),customers(customersList), output() {}

void OpenTable::act(Restaurant &restaurant)
{
    Table* table=restaurant.getTable(this.id);
    if(table== nullptr || table->isOpen()) {
        BaseAction::error("Table does not exist or is already open");
        std::cout << "Error: " << getErrorMsg() << std::endl;
    }
    else
    {
        table->openTable();
        for (int i = 0; i < customers.size(); i++)
            table->addCustomer(customers[i]);
        BaseAction::complete();
    }
}

void OpenTable::setOutput(std::string input)
{
    output=input;
}

std::string OpenTable::toString() const
{
    if(getStatus() == COMPLETED) return output + " Completed";
    return output + " Error: "+getErrorMsg();
}

///class Order that inherits from BaseAction,responsible for taking an order from a table
Order::Order(int id):BaseAction(),tableId(id), output(){}

void Order::act(Restaurant &restaurant)
{
    Table* table=restaurant.getTable(tableId);
    if(table== nullptr || !table->isOpen()) error("Table does not exist or is not open");
    else {
        table->order(restaurant.getMenu());
        complete();
    }
}

void Order::setOutput(std::string input)
{
    output=input;
}

std::string Order::toString() const
{
    if(getStatus() == COMPLETED) return output+" Completed";
    return output + " Error: "+getErrorMsg();
}

///class Order that inherits from BaseAction,responsible for taking an order from a table


