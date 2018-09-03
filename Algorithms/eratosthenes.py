MAX_N = 10000
is_prime = [True]*(MAX_N+1)

def sieve():
    is_prime[0] = is_prime[1] = False

    for i in range(2, MAX_N+1):
        if is_prime[i]:
            is_prime[i*2:MAX_N+1:i] = [False]*len(range(i*2, MAX_N+1, i))

def main():
    sieve()
    for i in range(1, 12):
        if is_prime[i]:
            print(i)
        
if __name__ == '__main__':
    main()
