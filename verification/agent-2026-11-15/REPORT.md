# Independent verification — 2026-11-15

Source reviewed: supplied archive of `iwasborninbali/oeis-A081978-unsubmitted`, commit `6cfe2bb1f18c71fdc8958382b3f75a00ee241b1e`. Independent of the authors and certificate writers. The archive contains no `programs/` directory; I reviewed all files in `verification/` instead.

## Claim

**Exact claim of `CERTIFICATE.md`:** For odd prime `j` and `r=j−1`, the third allowable form in A081978's characterization is `q=(p^r+1)/2` (not `q=(p^r−1)/2`).

The claim is a conditional characterization of triangular numbers with exactly `2j` positive divisors, not an existence result, a proof of minimality for an individual `a(2j)`, or a primality certificate for the OEIS `n=514` example.

## Proof check

**Referee verdict: correct. No invalid, unjustified, conjecture-dependent, or fatal steps.** Full line-by-line audit of `proof.md` (nonblank content at lines 1, 3, and 5):

- **Line 1 (title):** no mathematical assertion.
- **Line 3, divisor-count classification:** `tau(T_k)=2j` with odd prime `j` forces either `T_k=P^(2j−1)` or `T_k=p^(j−1) q` with distinct primes `p,q`: because the only multiplicative partitions of `2j` into factors `>=2` are `[2j]` and `[2,j]`. Correct.
- **Line 3, exclusion of one-prime case:** for `k=2m>=4`, `T_k=m(2m+1)`, and for `k=2m−1>=3`, `T_k=m(2m−1)`. Both factors are greater than 1 and coprime. Thus `T_k` cannot be a prime power. `T_1=1` and `T_2=3` have 1 and 2 divisors. Correct.
- **Line 3, conclusion:** the sole remaining prime-exponent pattern is `p^r q`, `r=j−1` (even and at least 2). Correct.
- **Line 5, parity factorizations and four assignments:** correct. With `x=p^r`, the assignments explicitly give:

  | Parity | Assignment | Result | Corresponding index |
  |---|---|---|---|
  | even, `k=2m` | `m=x` | `q=2x+1` | `k=2x` |
  | even, `k=2m` | `2m+1=x` | `q=(x−1)/2` | `k=x−1` |
  | odd, `k=2m−1` | `m=x` | `q=2x−1` | `k=2x−1` |
  | odd, `k=2m−1` | `2m−1=x` | `q=(x+1)/2` | `k=x` |

- **Line 5, excluded minus-half form:** if `p=2`, `x` is even and `(x−1)/2` is not integral. Otherwise `p` is odd and `r` is even, so `x=p^r ≡1 (mod 8)` and `(x−1)/2 ≡0 (mod 4)`; this integer is at least 4 and hence not prime. Correct, with no conjecture.
- **Line 5, sufficiency/converse:** if `p,q` are distinct primes and one of the remaining three integer expressions for `q` holds, the displayed index constructs `T_k=p^r q`; therefore `tau(T_k)=(r+1)*2=2j`. The half-form automatically requires `p` odd. Correct.
- **Line 5, scope:** the derivation does not assert any such prime `q` exists for every `j`. No reliance on the existence conjecture or on `n=514` primality. Correct.

The only **optional expository expansions**, not proof gaps, are to spell out the multiplicative partitions of `2j`, why odd squares are 1 modulo 8, and the four constructive `k` values shown above. All are elementary, fixable by adding a sentence, and **none is fatal**. There are **zero substantive gaps**.

## Independent computation

New program: [`independent.cpp`](independent.cpp), written from scratch in C++17 without importing or translating repository code. It uses a **linear least-prime-factor sieve** and the multiplicative divisor count of the *two coprime factors* `k/2,k+1` (even `k`) or `k,(k+1)/2` (odd `k`), rather than trial-factoring `T_k` as the repository checker does. Separately, it *generates* every feasible prime-power witness `p^r` (`r+1` odd prime), tests the primality of the three `q` expressions, reconstructs `k`, and compares generated and sieve-detected indices exhaustively. These are independent directions of the finite test.

Reproduce: `g++ -std=c++17 -O3 -Wall -Wextra -pedantic independent.cpp -o independent && /usr/bin/time -f 'wall_seconds=%e user_cpu_seconds=%U system_cpu_seconds=%S peak_kb=%M' ./independent 30000000`. Compiler used: `g++ (Debian 14.2.0-19) 14.2.0`. Recorded stdout and `/usr/bin/time` are in [`computation.log`](computation.log).

