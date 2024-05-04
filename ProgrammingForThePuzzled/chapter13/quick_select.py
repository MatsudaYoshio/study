def quick_select(lst, start, end, k):
    if start < end:
        pivot = pivotPartitionClever(lst, start, end)
        if k == pivot+1:
            return pivot
        elif k < pivot+1:
            return quick_select(lst, start, pivot - 1, k)
        else:
            return quick_select(lst, pivot + 1, end, k)
    else:
        return start

def pivotPartitionClever(lst, start, end):
    pivot = lst[end]
    bottom = start - 1
    top = end
    done = False

    while not done:
        while not done:
            bottom += 1
            if bottom == top:
                done = True
                break
            if lst[bottom] > pivot:
                lst[top] = lst[bottom]
                break

        while not done:
            top -= 1
            if top == bottom:
                done = True
                break
            if lst[top] < pivot:
                lst[bottom] = lst[top]
                break
        lst[top] = pivot
    return top

def main():
    a = [4, 65, 2, -31, 0, 99, 83, 782, 1]
    ans_index = quick_select(a, 0, len(a) - 1, 4)
    print(a[ans_index])

if __name__ == '__main__':
    main()
