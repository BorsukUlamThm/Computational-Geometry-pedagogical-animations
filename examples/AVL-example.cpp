#include "geometry/utils/AVL.h"
#include <iostream>
#include <vector>


namespace geo = geometry;

// Make a subclass of AVL_tree and override the methods compare and are_equal
class tree : public geo::AVL_tree<int>
{
public:
	std::vector<int> tab;

private:
	bool compare(const int& i,
				 const int& j) const override
	{
		return tab[i] <= tab[j];
	}

	bool are_equal(const int& i,
				   const int& j) const override
	{
		return tab[i] == tab[j];
	}
};

int main()
{
	tree T;

	T.tab = {0, 5, 3, 8, 2, 9, 7, 1, 6, 4};

	for (int i = 0; i < 10; ++i)
	{
		T.insert(i);
	}

	std::cout << "T contains : ";
	while (!T.is_empty())
	{
		std::cout << T.extract_min() << " ";
	}
	std::cout << std::endl;

	return 0;
}