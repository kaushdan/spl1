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
OpenTable::OpenTable(int id,std::vector<Customer *> &customersList):BaseAction(),tableId(id),customers(customersList) {}

void OpenTable::act(Restaurant &restaurant)
{
    Table* table=restaurant.getTable(this.id);
    if(table== nullptr || table->isOpen()) {
        BaseAction::error("Table does not exist or is already open");
        std::cout << "Error: " << getErrorMsg() << std::endl;s
    }
    else
    {
        table->openTable();
        for (int i = 0; i < customers.size(), i++)
            table->addCustomer(customers[i]);
        BaseAction::complete();
    }
}

