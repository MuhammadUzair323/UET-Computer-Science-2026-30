/*
    Recursive Algorithm Tracer
    CSC101 - Discrete Mathematics | Track 3: Algorithm Design & Analysis
    Muhammad Uzair | 2026(S)-CS-96 | UET Lahore

    Demonstrates five classic recursive algorithms with step-by-step
    call-depth traces and result logging to a file.
    
*/

#include <iostream>
#include <fstream>
using namespace std;

// ─── Global log file ──────────────────────────────────────────────────────────
ofstream logFile;

// ─── Helpers ──────────────────────────────────────────────────────────────────
void printLine() {
    cout << "\n------------------------------------------------------------\n";
    logFile << "\n------------------------------------------------------------\n";
}

void printHeader(const char* title) {
    printLine();
    cout << "  " << title << "\n";
    logFile << "  " << title << "\n";
    printLine();
}

// Print 'depth' levels of indentation to show call nesting
void indent(int depth) {
    for (int i = 0; i < depth; i++) {
        cout << "  |  ";
        logFile << "  |  ";
    }
}

void pause() {
    cout << "\n  Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// ─── 1. Factorial ─────────────────────────────────────────────────────────────
// n! = n * (n-1)!,  base case 0! = 1
// Rosen Ch. 5.3 - Recursive Definitions

long long factorial(int n, int depth) {
    indent(depth);
    cout << "factorial(" << n << ") called\n";
    logFile << "factorial(" << n << ") called\n";

    if (n == 0) {
        indent(depth);
        cout << "base case -> return 1\n";
        logFile << "base case -> return 1\n";
        return 1;
    }

    long long result = (long long)n * factorial(n - 1, depth + 1);

    indent(depth);
    cout << "factorial(" << n << ") = " << n << " * factorial(" << n - 1 << ") = " << result << "\n";
    logFile << "factorial(" << n << ") = " << n << " * factorial(" << n - 1 << ") = " << result << "\n";
    return result;
}

void runFactorial() {
    printHeader("1. FACTORIAL  --  n! = n * (n-1)!");

    int n;
    cout << "  Enter n (0 to 12): ";
    cin >> n;
    cin.ignore();

    if (n < 0 || n > 12) {
        cout << "  Please enter a value between 0 and 12.\n";
        return;
    }

    cout << "\n  Recursive call trace:\n\n";
    logFile << "\n  Recursive call trace:\n\n";

    long long ans = factorial(n, 0);

    cout << "\n  Result: " << n << "! = " << ans << "\n";
    logFile << "\n  Result: " << n << "! = " << ans << "\n";

    cout << "\n  How it works (Rosen Ch. 5.3):\n";
    cout << "  Each call reduces n by 1 until n=0 (base case).\n";
    cout << "  The multiplications unwind as the calls return.\n";
}

// ─── 2. Fibonacci ────────────────────────────────────────────────────────────
// F(n) = F(n-1) + F(n-2),  F(0)=0, F(1)=1
// Rosen Ch. 5.3

long long fibonacci(int n, int depth) {
    indent(depth);
    cout << "fib(" << n << ") called\n";
    logFile << "fib(" << n << ") called\n";

    if (n == 0) {
        indent(depth);
        cout << "base case -> return 0\n";
        logFile << "base case -> return 0\n";
        return 0;
    }
    if (n == 1) {
        indent(depth);
        cout << "base case -> return 1\n";
        logFile << "base case -> return 1\n";
        return 1;
    }

    long long a = fibonacci(n - 1, depth + 1);
    long long b = fibonacci(n - 2, depth + 1);
    long long result = a + b;

    indent(depth);
    cout << "fib(" << n << ") = fib(" << n-1 << ") + fib(" << n-2 << ") = "
         << a << " + " << b << " = " << result << "\n";
    logFile << "fib(" << n << ") = fib(" << n-1 << ") + fib(" << n-2 << ") = "
            << a << " + " << b << " = " << result << "\n";
    return result;
}

void runFibonacci() {
    printHeader("2. FIBONACCI  --  F(n) = F(n-1) + F(n-2)");

    int n;
    cout << "  Enter n (0 to 8, larger values create many lines): ";
    cin >> n;
    cin.ignore();

    if (n < 0 || n > 8) {
        cout << "  Please enter a value between 0 and 8.\n";
        return;
    }

    cout << "\n  Recursive call trace:\n\n";
    logFile << "\n  Recursive call trace:\n\n";

    long long ans = fibonacci(n, 0);

    cout << "\n  Result: F(" << n << ") = " << ans << "\n";
    logFile << "\n  Result: F(" << n << ") = " << ans << "\n";

    cout << "\n  Note: each call spawns TWO sub-calls (two base cases).\n";
    cout << "  This is why Fibonacci grows and why it appears in nature.\n";
}

// ─── 3. GCD (Euclidean Algorithm) ────────────────────────────────────────────
// gcd(a, b) = gcd(b, a mod b),  base case gcd(a,0) = a
// Rosen Ch. 4.3

int gcd(int a, int b, int depth) {
    indent(depth);
    cout << "gcd(" << a << ", " << b << ") called\n";
    logFile << "gcd(" << a << ", " << b << ") called\n";

    if (b == 0) {
        indent(depth);
        cout << "base case -> return " << a << "\n";
        logFile << "base case -> return " << a << "\n";
        return a;
    }

    int result = gcd(b, a % b, depth + 1);

    indent(depth);
    cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", "
         << a % b << ") = " << result << "\n";
    logFile << "gcd(" << a << ", " << b << ") = gcd(" << b << ", "
            << a % b << ") = " << result << "\n";
    return result;
}

void runGCD() {
    printHeader("3. GCD (EUCLIDEAN ALGORITHM)  --  gcd(a,b) = gcd(b, a mod b)");

    int a, b;
    cout << "  Enter a: "; cin >> a;
    cout << "  Enter b: "; cin >> b;
    cin.ignore();

    if (a <= 0 || b <= 0) {
        cout << "  Please enter positive integers.\n";
        return;
    }

    cout << "\n  Recursive call trace:\n\n";
    logFile << "\n  Recursive call trace:\n\n";

    int ans = gcd(a, b, 0);

    cout << "\n  Result: gcd(" << a << ", " << b << ") = " << ans << "\n";
    logFile << "\n  Result: gcd(" << a << ", " << b << ") = " << ans << "\n";

    cout << "\n  At each step the remainder (a mod b) replaces a,\n";
    cout << "  and the divisor b becomes the new a. When b hits 0\n";
    cout << "  the remaining a is the GCD (Rosen Ch. 4.3).\n";
}

// ─── 4. Power ────────────────────────────────────────────────────────────────
// power(base, exp) = base * power(base, exp-1),  base case exp=0 -> 1
// Rosen Ch. 5.3

long long power(long long base, int exp, int depth) {
    indent(depth);
    cout << "power(" << base << ", " << exp << ") called\n";
    logFile << "power(" << base << ", " << exp << ") called\n";

    if (exp == 0) {
        indent(depth);
        cout << "base case -> return 1\n";
        logFile << "base case -> return 1\n";
        return 1;
    }

    long long result = base * power(base, exp - 1, depth + 1);

    indent(depth);
    cout << "power(" << base << ", " << exp << ") = "
         << base << " * power(" << base << ", " << exp - 1 << ") = " << result << "\n";
    logFile << "power(" << base << ", " << exp << ") = "
            << base << " * power(" << base << ", " << exp - 1 << ") = " << result << "\n";
    return result;
}

void runPower() {
    printHeader("4. POWER  --  base^exp = base * base^(exp-1)");

    long long base;
    int exp;
    cout << "  Enter base (integer): "; cin >> base;
    cout << "  Enter exponent (0 to 10): "; cin >> exp;
    cin.ignore();

    if (exp < 0 || exp > 10) {
        cout << "  Please enter an exponent between 0 and 10.\n";
        return;
    }

    cout << "\n  Recursive call trace:\n\n";
    logFile << "\n  Recursive call trace:\n\n";

    long long ans = power(base, exp, 0);

    cout << "\n  Result: " << base << "^" << exp << " = " << ans << "\n";
    logFile << "\n  Result: " << base << "^" << exp << " = " << ans << "\n";

    cout << "\n  Each step strips one exponent off and multiplies on the way back.\n";
}

// ─── 5. Tower of Hanoi ───────────────────────────────────────────────────────
// Move n discs from 'from' to 'to' using 'via'
// Requires exactly 2^n - 1 moves (Rosen Ch. 5.3)

int hanoiMoves;

void hanoi(int n, char from, char to, char via, int depth) {
    if (n == 0) return;

    hanoi(n - 1, from, via, to, depth + 1);

    hanoiMoves++;
    indent(depth);
    cout << "Move disc " << n << ":  " << from << "  ->  " << to << "\n";
    logFile << "Move disc " << n << ":  " << from << "  ->  " << to << "\n";

    hanoi(n - 1, via, to, from, depth + 1);
}

void runHanoi() {
    printHeader("5. TOWER OF HANOI  --  T(n) = 2*T(n-1) + 1");

    int n;
    cout << "  Enter number of discs (1 to 5): ";
    cin >> n;
    cin.ignore();

    if (n < 1 || n > 5) {
        cout << "  Please enter a value between 1 and 5.\n";
        return;
    }

    hanoiMoves = 0;
    long long expected = 1;
    for (int i = 0; i < n; i++) expected *= 2;
    expected -= 1;

    cout << "\n  Pegs: A (source)  B (helper)  C (destination)\n\n";
    logFile << "\n  Pegs: A (source)  B (helper)  C (destination)\n\n";

    hanoi(n, 'A', 'C', 'B', 0);

    cout << "\n  Total moves made   : " << hanoiMoves << "\n";
    cout << "  Formula 2^n - 1    : " << expected << "\n";
    logFile << "\n  Total moves made   : " << hanoiMoves << "\n";
    logFile << "  Formula 2^n - 1    : " << expected << "\n";

    cout << "\n  The recurrence T(n) = 2*T(n-1) + 1 gives 2^n - 1 total moves.\n";
    cout << "  For n=64 discs that is 18,446,744,073,709,551,615 moves.\n";
}

// ─── Main ─────────────────────────────────────────────────────────────────────
int main() {
    logFile.open("recursion_log.txt");

    cout << "\n  ====================================================\n";
    cout << "   Recursive Algorithm Tracer\n";
    cout << "   CSC101 Discrete Mathematics  |  Muhammad Uzair\n";
    cout << "   UET Lahore  |  2026(S)-CS-96\n";
    cout << "  ====================================================\n";
    cout << "  All output is also saved to recursion_log.txt\n";

    logFile << "  Recursive Algorithm Tracer\n";
    logFile << "  CSC101 Discrete Mathematics  |  Muhammad Uzair\n";
    logFile << "  UET Lahore  |  2026(S)-CS-96\n";

    int choice = -1;
    while (choice != 0) {
        printLine();
        cout << "\n  1  Factorial\n";
        cout << "  2  Fibonacci\n";
        cout << "  3  GCD (Euclidean Algorithm)\n";
        cout << "  4  Power\n";
        cout << "  5  Tower of Hanoi\n";
        cout << "  0  Exit\n\n";
        cout << "  Choose: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: runFactorial(); pause(); break;
            case 2: runFibonacci(); pause(); break;
            case 3: runGCD();       pause(); break;
            case 4: runPower();     pause(); break;
            case 5: runHanoi();     pause(); break;
            case 0: cout << "\n  Goodbye. Check recursion_log.txt for the full log.\n\n"; break;
            default: cout << "\n  Enter a number between 0 and 5.\n"; break;
        }
    }

    logFile.close();
    return 0;
}
