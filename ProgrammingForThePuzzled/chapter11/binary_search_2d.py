import numpy as np


def removeQuadAlgorithm(x, L, is_found):
    if is_found:
        return is_found

    r = L.shape[0]
    c = L.shape[1]
    mid_r = r >> 1
    mid_c = c >> 1

    if x == L[mid_r][mid_c]:
        return True

    elif x > L[mid_r][mid_c]:
        if r > 2:
            is_found |= removeQuadAlgorithm(x, L[mid_r+1:, :mid_c+1], is_found)

        if c > 2:
            is_found |= removeQuadAlgorithm(x, L[:mid_r+1, mid_c+1:], is_found)

        if r > 2 and c > 2:
            is_found |= removeQuadAlgorithm(x, L[mid_r+1:, mid_c+1:], is_found)

    else:
        if r >= 2:
            is_found |= removeQuadAlgorithm(x, L[:mid_r, mid_c:mid_c+1], is_found)

        if c >= 2:
            is_found |= removeQuadAlgorithm(x, L[mid_r:mid_r+1, :mid_c], is_found)

        if r > 2 and c > 2:
            is_found |= removeQuadAlgorithm(x, L[:mid_r, :mid_c], is_found)

    return is_found


def removeOneLineAlgorithm(x, L, is_found):
    if x == L[0, -1]:
        return True
    elif x > L[0, -1]:
        if L.shape[0] > 1:
            is_found |= removeOneLineAlgorithm(x, L[1:], is_found)
    else:
        if L.shape[1] > 1:
            is_found |= removeOneLineAlgorithm(x, L[:, :-1], is_found)

    return is_found


def main():
    T = [
        [1, 4, 7, 11, 15],
        [2, 5, 8, 12, 19],
        [3, 6, 9, 16, 22],
        [10, 13, 14, 17, 24],
        [18, 21, 23, 26, 30]
    ]
    L = np.array(T)

    x = 13
    if removeQuadAlgorithm(x, L, False):
        print("Found ", x)
    else:
        print("Not found ", x)


if __name__ == '__main__':
    main()
