#include <iostream>
#include <vector>
#include <string>
#include <utility>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

int hash_integer(int x)
{
   return  ((34 * x + 2) % 10000019) % 1000;
}
/*
int hash_string(const string & x)
{
    int hash {0};
    for (int i = x.size()-1; i >= 0; --i)
    {
        hash = (hash * 31 + static_cast<int>(x[i])) % 179426549;
    }
    return hash_integer(hash);
}
*/
struct Chain {
    vector<vector<std::pair<int,string>>> contacts;
    Chain()
    {
        contacts.resize(1000);
    }
    string HasKey(int pn)
    {
        for (auto &x : contacts[hash_integer(pn)])
	{
	    if (x.first == pn) {return x.second;}
	}
	return "not found";
    }
    void set(int pn, string & name)
    {
        vector<std::pair<int,string>> & tmp = contacts[hash_integer(pn)];
	for (auto &x : tmp)
	{
	    if (x.first == pn)
	    {
	        x.second = name;
		return;
	    }
	}
	tmp.push_back(std::make_pair(pn,name));
    }
    void del(int pn)
    {
        vector<std::pair<int,string>> & tmp = contacts[hash_integer(pn)];
	for (int i =0; i < tmp.size(); ++i)
	{
	    if ( tmp[i].first == pn) {tmp.erase(tmp.begin()+i);return;}
	}
    }
};

vector<string> process_queries(vector<Query> queries) {
    Chain map;
    vector<string> result;
    for (size_t i = 0; i < queries.size(); ++i)
    {
        if(queries[i].type == "add") {map.set(queries[i].number,queries[i].name);}
	else if (queries[i].type == "del" ) {map.del(queries[i].number);}
	else {result.push_back(map.HasKey(queries[i].number));}
    }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
