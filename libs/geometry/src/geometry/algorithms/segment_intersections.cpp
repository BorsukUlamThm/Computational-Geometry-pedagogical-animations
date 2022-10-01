#include "geometry/algorithms/segment_intersections.h"
#include "geometry/algorithms/segment_intersections/utils.h"
#include "geometry/algorithms/segment_intersections/tree.h"
#include "geometry/algorithms/segment_intersections/events.h"


namespace geometry
{
	namespace sic = segment_intersections_components;

	DCEL segment_intersections(const std::vector<segment_2>& S)
	{
		DCEL D = sic::brute_dcel(S);
		sic::tree T;
		T.plot_segments(S);
		sic::queue Q(D, T);

		Q.handle_events();

		gr::Animation_canvas canvas;
		canvas.run_animation(T.animation);

		return D;
	}
}