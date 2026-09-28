#include <sstream>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, std::string size, std::string brand)
  : Product("clothing", name, price, qty), size_(size), brand_(brand)
{
}

Clothing::~Clothing()
{
}

std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> brandWords = parseStringToWords(brand_);
  return setUnion(nameWords, brandWords);
}

std::string Clothing::displayString() const
{
  stringstream ss;
  ss << name_ << "\n";
  ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
  ss << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
  Product::dump(os);
  os << size_ << "\n" << brand_ << "\n";
}