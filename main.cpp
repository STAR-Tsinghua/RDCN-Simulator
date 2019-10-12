#include "run.h"

int main() 
{
	vector<string> algNames = {"ofs"};  // {"wiro", "rush", "basic", "ofs"}

	for (int i = 0; i < algNames.size(); i++)
	{
		ALGORITHM algorithm;
		algorithm.algName = algNames[i];
		algorithm.run();
	}
	return 0;
}