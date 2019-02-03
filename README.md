Pretty often I was facing the same pattern in the code. Over and over.
It looks like that:

```
struct User {
    std::string city;
    int userId;
};

std::unordered_map<string, std::vector<User>>
groupUsersByCity(const std::vector<User>& users) {
    std::unordered_map<string, std::vector<User>> result;
    for (const auto& user : users) {
        result[user.city].push_back(user);
    }
    return result;
}
```

So annoying.

I literally hate `unordered_map`s as a results of a function calls:
they are too generic. And I don't like the repeating code
in case when we would like to have users aggregated by country,
for example.

So, I have created this pretty small library. It allows you
to do something like that:

```
 1: int main() {
 2:     std::vector<User> users { {"Moscow", 1}, {"Sochi", 2} };
 3:     auto groups = GroupBy(&User::city, users);
 4:         for (const auto& it : groups) {
 5:             const auto& city = it.first;
 6:             const auto& users = it.second;
 7:             // ...
```

Moreover, with only one extra line it allows to avoid an extra
bolierplate at lines 5—6.

```
 1: DECLARE_NAMED_GROUP_BY_RESULT(UsersByCity, city, users);
 2: int main() {
 3:     std::vector<User> users { {"Moscow", 1}, {"Sochi", 2} };
 4:     UsersByCity<std::string, User> groups = GroupBy(&User::city, users);
 5:     for (const auto& group : groups) {
 6:         if (group.city == "Moscow") {
 7:             assert(group.users.size() == 1
 8:             // ...
```

Library supports extracting key by
 1. Data memeber reference
 2. Member function reference
 3. Free function / lambda

Feel free to contact me if you have an ideas how to improve it or
do know a good standard way to replace it!