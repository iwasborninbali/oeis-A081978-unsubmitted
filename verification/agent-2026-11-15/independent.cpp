// Independent verification of OEIS A081978's 2j-divisor characterization.
// Method: linear sieve of tau(n), using two coprime factors of T_k;
// independently generate solutions by prime powers and test primality.
// C++17, no repository code or input data used.
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
using namespace std;

struct Stats {
    uint64_t eligible = 0;
    uint64_t form[3] = {0, 0, 0};
    map<uint32_t, uint64_t> by_j;
};

int main(int argc, char **argv) {
    uint32_t K = argc == 2 ? uint32_t(stoul(argv[1])) : 10000000u;
    if (K < 20000 || K > 30000000) throw runtime_error("K out of range");
    const uint32_t N = K + 1;
    vector<uint32_t> spf(N + 1, 0), primes;
    vector<uint16_t> tau(N + 1, 0);
    vector<uint8_t> exponent(N + 1, 0), generated(K + 1, 0);
    spf[1] = 1; tau[1] = 1;
    for (uint32_t n = 2; n <= N; ++n) {
        if (!spf[n]) { spf[n] = n; primes.push_back(n); }
        const uint32_t p = spf[n], m = n / p;
        if (m % p == 0) {
            exponent[n] = uint8_t(exponent[m] + 1);
            tau[n] = uint16_t(uint32_t(tau[m]) / (exponent[m] + 1) * (exponent[n] + 1));
        } else {
            exponent[n] = 1;
            tau[n] = uint16_t(2 * uint32_t(tau[m]));
        }
        for (uint32_t s : primes) {
            if (s > spf[n] || uint64_t(n) * s > N) break;
            spf[n * s] = s;
        }
    }
    auto isprime = [&](uint64_t n) -> bool {
        return n >= 2 && n <= N && spf[size_t(n)] == n;
    };
    auto mark = [&](uint64_t k, uint32_t p, uint64_t q, int form) {
        if (k < 1 || k > K || !isprime(q) || q == p) return;
        uint8_t bit = uint8_t(1u << form);
        if (generated[size_t(k)] & bit) {
            cerr << "duplicate generated witness at k=" << k << "\n";
            exit(2);
        }
        generated[size_t(k)] |= bit;
    };
    uint64_t generated_count = 0;
    // Generate all feasible prime powers x=p^r with even r>=2 and prime r+1.
    // Each corrected expression uniquely determines the triangular index:
    // q=2x-1 => k=2x-1; q=2x+1 => k=2x; q=(x+1)/2 => k=x.
    for (uint32_t p : primes) {
        if (uint64_t(p) * p > K) break;
        uint64_t x = uint64_t(p) * p;
        for (uint32_t r = 2; x <= K; r += 2) {
            if (isprime(r + 1)) {
                mark(2 * x - 1, p, 2 * x - 1, 0);
                mark(2 * x, p, 2 * x + 1, 1);
                if ((x & 1u) != 0u) mark(x, p, (x + 1) / 2, 2);
            }
            if (x > K / uint64_t(p) / p) break;
            x *= uint64_t(p) * p;
        }
    }
    Stats small, all;
    uint64_t false_positives = 0, false_negatives = 0, overlaps = 0;
    // tau(T_k) = tau(k/2)tau(k+1) when k even, otherwise
    // tau(k)tau((k+1)/2). This scan never factors T_k itself.
    for (uint32_t k = 1; k <= K; ++k) {
        uint32_t a = (k % 2 == 0 ? k / 2 : k);
        uint32_t b = (k % 2 == 0 ? k + 1 : (k + 1) / 2);
        uint32_t d = uint32_t(tau[a]) * tau[b];
        bool eligible = d % 2 == 0 && d / 2 >= 3 && isprime(d / 2);
        uint8_t mask = generated[k];
        if (mask && (mask & (mask - 1))) ++overlaps;
        if (eligible != (mask != 0)) {
            if (eligible) ++false_negatives;
            else ++false_positives;
            if (false_positives + false_negatives <= 8)
                cerr << "MISMATCH k=" << k << " tau=" << d << " mask=" << int(mask) << "\n";
        }
        if (!eligible) continue;
        auto record = [&](Stats &s) {
            ++s.eligible;
            ++s.by_j[d / 2];
            for (int i = 0; i < 3; ++i) if (mask & (1u << i)) ++s.form[i];
        };
        record(all);
        if (k <= 20000) record(small);
    }
    for (uint32_t k = 1; k <= K; ++k) if (generated[k]) ++generated_count;
    cout << "method: linear sieve of tau(n) plus independent prime-power witness generator\n";
    cout << "range: 1 <= k <= " << K << "\n";
    cout << "baseline k<=20000: cases=" << small.eligible << " f1=" << small.form[0]
         << " f2=" << small.form[1] << " f3=" << small.form[2] << "\n";
    cout << "all: cases=" << all.eligible << " f1=" << all.form[0]
         << " f2=" << all.form[1] << " f3=" << all.form[2] << "\n";
    cout << "generated eligible indices=" << generated_count << "\n";
    cout << "false positives=" << false_positives << " false negatives=" << false_negatives
         << " overlapping forms=" << overlaps << "\n";
    cout << "by j (tau(T_k)=2j):";
    for (auto [j, c] : all.by_j) cout << " " << j << ":" << c;
    cout << "\n";
    // Direct modular check for the excluded old expression in the OEIS example.
    uint32_t residue = 1;
    for (int t = 0; t < 256; ++t) residue = (residue * 331u) % 8u;
    cout << "331^256 mod 8=" << residue
         << "; (331^256-1)/2 mod 4=" << (residue - 1u) / 2u << "\n";
    cout << "status=" << ((false_positives || false_negatives || overlaps ||
                            small.eligible != 34 || small.form[0] != 15 ||
                            small.form[1] != 3 || small.form[2] != 16) ? "FAIL" : "PASS") << "\n";
    return (false_positives || false_negatives || overlaps || small.eligible != 34 ||
            small.form[0] != 15 || small.form[1] != 3 || small.form[2] != 16) ? 1 : 0;
}
