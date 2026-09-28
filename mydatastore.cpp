#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    // 所有 Product 和 User 都是 new 出来的，这里负责 delete，防止 memory leak
    for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        delete *it;
    }
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.insert(p);

    set<string> keys = p->keywords();
    for (set<string>::iterator it = keys.begin(); it != keys.end(); ++it) {
        keywordMap_[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    string name = convToLower(u->getName());
    users_[name] = u;
    carts_[name];  
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    set<Product*> result;
    for (size_t i = 0; i < terms.size(); i++) {
        string term = convToLower(terms[i]);
        set<Product*> matches;
        map<string, set<Product*> >::iterator found = keywordMap_.find(term);
        if (found != keywordMap_.end()) {
            matches = found->second;
        }

        if (i == 0) {
            result = matches;
        }
        else if (type == 0) {
            result = setIntersection(result, matches);   // AND
        }
        else {
            result = setUnion(result, matches);          // OR
        }
    }

    vector<Product*> hits(result.begin(), result.end());
    return hits;
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for (set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}

bool MyDataStore::userExists(string username)
{
    return users_.find(convToLower(username)) != users_.end();
}

void MyDataStore::addToCart(string username, Product* p)
{
    carts_[convToLower(username)].push_back(p);
}

vector<Product*> MyDataStore::getCart(string username)
{
    deque<Product*>& cart = carts_[convToLower(username)];
    vector<Product*> items(cart.begin(), cart.end());
    return items;
}

void MyDataStore::buyCart(string username)
{
    string name = convToLower(username);
    User* u = users_[name];
    deque<Product*>& cart = carts_[name];
    deque<Product*> remaining; 

    for (deque<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
        Product* p = *it;
        if (p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        }
        else {
            remaining.push_back(p);
        }
    }
    cart = remaining;
}