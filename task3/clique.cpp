#include <iostream>
#include <set>
#include <vector>
#include <numeric>		// for std::iota

bool party[][8] = {
	// correct answer is: {1,4,5,6,7}
	{ 1, 1, 0, 1, 1, 1, 1, 1 }, // 0
	{ 0, 1, 0, 0, 1, 1, 1, 1 }, // 1
	{ 1, 1, 1, 0, 1, 1, 1, 1 }, // 2
	{ 1, 1, 0, 1, 1, 1, 1, 1 }, // 3
	{ 0, 1, 0, 0, 1, 1, 1, 1 }, // 4
	{ 0, 1, 0, 0, 1, 1, 1, 1 }, // 5
	{ 0, 1, 0, 0, 1, 1, 1, 1 }, // 6
	{ 0, 1, 0, 0, 1, 1, 1, 1 }  // 7

};

inline bool knows(int a, int b);

std::set<int> find_celebrities(bool(*knows)(int, int), const std::vector<int>* ps);

bool is_known(bool(*knows)(int, int), const std::vector<int>* ps, int p);

int main()
{
	std::vector<int> people(sizeof(party[0]));

	// fill vector with numbers [0; sizeof(party[0]) )
	std::iota(people.begin(), people.end(), 0);

	std::set<int> celebrities = find_celebrities(knows, &people);

	if (celebrities.size() > 0) {
		std::cout << "Celebrities are: ";
		for (int c : celebrities)
			std::cout << c << " ";

		std::cout << "\n";
	}
	else
		std::cout << "There are no celebrities at the party.\n";

	system("pause");
	return 0;
}


inline bool knows(int a, int b)
{
	// here can be any logic
	return party[a][b];
}

std::set<int> find_celebrities(bool(*knows)(int, int), const std::vector<int>* ps)
{
	std::set<int> celebrities, local1, local2;

	// pick random member of party
	int w = (*ps)[rand() % ps->size()];

	// and save everyone he knows (in some cases can speed up algorithm)
	for (int p : *ps)
		if (knows(w, p))
			local1.insert(p);

	// find celebrity among saved people
	for (int p : local1) {
		if (is_known(knows, ps, p)) // p is from clique
		{
			// save everyone that p know 
			for (int q : *ps)
				if (knows(p, q))
					local2.insert(q);

			return local2;
		}
	}
}

// is p known by everyone at the party?
bool is_known(bool(*knows)(int, int), const std::vector<int>* ps, int p)
{
	for (int i : *ps)
		if (!knows(i, p)) return false;

	return true;
}