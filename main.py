import random
import time

def max_route(n: int, m: int, matrix: list[list[int]]) -> int:
    if n == 0 and m == 0: return matrix[n][m]
    if n == 0: return max_route(0, m-1, matrix) + matrix[n][m]
    if m == 0: return max_route(n-1, 0, matrix) + matrix[n][m]
    
    return max(
        max_route(n-1, m, matrix),
        max_route(n, m-1, matrix),
        max_route(n-1, m-1, matrix)
    )
    

n = random.randint(10, 20)
m = random.randint(10, 20)

print(f"n = {n}, m = {m}")

matrix = [[random.randint(-1000, 1000) for _ in range(m)] for _ in range(n)]


start = time.time()
print("Max route:", max_route(n-1, m-1, matrix))
print(f"Time elapsed: {time.time()-start:.2f}")
