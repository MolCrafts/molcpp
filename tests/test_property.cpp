#include "utils.h"
#include "property.h"

namespace molcpp
{
    TEST(TestProperty, DefaultConstructor)
    {
        Property<int, double> prop;
        EXPECT_TRUE(prop.is<int>());
        EXPECT_EQ(prop.get<int>(), 0);
    }

    TEST(TestProperty, ValueConstructor)
    {
        Property<int, double> prop(3.14);
        EXPECT_TRUE(prop.is<double>());
        EXPECT_EQ(prop.get<double>(), 3.14);
    }

    TEST(TestProperty, AssignmentOperator)
    {
        Property<int, double> prop;
        prop = 42;
        EXPECT_TRUE(prop.is<int>());
        EXPECT_EQ(prop.get<int>(), 42);

        prop = 2.718;
        EXPECT_TRUE(prop.is<double>());
        EXPECT_EQ(prop.get<double>(), 2.718);
    }

    TEST(TestProperty, Get)
    {
        Property<int, double> prop(3.14);
        EXPECT_THROW(prop.get<int>(), std::bad_variant_access);
        EXPECT_EQ(prop.get<double>(), 3.14);
    }

    TEST(TestPropertyMap, SetAndGet)
    {
        Property_map<int, double> map;
        map.set("int", 42);
        map.set("double", 3.14);

        EXPECT_EQ(map.get<int>("int"), 42);
        EXPECT_EQ(map.get<double>("double"), 3.14);
    }

    TEST(TestPropertyMap, OutOfRange)
    {
        Property_map<int, double> map;
        EXPECT_THROW(map.get<int>("not_found"), std::out_of_range);
    }

    TEST(TestPropertyMap, Key)
    {
        Property_map<int, std::string, std::vector<double>> pm;

        pm.set("int_property", 42);
        pm.set("string_property", "hello world");
        pm.set("vector_property", std::vector<double>{1.2, 3.4, 5.6});

        std::vector<std::string> expected_keys = {"int_property", "string_property", "vector_property"};

        EXPECT_EQ(pm.key(), expected_keys);
    }

    TEST(Property_mapTest, Value)
    {
        Property_map<int, std::string, std::vector<double>> pm;

        pm.set("int_property", 42);
        pm.set("string_property", "hello world");
        pm.set("vector_property", std::vector<double>{1.2, 3.4, 5.6});

        std::vector<Property<int, std::string, std::vector<double>>> expected_values = {
            Property<int, std::string, std::vector<double>>(42),
            Property<int, std::string, std::vector<double>>("hello world"),
            Property<int, std::string, std::vector<double>>(std::vector<double>{1.2, 3.4, 5.6})};

        auto value = pm.value();

        EXPECT_EQ(value, expected_values);
        EXPECT_EQ(value[0], expected_values[0]);
        EXPECT_EQ(value[1], expected_values[1]);
        EXPECT_EQ(value[2], expected_values[2]);
    }

}