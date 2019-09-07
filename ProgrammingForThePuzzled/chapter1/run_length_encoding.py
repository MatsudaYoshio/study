def encode(org_str):
    res_str = ''
    start = 0
    for i in range(1, len(org_str)):
        if org_str[i] != org_str[i-1]:
            res_str = res_str + str(i-start) + org_str[i-1]
            start = i
    res_str = res_str + str(len(org_str)-start) + org_str[-1]

    return res_str

def decode(org_str):
    org_str = org_str + '1a'

    res_str = ''
    start = n = 0
    for i in range(1, len(org_str)):
        if org_str[i] != org_str[i-1]:  
            if org_str[i].isdecimal():
                n = int(org_str[start:(i-1)])
                start = i-1
            elif org_str[i].isalpha():
                res_str = res_str + org_str[start:(i-1)]*n
                start = i-1

    return res_str

def main():
    s = 'FFBHBFBBBFHFF'
    encoded_s = encode('FFBHBFBBBFHFF')
    decoded_s = decode(encoded_s)
    
    print('\n'.join([s, encoded_s, decoded_s]))

if __name__ == '__main__':
    main()