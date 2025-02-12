#include "sum/output.hpp"

#include <sstream> // ostringstream
#include <iostream> // ostream implementation

std::ostream& operator<<(std::ostream& os, const std::vector<double>& seq)
{
    auto b = std::begin(seq), e = std::end(seq);
    if (b != e) {
        os << *b;
        while (++b != e)
            os << ", " << *b;
    }
    return os;
}

std::string to_string(const std::vector<double>& seq)
{
    auto os = std::ostringstream{};
    os << seq;
    return os.str();
}