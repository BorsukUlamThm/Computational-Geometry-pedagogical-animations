/** @cond */
#include <cmath>
#include <boost/multiprecision/cpp_int.hpp>
/** @endcond */
#include "Graphics/View/View.h"

namespace Other_stuff_syracuse
{
    using boost::multiprecision::cpp_int;
    typedef cpp_int integer;

    std::string number_to_string(integer n)
    {
        std::vector<integer> numbers;
        while(n >= 1000)
        {
            numbers.push_back(n % 1000);
            n = n / 1000;
        }
        numbers.push_back(n);

        std::string str;
        str += std::to_string(numbers[numbers.size() - 1].convert_to<unsigned>());
        for(unsigned i = numbers.size() - 2; i != -1; --i)
        {
            str += " ";
            if(numbers[i] < 100)
            {
                str += "0";
            }
            if(numbers[i] < 10)
            {
                str += "0";
            }
            str += std::to_string(numbers[i].convert_to<unsigned>());
        }

        return str;
    }

    std::string number_to_string(unsigned n)
    {
        std::vector<unsigned> numbers;
        while(n >= 1000)
        {
            numbers.push_back(n % 1000);
            n = n / 1000;
        }
        numbers.push_back(n);

        std::string str;
        str += std::to_string(numbers[numbers.size() - 1]);
        for(unsigned i = numbers.size() - 2; i != -1; --i)
        {
            str += " ";
            if(numbers[i] < 100)
            {
                str += "0";
            }
            if(numbers[i] < 10)
            {
                str += "0";
            }
            str += std::to_string(numbers[i]);
        }

        return str;
    }

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

    void syracuse(integer& n)
    {
        unsigned seed = n.convert_to<unsigned>();

        gr::Figure fig;
        fig.add_horizontal_line(0);
        fig.add_vertical_line(0);

        integer M = n;

        unsigned i = 0;
        for(; ; ++i)
        {
            fig.add_point(i, log(double(n)), gr::YELLOW);
            // std::cout << i << " " << n << std::endl;
            n = next(n);

            if(n > M)
            {
                M = n;
            }

            if(n == 1)
            {
                break;
            }
        }

        std::cout << "Number of terms before we hit 1 : " << number_to_string(i + 1) << std::endl;
        std::cout << "Maximal term : " << number_to_string(M) << std::endl;

        gr::Display_canvas canvas;

        std::string title = number_to_string(seed);

        title += " first terms of the Syracuse sequence";

        canvas.set_title(title);
        canvas.display_figure(fig);
    }
}

int main(int argc, char** argv)
{
    using namespace Other_stuff_syracuse;

    integer n = std::stoi(std::string(argv[1]));

    syracuse(n);

    return 0;
}