import re

def is_ip_adress(s):
    regex = re.compile(r"^(([1-9]?\d|1\d{2}|2[0-4]\d|25[0-5])\.){3}([1-9]?\d|1\d{2}|2[0-4]\d|25[0-5])$")
    return re.match(regex, s)

def main():
    M = int(input())
    for i in range(M):
        S = str(input())
        print("True" if is_ip_adress(S) else "False")
        
if __name__ == '__main__':
    main()
