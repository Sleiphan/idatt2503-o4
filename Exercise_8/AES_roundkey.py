from AES_matrix import matrix2bytes

state = [
    [206, 243, 61, 34],
    [171, 11, 93, 31],
    [16, 200, 91, 108],
    [150, 3, 194, 51],
]

round_key = [
    [173, 129, 68, 82],
    [223, 100, 38, 109],
    [32, 189, 53, 8],
    [253, 48, 187, 78],
]

def add_round_key(s, k):
    result = s.copy()
    for x in range(0, 4):
        for y in range(0, 4):
            result[x][y] = s[x][y] ^ k[x][y]
    return result

if __name__ == "__main__":
    print(matrix2bytes(add_round_key(state, round_key)))

