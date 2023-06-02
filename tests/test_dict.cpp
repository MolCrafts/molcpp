#include "utils.h"
#include "dict.h"
#include "linalg.hpp"

namespace molcpp
{
    TEST(TestData, test_default_constructor)
    {
        Data<int, double> d;
        EXPECT_EQ(d.get<int>(), 0);
    }

    TEST(TestData, test_constructor)
    {
        Data<int, double> d(3.14);
        EXPECT_FALSE(d.is<int>());
        EXPECT_TRUE(d.is<double>());
        EXPECT_EQ(d.get<double>(), 3.14);

        // TODO
        // Data<Vector3D> d2({0, 1, 2});
        // EXPECT_TRUE(d2.is<Vector3D>());
        // EXPECT_TRUE(d2.get<Vector3D>() == Vector3D(0, 1, 2));

        Data<Vector3D> d3(Vector3D(1, 2, 3));
        EXPECT_TRUE(d3.is<Vector3D>());
        EXPECT_TRUE(d3.get<Vector3D>() == Vector3D(1, 2, 3));
    }

    TEST(TestData, test_copy_constructor)
    {
        Data<int, double> d1(3.14);
        Data<int, double> d2(d1);
        EXPECT_TRUE(d1.is<double>());
        EXPECT_EQ(d1.get<double>(), 3.14);
        EXPECT_TRUE(d2.is<double>());
        EXPECT_EQ(d2.get<double>(), 3.14);
    }

    TEST(TestData, test_move_constructor)
    {
        
        Data<int, double> d1(3.14);
        Data<int, double> d2(std::move(d1));
        EXPECT_TRUE(d1.is<double>());
        EXPECT_EQ(d1.get<double>(), 3.14);
        EXPECT_TRUE(d2.is<double>());
        EXPECT_EQ(d2.get<double>(), 3.14);

        Data<Vector3D> d3(Vector3D(1, 2, 3));
        Data<Vector3D> d4(std::move(d3));
        EXPECT_TRUE(d3.is<Vector3D>());
        EXPECT_TRUE(d3.get<Vector3D>() == Vector3D(1, 2, 3));
        EXPECT_TRUE(d4.is<Vector3D>());
        EXPECT_TRUE(d4.get<Vector3D>() == Vector3D(1, 2, 3));

    }

    TEST(TestData, test_assigment_op)
    {
        Data<int, double> d;
        d = 42;
        EXPECT_TRUE(d.is<int>());
        EXPECT_EQ(d.get<int>(), 42);

        d = 2.718;
        EXPECT_TRUE(d.is<double>());
        EXPECT_EQ(d.get<double>(), 2.718);
    }

    TEST(TestData, test_equality_op)
    {
        Data<int, double> d1(3.14);
        Data<int, double> d2(3.14);
        Data<int, double> d3(2.718);

        EXPECT_TRUE(d1 == d2);
        EXPECT_FALSE(d1 == d3);
    }

    TEST(TestData, test_inhomogeneous_eq_op)
    {
        Data<int, std::string, Vector3D> d1(1);
        // Data<int, std::string, Vector3D> d2("hello");
        Data<int, std::string, Vector3D> d3(Vector3D(1, 2, 3));

        EXPECT_TRUE(d1 == 1);
        // EXPECT_TRUE(d2 == "hello");
        EXPECT_TRUE(d3 == Vector3D(1, 2, 3));
    }

    TEST(TestData, test_get)
    {
        Data<int, double> d(3.14);
        EXPECT_THROW(d.get<int>(), std::bad_variant_access);
        EXPECT_EQ(d.get<double>(), 3.14);
    }

    TEST(TestData, test_set)
    {
        Data<int, double> d;
        d.set(42);
        EXPECT_TRUE(d.is<int>());
        EXPECT_EQ(d.get<int>(), 42);

        d.set(2.718);
        EXPECT_TRUE(d.is<double>());
        EXPECT_EQ(d.get<double>(), 2.718);
    }

    TEST(TestData, test_is)
    {
        Data<int, double> d(3.14);
        EXPECT_FALSE(d.is<int>());
        EXPECT_TRUE(d.is<double>());
    }

    TEST(TestData, test_get_index)
    {
        Data<int, double> d;
        EXPECT_EQ(d.index(), 0);
        d.set(3.14);
        EXPECT_EQ(d.index(), 1);
    }

