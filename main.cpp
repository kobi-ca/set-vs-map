#include <iostream>
#include <set>
#include <map>

#include "fmt/format.h"

namespace {
    struct Object final {
        int id_;
        std::string name_;
    };
}

void add_new(std::map<int, Object>& m, Object obj) {
    m.insert(std::make_pair(obj.id_, std::move(obj)));
}

void add_new(std::map<int, Object>& m, const int id, const std::string& name) {
    m.insert(std::make_pair(id, Object{id, name}));
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

    return 0;
}
