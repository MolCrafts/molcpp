#include <doctest/doctest.h>
#include "item.h"

TEST_SUITE("Item") {

    TEST_CASE("get id") {
        molcpp::Item item;
        CHECK(item.get_id() == reinterpret_cast<size_t>(&item));
    }

    TEST_CASE("setter and getter") {
        molcpp::Item item;
        item.set("foo", 42);
        CHECK(item.get<int>("foo") == 42);
    }

    TEST_CASE("clone") {

        molcpp::Item item;
        item.set("foo", 42);
        item.set<std::string>("bar", "baz");

        auto item2 = item.clone();
        CHECK(item2->get<int>("foo") == 42);
        CHECK(item2->get<std::string>("bar") == "baz");

    }

}

TEST_SUITE("Atom") {

    TEST_CASE("get id") {
        molcpp::Atom atom;
        CHECK(atom.get_id() == reinterpret_cast<size_t>(&atom));
    }

    TEST_CASE("setter and getter") {
        molcpp::Atom atom;
        atom.set("foo", 42);
        CHECK(atom.get<int>("foo") == 42);
    }

    TEST_CASE("clone") {

        molcpp::Atom atom;
        atom.set("foo", 42);
        atom.set<std::string>("bar", "baz");

        auto atom2 = atom.clone();
        CHECK(atom2->get<int>("foo") == 42);
        CHECK(atom2->get<std::string>("bar") == "baz");

    }

}