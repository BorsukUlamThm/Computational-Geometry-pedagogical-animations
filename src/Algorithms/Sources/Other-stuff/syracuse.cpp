#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>

namespace Other_stuff_syracuse
{
    using boost::multiprecision::cpp_int;
    typedef cpp_int integer;

    int next(int n)
    {
        if(n % 2 == 0)
        {
            return n / 2;
        }
        return 3 * n + 1;
    }

    unsigned next(unsigned n)
    {
        if(n % 2 == 0)
        {
            return n / 2;
        }
        return 3 * n + 1;
    }

    integer next(integer& n)
    {
        if(n % 2 == 0)
        {
            return n / 2;
        }
        return 3 * n + 1;
    }

    void syracuse(integer& n, integer& N)
    {
        unsigned seed = n.convert_to<unsigned>();

        gr::Figure fig;
        fig.add_horizontal_line(0);
        fig.add_vertical_line(0);

        bool found4 = false;
        for(unsigned i = 0; i < N; ++i)
        {
            fig.add_point(i, log(double(n)), gr::YELLOW);
            std::cout << i << " " << n << std::endl;
            n = next(n);

            if(n == 4 && (!found4))
            {
                std::cout << i << std::endl;
                found4 = true;
            }
            if(found4)
            {
                break;
            }
        }

        gr::Display_canvas canvas;

        std::vector<unsigned> numbers;
        while(seed >= 1000)
        {
            numbers.push_back(seed % 1000);
            seed = seed / 1000;
        }
        numbers.push_back(seed);

        std::string title;
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

        title += " first terms of the Syracuse sequence";

        canvas.set_title(title);
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