#include "../include/Restaurant.h"
#include <fstream>
#include <string>

Restaurant::Restaurant():open(true),count(0),tables(),menu(),actionsLog(){}

Restaurant::Restaurant(const std::string& configFilePath):open(true),count(0),tables(),menu(),actionsLog()
{
    std::fstream myFile(configFilePath);
    std::string line;
    int line_counter=0,src,dst;
    std::vector<std::string> dish_components(3);
    if(myFile.is_open())
    {
        while(getline(myFile,line))
        {
            if(!line.empty()||line.at(0)!='#')
            {
                line_counter++;
                if(line_counter==1)
                {
                    tables.resize(std::stoi(line));
                }
                else if(line_counter==2)
                {
                    src=0;
                    for(int i=0;i<line.length();i++)
                    {
                        if(line.at(i)==',')
                        {
                            dst = i;
                            addTable(src,dst,line);
                            src = dst + 1;
                        }
                    }
                    dst=line.length()+1;
                    addTable(src,dst,line);
                }
                else
                {
                    src=0;
                    for(int i=0;i<line.length();i++)
                    {
                        if(line.at(i)==',')
                        {
                            dst = i;
                            dish_components.push_back(line.substr(src,dst-src));
                            src = dst + 1;
                        }
                    }
                    dst=line.length()+1;
                    dish_components.push_back(line.substr(src,dst-src));
                    addDish(dish_components);
                }
            }
        }
        myFile.close();
    }
}

void Restaurant::receive(std::string &ref1, std::string &ref2)
{
    std::cin >> ref1;
    std::getline (std::cin, ref2);
    setLine(ref2);
}

void Restaurant::setLine(std::string &params)
{
    if(!params.empty())
        params=params.substr(1);
}

void Restaurant::start()
{
    std::string command_name;
    std::string params;
    std::string& ref1=command_name;
    std::string& ref2=params;
    std::cout <<"Our restaurant is open for business!";
    Restaurant::receive(ref1,ref2);
    while (!command_name.empty())
    {
        if(command_name=="open")
        {
            openTable(params);
        }
        else if(command_name=="order")
        {
            order(params);
        }
        else if(command_name=="move")
        {
            moveCustomer(params);
        }
        else if(command_name=="close")
        {
            close(params);
        }
        else if(command_name=="closeall")
        {
            closeAll();
        }
        else if(command_name=="menu")
        {
            printMenu();
        }
        else if(command_name=="status")
        {
            printTableStatus(params);
        }
        else if(command_name=="log")
        {
            printActionsLog();
        }
        else if(command_name=="backup")
        {
            backupRestaurant();
        }
        else
        {
            restoreRestaurant();
        }
        Restaurant::receive(ref1,ref2);
    }

}

void Restaurant::moveCustomer(std::string params)
{
    int src,dst,id;
    for(int i=0;i<2;i++)
    {
        int j=0;
        while (params.at(j)!=' ')
        {
            j++;
        }
        if(i==1)
        {
            src=std::stoi(params.substr(0,j));
        }
        else
        {
            dst=std::stoi(params.substr(0,j));
        }
        params=params.substr(j+1);
    }
    id=std::stoi(params);
    BaseAction* moveCustomer=new MoveCustomer(src,dst,id);
    moveCustomer->act(*this);
    actionsLog.push_back(moveCustomer);
}
void Restaurant::openTable(std::string params)
{
    int id;
    std::string name;
    std::string type;
    int i=0;
    while (params.at(i)!=' ')
        i++;
    id=std::stoi(params.substr(0,i));
    params=params.substr(i+1);
    std::vector<Customer*> tableCustomers;
    int src=0;
    for(i=0;i<params.length();i++)
    {
        if(params.at(i)==',')
        {
            type=params.substr(i+1,3);
            name=params.substr(src,i-src);
            if (type=="chp")
            {
                tableCustomers.push_back(new CheapCustomer(name,count));
            }
            else if(type=="alc")
            {
                tableCustomers.push_back(new AlchoholicCustomer(name,count));
            }
            else if(type=="spc")
            {
                tableCustomers.push_back(new SpicyCustomer(name,count));
            }
            else
            {
                tableCustomers.push_back(new VegetarianCustomer(name,count));
            }
            count++;
            src=i+5;
            i=i+5;
        }
    }
    BaseAction* openTable=new OpenTable(id,tableCustomers);
    openTable->act(*this);
    actionsLog.push_back(openTable);
}

