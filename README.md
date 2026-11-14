# OEIS A081978: correction of the third form (not yet submitted)

<!-- oeis-status:begin -->
**OEIS status: not submitted** (lab registry, 15 Nov 2026).

- [A081978](https://oeis.org/A081978), third form should be (p^r+1)/2: **candidate** (2026-11-13: repository built (core c6)). Certificate: complete.

Rules and the full registry: [athanor-oeis](https://github.com/iwasborninbali/athanor-oeis/blob/main/REGISTRY.md).
<!-- oeis-status:end -->

## Definition

For n≥1, a(n) is the least triangular number T_k=k(k+1)/2, k≥1, with exactly n positive divisors, or 0 if none exists. The offset is 1.

## Terms / result

The change concerns the characterization for n=2j, j an odd prime: its third form should be q=(p^r+1)/2, where r=j−1, instead of q=(p^r−1)/2. No term is changed.

The live [A081978](https://oeis.org/A081978), read 2026-11-13, attributes the block to Jon E. Schoenfield, May 25 2014, and contains the exact line `q = f3(p^r) = (p^r - 1)/2` and the example `at n=514, q = f3(p^r), with p=331.`

## How it was obtained

The two coprime factors in each of the two standard triangular-number factorizations yield four possible relationships. One is impossible and the remaining half-expression has a plus sign. See [proof.md](proof.md).

## Verification

An independently written trial-factorization program checked all triangular indices through 20000 against the three corrected forms; 34 relevant cases were found. The proof covers the general characterization; this finite check does not prove the existence conjecture or certify the primality of the n=514 example. See [CERTIFICATE.md](CERTIFICATE.md).

## Prior art and credit

The correction was identified in the lab's ChatGPT answer and checked by Claude Code; the original characterization is due to Schoenfield. See [PRIOR-ART.md](PRIOR-ART.md).

## Reproduce

Run `python3 verification/check.py` (under one second on the recorded machine). Expected output:

```text
triangular indices checked: 20000
counts by corrected forms: 15 3 16
old minus form at p=331, r=256 is divisible by 4: True
```

## Provenance

Source: `projects/science/athanor-oeis`, commit `11b7ea9cc6f4c0057731d8e36c023f8b36e7c27f`, `tasks/2026-11-12-A081978-triangular-even-divisors/answers/2026-11-12-chatgpt.md`. The proof and checker were independently written for this repository; no source file was copied.

## Author, licence

Aleksei Kudriashov (ORCID 0009-0006-8885-5338), Athanor lab, with AI assistance (OpenAI Codex cores; Claude Code as the lab's guide). Code: MIT; data and text: CC BY 4.0 (see LICENSE.md).
