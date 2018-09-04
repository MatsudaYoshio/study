MAX_N = 10000000
MAX_N_SQRT = int(round(MAX_N**0.5))

is_prime = [True]*(MAX_N+1)

def sieve():
    is_prime[0] = is_prime[1] = False

    for i in range(2, MAX_N_SQRT+1):
        if is_prime[i]:
            is_prime[i*2:MAX_N+1:i] = [False]*int(MAX_N / i - 1)

def main():
    sieve()
    
    for i in range(50):
        if is_prime[i]:
            print(i)
            
if __name__ == '__main__':
    main()