    TEST(TestData, test_get_raw)
    {
        Data<int, double> d;
        EXPECT_EQ(d.get_raw().index(), 0);
        d.set(3.14);
        EXPECT_EQ(d.get_raw().index(), 1);
    }

    TEST(TestDict, test_default_constructor)
    {
        Dict<int, double> d;
        EXPECT_EQ(d.size(), 0);
    }

    TEST(TestDict, test_constructor)
    {
        Dict<int, double> d({{"int", 42}, {"double", 3.14}});
        EXPECT_EQ(d.size(), 2);
        EXPECT_EQ(d.get<int>("int"), 42);
        EXPECT_EQ(d.get<double>("double"), 3.14);
    }

    TEST(TestDict, test_move_constructor)
    {
        Dict<int, double> d1({{"int", 42}, {"double", 3.14}});
        Dict<int, double> d2(std::move(d1));
        EXPECT_EQ(d1.size(), 0);
        EXPECT_EQ(d2.size(), 2);
        EXPECT_EQ(d2.get<int>("int"), 42);
        EXPECT_EQ(d2.get<double>("double"), 3.14);
    }

    TEST(TestDict, test_copy_constructor)
    {
        Dict<int, double> d1({{"int", 42}, {"double", 3.14}});
        Dict<int, double> d2(d1);
        EXPECT_EQ(d1.size(), 2);
        EXPECT_EQ(d2.size(), 2);
        EXPECT_EQ(d2.get<int>("int"), 42);
        EXPECT_EQ(d2.get<double>("double"), 3.14);
    }

    TEST(TestDict, test_assignment)
    {
        Dict<int, double> d1({{"int", 42}, {"double", 3.14}});
        Dict<int, double> d2;
        d2 = d1;
        EXPECT_EQ(d1.size(), 2);
        EXPECT_EQ(d2.size(), 2);
        EXPECT_EQ(d2.get<int>("int"), 42);
        EXPECT_EQ(d2.get<double>("double"), 3.14);
    }

    TEST(TestDict, test_set_get)
    {
        Dict<int, double> d;
        d.set("int", 42);
        d.set("double", 3.14);

        EXPECT_EQ(d.get<int>("int"), 42);
        EXPECT_EQ(d.get<double>("double"), 3.14);

        // overwrite 
        d.set("int", 2);
        EXPECT_EQ(d.get<int>("int"), 2);
        d.set("double", 2.718);
        EXPECT_EQ(d.get<double>("double"), 2.718);

        // test double set
        d.set("double", 1.11);
        EXPECT_EQ(d.get<double>("double"), 1.11);
    }

    TEST(TestDict, test_key_out_found)
    {
        Dict<int, double> map;
        EXPECT_THROW(map.get<int>("not_found"), KeyError);
    }

    TEST(TestDict, test_get_keys)
    {
        Dict<int, std::string, std::vector<double>> pm;

        pm.set("int", 42);
        pm.set("string", "hello world");
        pm.set("vector", std::vector<double>{1.2, 3.4, 5.6});

        std::vector<std::string> expected_keys = {"int", "string", "vector"};

        EXPECT_EQ(pm.keys(), expected_keys);
    }

    TEST(TestDict, test_get_values)
    {
        Dict<int, std::string, std::vector<double>> pm;

        pm.set("int", 42);
        pm.set("string", "hello world");
        pm.set("vector", std::vector<double>{1.2, 3.4, 5.6});

        std::vector<Data<int, std::string, std::vector<double>>> expected_values = {
            Data<int, std::string, std::vector<double>>(42),
            Data<int, std::string, std::vector<double>>("hello world"),
            Data<int, std::string, std::vector<double>>(std::vector<double>{1.2, 3.4, 5.6})};

        auto value = pm.values();

        EXPECT_EQ(value, expected_values);
    }

    TEST(TestDict, test_has_key)
    {
        Dict<int, std::string, std::vector<double>> pm;

        pm.set("int", 42);
        EXPECT_TRUE(pm.has("int"));
        EXPECT_FALSE(pm.has("double"));
    }

    TEST(TestDict, test_operator_square_brackets)
    {
        Dict<int, std::string, std::vector<double>> pm;

        pm["int"] = 42;
        EXPECT_EQ(pm["int"].get<int>(), 42);

        const Dict<int, std::string, std::vector<double>> pm2 = pm;
        EXPECT_EQ(pm2["int"].get<int>(), 42);
    }

}