void Restaurant::order(std::string params)
{
    int id=std::stoi(params);
    BaseAction* orderAction=new Order(id);
    orderAction->act(*this);
    actionsLog.push_back(orderAction);
}

void Restaurant::closeAll()
{
    BaseAction* closeAll=new CloseAll();
    closeAll->act(*this);
    actionsLog.push_back(closeAll);
}

void Restaurant::printMenu()
{
    BaseAction* printMenu=new PrintMenu();
    printMenu->act(*this);
    actionsLog.push_back(printMenu);
}

void Restaurant::printActionsLog()
{
    BaseAction* printactionsLog=new PrintActionsLog();
    printactionsLog->act(*this);
    actionsLog.push_back(printactionsLog);
}

void Restaurant::printTableStatus(std::string params)
{
    int id=std::stoi(params);
    BaseAction* printtableStatus=new PrintTableStatus(id);
    printtableStatus->act(*this);
    actionsLog.push_back(printtableStatus);
}

void Restaurant::backupRestaurant()
{
    BaseAction* backupRestaurant=new BackupRestaurant();
    backupRestaurant->act(*this);
    actionsLog.push_back(backupRestaurant);
}

void Restaurant::restoreRestaurant()
{
    BaseAction* restoreRestaurant=new RestoreResturant();
    restoreRestaurant->act(*this);
    actionsLog.push_back(restoreRestaurant);
}

void Restaurant::close(std::string params)
{
    int id=std::stoi(params);
    BaseAction* close=new Close(id);
    close->act(*this);
    actionsLog.push_back(close);
}

void Restaurant::addDish(std::vector<std::string> dish_components)
{
    DishType dish_type=Restaurant::type(dish_components[1]);
    Dish dish(menu.size(),dish_components[0],std::stoi(dish_components[2]),dish_type);
    menu.push_back(dish);

}

DishType Restaurant::type(std::string data)
{
    if(data=="ALC")
        return ALC;
    else if(data=="BVG")
        return BVG;
    else if(data=="SPC")
        return SPC;
    return VEG;
}
void Restaurant::addTable(int src,int dst,std::string line)
{
    int capacity = std::stoi(line.substr(src, dst - src));
    Table tmp(capacity);
    Table *table = &tmp;
    tables.push_back(table);
}

Restaurant::Restaurant(const Restaurant& other):tables(),menu(),actionsLog()
{
    copy(other);
}

Restaurant::Restaurant(Restaurant&& other):tables(),menu(),actionsLog()
{
    copy(other);
}

Restaurant& Restaurant::operator=(const Restaurant& other)
{
    if(&other!=this)
    {
        clean();
        copy(other);
    }
    return *this;
}

Restaurant& Restaurant::operator=(Restaurant&& other)
{
    clean();
    copy(other);
    return *this;
}

void Restaurant::copy(const Restaurant& other)
{
//    open=other.open;
//    tables=other.tables;
//    menu=other.menu;
//    actionsLog=other.actionsLog;
}

void Restaurant::clean()
{
    for(int i=0;i<tables.size();i++)
    {
        delete tables[i];
    }
    tables.clear();

    for(int i=0;i<actionsLog.size();i++)
    {
        delete actionsLog[i];
    }
    actionsLog.clear();

    menu.clear();
}

int Restaurant::getNumOfTables() const
{
    return tables.size();
}

Table* Restaurant::getTable(int ind)
{
    return  tables[ind];
}

const std::vector<BaseAction*>& Restaurant::getActionsLog() const
{
    return actionsLog;
}

std::vector<Dish>& Restaurant::getMenu()
{
    std::vector<Dish>& returnMenu=menu;
    return returnMenu;
}

