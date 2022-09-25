#include "graphics/view/Animation_canvas.h"
#include "graphics/view/Acquisition_canvas.h"
#include "utils/Program_options.h"
#include "geometry/model/DCEL.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/polygon_utils.h"
#include "geometry/utils/event_queue.h"
#include "geometry/utils/AVL.h"
#include "geometry/utils/line_intersections.h"


namespace gr = graphics;
namespace geo = geometry;

class tree : public geo::AVL_tree<int>
{
	bool compare(const int& i,
				 const int& j) const override
	{
		return i <= j;
	}

	bool are_equal(const int& i,
				   const int& j) const override
	{
		return i == j;
	}
};

void print_and_clear_T(geo::AVL_tree<int>& T)
{
	while (!T.is_empty())
	{
		unsigned i = T.extract_min();
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

class tree1 : public geo::AVL_tree<int>
{
public:
	std::vector<int> tab;

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

int main(int argc, char** argv)
{
	tree T;
	for (int i = 0; i < 10; ++i)
	{
		T.insert(i);
	}

	print_and_clear_T(T);

	tree1 T1;
	for (int i = 4; i >= 0; --i)
	{
		T1.tab.push_back(i);
	}
	for (int i = 5; i < 10; ++i)
	{
		T1.tab.push_back(i);
	}

	for (int i = 0; i < 10; ++i)
	{
		T1.insert(i);
	}

	print_and_clear_T(T1);

	return 0;
}