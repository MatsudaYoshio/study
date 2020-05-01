def noConflicts(board, current):
    for i in range(current):
        if board[i] == board[current]:
            return False
        if current - i == abs(board[current] - board[i]):
            return False

    return True

def rQueens(board, current, size, location):
    if current == size:
        return True
    else:
        if location[current] == -1:
            for i in range(size):
                board[current] = i
                if noConflicts(board, current):
                    found = rQueens(board, current + 1, size, location)
                    if found:
                        return True
        else:
            board[current] = location[current]
            if noConflicts(board, current):
                found = rQueens(board, current + 1, size, location)
                if found:
                    return True
    
    return False

def nQueens(N):
    board = [-1]*N

    location = [-1]*N
    #location = [-1, -1, 4, -1, -1, -1, -1, 0, -1, 5]

    rQueens(board, 0, N, location)

    view_board = [['.' for i in range(N)] for j in range(N)]
    for i in range(N):
        view_board[board[i]][i] = 'Q'

    for i in range(N):
        print(view_board[i][0], end='')
        for j in range(1,N):
            print('', view_board[i][j], end='')
        print()

def main():
    nQueens(10)

if __name__ == '__main__':
    main()