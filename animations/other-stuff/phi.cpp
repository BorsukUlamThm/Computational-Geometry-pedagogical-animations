#include <iostream>
#include "graphics/view/Animation_canvas.h"


namespace Other_stuff_phi
{
	namespace gr = graphics;

	typedef unsigned integer;

    std::vector<double> make_phi(integer n)
    {
        std::vector<integer> primes;
        std::vector<double> tab_phi;

        primes.push_back(2);
        tab_phi.push_back(1);

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

            double phi(1);
            bool is_prime = true;

            integer k = i;
            for (unsigned j = 0; j < primes.size() && k > 1; ++j)
            {
                integer d = 1;
                while (k % primes[j] == 0)
                {
                    k /= primes[j];
                    d *= primes[j];
                    is_prime = false;
                }
                if (d > 1)
                {
                    phi *= double(d) * (1 - 1 / double(d));
                }
            }
            if (is_prime)
            {
                phi = double(i - 1);
                primes.push_back(i);
            }
            tab_phi.push_back(phi);
        }

        std::cout << "phi done" << std::endl;
        return tab_phi;
    }

	void plot_phi(integer n,
				  float r)
	{
        std::vector<double> tab_phi = make_phi(n);

        gr::Figure fig;
        fig.add_vertical_line(0);
        fig.add_horizontal_line(0);
		for (unsigned i = 0; i < tab_phi.size(); ++i)
		{
			fig.add_point(i, tab_phi[i], gr::DEFAULT_SHAPE_COLOR, r);
		}

		tab_phi.clear();

		gr::Animation_canvas canvas;

		std::vector<unsigned> numbers;
		while (n >= 1000)
		{
			numbers.push_back(n % 1000);
			n = n / 1000;
		}
		numbers.push_back(n);

		std::string title = "phi(n) for n up to ";
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
	using namespace Other_stuff_phi;

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

	plot_phi(n, r);

	return 0;
}