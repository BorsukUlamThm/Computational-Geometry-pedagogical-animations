#include <iostream>
#include "graphics/view/Animation_canvas.h"
#include <cmath>
#include <map>


namespace Other_stuff_mu
{
	namespace gr = graphics;

	typedef int integer;

	std::vector<integer> make_pi(integer n)
	{
		std::vector<integer> primes;
		std::vector<integer> tab_mu;

		primes.push_back(2);
		tab_mu.push_back(1);

		std::cout << "computing mu ..." << std::endl;
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

			integer mu(1);
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
                    if (vp == 2)
                    {
                        mu = 0;
                        break;
                    }
				}
                mu *= -1;
			}
			if (is_prime)
			{
                mu = -1;
				primes.push_back(i);
			}
			tab_mu.push_back(mu);
		}

		std::cout << "mu done" << std::endl << std::endl;

		return tab_mu;
	}

    void print_mu_values(const std::vector<integer>& tab_mu)
    {
        unsigned nb_m1 = 0;
        unsigned nb_0 = 0;
        unsigned nb_1 = 0;

        for(auto& mu : tab_mu)
        {
            if (mu == -1)
            { nb_m1++; }
            else if (mu == 0)
            { nb_0++; }
            else
            { nb_1++; }
        }
        unsigned S = nb_m1 + nb_0 + nb_1;

        std::cout << nb_m1 << " integers such that mu(n) = -1 ("
                << double(nb_m1) / double(S) << "%)" << std::endl
                << nb_0 << " integers such that mu(n) = 0 ("
                        << double(nb_0) / double(S) << "%)" << std::endl
                << nb_1 << " integers such that mu(n) = 1 ("
                        << double(nb_1) / double(S) << "%)" << std::endl
                << std::endl;
    }

	void plot_pi(integer n,
                 float r)
	{
		std::vector<integer> tab_mu = make_pi(n);
        print_mu_values(tab_mu);

        gr::Figure fig;
		for (unsigned i = 0; i < tab_mu.size(); ++i)
		{
			fig.add_point(i, n * (tab_mu[i]) * 0.1 , gr::DEFAULT_SHAPE_COLOR,
                          r);
		}

		tab_mu.clear();

		gr::Animation_canvas canvas;

		std::vector<unsigned> numbers;
		while (n >= 1000)
		{
			numbers.push_back(n % 1000);
			n = n / 1000;
		}
		numbers.push_back(n);

		std::string title = "mu(n) for n up to ";
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

    plot_pi(n, r);

	return 0;
}
