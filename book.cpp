#include <sstream>
#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string name, double price, int qty, std::string isbn, std::string author)
  : Product("book", name, price, qty), isbn_(isbn), author_(author)
{
}

Book::~Book()
{
}

std::set<std::string> Book::keywords() const
{
  std::set<std::string> nameWords = parseStringToWords(name_);
  std::set<std::string> authorWords = parseStringToWords(author_);
  std::set<std::string> result = setUnion(nameWords, authorWords);
  result.insert(isbn_);
  return result;
}

std::string Book::displayString() const
{
  stringstream ss;
  ss << name_ << "\n";
  ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
  ss << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Book::dump(std::ostream& os) const
{
  Product::dump(os);
  os << isbn_ << "\n" << author_ << "\n";
}