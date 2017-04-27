#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    char type;
    int position;
    
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }
};

int main() {
    std::string text;
    getline(std::cin, text);
    bool flag = true;
    int faulty_position;
    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];
        if (next == '(' || next == '[' || next == '{') {
	    opening_brackets_stack.push(Bracket(next,position+1));
        }

        if (next == ')' || next == ']' || next == '}') {
	    if (opening_brackets_stack.empty() || !opening_brackets_stack.top().Matchc(next)) {
	        flag=false;
	       	faulty_position = position+1;
		break;
	    }
	    else opening_brackets_stack.pop();
	}
    }
    if (flag == true && !opening_brackets_stack.empty()){
	flag = false;
        faulty_position = opening_brackets_stack.top().position;
    }
    if (flag == true) {std::cout << "Success" << std::endl;}
    else {std::cout << faulty_position << std::endl;}

    return 0;
}
