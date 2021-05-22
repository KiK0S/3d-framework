#include <cxxtest/TestSuite.h>
#include "../src/point.h"

class MyTestSuite1 : public CxxTest::TestSuite
{
public:
    void testAddition(void)
    {
    	app::Point4d a(0, 0, 0);
    	app::Point4d b(1, 2, 3);
        TS_ASSERT((a + b).x == 1);
    }
};