- **Range:** all `1 <= k <= 30,000,000` (1,500 times the archive's `k<=20,000` check).
- **Result:** 270 indices with `tau(T_k)=2j`, `j` an odd prime, all exactly accounted for by the corrected forms: `q=2p^r−1` **137**; `q=2p^r+1` **3**; `q=(p^r+1)/2` **130**. Independently generated indices: **270**. **0** false positives, **0** false negatives, **0** overlaps.
- **Counts by `j`:** `3:247`, `5:16`, `7:3`, `13:2`, `17:1`, `19:1`.
- **Archive baseline reproduced:** through `k=20,000`, **34** indices: **15, 3, 16** in the respective forms.
- **Direct modular check of cited old `p=331, r=256` example:** `331^256 ≡ 1 (mod 8)`, so `(331^256−1)/2 ≡ 0 (mod 4)` is composite; **no primality claim** for `(331^256+1)/2` was made or tested.
- **Resource usage:** 0.68 seconds wall, 0.32 seconds user CPU, 0.35 seconds system CPU, 244,192 KiB maximum resident (from `/usr/bin/time`).
- **SHA-256, program (`independent.cpp`):** `0c9e8754e28946ddfcb5a8a8a34a12445b94bda1a86f85ca666d049922575fc0`.
- **SHA-256, output (`computation.log`):** `b95d5b32238aad9e734a9db6600fb2db00d72d3bd932a250d1f527135b47544f`.

The computational check is finite and is *not* substituted for the general proof.

## Prior art

Web searches and entry inspections performed 2026-11-15. The crucial **pre-existing published OEIS mathematics already contains the plus sign**:

1. [OEIS A081978](https://oeis.org/A081978), Schoenfield's comment dated **2014-05-25**, still prints `f3(p^r)=(p^r−1)/2` and cites `n=514,p=331`. Its same-entry coprime factor argument supports the corrected plus sign. The live main entry still had the erroneous minus sign at inspection; no changed `a(n)` value is claimed here. [Internal format](https://oeis.org/A081978/internal).
2. [OEIS A340865](https://oeis.org/A340865), **Jon E. Schoenfield, 2021-01-24**, explicitly derives all four prime-power assignments for **six divisors** (`j=3, r=2`). Its Case 1 gives `q=(p^2+1)/2`, and its Case 4 rules out the minus-half version by divisibility by 4. **Direct prior art for the same correction mechanism**, though for one exponent.
3. [OEIS A349699](https://oeis.org/A349699), **Jon E. Schoenfield, 2021-11-25**, explicitly states that triangular numbers with **ten divisors** (`j=5, r=4`) include `q=(p^4+1)/2`, e.g. `3321=3^4*41`. **Direct prior art for another exponent**.
4. [OEIS A292989](https://oeis.org/A292989), **Schoenfield, 2017-12-08**, classifies six-divisor triangular numbers; its `45=3^2*5` and `325=5^2*13` encode the plus-half branch indirectly. [OEIS A398195](https://oeis.org/A398195), **2026-07-23**, also writes `p*(p^2+1)/2` explicitly. Related prime source: [A048161](https://oeis.org/A048161).
5. [Mathematics Stack Exchange, *How many triangular numbers have exactly d divisors?*](https://math.stackexchange.com/questions/3103932/how-many-triangular-numbers-have-exactly-d-divisors), **2019-02-07**, states the coprime factor reasoning and analyzes the six-divisor case, without making the universal `j` sign correction explicit.
6. Direct cross-references inspected: [A081979](https://oeis.org/A081979), [A242585](https://oeis.org/A242585), [A319037](https://oeis.org/A319037), and the references appearing in A081978 to [A000129](https://oeis.org/A000129), [A001110](https://oeis.org/A001110), [A001653](https://oeis.org/A001653), and [A002315](https://oeis.org/A002315). The latter concern Pell/square-triangular structure or related divisor sequences, not an independent general proof of this sign correction.
7. Searched arXiv, MathOverflow, Math StackExchange, zbMATH and journal-indexed pages for `A081978`, `f3(p^r)`, `triangular numbers exactly 2p divisors`, and `triangular numbers divisors prime power`; **no further independently identified exact general sign-correction paper or post** was found in those searches. This is not an exhaustive negative bibliographic result. The OEIS [history endpoint](https://oeis.org/history?seq=A081978) was attempted, but returned **HTTP 403** to the search client, so complete edit-history priority could **not** be audited.

**Novelty finding:** The plus-half formula and the argument excluding the minus-half formula are **not new mathematics**: A340865 and A349699 publish explicit special cases in 2021, by the same original contributor. A first public identification of the **specific inconsistent line in A081978**, or a prior all-odd-prime formulation, is **not established** by the accessible sources. A correction submission remains useful, but must not be advertised as a new theorem or as securely first.

## Verdict

**COMPLETE for the certificate's precise mathematical claim:** proof **correct**, each step independently refereed, and all finite checks independently reproduced and substantially extended; no counterexample. The proposed `+` is right and the printed `−` cannot give a prime. **NOT NEW as a mathematical formula**, in view of the explicit 2021 prior art. Historical priority of the specific A081978 typo discovery is **not established** (OEIS history inaccessible).

**Outside scope / still unchecked:** `a(2j)>0` for all odd prime `j`, primality and minimality of the OEIS `n=514, p=331` example, other OEIS commentary, and the omitted external `programs/` or source program referenced in the certificate. These do **not** undermine the certified conditional identity. No existing repository files were altered by this review.
