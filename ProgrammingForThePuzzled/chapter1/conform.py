def pleaseConformOnepass(caps):
    if not caps:
        return

    caps = caps + caps[0]
    caps = caps.replace('H', caps[0])

    start = 0
    for i in range(1, len(caps)):
        if caps[i] != caps[i-1]:
            if caps[i] != caps[0]:
                start = i
            else:
                if i-start == 1:
                    print('People at positions', start, 'flip your caps!')
                else:
                    print('People in positions', start, 'through', i-1, 'flip your caps!')

def main():
    pleaseConformOnepass('FFBHBFBBBFHFF')

if __name__ == '__main__':
    main()