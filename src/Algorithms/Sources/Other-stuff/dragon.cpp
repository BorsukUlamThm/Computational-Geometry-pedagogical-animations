#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"
#include <set>

namespace Other_stuff_dragon
{
    struct complex
    {
        double real = 0;
        double imag = 0;

        complex(double x = 0, double y = 0)
        {
            real = x;
            imag = y;
        }
    };

    complex operator+(const complex& z1, const complex& z2)
    {
        complex z;
        z.real = z1.real + z2.real;
        z.imag = z1.imag + z2.imag;
        return z;
    }

    complex operator-(const complex& z1, const complex& z2)
    {
        complex z;
        z.real = z1.real - z2.real;
        z.imag = z1.imag - z2.imag;
        return z;
    }

    complex operator-(const complex& z)
    {
        return complex(-z.real, -z.imag);
    }

    complex operator*(const complex& z1, const complex& z2)
    {
        complex z;
        z.real = z1.real * z2.real - z1.imag * z2.imag;
        z.imag = z1.real * z2.imag + z1.imag * z2.real;
        return z;
    }

    complex operator*(double a, const complex& z)
    {
        return complex(a * z.real, a * z.imag);
    }

    bool operator<(const complex& z1, const complex& z2)
    {
        if(z1.real == z2.real)
        {
            return z1.imag < z2.imag;
        }
        return z1.real < z2.real;
    }


    typedef std::set<complex> set;

    complex f1(const complex& z)
    {
        return 0.5 * complex(1, 1) * z;
    }

    complex f2(const complex& z)
    {
        return 1 - 0.5 * complex(1, -1) * z;
    }

    set iterations(unsigned n)
    {
        set S;
        S.emplace(0);
        S.emplace(1);
        set buffer;

        for(unsigned i = 0; i < n; ++i)
        {
            buffer.clear();
            for(auto& z : S)
            {
                buffer.insert(f1(z));
                buffer.insert(f2(z));
            }

            std::swap(S, buffer);
        }

        return S;
    }

    void plot_dragon(unsigned n, float r)
    {
        set S = iterations(n);
        gr::Figure fig;

        for(auto& z : S)
        {
            gr::Coordinate x = gr::Coordinate(z.real);
            gr::Coordinate y = gr::Coordinate(z.imag);
            fig.add_point(x, y, gr::DEFAULT_PLOT_COLOR, r);
        }

        gr::Display_canvas canvas;
        canvas.set_title("Dragon curve - " + std::to_string(n) + " iterations");
        canvas.display_figure(fig);
    }
}

int main(int argc, char** argv)
{
    using namespace Other_stuff_dragon;

    unsigned n = std::stoi(std::string(argv[1]));
    float r = std::stof(std::string(argv[2]));

    plot_dragon(n, r);

    return 0;
}