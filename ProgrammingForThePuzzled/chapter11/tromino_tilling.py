EMPTYPIECE = -1


def recursiveTile(yard, size, originR, originC, rMiss, cMiss, nextPiece):
    quadMiss = 2*(rMiss >= size//2) + (cMiss >= size//2)

    if size == 2:
        piecePos = [(0, 0), (0, 1), (1, 0), (1, 1)]
        piecePos.pop(quadMiss)
        for (r, c) in piecePos:
            yard[originR + r][originC + c] = nextPiece
        nextPiece += 1
        return nextPiece

    for quad in range(4):
        shiftR = size//2 * (quad >= 2)
        shiftC = size//2 * (quad % 2 == 1)
        if quad == quadMiss:
            nextPiece = recursiveTile(
                yard, size//2, originR + shiftR, originC + shiftC, rMiss - shiftR, cMiss - shiftC, nextPiece)
        else:
            newrMiss = (size//2 - 1) * (quad < 2)
            newcMiss = (size//2 - 1) * (quad % 2 == 0)
            nextPiece = recursiveTile(
                yard, size//2, originR + shiftR, originC + shiftC, newrMiss, newcMiss, nextPiece)

    centerPos = [(r + size//2 - 1, c + size//2 - 1)
                 for (r, c) in [(0, 0), (0, 1), (1, 0), (1, 1)]]
    centerPos.pop(quadMiss)
    for (r, c) in centerPos:
        yard[originR + r][originC + c] = nextPiece
    nextPiece += 1
    return nextPiece


def tileMissingYard(n, rMiss, cMiss):
    yard = [[EMPTYPIECE for i in range(2**n)] for j in range(2**n)]
    recursiveTile(yard, 2**n, 0, 0, rMiss, cMiss, 0)
    return yard


def printYard(yard):
    for i in range(len(yard)):
        row = ''
        for j in range(len(yard[0])):
            row += ' ' if yard[i][j] == EMPTYPIECE else chr(
                (yard[i][j] % 26) + ord('A'))
        print(row)


def main():
    printYard(tileMissingYard(4, 4, 6))


if __name__ == '__main__':
    main()
