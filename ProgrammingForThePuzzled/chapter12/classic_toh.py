def hanoi3peg(num_rings, num_pegs, start_peg, end_peg, ring_index):
    num_moves = 0
    if num_rings > 0:
        num_moves += hanoi3peg(num_rings - 1, num_pegs, start_peg, num_pegs*2 - start_peg - end_peg, ring_index - 1)
        print('Move ring', ring_index, 'from peg', start_peg, 'to peg', num_pegs*2 - start_peg - end_peg)
        num_moves += 1
        num_moves += hanoi3peg(num_rings - 1, num_pegs, num_pegs*2 - start_peg - end_peg, end_peg, ring_index - 1)
    
    return num_moves


# num_rings: 2k
def hanoi4pegSimpleAlgorithm(num_rings):
    num_moves = 0
    num_moves += hanoi3peg(num_rings >> 1, 4, 1, 4, num_rings >> 1)
    num_moves += hanoi3peg(num_rings >> 1, 4, 1, 3, num_rings)
    num_moves += hanoi3peg(num_rings >> 1, 4, 4, 3, num_rings >> 1)

    return num_moves

# hanoi4pegGoodAlgorithm用の3peg動かす再帰関数
# pegs_mapでpegの番号をマッピング
def hanoi3pegUsingMap(num_rings, start_peg, end_peg, pegs_map, ring_index):
    num_moves = 0
    if num_rings > 0:
        num_moves += hanoi3pegUsingMap(num_rings - 1, start_peg, 6 - start_peg - end_peg, pegs_map, ring_index - 1)
        print('Move ring', ring_index, 'from peg',
              pegs_map[start_peg-1], 'to peg', pegs_map[end_peg-1])
        num_moves += 1
        num_moves += hanoi3pegUsingMap(num_rings - 1, 6 - start_peg - end_peg, end_peg, pegs_map, ring_index - 1)

    return num_moves

# num_rings: 2^n
def hanoi4pegGoodAlgorithm(num_rings, start_peg, end_peg):
    num_moves = 0
    if num_rings == 1:
        print('Move ring', num_rings, 'from peg', start_peg, 'to peg', end_peg)
    else:
        available_pegs = list(
            filter(lambda x: x not in [start_peg, end_peg], [1, 2, 3, 4]))
        pegs_map = [start_peg, available_pegs[0], end_peg]

        num_moves += hanoi4pegGoodAlgorithm(num_rings >> 1, start_peg, available_pegs[1])
        num_moves += hanoi3pegUsingMap(num_rings >> 1, 1, 3, pegs_map, num_rings)
        num_moves += hanoi4pegGoodAlgorithm(num_rings >> 1, available_pegs[1], end_peg)

    return num_moves


def main():
    print(hanoi4pegSimpleAlgorithm(8))
    print(hanoi4pegGoodAlgorithm(8, 1, 3))


if __name__ == '__main__':
    main()
