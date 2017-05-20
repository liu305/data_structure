#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

unsigned long long hash_func(const string& s) {
    static const size_t multiplier = 263;
    static const size_t prime = 179426549;
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
         hash = (hash * multiplier + s[i]) % prime; 
    return hash;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<unsigned long long> hash_array;
    hash_array.resize(t.size() - s.size() + 1);
    hash_array[t.size()-s.size()] = hash_func(t.substr(t.size()-s.size()));
    unsigned long long y = 1;
    static const size_t multiplier = 263;
    static const size_t prime = 179426549;
    for (int i = 0; i < s.size(); ++i)
    {
        y = (y * multiplier) % prime;
    }
    for (int i = t.size()-s.size()-1; i>=0; --i)
    {
        hash_array[i] = (hash_array[i+1]*multiplier + t[i] - y*t[i+s.size()]) % prime;
    }
    unsigned long long p_hash = hash_func(s);
    std::vector<int> ans;
    for (int i = 0; i <= t.size()-s.size(); ++i)
    {
        if (p_hash != hash_array[i]) {continue;}
	if (t.substr(i,s.size()) == s) {ans.push_back(i);} 
    }
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
