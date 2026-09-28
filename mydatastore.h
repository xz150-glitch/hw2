#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include "datastore.h"

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();


    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);


    bool userExists(std::string username);
    void addToCart(std::string username, Product* p);
    std::vector<Product*> getCart(std::string username);
    void buyCart(std::string username);

private:
    std::set<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*> > keywordMap_;
    std::map<std::string, std::deque<Product*> > carts_;
};
#endif