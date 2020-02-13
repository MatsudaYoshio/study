def f(x): return pow(x,3)+x**2-11

def main():
    low = -10
    high = 10
    ans = (low+high)/2.0
    while abs(f(ans)) >= 0.01:
        if(f(ans)) < 0:
            low = ans
        else:
            high = ans
        ans = (low+high)/2.0

    print('x = ', ans)

if __name__ == '__main__':
    main()