import random

def make_hull(n):
    print(n, 11, 11)
    hull = []
    for i in range(n):
        hull.append((random.randint(1, 10), random.randint(1, 10)))
    for h in hull:
        print("1 A", h[0], h[1])
