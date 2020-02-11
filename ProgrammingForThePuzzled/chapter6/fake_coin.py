def compare(groupA, groupB):
    if sum(groupA) > sum(groupB):
        result = 'left'
    elif sum(groupA) < sum(groupB):
        result = 'right'
    else:
        result = 'equal'       

    return result

def splitCoins(coinsList):
    length = len(coinsList)
    group1 = coinsList[0:length//3]
    group2 = coinsList[length//3:length//3*2]
    group3 = coinsList[length//3*2:length]

    return group1, group2, group3

def findFakeGroupHeavier(group1, group2, group3):
    result1and2 = compare(group1, group2)
    if result1and2 == 'left':
        fakeGroup = group1
    elif result1and2 == 'right':
        fakeGroup = group2
    else:
        fakeGroup = group3

    return fakeGroup

def findFakeGroupLighter(group1, group2, group3):
    result1and2 = compare(group1, group2)
    if result1and2 == 'right':
        fakeGroup = group1
    elif result1and2 == 'left':
        fakeGroup = group2
    else:
        fakeGroup = group3

    return fakeGroup

def findFakeGroupAndType(group1, group2, group3):
    result1and2 = compare(group1, group2)
    if result1and2 == 'left':
        result1and3 = compare(group1, group3)
        if result1and3 == 'left':
            fakeGroup = group1
            type = 'heavier'
        elif result1and3 == 'equal':
            fakeGroup = group2
            type = 'lighter'
    elif result1and2 == 'right':
        result1and3 = compare(group1, group3)
        if result1and3 == 'right':
            fakeGroup = group1
            type = 'lighter'
        elif result1and3 == 'equal':
            fakeGroup = group2
            type = 'heavier'
    else:
        fakeGroup = group3
        type = 'unknown'

    return fakeGroup, type

def CoinComparisonGeneral(coinsList):
    counter = 0
    currList = coinsList
    type = 'unknown'
    while len(currList) > 1:
        group1, group2, group3 = splitCoins(currList)
        if type == 'heavier':
            currList = findFakeGroupHeavier(group1, group2, group3)
        elif type == 'lighter':
            currList = findFakeGroupLighter(group1, group2, group3)
        else:
            currList, type = findFakeGroupAndType(group1, group2, group3)
        counter += 1
    
    if type == 'unknown':
        print('The fake coin was not found')
    else:
        fake = currList[0]
        print('The fake coin is coin', coinsList.index(fake)+1, 'in the original list,', type, 'than other coins')
        counter += 1

    print('Number of weighings:', counter)

def main():
    coins = [10, 10, 10, 10, 10, 10, 10, 10, 10,
             10, 10, 10, 10, 11, 10, 10, 10, 10,
             10, 10, 10, 10, 10, 10, 10, 10, 10]

    CoinComparisonGeneral(coins)

if __name__ == '__main__':
    main()