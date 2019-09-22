def noConflicts(board, current):
    for i in range(current):
        if board[i] == board[current]:
            return False
        if current-i == abs(board[current]-board[i]):
            return False
    
    return True

def EightQueens(location, ans_num, n=8):
    board = [-1]*n
    ans_count = 0

    loop_num = [n if l == -1 else 1 for l in location]

    for i in range(loop_num[0]):
        board[0] = i if location[0] == -1 else location[0]
        for j in range(loop_num[1]):
            board[1] = j if location[1] == -1 else location[1]
            if not noConflicts(board, 1):
                continue
            for k in range(loop_num[2]):
                board[2] = k if location[2] == -1 else location[2]
                if not noConflicts(board, 2):
                    continue
                for l in range(loop_num[3]):
                    board[3] = l if location[3] == -1 else location[3]
                    if not noConflicts(board, 3):
                        continue
                    for m in range(loop_num[4]):
                        board[4] = m if location[4] == -1 else location[4]
                        if not noConflicts(board, 4):
                            continue
                        for o in range(loop_num[5]):
                            board[5] = o if location[5] == -1 else location[5]
                            if not noConflicts(board, 5):
                                continue
                            for p in range(loop_num[6]):
                                board[6] = p if location[6] == -1 else location[6]
                                if not noConflicts(board, 6):
                                    continue
                                for q in range(loop_num[7]):
                                    board[7] = q if location[7] == -1 else location[7]
                                    if noConflicts(board, 7) and ans_count < ans_num:
                                        ans_count += 1
                                        print(board)

def main():
    EightQueens([-1, 4, -1, -1, -1, -1,-1, 0], 2)

if __name__ == '__main__':
    main()