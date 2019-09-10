def bestTimeToParty(schedule, ystart, yend):
    n = len(schedule)
    times = [None]*(2*n)

    for i in range(n):
        times[2*i] = (schedule[i][0], 1)
        times[2*i+1] = (schedule[i][1], -1)

    times = sorted(times)

    rcount = 0
    maxcount = time = 0
    for t in times:
        if ystart <= t[0] and t[0] < yend:
            rcount = rcount + t[1]
        
        if rcount > maxcount:
            maxcount = rcount
            time = t[0]

    print('Best time to attend the party is at', time, 'o\'clock', ':', maxcount, 'celebrities will be attending!')

def bestTimeToParty2(schedule, ystart, yend):
    maxcount = time = 0
    for s1 in schedule:
        if ystart <= s1[0] and s1[0] < yend:
            rcount = 0
            for s2 in schedule:
                if s2[0] <= s1[0] and s1[0] < s2[1]:
                    rcount = rcount + 1
            
            if rcount > maxcount:
                maxcount = rcount
                time = s1[0]

    print('Best time to attend the party is at', time, 'o\'clock', ':', maxcount, 'celebrities will be attending!')

def bestTimeToParty3(schedule, ystart, yend):
    n = len(schedule)
    times = [None]*(2*n)

    for i in range(n):
        times[2*i] = (schedule[i][0], schedule[i][2])
        times[2*i+1] = (schedule[i][1], -schedule[i][2])

    times = sorted(times)

    rcount = 0
    maxcount = time = 0
    for t in times:
        if ystart <= t[0] and t[0] < yend:
            rcount = rcount + t[1]
        
        if rcount > maxcount:
            maxcount = rcount
            time = t[0]

    print('Best time to attend the party is at', time, 'o\'clock', ':', maxcount, 'celebrities will be attending!')

def main():
    sched = [(6.0, 8.0), (6.5, 12.0), (6.5, 7.0), (7.0, 8.0),
             (7.5, 10.0), (8.0, 9.0), (8.0, 10.0), (9.0, 12.0),
             (9.5, 10.0), (10.0, 11.0), (10.0, 12.0), (11.0, 12.0)]

    sched3 = [(6.0, 8.0, 2), (6.5, 12.0, 1), (6.5, 7.0, 2),
              (7.0, 8.0, 2), (7.5, 10.0, 3), (8.0, 9.0, 2), 
              (8.0, 10.0, 1), (9.0, 12.0, 2),
              (9.5, 10.0, 4), (10.0, 11.0, 2),
              (10.0, 12.0, 3), (11.0, 12.0, 7)]

    bestTimeToParty(sched, 6.0, 10.0)
    bestTimeToParty2(sched, 6.0, 10.0)
    bestTimeToParty3(sched3, 3.0, 15.0)

if __name__ == "__main__":
    main()