#include <iostream>
#include <set>
#include <map>
#include <cassert>
#include <utility>

#include "fmt/format.h"

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
        friend bool operator<(const int id, const Object& o) noexcept {
            return id < o.id_;
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
