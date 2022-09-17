#include "graphics/view/Display_canvas.h"
#include "graphics/view/Acquisition_canvas.h"
#include "utils/Program_options.h"
#include "geometry/DCEL/DCEL.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/polygon_utils.h"
#include "geometry/utils/Event_queue.h"
#include "geometry/utils/line_intersections.h"


namespace gr = graphics;
namespace geo = geometry;

int main(int argc, char** argv)
{
	std::string str ("0123456789");

	std::cout << str.substr(3, 5) << std::endl;

	return 0;
}