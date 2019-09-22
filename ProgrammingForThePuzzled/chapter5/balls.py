import math

def convert2decimal(r, d, rep):
    n = 0
    for i in range(d-1):
        n = (n+rep[i])*r
    n += rep[d-1]
    
    return n

def howHardIsTheCrystal(n, d):
    r = math.ceil(math.pow(n, 1/d))

    print('Radix chosen is', r, '\n')
    ball_index = 1
    drop_num = 0
    break_num = 0
    floor_no_break = [0]*d
    s = 0
    t = n
    for i in range(d):
        for j in range(r-1):
            floor_no_break[i] += 1
            floor = convert2decimal(r, d, floor_no_break)
            if floor > n:
                floor_no_break[i] -= 1
                ball_index -= 1
                break
            print('[{}, {}]'.format(s, t))
            print('Drop ball {} from Floor {}'.format(i+ball_index, floor))
            res = input('Did the ball break (yes/no)?:')
            drop_num += 1
            if res == 'yes':
                floor_no_break[i] -= 1
                break_num += 1
                t = floor-1
                break
            else:
                s = floor
    
    hardness = convert2decimal(r, d, floor_no_break)

    print('\nnubmer of break:', break_num)
    print('Hardness:', hardness)

def main():
    howHardIsTheCrystal(128, 4)

if __name__ == '__main__':
    main()