#include "loader.h"
#include "point.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace app {

SurfaceObject Loader::load(const std::string& filename) {
	if (filename.size() < 4) {
		throw std::invalid_argument("invalid filename");
	}
	size_t length = filename.size();
	std::string format = filename.substr(length - 4, 4);
	if (format != ".off") {
		throw std::invalid_argument("format not supported");
	}
	std::ifstream in(filename);
	std::string line;

	getline(in, line); // first line is OFF by standard
	std::vector<Point4d> points;
	std::vector<SurfaceObject::Triplet> triangles;
	int surfaces;
	
	while (getline(in, line)) {
		if (line.empty()) {
			continue;
		}
		if (line[0] == '#') {
			continue;
		}
		std::istringstream iss(line);
		int a, b, c;
		iss >> a >> b >> surfaces;
		points.resize(a);
		break;
	}

	for (size_t i = 0; i < points.size(); i++) {
		getline(in, line);
		std::istringstream iss(line);
		double a, b, c;
		iss >> a >> b >> c;
		points[i] = Point4d(a, b, c);
		// points[i] *= 30;
	}


	for (size_t i = 0; i < surfaces; i++) {
		getline(in, line);
		std::istringstream iss(line);
		int n;
		iss >> n;
	 	std::vector<int> indices(n);
		for (int j = 0; j < n; j++) {
			iss >> indices[j];
		}
		iss.eof();
		double A, B, C;
		if (iss.peek() == ' ') {
			iss >> A >> B >> C;
		} else {
			A = rand() * 1.0 / RAND_MAX;
			B = rand() * 1.0 / RAND_MAX;
			C = rand() * 1.0 / RAND_MAX;
		}
		A *= 255;
		B *= 255;
		C *= 255;
		for (int j = 1; j + 1 < n; j++) {
			triangles.emplace_back(indices[0], indices[j], indices[j + 1], sf::Color(A, B, C));	
		}
		triangles.emplace_back(indices[0], indices[1], indices[n - 1], sf::Color(A, B, C));
	}
	in.close();
	return SurfaceObject(points, {}, triangles);
}


}