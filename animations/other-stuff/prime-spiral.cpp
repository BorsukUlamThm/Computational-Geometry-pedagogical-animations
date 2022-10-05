#include <cmath>
#include "graphics/view/Animation_canvas.h"


namespace Other_stuff_prime_spiral
{
	namespace gr = graphics;

	typedef unsigned integer;

	std::vector<integer> make_primes(integer n)
	{
		std::vector<integer> P;
		P.push_back(2);
		P.push_back(3);
		for (integer k = 5; k <= n; k += 2 + 2 * ((k + 1) % 3) / 2)
		{
			bool is_prime = true;
			for (auto& p : P)
			{
				if (p * p > k)
				{
					break;
				}
				if (k % p == 0)
				{
					is_prime = false;
					break;
				}
			}

			if (is_prime)
			{
				P.push_back(k);
			}
		}

		return P;
	}

	void prime_spiral(integer n,
					  float rad)
	{
		std::vector<integer> P = make_primes(n);

		gr::Animation animation(2);

		animation[0].add_vertical_line(0);
		animation[0].add_horizontal_line(0);

		for (unsigned i = 1; i <= n; ++i)
		{
			gr::Coordinate i_(i);

			gr::Coordinate x = i_ * std::cos(i_);
			gr::Coordinate y = i_ * std::sin(i_);
			animation[1].add_point(x, y, gr::YELLOW, rad);
		}
		animation.make_new_frame();
		animation[1].clear();

		while (!P.empty())
		{
			gr::Coordinate p_(P.back());
			P.pop_back();

			gr::Coordinate x = p_ * std::cos(p_);
			gr::Coordinate y = p_ * std::sin(p_);

			animation[1].add_point(x, y, gr::YELLOW, rad);
		}
		animation.make_new_frame();

		gr::Animation_canvas canvas;

		std::vector<unsigned> numbers;
		while (n >= 1000)
		{
			numbers.push_back(n % 1000);
			n = n / 1000;
		}
		numbers.push_back(n);

		std::string title = "p exp(i p) for the primes lower than ";
		title += std::to_string(numbers[numbers.size() - 1]);
		for (unsigned i = numbers.size() - 2; i != -1; --i)
		{
			title += " ";
			if (numbers[i] < 100)
			{
				title += "0";
			}
			if (numbers[i] < 10)
			{
				title += "0";
			}
			title += std::to_string(numbers[i]);
		}
//		title += " first primes";

		canvas.set_title(title);
		canvas.run_animation(animation);
	}
}

int main(int argc, char** argv)
{
	using namespace Other_stuff_prime_spiral;

	if (argc < 3)
	{
		std::cerr << "Missing program options"
				  << std::endl
				  << "Usage : ./prime-spiral <n> <r> displays the set of "
				  << "complexes p exp(i p) for all primes p lower than n. r is "
				  << "the radius of the displayed points"
				  << std::endl
				  << "        You may not go higher tan 10^5 for n, and reduce "
				  << "r when n is high in order to see something";
		return 1;
	}

	integer n = std::stoi(std::string(argv[1]));
	float r = std::stof(std::string(argv[2]));

	prime_spiral(n, r);

	return 0;
}