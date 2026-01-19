#include <iostream>

void test_grid_basic();
void test_moves_basic();

int main() {
    std::cout << "tests_runner\n";
    test_grid_basic();
    test_moves_basic();
    std::cout << "All tests executed\n";
    return 0;
}
