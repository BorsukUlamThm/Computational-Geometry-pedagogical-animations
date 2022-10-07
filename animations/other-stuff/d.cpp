#include <iostream>
#include "graphics/view/Animation_canvas.h"
#include <cmath>
#include <map>


namespace Other_stuff_mu
{
	namespace gr = graphics;

	typedef unsigned integer;

	std::vector<integer> make_d(integer n)
	{
		std::vector<integer> primes;
		std::vector<integer> tab_d;

		primes.push_back(2);
		tab_d.push_back(1);

		std::cout << "computing phi ..." << std::endl;
		std::vector<double> percents = {0.9, 0.8, 0.7, 0.6, 0.5,
										0.4, 0.3, 0.2, 0.1};

		for (unsigned i = 2; i <= n; ++i)
		{
			if (!percents.empty() &&
				double(i) / double(n) > percents.back())
			{
				std::cout << percents.back() * 100 << "% done" << std::endl;
				percents.pop_back();
			}

			integer d(1);
			bool is_prime = true;

			integer k = i;
			for (unsigned j = 0; j < primes.size() && k > 1; ++j)
			{
				integer vp = 0;
				while (k % primes[j] == 0)
				{
					k /= primes[j];
					vp++;
					is_prime = false;
				}
				d *= (vp + 1);
			}
			if (is_prime)
			{
				d = 2;
				primes.push_back(i);
			}
			tab_d.push_back(d);
		}

		std::cout << "d done" << std::endl;

		return tab_d;
	}

	std::map<integer, unsigned> make_map(const std::vector<integer>& d_values)
	{
		std::map<integer, unsigned> map;

		for (auto& k : d_values)
		{
			if (map.find(k) == map.end())
			{
				map[k] = 1;
			}
			else
			{
				map[k]++;
			}
		}

		return map;
	}

	std::multimap<unsigned, integer>
	make_reverse_map(const std::map<integer, unsigned>& map)
	{
		std::multimap<unsigned, integer> reverse_map;
		for (auto& key_val : map)
		{
			reverse_map.insert({key_val.second, key_val.first});
		}

		return reverse_map;
	}

	void plot_d(integer n,
				float r)
	{
		std::vector<integer> d_values = make_d(n);
		std::map<integer, unsigned> map = make_map(d_values);
		std::multimap<unsigned, integer> reverse_map = make_reverse_map(map);

		std::cout << std::endl;

//		for (auto& key_val : map)
//		{
//			std::cout << key_val.second;
//
//			unsigned k = 6;
//			while (key_val.second < std::pow(10, k))
//			{
//				std::cout << " ";
//				k--;
//			}
//
//			std::cout << " integers such that d(n) = "
//					  << key_val.first << std::endl;
//		}

		for (auto& key_val : reverse_map)
		{
			std::cout << key_val.first;

			unsigned k = 6;
			while (key_val.first < std::pow(10, k))
			{
				std::cout << " ";
				k--;
			}

			std::cout << " integers such that d(n) = "
					  << key_val.second << std::endl;
		}

		integer max = *std::max_element(d_values.begin(), d_values.end());

        gr::Figure fig;
        fig.add_vertical_line(0);
        fig.add_horizontal_line(0);
		for (unsigned i = 0; i < d_values.size(); ++i)
		{
			fig.add_point(i, n * (d_values[i]) * 0.6 / double(max), gr::DEFAULT_SHAPE_COLOR,
						  r);
		}

		d_values.clear();

		gr::Animation_canvas canvas;

		std::vector<unsigned> numbers;
		while (n >= 1000)
		{
			numbers.push_back(n % 1000);
			n = n / 1000;
		}
		numbers.push_back(n);

		std::string title = "d(n) for n up to ";
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

		canvas.set_title(title);
		canvas.display_figure(fig);
	}
}

int main(int argc, char** argv)
{
	using namespace Other_stuff_mu;

	if (argc < 3)
	{
		std::cerr << "Missing program options"
				  << std::endl
				  << "Usage : ./phi <n> <r> displays the graph of phi between "
				  << "1 and n. r is the radius of the displayed points"
				  << std::endl
				  << "        You may not go higher tan 10^4 for n, and reduce "
				  << "r when n is high in order to see something";
		return 1;
	}

	integer n = std::stoi(std::string(argv[1]));
	float r = std::stof(std::string(argv[2]));

	plot_d(n, r);

	return 0;
}
