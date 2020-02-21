def InviteDinner(guestList, dislikePairs):
    n, invite = len(guestList), []
    max_weight = 0
    for i in range(2**n):
        Combination = []
        num = i
        for j in range(n):
            if num & 1 == 1:
                Combination = [guestList[n-1-j]] + Combination
            num >>= 1
        
        c = [x[0] for x in Combination]
        for k in range(len(dislikePairs)):
            d = dislikePairs[:k]+dislikePairs[(k+1):]
            
            good = True
            for j in d:
                if j[0] in c and j[1] in c:
                    good = False
            if good:
                w = sum(x[1] for x in Combination)
                if w > max_weight:
                        max_weight = w
                        invite = Combination

    return invite

def main():
    #dislikePairs = [['Alice', 'Bob'], ['Bob', 'Eve']]
    #guestList = [('Alice', 2), ('Bob', 6), ('Cleo', 3), ('Don', 10), ('Eve', 3)]

    LargeDislikes = [['B', 'C'], ['C', 'D'], ['D', 'E'], ['F', 'G'], ['F', 'H'], ['F', 'I'], ['G', 'H']]
    LargeGuestList = [('A', 2), ('B', 1), ('C', 3), ('D', 2), ('E', 1), ('F', 4), ('G', 2), ('H', 1), ('I', 3)]

    goodGuestList = []
    badGuestList = []
    for i in LargeGuestList:
        good = True
        for j in LargeDislikes:
            if i[0] in j:
                badGuestList.append(i)
                good = False
                break
        if good:
            goodGuestList.append(i)

    invite = InviteDinner(badGuestList, LargeDislikes)
    invite = goodGuestList + invite

    print('Optimum Solution:', invite)
    print('Weight is:', sum(x[1] for x in invite))

if __name__ == '__main__':
    main()