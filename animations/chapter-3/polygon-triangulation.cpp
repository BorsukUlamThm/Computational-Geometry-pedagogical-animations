#include "include/pt_utils.h"
#include "include/monotone_partition.h"
#include "include/triangulate_monotone.h"
#include "geometry/model/serialization.h"
#include "graphics/view/Animation_canvas.h"
#include "geometry/algorithms/segment_intersections_components/face_computation.h"


namespace chap3_polygon_triangulation
{
	namespace gr = graphics;
	namespace geo = geometry;
	using namespace polygon_triangulation;


	void triangulate(DCEL& D,
					 gr::Animation& animation)
	{
		if (!is_valid(D))
		{ return; }

		plot_polygon(D, animation);

		auto faces = make_monotone(D, animation);
		for (auto& f : faces)
		{
			triangulate_monotone(D, f, animation);
		}
	}
}

int main(int argc, char** argv)
{
	using namespace chap3_polygon_triangulation;

	Options opt = process_command_line(argc, argv);
	DCEL D = make_polygon(opt);
	gr::Animation faces_anim = D.display_faces();
	gr::Animation_canvas faces_canvas;
	faces_canvas.run_animation(faces_anim);

	geo::save_DCEL("log/chapter-3/polygon_triangulation", D);
	gr::Animation animation(NB_FIGURES);
	triangulate(D, animation);

	gr::Animation_canvas canvas;
	canvas.set_title("Polygon Triangulation - animation");
	canvas.run_animation(animation);

	return 0;
}