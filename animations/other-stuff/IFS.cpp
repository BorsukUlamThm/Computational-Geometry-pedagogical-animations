#include <cmath>
#include <complex>
#include <random>
#include "graphics/view/Animation_canvas.h"
#include "utils/file_management.h"


namespace Other_stuff_IFS
{
	namespace gr = graphics;

	typedef float real;

	struct vector
	{
		real x = 0;
		real y = 0;

		vector() = default;

		vector(real x,
			   real y) :
				x(x),
				y(y)
		{}
	};

	struct matrix
	{
		real a = 1;
		real b = 0;
		real c = 0;
		real d = 1;

		matrix() = default;

		matrix(real a, real b,
			   real c, real d) :
				a(a), b(b),
				c(c), d(d)
		{}

		matrix(real r,
			   real theta)
		{
			a = r * std::cos(theta);
			b = -r * std::sin(theta);
			c = r * std::sin(theta);
			d = r * std::cos(theta);
		}
	};

	vector operator+(const vector& u,
					 const vector& v)
	{
		return {u.x + v.x,
				u.y + v.y};
	}

	matrix operator*(const matrix& A,
					 const matrix& B)
	{
		return {A.a * B.a + A.b * B.c, A.a * B.b + A.b * B.d,
				A.c * B.a + A.d * B.c, A.c * B.b + A.d * B.d};
	}

	matrix operator*(real lam,
					 const matrix& A)
	{
		return {lam * A.a, lam * A.b,
				lam * A.c, lam * A.d};
	}

	vector operator*(const matrix& A,
					 const vector& u)
	{
		return {A.a * u.x + A.b * u.y,
				A.c * u.x + A.d * u.y};
	}

	struct Ifun
	{
		matrix M;
		vector X;

		explicit Ifun(const std::vector<real>& params)
		{
			if (params.size() == 4)
			{
				M = matrix(params[0], params[1]);
				X = vector(params[2], params[3]);
			}
			else
			{
				M = matrix(params[0], params[1],
						   params[2], params[3]);
				X = vector(params[4], params[5]);
			}
		}

		vector apply(const vector& u) const
		{ return (M * u) + X; }
	};

	struct IFS
	{
		std::vector<Ifun> funs;

		explicit IFS(const std::string& file)
		{
			std::filesystem::path data_dir = utils::get_data_directory();
			std::ifstream ifs(data_dir / "IFS" / file);

			if (!ifs.is_open())
			{
				std::cerr << "invalid file read " << file << std::endl;
			}

			while (!ifs.eof())
			{
				std::string line;
				std::getline(ifs, line);

				if (line.empty() || line[0] == '#')
				{ continue; }

				std::vector<real> params;
				std::istringstream iss(line);

				for (real x; iss >> x;)
				{ params.push_back(x); }

				if (params.size() == 4 || params.size() == 6)
				{ funs.emplace_back(params); }

				if (funs.size() == 5)
				{ return; }
			}
		}
	};

	typedef std::vector<vector> compact;

	enum Figs
	{
		AXIS,
		FRACTAL,
		NB_FIGS
	};

	compact iterations(gr::Animation& animation,
					   IFS& ifs,
					   bool colors)
	{
		std::vector<gr::Color> colors_vec =
				{gr::RED, gr::PURPLE, gr::BLUE, gr::GREEN, gr::YELLOW};

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0., 1.0);
		vector p0(dis(gen), dis(gen));
//		vector p0(0.5, 0.28867513459);

		compact K;
		K.push_back(p0);
		compact buffer;

		unsigned max_iter = 50;
		unsigned max_points = 1000000;
		for (unsigned k = 0; k < max_iter; ++k)
		{
			if (K.size() > max_points)
			{ break; }

			for (unsigned j = 0; j < K.size(); ++j)
			{
				auto col = gr::DEFAULT_SHAPE_COLOR;
				if (colors)
				{
					col = colors_vec[j % ifs.funs.size()];
				}

				auto x = gr::Coordinate(K[j].x);
				auto y = gr::Coordinate(K[j].y);
				animation[FRACTAL].add_point(x, y, col);
			}
			animation.make_new_frame();
			animation[FRACTAL].clear();

			buffer.clear();
			for (auto& p : K)
			{
				for (auto& f : ifs.funs)
				{
					buffer.push_back(f.apply(p));
				}
			}

			std::swap(K, buffer);
		}

		return K;
	}
}

int main(int argc, char** argv)
{
	using namespace Other_stuff_IFS;

	std::string file = "IFS";
	bool colors = false;

	if (argc > 1)
	{ file = std::string(argv[1]); }
	if (argc > 2 && argv[2] == std::string("-colors"))
	{ colors = true; }

	gr::Animation animation(NB_FIGS);
	//			animation[AXIS].add_point(0, 0, gr::BACKGROUND_COLOR);
	//			animation[AXIS].add_point(1, 1, gr::BACKGROUND_COLOR);
	//			animation[AXIS].add_vertical_line(0);
	//			animation[AXIS].add_horizontal_line(0);

	IFS ifs(file);
	compact K = iterations(animation, ifs, colors);

	gr::Animation_canvas canvas;
	canvas.slow_down();
	canvas.run_animation(animation);

	return 0;
}