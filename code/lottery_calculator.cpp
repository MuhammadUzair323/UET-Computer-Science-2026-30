/*
    Lottery Probability Calculator
    CSC101 - Discrete Mathematics | Track 6: Counting & Combinatorics
    Muhammad Uzair | 2026(S)-CS-96 | UET Lahore

    Core concept: C(n, r) = n! / (r! * (n - r)!)
    Computes jackpot odds, partial match odds, tickets-to-guarantee, and
    expected value. Every calculation is shown step by step.

    Compile:  g++ -std=c++17 -o lottery lottery_calculator.cpp
    Run:      ./lottery
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// ─── Combination formula ──────────────────────────────────────────────────────
// Computed iteratively to avoid factorial overflow.
// C(n,r) = [n * (n-1) * ... * (n-r+1)] / r!
// We divide at each step to keep intermediate values small.
long long combination(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n - r) r = n - r;  // C(n,r) = C(n, n-r); pick smaller r

    long long result = 1;
    for (int i = 0; i < r; i++) {
        result = result * (n - i) / (i + 1);
    }
    return result;
}

// ─── Display helpers ──────────────────────────────────────────────────────────
void divider() {
    cout << "\n" << string(60, '-') << "\n";
}

void header(const string& title) {
    divider();
    cout << "  " << title << "\n";
    divider();
}

void pause() {
    cout << "\n  Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ─── Feature 1: Jackpot Probability ──────────────────────────────────────────
void jackpot_odds(int n, int r) {
    header("JACKPOT PROBABILITY");

    long long total = combination(n, r);

    cout << "\n  Formula:  P(jackpot) = 1 / C(n, r)\n";
    cout << "\n  Step 1  Compute C(" << n << ", " << r << "):\n";
    cout << "           C(" << n << ", " << r << ") = "
         << n << "! / (" << r << "! x " << (n - r) << "!) = " << total << "\n";
    cout << "\n  Step 2  Probability:\n";
    cout << "           P = 1 / " << total << "\n";
    cout << "\n  Result:  1 in " << total << "\n";
    cout << "           That is " << fixed << setprecision(10)
         << (1.0 / total) * 100.0 << " percent per ticket.\n";
}

// ─── Feature 2: Partial Match Probabilities ───────────────────────────────────
void partial_match_odds(int n, int r) {
    header("PARTIAL MATCH PROBABILITIES");

    long long total = combination(n, r);

    cout << "\n  Formula: P(match m) = C(" << r << ", m) x C("
         << (n - r) << ", " << r << " - m)  /  C(" << n << ", " << r << ")\n";
    cout << "\n  The first factor counts ways to pick m correct numbers.\n";
    cout << "  The second counts ways to fill remaining spots from non-winners.\n\n";

    cout << "  " << left << setw(14) << "Match"
              << setw(18) << "Combinations"
              << setw(20) << "Probability"
              << "Odds (1 in X)\n";
    cout << "  " << string(56, '-') << "\n";

    for (int m = 0; m <= r; m++) {
        long long ways = combination(r, m) * combination(n - r, r - m);
        double prob = (double)ways / total;
        string odds_str = (prob > 0)
            ? to_string((long long)round(1.0 / prob))
            : "impossible";

        cout << "  " << setw(14) << (to_string(m) + " of " + to_string(r))
             << setw(18) << ways
             << setw(20) << fixed << setprecision(8) << prob
             << odds_str << "\n";
    }
}

// ─── Feature 3: Tickets to Guarantee a Win ────────────────────────────────────
void tickets_to_guarantee(int n, int r) {
    header("TICKETS NEEDED TO GUARANTEE A WIN");

    long long total = combination(n, r);

    cout << "\n  To guarantee a jackpot win, every possible combination must\n";
    cout << "  be covered. The total number of combinations is C("
         << n << ", " << r << ").\n\n";
    cout << "  Step 1  C(" << n << ", " << r << ") = " << total << " tickets required.\n";

    double years_weekly = (total / 1.0) / 52.0;
    cout << "\n  Step 2  Buying 1 ticket per week:\n";
    cout << "           " << fixed << setprecision(0) << years_weekly
         << " years on average to cover all combinations.\n";

    double years_1000 = (total / 1000.0) / 365.0;
    cout << "\n  Step 3  Buying 1,000 tickets per day:\n";
    cout << "           " << fixed << setprecision(1) << years_1000
         << " years to cover all combinations.\n";

    cout << "\n  This is why guaranteeing a lottery win through brute force\n";
    cout << "  is not a meaningful strategy. The numbers are that extreme.\n";
}

// ─── Feature 4: Expected Value ────────────────────────────────────────────────
void expected_value(int n, int r) {
    header("EXPECTED VALUE OF ONE TICKET");

    long long total = combination(n, r);

    cout << "\n  Enter the jackpot prize amount: ";
    double prize;
    cin >> prize;
    cout << "  Enter the cost of one ticket:   ";
    double ticket_cost;
    cin >> ticket_cost;
    cin.ignore();

    double p_win = 1.0 / (double)total;
    double ev = prize * p_win - ticket_cost;

    cout << "\n  Formula: EV = (Prize x P_win)  -  Ticket_cost\n";
    cout << "\n  Step 1  P(win) = 1 / " << total << "\n";
    cout << "           = " << fixed << setprecision(10) << p_win << "\n";
    cout << "\n  Step 2  EV = (" << fixed << setprecision(2) << prize
         << " x " << setprecision(10) << p_win << ")  -  "
         << fixed << setprecision(2) << ticket_cost << "\n";
    cout << "           = " << fixed << setprecision(6) << prize * p_win
         << "  -  " << ticket_cost << "\n";
    cout << "           = " << ev << "\n\n";

    if (ev < 0) {
        cout << "  Result: Negative expected value (" << fixed
             << setprecision(4) << ev << ").\n";
        cout << "          On average you lose "
             << fixed << setprecision(4) << abs(ev)
             << " per ticket played.\n";
    } else {
        cout << "  Result: Positive expected value (" << ev << ").\n";
        cout << "          Statistically worthwhile given this prize size,\n";
        cout << "          though individual results are still random.\n";
    }
}

// ─── Feature 5: Step-by-step C(n, r) Breakdown ───────────────────────────────
void cnr_breakdown(int n, int r) {
    header("STEP-BY-STEP C(n, r) BREAKDOWN");

    int use_r = (r > n - r) ? n - r : r;

    cout << "\n  Computing C(" << n << ", " << r << ")  =  "
         << n << "! / (" << r << "! x " << (n - r) << "!)\n";
    cout << "\n  Because C(n, r) = C(n, n-r), we use r = " << use_r
         << " (whichever is smaller) to minimize steps.\n";
    cout << "\n  At each step: multiply by the next numerator term,\n";
    cout << "  divide by the next denominator term.\n\n";

    cout << "  Step  |  Numerator term  |  Denominator term  |  Running total\n";
    cout << "  " << string(58, '-') << "\n";

    long long result = 1;
    for (int i = 0; i < use_r; i++) {
        long long num_f = n - i;
        long long den_f = i + 1;
        result = result * num_f / den_f;
        cout << "  " << setw(5) << (i + 1)
             << " |  " << setw(14) << num_f
             << "  |  " << setw(16) << den_f
             << "  |  " << result << "\n";
    }

    cout << "\n  C(" << n << ", " << r << ")  =  " << result << "\n";
    cout << "  Jackpot odds  =  1 in " << result << "\n";
}

// ─── Feature 6: Compare Two Lotteries ────────────────────────────────────────
void compare_lotteries() {
    header("COMPARE TWO LOTTERY FORMATS");

    int n1, r1, n2, r2;
    cout << "\n  Lottery A total balls: "; cin >> n1;
    cout << "  Lottery A balls drawn: "; cin >> r1;
    cout << "  Lottery B total balls: "; cin >> n2;
    cout << "  Lottery B balls drawn: "; cin >> r2;
    cin.ignore();

    long long cA = combination(n1, r1);
    long long cB = combination(n2, r2);

    cout << "\n  Lottery A  C(" << n1 << ", " << r1 << ") = " << cA
         << "  ->  1 in " << cA << "\n";
    cout << "  Lottery B  C(" << n2 << ", " << r2 << ") = " << cB
         << "  ->  1 in " << cB << "\n\n";

    if (cA < cB) {
        cout << "  Lottery A is easier to win by a factor of "
             << fixed << setprecision(2) << (double)cB / cA << "x.\n";
    } else if (cB < cA) {
        cout << "  Lottery B is easier to win by a factor of "
             << fixed << setprecision(2) << (double)cA / cB << "x.\n";
    } else {
        cout << "  Both lotteries have identical jackpot odds.\n";
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────
int main() {
    cout << "\n  ====================================================\n";
    cout << "   Lottery Probability Calculator\n";
    cout << "   CSC101 Discrete Mathematics  |  Muhammad Uzair\n";
    cout << "   UET Lahore  |  2026(S)-CS-96\n";
    cout << "  ====================================================\n";

    int n, r;
    cout << "\n  Enter the total number of balls in the lottery: ";
    cin >> n;
    cout << "  Enter how many balls are drawn per ticket:      ";
    cin >> r;
    cin.ignore();

    if (r <= 0 || n <= 0 || r > n) {
        cout << "\n  Invalid configuration. r must satisfy 0 < r <= n.\n\n";
        return 1;
    }

    int choice = -1;
    while (choice != 0) {
        divider();
        cout << "\n  Configured: pick " << r << " from " << n << "\n\n";
        cout << "  1  Jackpot probability\n";
        cout << "  2  Partial match probabilities\n";
        cout << "  3  Tickets needed to guarantee a win\n";
        cout << "  4  Expected value of one ticket\n";
        cout << "  5  Step-by-step C(n,r) breakdown\n";
        cout << "  6  Compare with another lottery format\n";
        cout << "  0  Exit\n\n";
        cout << "  Choose: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: jackpot_odds(n, r);         pause(); break;
            case 2: partial_match_odds(n, r);   pause(); break;
            case 3: tickets_to_guarantee(n, r); pause(); break;
            case 4: expected_value(n, r);       pause(); break;
            case 5: cnr_breakdown(n, r);        pause(); break;
            case 6: compare_lotteries();        pause(); break;
            case 0: cout << "\n  Goodbye.\n\n";        break;
            default: cout << "\n  Enter a number between 0 and 6.\n"; break;
        }
    }

    return 0;
}
