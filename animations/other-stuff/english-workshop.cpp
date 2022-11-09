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

	complex f1(complex z)
	{
		return z / 3.0f;
	}

	complex f2(complex z)
	{
		return z / 3.0f + 2.0f / 3.0f;
	}

	complex f3(complex z)
	{
		return z / 3.0f + std::exp(i * pi / 3.0f) * 2.0f / 3.0f;
	}

	compact iterations(gr::Animation& animation)
	{
		std::random_device rd;  // Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<> dis(0., 1.0);
		complex z0(dis(gen), dis(gen));

		compact K;
		K.push_back(z0);
		compact buffer;

		unsigned max_iter = 50;
		for (unsigned k = 0; k < max_iter; ++k)
		{
			if (K.size() > 10000)
			{ break; }

			for (auto& z : K)
			{
				auto x = gr::Coordinate(z.real());
				auto y = gr::Coordinate(z.imag());
				animation[SIERPINSKI].add_point(x, y);
			}
			animation.make_new_frame();
			animation[SIERPINSKI].clear();

			buffer.clear();
			for (auto& z : K)
			{
				buffer.push_back(f1(z));
				buffer.push_back(f2(z));
				buffer.push_back(f3(z));
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
			z = f2(z);
		}
	}

	void ifs()
	{
		while(true)
		{
			gr::Animation animation(NB_FIGS);
			animation[AXIS].add_point(0, 0, gr::BACKGROUND_COLOR);
			animation[AXIS].add_point(1, 1, gr::BACKGROUND_COLOR);
			animation[AXIS].add_vertical_line(0);
			animation[AXIS].add_horizontal_line(0);

			compact K = iterations(animation);

			gr::Animation_canvas canvas;
			canvas.run_animation(animation);
		}
	}
}

int main(int argc, char** argv)
{
	using namespace Other_stuff_english_workshop;

	if (argc > 1 && argv[1] == std::string("???"))
	{ ifs(); }
	else
	{ iterated_f2(); }

	return 0;
}