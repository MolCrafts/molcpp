#include "utils.h"
#include "element.h"

TEST(TestElement, test_get_element)
{
    molcpp::Element H = molcpp::Element::get_element(1);
    EXPECT_EQ(H.get_atomic_number(), 1);
    EXPECT_EQ(H.get_symbol(), "H");
}