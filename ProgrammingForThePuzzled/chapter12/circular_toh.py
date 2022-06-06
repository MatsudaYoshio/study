def cw(num_rings, start_peg, end_peg):
    num_moves = 0
    if num_rings == 1:
        print('Move ring', num_rings, 'from peg', start_peg, 'to peg', end_peg)
        num_moves += 1
    else:
        mid_peg = 6 - start_peg - end_peg

        num_moves += ccw(num_rings-1, start_peg, mid_peg)

        print('Move ring', num_rings, 'from peg', start_peg, 'to peg', end_peg)
        num_moves += 1

        num_moves += ccw(num_rings-1, mid_peg, end_peg)

    return num_moves


def ccw(num_rings, start_peg, end_peg):
    num_moves = 0
    mid_peg = 6 - start_peg - end_peg

    if num_rings == 1:
        print('Move ring', num_rings, 'from peg', start_peg, 'to peg', mid_peg)
        print('Move ring', num_rings, 'from peg', mid_peg, 'to peg', end_peg)
        num_moves += 2
    elif num_rings > 0:
        num_moves += cw(num_rings-1, start_peg, mid_peg)
        num_moves += cw(num_rings-1, mid_peg, end_peg)

        print('Move ring', num_rings, 'from peg', start_peg, 'to peg', mid_peg)
        num_moves += 1

        num_moves += cw(num_rings-1, end_peg, start_peg)

        print('Move ring', num_rings, 'from peg', mid_peg, 'to peg', end_peg)
        num_moves += 1

        num_moves += cw(num_rings-1, start_peg, mid_peg)
        num_moves += cw(num_rings-1, mid_peg, end_peg)

    return num_moves


def main():
    print(cw(3, 1, 2))


if __name__ == '__main__':
    main()
