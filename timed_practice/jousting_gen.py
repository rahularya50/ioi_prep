import random

def gen(n):
    cat = random.randint(1, n)
    v = []
    for i in range(1, n + 1):
        if i != cat:
            v.append(i)
    random.shuffle(v)
    cnt = n
    moves = []
    while cnt > 1:
        x = random.randint(0, cnt - 1)
        y = random.randint(0, cnt - 1)
        if x == y:
            continue
        x, y = min(x, y), max(x, y)
        moves += [(x, y)]
        cnt -= (y - x)
    print(n, len(moves), cat)
    print(*v)
    for x in moves:
        print(*x)
