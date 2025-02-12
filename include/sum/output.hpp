#ifndef SUM_OUTPUT_HPP
#define SUM_OUTPUT_HPP

#include <vector>
#include <iosfwd>  // ostream declarations only

std::ostream& operator<<(std::ostream& os, const std::vector<double>& seq);
std::string to_string(const std::vector<double>& seq);

#endif  // SUM_OUTPUT_HPP
