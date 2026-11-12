# Verification certificate

## Claim

For odd prime j and r=j−1, the third allowable form in A081978's characterization is q=(p^r+1)/2.

## Evidence

| What | Path | Author and date | Coverage | Result |
|---|---|---|---|---|
| Derivation | [proof.md](proof.md) | OpenAI Codex, 2026-11-13, using the reviewed source argument | All odd prime j | Three forms derived |
| Independent finite check | [verification/check.py](verification/check.py) | OpenAI Codex, 2026-11-13 | k=1..20000 | 34 cases satisfy corrected forms |

The finite checker shares no code or input data with the source program. It uses the same mathematical definition and tests only a finite range.

## Replayed for this repository

2026-11-13, macOS local workstation: `python3 verification/check.py`; output is in [verification/logs/check.txt](verification/logs/check.txt) and reproduced in README.

## Not covered

The conjecture that a(2j)>0 for every j>1, primality of the n=514 candidate, and other assertions in the OEIS entry were not checked. The finite test is not a proof of the universal claim; the derivation is supplied for inspection.

## Guide's independent check

pending

## Verdict

complete — the independent finite check was replayed in full for its stated range; the general derivation remains subject to mathematical review.
