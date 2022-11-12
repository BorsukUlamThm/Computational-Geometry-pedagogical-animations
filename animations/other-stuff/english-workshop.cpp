#include <cmath>
#include <complex>
#include <random>
#include <set>
#include "graphics/view/Animation_canvas.h"


namespace Other_stuff_english_workshop
{
	namespace gr = graphics;

	typedef float real;
	typedef std::complex<real> complex;
	typedef std::vector<complex> compact;

	constexpr real pi = M_PI;
	constexpr complex i = complex(0, 1);

	enum Figs
	{
		AXIS,
		SIERPINSKI,
		NB_FIGS
	};

	complex s1(complex z)
	{
		return z / 2.0f;
	}

	complex s2(complex z)
	{
		return z / 2.0f + 1.0f / 2.0f;
	}

	complex s3(complex z)
	{
		return z / 2.0f + std::exp(i * pi / 3.0f) / 2.0f;
	}

    complex r1(complex z)
    {
        return z / 2.0f;
    }

    complex r2(complex z)
    {
        return (z + 1.0f) / 2.0f;
    }

    complex r3(complex z)
    {
        return (z + i) / 2.0f;
    }

    complex r4(complex z)
    {
        return (z + i + 1.0f) / 2.0f;
    }

    complex vk1(complex z)
    {
        return z / 3.0f;
    }

    complex vk2(complex z)
    {
        return (z + 2.0f) / 3.0f;
    }

    complex vk3(complex z)
    {
        return (z * std::exp(i * pi / 3.0f) + 1.0f) / 3.0f;
    }

    complex vk4(complex z)
    {
        return (z * std::exp(-i * pi / 3.0f) + 1.0f + std::exp(i * pi / 3.0f)) / 3.0f;
    }

    complex p1(complex z)
    {
        return (z + std::exp((3.0f * i * pi) / 5.0f)) / 2.0f;
    }

    complex p2(complex z)
    {
        return (z + std::exp((6.0f * i * pi) / 5.0f)) / 3.0f;
    }

    complex p3(complex z)
    {
        return (z + std::exp((9.0f * i * pi) / 5.0f)) / 4.0f;
    }

    complex p4(complex z)
    {
        return (z + std::exp((12.0f * i * pi) / 5.0f)) / 5.0f;
    }

    complex p5(complex z)
    {
        return (z + std::exp((15.0f * i * pi) / 5.0f)) / 6.0f;
    }

    complex truc(complex z)
    {
        return std::sin(z) / 2.0f;
    }

    complex machin(complex z)
    {
        return std::sin(2.0f * z) / 4.0f;
    }

    complex d1(complex z)
    {
        return z * (1.0f + i) / 2.0f;
    }

    complex d2(complex z)
    {
        return 1.0f - z * (1.0f - i) / 2.0f;
    }

    complex f1(complex z)
    {
        real x = 0;
        real y = 0.16 * z.imag();
        return x + y * i;
    }

    complex f2(complex z)
    {
        real x = 0.85 * z.real() + 0.04 * z.imag();
        real y = -0.04 * z.real() + 0.85 * z.imag() + 1.6;
        return x + y * i;
    }

    complex f3(complex z)
    {
        real x = 0.2 * z.real() - 0.26 * z.imag();
        real y = 0.23 * z.real() + 0.22 * z.imag() + 1.6;
        return x + y * i;
    }

    complex f4(complex z)
    {
        real x = -0.15 * z.real() + 0.28 * z.imag();
        real y = 0.26 * z.real() + 0.24 * z.imag() + 0.44f;
        return x + y * i;
    }

	compact iterations(gr::Animation& animation, bool colors)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0., 1.0);
		complex z0(dis(gen), dis(gen));

		compact K;
		K.push_back(z0);
		compact buffer;

		unsigned max_iter = 50;
		for (unsigned k = 0; k < max_iter; ++k)
		{
			if (K.size() > 100000)
			{ break; }

			for (unsigned j = 0; j < K.size(); ++j)
			{
				auto col = gr::DEFAULT_SHAPE_COLOR;
				if (colors)
				{
                    switch(j % 4)
                    {
                        case 0:
                            col = gr::RED;
                            break;
                        case 1:
                            col = gr::BLUE;
                            break;
                        case 2:
                            col = gr::GREEN;
                            break;
                        case 3:
                            col = gr::YELLOW;
                            break;/*
                        case 4:
                            col = gr::PURPLE;
                            break;*/
                    }
				}

				auto x = gr::Coordinate(K[j].real());
				auto y = gr::Coordinate(K[j].imag());
				animation[SIERPINSKI].add_point(x, y, col);
			}
			animation.make_new_frame();
			animation[SIERPINSKI].clear();

			buffer.clear();
			for (auto& z : K)
			{
                buffer.push_back(f1(z));
                buffer.push_back(f2(z));
                buffer.push_back(f3(z));
                buffer.push_back(f4(z));
			}

			std::swap(K, buffer);
		}

		return K;
	}

	void iterated_f2()
	{
		complex z = i;

		std::cout << "Computing a fix point of f(z) = z/3 + 2/3" << std::endl
				  << "starting with u0 = i" << std::endl << std::endl;

		for (unsigned n = 0; n <= 20; ++n)
		{
			std::cout << "u" << n << " = "
					  << z.real() << " + "
					  << z.imag() << "i" << std::endl;
			z = s2(z);
		}
	}

	void ifs(bool colors)
	{
		while (true)
		{
			gr::Animation animation(NB_FIGS);
			animation[AXIS].add_point(0, 0, gr::BACKGROUND_COLOR);
			animation[AXIS].add_point(1, 1, gr::BACKGROUND_COLOR);
			animation[AXIS].add_vertical_line(0);
			animation[AXIS].add_horizontal_line(0);

			compact K = iterations(animation, colors);

			gr::Animation_canvas canvas;
			canvas.run_animation(animation);
		}
	}
}

int main(int argc, char** argv)
{
	using namespace Other_stuff_english_workshop;

	if (argc > 1)
	{ ifs(argc > 2 && argv[2] == std::string("-color")); }
	else
	{ iterated_f2(); }

	return 0;
}