#include <iostream>
#include "sq_stack.h"

using namespace std;

int main()
{
	/* Post: The program has notified the user of any bracket mismatch in the standerd imput file
	   Uses: The class Stack
    	*/

	SqStack openings;
	char symbol;
	bool is_matched = true;
	while (is_matched && ((symbol = getchar())!='\n'))
	{
		if (symbol == '{' || symbol == '[' || symbol == '(')
		{
			openings.Push(symbol);
		}
		if (symbol == '}' || symbol == ']' || symbol == ')')
		{
			if (openings.Empty())
			{
				cout << "Unmatched closing bracket " << symbol << " deteced.";
				is_matched = false;
			}
			else
			{	char match;
			//	openings.Top(match);
				openings.Pop(match);
				is_matched = (symbol == '}' && match == '{') 
					|| (symbol == ']' && match == '[')
					|| (symbol == ')' && match == '(');

				if (!is_matched)
				{
					cout << "Bad match " << match << symbol << endl;
				}
			}
		}
	}

	if(!openings.Empty())
	{
		cout << "Ummatched opening bracket(s) deteced." << endl;
	}

	return 0;
}