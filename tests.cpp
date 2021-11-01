#include "src/Graphics/View/View.h"
#include "src/Algorithms/Algorithms.h"

typedef unsigned integer;

bool is_prime(unsigned n)
{
    for(unsigned i = 2; i * i <= n; ++i)
    {
        if(n % i == 0)
        {
            return false;
        }
    }
    return true;
}

void spiral(integer n, float rad)
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

        fig.add_point(x, y, DEFAULT_PLOT_COLOR, rad);
    }

    gr::Display_canvas canvas;
    canvas.display_figure(fig);
}

int main(int argc, char** argv)
{
    integer n = std::stoi(std::string(argv[1]));
    float r = std::stof(std::string(argv[2]));

    spiral(n, r);

    return 0;
}

