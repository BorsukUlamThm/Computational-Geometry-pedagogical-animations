#include "geometry/model/serialization.h"
#include "geometry/algorithms/segment_intersections.h"
#include "graphics/view/Animation_canvas.h"


namespace gr = graphics;
namespace geo = geometry;

int main ()
{
	auto segments = geo::load_segment_2_set("log/chapter-2/segment_intersections");

	geo::DCEL D = geo::segment_intersections(segments);

	graphics::Animation animation(2);
//	D.add_to_figure(animation[0]);
//	animation.make_new_frame();

	std::vector<geo::point_2> save;
	for (auto& v : D.vertices)
	{
		gr::Coordinate x(v->x);
		gr::Coordinate y(v->y);
		save.emplace_back(v->x, v->y);

		animation[1].add_point(x, y, gr::Color::RED);
	}
	animation.make_new_frame();


	geo::save_point_2_set("serialization-test", save);
	auto load = geo::load_point_2_set("serialization-test");

	for (auto& p : load)
	{
		gr::Coordinate x(p.x);
		gr::Coordinate y(p.y);
		animation[1].add_point(x, y, gr::Color::YELLOW);
	}
	animation.make_new_frame();


	gr::Animation_canvas canvas;
	canvas.run_animation(animation);

	return 0;
}