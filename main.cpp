#include <iostream>
#include <set>
#include <map>
#include <cassert>
#include <utility>

#include "fmt/format.h"

/**
 * This exercise came from a code review where the author used map<int, object>
 * while the int came from the object itself. The question is can we use BST
 * and reduce the memory footprints by using set and add op< to allow comparison of objects?
 * This requires op< and few more things.
 *
 * An example that shows 2 options to use BST from the Standard library.
 * one option is std::map with id/object and the other one is std::set
 * The map has the overhead of storing a pair to get access to the object via id
 * the set does not have this overhead and in both cases we want to have a semantic
 * to allow us to get the object via an id as the key.
 * Also this is the case where the id is part of the object and we take advantage of
 * it using operator< definition in Object.
 *
 * Initially, we did not need any ctor for map or set.
 * But once we had std::set::find(int) like in the example below, we need a conversion operator.
 *
 * No need to use std::less<> in set. this is already done by default.
 *
 * std::less is a template struct with operator() that calls op< if such exists
 * for the type T - Object in our case.
 * Or, you can just have your own function/functor that will mimic std::less.
 *
 * Once we needed the std::set::find(int), we needed a conversion constructor which
 * makes this object and non-aggregate anymore. and we needed to bring in =default of empty ctor
 * because of sizeof of std::pair (FIXME this should change)
 * and also we brought in the id/string constructor
 */

namespace {
    struct Object final {
        Object() = default;
        Object(const int id) : id_(id) {}
        Object(const int id, std::string n) : id_(id), name_(std::move(n)) {}
        int id_{};
        std::string name_;
        bool operator<(const Object& o) const noexcept {
            return id_ < o.id_;
        }
    };
}

void add_new(std::map<int, Object>& m, Object obj) {
    m.insert(std::make_pair(obj.id_, std::move(obj)));
}

void add_new(std::map<int, Object>& m, const int id, const std::string& name) {
    m.insert(std::make_pair(id, Object{id, name}));
}

void add_new(std::set<Object>& s, Object obj) {
    s.insert(std::move(obj));
}

void add_new(std::set<Object>& s, const int id, const std::string& name) {
    s.insert(Object{id, name});
}

int main() {
    using namespace std::string_literals;
    std::map<int, Object> mymap;
    add_new(mymap, Object{1, "1"s});
    add_new(mymap, 5, "5"s);
    add_new(mymap, 3, "3"s);
    add_new(mymap, -7, "-7"s);
    add_new(mymap, Object{4, "4"s});

    fmt::print("map: \n");
    for(const auto& [id, obj] : mymap) {
        fmt::print("id: {} obj id {} name {}\n", id, obj.id_, obj.name_);
    }

    fmt::print("sizeof pair {}, object {}, string {}\n",
               sizeof(std::make_pair(1, Object{})), sizeof(Object), sizeof(std::string));

    const auto& n = mymap[5].name_;
    fmt::print("get 5's name {}\n", n);
    assert(n == "5"s);

    // set
    std::set<Object> myset;
    add_new(myset, Object{1, "1"s});
    add_new(myset, 5, "5"s);
    add_new(myset, 3, "3"s);
    add_new(myset, -7, "-7"s);
    add_new(myset, Object{4, "4"s});

    fmt::print("set: \n");
    for(const auto& obj : myset) {
        fmt::print("obj id {} name {}\n", obj.id_, obj.name_);
    }

    const auto& nset = myset.find(5)->name_;
    fmt::print("get 5's name {}\n", nset);
    assert(nset == "5"s);

    return 0;
}
