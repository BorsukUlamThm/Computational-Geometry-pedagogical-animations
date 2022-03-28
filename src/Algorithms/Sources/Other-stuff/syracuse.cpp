#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"
#include <cmath>

namespace Other_stuff_syracuse
{
    typedef unsigned integer;

    int next(int n)
    {
        if(n % 2 == 0)
        {
            return n / 2;
        }
        return 5 * n + 1;
    }

    void syracuse(int n, int N)
    {
        gr::Figure fig;
        fig.add_horizontal_line(0);
        fig.add_vertical_line(0);

        bool found4 = false;
        for(unsigned i = 0; i < N; ++i)
        {
            fig.add_point(i, log(double(n)), YELLOW);
            n = next(n);

            if(n == 4 && (!found4))
            {
                std::cout << i << std::endl;
                found4 = true;
            }

            std::cout << n << ' ' << std::flush;
        }
        gr::Display_canvas canvas;
        canvas.display_figure(fig);
    }
}

int main(int argc, char** argv)
{
    using namespace Other_stuff_syracuse;

    integer n = std::stoi(std::string(argv[1]));
    integer N = std::stoi(std::string(argv[2]));

    syracuse(n, N);

    return 0;
}