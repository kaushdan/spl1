#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"


class Restaurant{		
public:
	Restaurant();
	Restaurant(const Restaurant& other);
    Restaurant(Restaurant&& other);
	Restaurant& operator=(const Restaurant& other);
    Restaurant& operator=(Restaurant&& other);
    Restaurant(const std::string &configFilePath);
    void start();
    int getNumOfTables() const;
    Table* getTable(int ind);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Dish>& getMenu(); 

private:
    bool open;
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
    int count;
    void clean();
    void copy(const Restaurant& other);
    void addTable(int src,int dst,std::string line);
    void addDish(std::vector<std::string> dish_components);
    void setLine(std::string& params);
    void receive(std::string& ref1,std::string& ref2);
    void openTable(std::string params);
    void order(std::string params);
    void moveCustomer(std::string params);
    void close(std::string params);
    void closeAll();
    void printMenu();
    void printTableStatus(std::string params);
    void printActionsLog();
    void backupRestaurant();
    void restoreRestaurant();
    DishType type(std::string data);
};

#endif
