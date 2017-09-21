#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace shiyanlou_lou12{
    vector<string> split_string(const string &data, char c) {
        vector<string> ret;
        auto old = cbegin(data);
        for(auto it = old; it != cend(data); ++it) {
            if( *it == c ) {
                ret.emplace_back(old, it); 
                old = ++it;
            }
        }
        if( old != cend(data) ) { 
            ret.emplace_back(old, cend(data)); 
        }
        return ret;
    }
}

int main() {

    string str("Welcome to shiyanlou contest lou12");

    vector<string> v = shiyanlou_lou12::split_string(str, ' ');
    for(const string &s : v) {
        cout << s << endl;
    }

    return 0;

}
