import re

def is_strong(password):
    regex = re.compile(r'^(?=.*?[a-z])(?=.*?[A-Z])(?=.*?\d)[a-zA-Z\d]{8,}')
    return re.match(regex, password)

def main():
    password = "lisdfDDh9fg"
    if is_strong(password):
        print("This is strong!!")
    else:
        print("This is weak!!")
        
if __name__ == '__main__':
    main()
