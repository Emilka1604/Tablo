#include "stack.h"
#include <gtest.h>

TEST(tablo<polynom>, can_push_element) {
	tablo<polynom> t;
	polynom p;
	p.parser("X^2");
	t.push(1, p);
	EXPECT_TRUE(t.getelem() == p);
}


