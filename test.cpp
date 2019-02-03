#include <string>
#include <vector>
#include <stdexcept>

#include "groupby.hpp"


struct User {
    std::string city;
    int userId;

    int getRegionId() const {
        if (city == "Moscow") { return 77; }
        if (city == "Sochi") { return 23; }
        return -1;
    }
};


void test1() {
    std::vector<User> users { {"Moscow", 1}, {"Sochi", 2} };
    auto groped = GroupBy(&User::city, users);
    bool hasMoscow = false;
    bool hasSochi = false;
    for (const auto& it : groped) {
        if (it.first == "Moscow") {
            hasMoscow = true;
            if (it.second.size() != 1) {
                throw std::logic_error("Amount of Moscow users is not 1");
            }
            if (it.second[0].userId != 1) {
                throw std::logic_error("UserID for Moscow users is not 1");
            }
        }
        if (it.first == "Sochi") {
            hasSochi = true;
            if (it.second.size() != 1) {
                throw std::logic_error("Amount of Sochi users is not 1");
            }
            if (it.second[0].userId != 2) {
                throw std::logic_error("UserID for Sochi users is not 2");
            }
        }
    }
    if (!hasMoscow || !hasSochi) {
        throw std::logic_error("Expected to find both cities in the groupBy result");
    }
}

void test2() {
    std::vector<User> users { {"Moscow", 1}, {"Sochi", 2} };
    auto groped = GroupBy(&User::getRegionId, users);
    bool hasMoscow = false;
    bool hasSochi = false;
    for (const auto& it : groped) {
        if (it.first == 77) {
            hasMoscow = true;
            if (it.second.size() != 1) {
                throw std::logic_error("Amount of Moscow users is not 1");
            }
            if (it.second[0].userId != 1) {
                throw std::logic_error("UserID for Moscow users is not 1");
            }
        }
        if (it.first == 23) {
            hasSochi = true;
            if (it.second.size() != 1) {
                throw std::logic_error("Amount of Sochi users is not 1");
            }
            if (it.second[0].userId != 2) {
                throw std::logic_error("UserID for Sochi users is not 2");
            }
        }
    }
    if (!hasMoscow || !hasSochi) {
        throw std::logic_error("Expected to find both cities in the groupBy result");
    }
}

DECLARE_NAMED_GROUP_BY_RESULT(UsersByCity, city, users);
void test3() {
    std::vector<User> users { {"Moscow", 1}, {"Sochi", 2} };
    UsersByCity<std::string, User> groped = GroupBy(&User::city, users);
    bool hasMoscow = false;
    bool hasSochi = false;
    for (const auto& it : groped) {
        if (it.city == "Moscow") {
            hasMoscow = true;
            if (it.users.size() != 1) {
                throw std::logic_error("Amount of Moscow users is not 1");
            }
            if (it.users[0].userId != 1) {
                throw std::logic_error("UserID for Moscow users is not 1");
            }
        }
        if (it.city == "Sochi") {
            hasSochi = true;
            if (it.users.size() != 1) {
                throw std::logic_error("Amount of Sochi users is not 1");
            }
            if (it.users[0].userId != 2) {
                throw std::logic_error("UserID for Sochi users is not 2");
            }
        }
    }
    if (!hasMoscow || !hasSochi) {
        throw std::logic_error("Expected to find both cities in the groupBy result");
    }
}

int main() {
    test1();
    test2();
    test3();
}