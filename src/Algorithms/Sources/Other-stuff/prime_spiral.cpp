#include "Graphics/View/View.h"


namespace Other_stuff_prime_spiral
{
	namespace gr = graphics;

	typedef unsigned integer;

	void prime_spiral(integer n, float rad)
	{
		std::vector<integer> P;
		P.push_back(2);
		P.push_back(3);
		for(integer k = 5; P.size() < n; k += 2 + 2 * ((k + 1) % 3) / 2)
		{
			bool is_prime = true;
			for(auto& p : P)
			{
				if(p * p > k)
				{
					break;
				}
				if(k % p == 0)
				{
					is_prime = false;
					break;
				}
			}

			if(is_prime)
			{
				P.push_back(k);
			}
		}

		gr::Figure fig;
		while(!P.empty())
		{
			gr::Coordinate p_ = gr::Coordinate(P.back());
			P.pop_back();

			gr::Coordinate x = p_ * std::cos(p_);
			gr::Coordinate y = p_ * std::sin(p_);

			fig.add_point(x, y, gr::DEFAULT_SHAPE_COLOR, rad);
		}

		gr::Display_canvas canvas;

		std::vector<unsigned> numbers;
		while(n >= 1000)
		{
			numbers.push_back(n % 1000);
			n = n / 1000;
		}
		numbers.push_back(n);

		std::string title = "p exp(i p) for the ";
		title += std::to_string(numbers[numbers.size() - 1]);
		for(unsigned i = numbers.size() - 2; i != -1; --i)
		{
			title += " ";
			if(numbers[i] < 100)
			{
				title += "0";
			}
			if(numbers[i] < 10)
			{
				title += "0";
			}
			title += std::to_string(numbers[i]);
		}
		title += " first primes";

		canvas.set_title(title);
		canvas.display_figure(fig);
	}
}

int main(int argc, char** argv)
{
	using namespace Other_stuff_prime_spiral;

	integer n = std::stoi(std::string(argv[1]));
	float r = std::stof(std::string(argv[2]));

	prime_spiral(n, r);

	return 0;
}