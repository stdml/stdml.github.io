#pragma once
#include <string>
#include <vector>

class slist : public std::vector<std::string>
{
    using vector::vector;

  public:
    slist operator+(const slist &b) const
    {
        slist a;
        a.insert(a.end(), begin(), end());
        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
};
