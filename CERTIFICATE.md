# Verification certificate

## Claim

For odd prime j and r=j−1, the third allowable form in A081978's characterization is q=(p^r+1)/2.

## Evidence

| What | Path | Author and date | Coverage | Result |
|---|---|---|---|---|
| Derivation | [proof.md](proof.md) | OpenAI Codex, 2026-11-13, using the reviewed source argument | All odd prime j | Three forms derived |
| Independent finite check | [verification/check.py](verification/check.py) | OpenAI Codex, 2026-11-13 | k=1..20000 | 34 cases satisfy corrected forms |
| Independent referee and check | `verification/agent-2026-11-15/` (REPORT.md, independent.cpp) | ChatGPT agent, 2026-11-15; own C++, no repository code | Divisor counts of triangular numbers with 2j divisors for odd primes j; the excluded minus-half branch (331^256 case); derivation read line by line | Passed; derivation correct |

The finite checker shares no code or input data with the source program. It uses the same mathematical definition and tests only a finite range.

## Replayed for this repository

2026-11-13, macOS local workstation: `python3 verification/check.py`; output is in [verification/logs/check.txt](verification/logs/check.txt) and reproduced in README.

2026-11-15, Darwin arm64 (Apple clang `-O3`), by the guide: `./independent` in `verification/agent-2026-11-15/`
reports `status=PASS` (counts by j: 3:161, 5:13, 7:3, 13:2, 17:1, 19:1).

## Not covered

The conjecture that a(2j)>0 for every j>1, primality of the n=514 candidate, and other assertions in the OEIS entry were not checked. The finite test is not a proof of the universal claim; the derivation is supplied for inspection.

## Guide's independent check

15 November 2026: the guide read `proof.md` and checked the four assignments by hand: T(2m-1) = m(2m-1) gives
q = 2p^r - 1 or q = (p^r + 1)/2; T(2m) = m(2m+1) gives q = 2p^r + 1 or q = (p^r - 1)/2, and the last is impossible
because p^r = 1 (mod 8) for odd p and even r = j - 1, so (p^r - 1)/2 is divisible by 4. Verdict: correct; the third
form is (p^r + 1)/2.

## Verdict

complete — the corrected third form is derived (read independently by the guide and by a separate referee) and
checked by programs that share no code. It is a sign correction of an existing comment, not new mathematics.
