#pragma once

#include <vector>
#include <utility>
#include "line.h"
#include "point.h"

namespace app {
	template <typename T = double>
	class WireObject {
	  public:
	    std::vector<Line4d<T>> lines() const;
	    virtual ~WireObject();
	 
	  protected:
	    std::vector<Point4d<T>> points_;
	    std::vector<std::pair<int, int>> edges_;
	};
}