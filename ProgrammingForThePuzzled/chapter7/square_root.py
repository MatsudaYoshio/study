def bisectionSearchForSquareRoot(x, epsilon):
    if x < 0:
        print('Sorry, imaginary numbers are out of scope!')
        return
    
    numGuesses = 0
    
    if x < 1.0:
        low = x
        high = 1.0
    else: 
        low = 0.0
        high = x
    
    ans = (high+low)/2.0

    while abs(ans**2-x) >= epsilon:
        if ans**2 < x:
            low = ans
        else:
            high = ans
        ans = (high+low)/2.0
        numGuesses += 1

    print('numGuesses =', numGuesses)
    print(ans, 'is close to square root of', x)

def main():
    bisectionSearchForSquareRoot(0.25, .01)

if __name__ == '__main__':
    main()