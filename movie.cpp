#include <sstream>
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string name, double price, int qty, std::string genre, std::string rating)
  : Product("movie", name, price, qty), genre_(genre), rating_(rating)
{
}

Movie::~Movie()
{
}

std::set<std::string> Movie::keywords() const
{
  std::set<std::string> result = parseStringToWords(name_);
  result.insert(convToLower(genre_));
  return result;
}

std::string Movie::displayString() const
{
  stringstream ss;
  ss << name_ << "\n";
  ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
  ss << price_ << " " << qty_ << " left.";
  return ss.str();
}

void Movie::dump(std::ostream& os) const
{
  Product::dump(os);
  os << genre_ << "\n" << rating_ << "\n";
}