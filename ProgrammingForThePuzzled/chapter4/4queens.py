def noConflicts(board, current, qindex, n):
    for j in range(current):
        if board[qindex][j] == 1:
            return False
    
    k = 1
    while qindex - k >= 0 and current - k >= 0:
        if board[qindex - k][current - k] == 1:
            return False
        k += 1
    k = 1
    while qindex + k < n and current - k >= 0:
        if board[qindex + k][current - k] == 1:
            return False
        k += 1

    return True

def FourQueens(n=4):
    board = [[0]*n for i in range(n)]

    for i in range(n):
        board[i][0] = 1
        for j in range(n):
            board[j][1] = 1
            if not noConflicts(board, 1, j, n):
                board[j][1] = 0
                continue
            for k in range(n):
                board[k][2] = 1
                if not noConflicts(board, 2, k, n):
                    board[k][2] = 0
                    continue
                for m in range(n):
                    board[m][3] = 1
                    if noConflicts(board, 3, m, n):
                        print(board)
                    board[m][3] = 0
                board[k][2] = 0
            board[j][1] = 0
        board[i][0] = 0

def main():
    FourQueens()

if __name__ == '__main__':
    main()