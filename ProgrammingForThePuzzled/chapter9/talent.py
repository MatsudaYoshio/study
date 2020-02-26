def Hire4Show(candList, candTalents, talentList):
    n = len(candList)
    hire = candList[:]
    for i in range(2**n):
        Combination = []
        num = i
        for j in range(n):
            if num & 1 == 1:
                Combination = [candList[n-1-j]] + Combination
            num >>= 1
        
        if Good(Combination, candList, candTalents, talentList):
            if len(Combination) < len(hire):
                hire = Combination
    
    return hire

def Good(Comb, candList, candTalents, AllTalents):
    s = set()
    for c in Comb:
        candTal = candTalents[candList.index(c)]
        for t in candTal:
            s.add(t)
    
    return True if len(s) == len(AllTalents) else False

def RemoveUpwardCompatible(candList, candTalents):
    Candidates = []
    CandidateTalents = []
    RemoveSet = set()
    for i in range(len(candTalents)):
        for j in range(i+1, len(candTalents)):
            if set(candTalents[i]) <= set(candTalents[j]):
                RemoveSet.add(i)
            elif set(candTalents[j]) <= set(candTalents[i]):
                RemoveSet.add(j)

    for i in range(len(candList)):
        if i not in RemoveSet:
            Candidates.append(candList[i])
            CandidateTalents.append(candTalents[i])

    return Candidates, CandidateTalents

def ChooseMustCandidates(candList, candTalents, talentList):
    TalentCount = [[0 for i in range(2)] for j in range(len(talentList))]
    for i in range(len(candTalents)):
        for c in candTalents[i]:
            idx = talentList.index(c)
            TalentCount[idx][0] += 1
            TalentCount[idx][1] = i

    MustCandNum = []
    for i in range(len(TalentCount)):
        if TalentCount[i][0] == 1:
            RemoveList = candTalents[TalentCount[i][1]][:]

            for r in RemoveList:
                for ct in candTalents:
                    try:
                        ct.remove(r)
                    except ValueError:
                        pass
                
                try:
                    talentList.remove(r)
                except ValueError:
                    pass

            MustCandNum.append(TalentCount[i][1])

    MustHire = []
    Candidates = []
    CandidateTalents = []
    for i in range(len(candList)):
        if i in MustCandNum:
            MustHire.append(candList[i])
        else:
            Candidates.append(candList[i])
            CandidateTalents.append(candTalents[i])

    return MustHire, Candidates, CandidateTalents, talentList

def main():
    Talents = ['Sing', 'Dance', 'Magic', 'Act', 'Flex', 'Code']
    Candidates = ['Aly', 'Bob', 'Cal', 'Don', 'Eve', 'Fay']
    CandidateTalents = [['Flex', 'Code'], ['Dance', 'Magic'], ['Sing', 'Magic'], ['Sing', 'Dance'], ['Dance', 'Act', 'Code'], ['Act', 'Code']]

    Candidates, CandidateTalents = RemoveUpwardCompatible(Candidates, CandidateTalents)

    MustHire, Candidates, CandidateTalents, Talents = ChooseMustCandidates(Candidates, CandidateTalents, Talents)

    Hire = Hire4Show(Candidates, CandidateTalents, Talents)

    print('Optimum Solution:', Hire+MustHire)


    ShowTalent = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    CandidateList = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
    CandToTalents = [[4, 5, 7], [1, 2, 8], [2, 4, 6, 9], [3, 6, 9], [2, 3, 9], [7, 8, 9], [1, 3, 7]]

    CandidateList, CandToTalents = RemoveUpwardCompatible(CandidateList, CandToTalents)

    MustHire, CandidateList, CandToTalents, ShowTalent = ChooseMustCandidates(CandidateList, CandToTalents, ShowTalent)

    Hire = Hire4Show(CandidateList, CandToTalents, ShowTalent)

    print('Optimum Solution:', Hire+MustHire)

if __name__ == '__main__':
    main()