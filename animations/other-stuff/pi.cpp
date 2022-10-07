#include <iostream>
#include "graphics/view/Animation_canvas.h"
#include <cmath>
#include <map>


namespace Other_stuff_mu
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

    std::vector<integer> make_pi(integer n)
    {
        std::vector<integer> primes = make_primes(n);
        std::vector<integer> mu_values;

        primes.push_back(2);
        mu_values.push_back(0);
        mu_values.push_back(0);

        std::cout << "computing pi ..." << std::endl;
        std::vector<double> percents = {0.9, 0.8, 0.7, 0.6, 0.5,
                                        0.4, 0.3, 0.2, 0.1};

        integer k = 0;
        for (unsigned i = 2; i <= n; ++i)
        {
            if (!percents.empty() &&
                double(i) / double(n) > percents.back())
            {
                std::cout << percents.back() * 100 << "% done" << std::endl;
                percents.pop_back();
            }

            if (i >= primes[k + 1]) { k++; }
            mu_values.push_back(k + 1);
        }

        std::cout << "pi done" << std::endl;

        return mu_values;
    }

    void plot_pi(integer n,
                 float r)
    {
        std::vector<integer> tab_pi = make_pi(n);

        std::cout << std::endl;

        gr::Figure fig;
        fig.add_vertical_line(0);
        fig.add_horizontal_line(0);
        for (unsigned i = 0; i < tab_pi.size(); ++i)
        {
            fig.add_point(i, (tab_pi[i]) , gr::DEFAULT_SHAPE_COLOR,
                          r);
        }

        tab_pi.clear();

        gr::Animation_canvas canvas;

        std::vector<unsigned> numbers;
        while (n >= 1000)
        {
            numbers.push_back(n % 1000);
            n = n / 1000;
        }
        numbers.push_back(n);

        std::string title = "pi(x) for x up to ";
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
