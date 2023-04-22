#include "utils.h"
#include "dict.h"

namespace molcpp
{
    TEST(TestData, DefaultConstructor)
    {
        Data<int, double> d;
        EXPECT_TRUE(d.is<int>());
        EXPECT_EQ(d.get<int>(), 0);
    }

    TEST(TestData, ValueConstructor)
    {
        Data<int, double> d(3.14);
        EXPECT_TRUE(d.is<double>());
        EXPECT_EQ(d.get<double>(), 3.14);
    }

    TEST(TestData, AssignmentOperator)
    {
        Data<int, double> d;
        d = 42;
        EXPECT_TRUE(d.is<int>());
        EXPECT_EQ(d.get<int>(), 42);

        d = 2.718;
        EXPECT_TRUE(d.is<double>());
        EXPECT_EQ(d.get<double>(), 2.718);
    }

    TEST(TestData, Get)
    {
        Data<int, double> d(3.14);
        EXPECT_THROW(d.get<int>(), std::bad_variant_access);
        EXPECT_EQ(d.get<double>(), 3.14);
    }

    TEST(TestDict, SetAndGet)
    {
        Dict<int, double> d;
        d.set("int", 42);
        d.set("double", 3.14);

        EXPECT_EQ(d.get<int>("int"), 42);
        EXPECT_EQ(d.get<double>("double"), 3.14);

        // test double set
        d.set("double", 1.11);
        EXPECT_EQ(d.get<double>("double"), 1.11);
    }

    TEST(TestDict, OutOfRange)
    {
        Dict<int, double> map;
        EXPECT_THROW(map.get<int>("not_found"), std::out_of_range);
    }

    TEST(TestDict, Key)
    {
        Dict<int, std::string, std::vector<double>> pm;

        pm.set("int_Dict", 42);
        pm.set("string_Dict", "hello world");
        pm.set("vector_Dict", std::vector<double>{1.2, 3.4, 5.6});

        std::vector<std::string> expected_keys = {"int_Dict", "string_Dict", "vector_Dict"};

        EXPECT_EQ(pm.key(), expected_keys);
    }

    TEST(TestDict, Value)
    {
        Dict<int, std::string, std::vector<double>> pm;

        pm.set("int_Dict", 42);
        pm.set("string_Dict", "hello world");
        pm.set("vector_Dict", std::vector<double>{1.2, 3.4, 5.6});

        std::vector<Data<int, std::string, std::vector<double>>> expected_values = {
            Data<int, std::string, std::vector<double>>(42),
            Data<int, std::string, std::vector<double>>("hello world"),
            Data<int, std::string, std::vector<double>>(std::vector<double>{1.2, 3.4, 5.6})};

        auto value = pm.value();

        EXPECT_EQ(value, expected_values);
        EXPECT_EQ(value[0], expected_values[0]);
        EXPECT_EQ(value[1], expected_values[1]);
        EXPECT_EQ(value[2], expected_values[2]);
    }

}