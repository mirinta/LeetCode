#include <iostream>

size_t sum0toN(size_t n)
{
    std::cout << n << ", before base" << '\n';
    if (n == 0) {
        std::cout << n << ", reach base" << '\n';
        return 0;
    }
    std::cout << n << ", before recursion" << '\n';
    const auto result = n + sum0toN(n - 1);
    std::cout << n << ", after recursion" << '\n';
    return result;
}

int main()
{
    std::cout << "---begin---" << '\n';
    sum0toN(5);
    std::cout << "---end---" << '\n';
}
