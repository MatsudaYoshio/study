def quick_sort(lst, start, end):
    if start < end:
        move_num, pivot = pivotPartitionClever(lst, start, end)
        return move_num + quick_sort(lst, start, pivot - 1) + quick_sort(lst, pivot + 1, end)
    return 0

def pivotPartition(lst, start, end):
    pivot = lst[end]
    less, pivotList, more = [], [], []
    for e in lst:
        if e < pivot:
            less.append(e)
        elif e > pivot:
            more.append(e)
        else:
            pivotList.append(e)
        
    i = 0
    for e in less:
        lst[i] = e
        i += 1
    for e in pivotList:
        lst[i] = e
        i += 1
    for e in more:
        lst[i] = e
        i += 1

    return lst.index(pivot)

def pivotPartitionClever(lst, start, end):
    pivot = lst[end]
    bottom = start - 1
    top = end
    done = False
    move_num = 0

    while not done:
        while not done:
            bottom += 1
            move_num += 1
            if bottom == top:
                done = True
                break
            if lst[bottom] > pivot:
                lst[top] = lst[bottom]
                break

        while not done:
            top -= 1
            move_num += 1
            if top == bottom:
                done = True
                break
            if lst[top] < pivot:
                lst[bottom] = lst[top]
                break
        lst[top] = pivot
    return move_num, top

def main():
    a = [4, 65, 2, -31, 0, 99, 83, 782, 1]
    move_num = quick_sort(a, 0, len(a) - 1)
    print(a)
    print(move_num)

    L = list(range(100))
    move_num = quick_sort(L, 0, len(L) - 1)
    print(L)
    print(move_num)

    # 降順の配列だとソート効率は悪い
    D = list(range(99, -1, -1))
    move_num = quick_sort(D, 0, len(D) - 1)
    print(D)
    print(move_num)

    # ランダムな配列だとソート効率は良い
    R = [0] * 100
    R[0] = 29
    for i in range(100):
        R[i] = (9679 * R[i-1] + 12637 * 1) % 2287

    move_num = quick_sort(R, 0, len(R) - 1)
    print(R)
    print(move_num)

if __name__ == '__main__':
    main()
