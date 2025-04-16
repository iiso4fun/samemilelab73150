#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <iostream>
#include <chrono>
#include <utility>
#include <string>
#include "bigint.h"

using BigFrac = std::pair<bigint, bigint>;

BigFrac addBigFracs(const BigFrac& x, const BigFrac& y) {
    bigint a = x.first, b = x.second, c = y.first, d = y.second;
    bigint top = a * d + b * c;
    bigint bottom = b * d;
    return {top, bottom};
}

BigFrac multBigFracs(const BigFrac& x, const BigFrac& y) {
    bigint a = x.first, b = x.second, c = y.first, d = y.second;
    bigint top = a * c;
    bigint bottom = b * d;
    return {top, bottom};
}

struct Times {
    long long bigIntTime;
    long long intTime;
    long long longTime;
};

Times runBenchmarks() {
    using namespace std::chrono;
    Times result;
    const int count = 100000;

    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        bigint x("123456789012345678901234567890");
        bigint y("987654321098765432109876543210");
        volatile bigint z = x * y;
    }
    auto t2 = high_resolution_clock::now();
    result.bigIntTime = duration_cast<microseconds>(t2 - t1).count();

    t1 = high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        int x = 12345, y = 67890;
        volatile int z = x * y;
    }
    t2 = high_resolution_clock::now();
    result.intTime = duration_cast<microseconds>(t2 - t1).count();

#ifdef _WIN32
    long int a = 12345, b = 67890;
#else
    long int a = 1234567890123L, b = 9876543210123L;
#endif

    t1 = high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        volatile long int z = a * b;
    }
    t2 = high_resolution_clock::now();
    result.longTime = duration_cast<microseconds>(t2 - t1).count();

    return result;
}

TEST_CASE("Addition Check") {
    BigFrac f1 = {bigint("1"), bigint("2")};
    BigFrac f2 = {bigint("1"), bigint("3")};
    BigFrac expected = {bigint("5"), bigint("6")};
    BigFrac actual = addBigFracs(f1, f2);
    CHECK(actual.first == expected.first);
    CHECK(actual.second == expected.second);
}

TEST_CASE("Multiplication Check") {
    BigFrac f1 = {bigint("1"), bigint("2")};
    BigFrac f2 = {bigint("1"), bigint("3")};
    BigFrac expected = {bigint("1"), bigint("6")};
    BigFrac actual = multBigFracs(f1, f2);
    CHECK(actual.first == expected.first);
    CHECK(actual.second == expected.second);
}

int main(int argc, char** argv) {
    doctest::Context ctx;
    ctx.applyCommandLine(argc, argv);
    int result = ctx.run();
    if (ctx.shouldExit()) return result;

    Times timing = runBenchmarks();

    std::cout << "\n----------------------------------------------\n";
    std::cout << "       Benchmark Results (100000 iterations)    \n";
    std::cout << "----------------------------------------------\n";
    std::cout << "BigInt multiplication time: " << timing.bigIntTime << " μs "
              << "(" << timing.bigIntTime / 1000.0 << " ms)" << "\n";
    std::cout << "   Int multiplication time: " << timing.intTime << " μs "
              << "(" << timing.intTime / 1000.0 << " ms)" << "\n";
    std::cout << "Long Int multiplication time: " << timing.longTime << " μs "
              << "(" << timing.longTime / 1000.0 << " ms)" << "\n";
    std::cout << "----------------------------------------------\n";

    int a = 100000, b = 100000;
    int regularResult = a * b;
    std::cout << "\n--- Example: Integer Overflow with Built-in int ---\n";
    std::cout << "Using built-in int:\n";
    std::cout << "  " << a << " * " << b << " = " << regularResult << "\n";

    bigint ba("100000"), bb("100000"), bigResult = ba * bb;
    std::cout << "Using bigint for correct computation:\n";
    std::cout << "  " << ba << " * " << bb << " = " << bigResult << "\n";
    std::cout << "Note: built-in int overflows whereas bigint handles the large result correctly.\n";

    std::cout << "\nInteractive Fraction Operations\n";
    std::cout << "Enter two fractions.\nFor each fraction, input numerator and denominator (as strings).\n";

    std::string n1, d1, n2, d2;
    std::cout << "\nFraction 1 numerator: ";
    std::cin >> n1;
    std::cout << "Fraction 1 denominator: ";
    std::cin >> d1;
    std::cout << "Fraction 2 numerator: ";
    std::cin >> n2;
    std::cout << "Fraction 2 denominator: ";
    std::cin >> d2;

    BigFrac input1 = {bigint(n1), bigint(d1)};
    BigFrac input2 = {bigint(n2), bigint(d2)};

    BigFrac added = addBigFracs(input1, input2);
    BigFrac multiplied = multBigFracs(input1, input2);

    std::cout << "\n---------- Calculation Results ----------\n";
    std::cout << "Sum: " << added.first << " / " << added.second << "\n";
    std::cout << "Product: " << multiplied.first << " / " << multiplied.second << "\n";
    std::cout << "-------------------------------------------\n";

    return result;
}
