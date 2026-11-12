from math import isqrt

def factors(n):
    out = []
    d = 2
    while d * d <= n:
        if n % d == 0:
            e = 0
            while n % d == 0:
                n //= d
                e += 1
            out.append((d, e))
        d += 1
    if n > 1:
        out.append((n, 1))
    return out

def prime(n):
    return n >= 2 and all(n % d for d in range(2, isqrt(n) + 1))

counts = [0, 0, 0]
for k in range(1, 20001):
    fs = factors(k * (k + 1) // 2)
    tau = 1
    for _, e in fs:
        tau *= e + 1
    if tau % 2 or tau <= 4 or not prime(tau // 2):
        continue
    j = tau // 2
    assert len(fs) == 2 and sorted(e for _, e in fs) == [1, j - 1]
    p = next(p for p, e in fs if e == j - 1)
    q = next(p for p, e in fs if e == 1)
    x = p ** (j - 1)
    options = (2*x - 1, 2*x + 1, (x + 1)//2 if x % 2 else -1)
    assert q in options, (k, p, q, j)
    counts[options.index(q)] += 1
print('triangular indices checked: 20000')
print('counts by corrected forms:', *counts)
print('old minus form at p=331, r=256 is divisible by 4:', ((331**256-1)//2) % 4 == 0)
