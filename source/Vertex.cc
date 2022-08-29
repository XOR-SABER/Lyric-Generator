#include "headers/Vertex.hpp"

std::ostream &operator<<(std::ostream &outs,const Edge &e) {
    outs << "\t\t " << e.word << ": " << e.weight;
    return outs;
}

std::ostream &operator<<(std::ostream &outs,const Vertex &v) {
	outs << "\tVertex: '" << v.word << "' - Count: " << v.count <<
		" TEW: " << v.total_edge_weight <<
		" Start Count: " << v.start_count <<
		" End Count: " << (v.count - v.total_edge_weight) <<
		" Comma Count: " << v.comma_count << 
		" Edges: " << v.edges.size() << std::endl;
	for (const Edge &e : v.edges) {
		outs << e << std::endl;
	}
	return outs;
}