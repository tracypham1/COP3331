#include <vector>

vector<int>& operator+=(vector<int>& lhs, const vector<int>& rhs){
    for(i = 0; i < rhs.size; i++)
        lhs.push_back(rhs.at(i));
    return lhs;
}
