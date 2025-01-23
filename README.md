<h1 align="center"><a href="https://github.com/nlohmann/json">nlohmann/json</a> 🔗 <a href="https://github.com/getml/reflect-cpp">reflect-cpp</a></h1>

<h4 align="center">nlohmann/json backend for reflect-cpp</h4>

## __*CMake Import*__

```cmake
# add nlohmann/json and reflect-cpp libraries!

add_subdirectory(nlohmann-reflect-cpp)
target_link_libraries(your_target nlohmann-reflectcpp)
```

## __*Usage*__

If you've used reflect-cpp json api, you'd feel comfortable with this api:

```cpp
#include <rfl/nlohmann.hpp>

struct Person {
  std::string first_name;
  std::string last_name;
  int age;
};

const Person homer{
  first_name = "Homer",
  .last_name = "Simpson",
  .age = 45
};

// We can now write into and read from a JSON string.
const std::string json_string{ rfl::nlohmann::write(homer) };
auto homer2{ rfl::nlohmann::read<Person>(json_string).value() };
```
