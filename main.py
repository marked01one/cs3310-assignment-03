import random
from datetime import datetime

def max_route(n: int, m: int, matrix: list[list[int]]) -> int:
    if n == 0 and m == 0: return matrix[n][m]
    if n == 0: return max_route(0, m-1, matrix) + matrix[n][m]
    if m == 0: return max_route(n-1, 0, matrix) + matrix[n][m]
    
    return max(
        max_route(n-1, m, matrix),
        max_route(n, m-1, matrix),
        max_route(n-1, m-1, matrix)
    )
    

def max_route_dp(matrix: list[list[int]]) -> int:
    n, m = len(matrix), len(matrix[0])
    checker = [[0] * m for _ in range(n)]
    cache = [[float('inf')] * m for _ in range(n)]
    
    def dp(x, y):
        if checker[x][y] == 1:
            return cache[x][y]
        
        max_value = matrix[x][y]
        
        if x == 0 and y == 0:
            max_value = max_value
        elif x == 0:
            max_value += dp(x, y-1)
        elif y == 0:
            max_value += dp(x-1, y)
        else:
            max_value += max(dp(x-1, y), dp(x, y-1), dp(x-1, y-1))
        
        checker[x][y] = 1
        cache[x][y] = max_value
        return max_value  
    
    return dp(n-1, m-1)
    
def main():
    n = 11
    m = 11

    print(f"n = {n}, m = {m}")

    matrix = [[random.randint(-1000, 1000) for _ in range(m)] for _ in range(n)]


    start = datetime.now()
    print("Max route:", max_route(n-1, m-1, matrix))
    end = datetime.now()
    print(f"Time elapsed: {(end-start).microseconds / 1000:.4f} ms\n")
    
    start = datetime.now()
    print("Max route (DP):", max_route_dp(matrix))
    end = datetime.now()
    print(f"Time elapsed: {(end-start).microseconds / 1000:.4f} ms")


if __name__ == '__main__':
    main()