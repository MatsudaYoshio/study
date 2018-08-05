def collatz(number):
    return 3*number + 1 if number & 1 else number/2

def main():
    while True:
        try:
            n = int(input("Please Enter Number: "))
            break
        except ValueError:
            print("Please Enter Integer!!")
    
    while n != 1:
        n = int(collatz(n))

        print(n)

if __name__ == '__main__':
    main()
