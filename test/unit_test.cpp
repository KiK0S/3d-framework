#include <cxxtest/TestSuite.h>
#include "../src/point.h"
#include "../src/matrix.h"
#include "../src/triangle.h"
#include <bits/stdc++.h>

class UnitTest : public CxxTest::TestSuite
{
public:
    void testPoint(void) {
    	app::Point4d a(0, 0, 0);
    	app::Point4d b(1, 2, 3);
        TS_ASSERT((a + b).x == 1);

    }
    void testMatrix(void) {
    	app::Matrix4d matrix{1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1};
    	app::Matrix4d eye = app::Matrix4d::identity_matrix();
    	TS_ASSERT(matrix * eye == matrix);
    	TS_ASSERT(eye * matrix == matrix);
        TS_ASSERT(matrix * matrix == app::Matrix4d({1, 0, 0, 2, 0, 1, 0, 2, 0, 0, 1, 2, 0, 0, 0, 1}));
    	TS_ASSERT((matrix * matrix.inverse() == eye));
    }
    void testTriangle() {
    	app::Triangle2d triangle({0, 0}, {1, 0}, {0, -1});
    	TS_ASSERT(triangle.inner_point({0.5, -0.5}));
    	TS_ASSERT(triangle.inner_point({0.5, -0.4}));
    	TS_ASSERT(!triangle.inner_point({1.05, -0.02}));
    	TS_ASSERT((triangle.get_order() == std::array<int, 3>({2, 1, 0})));
    }
};