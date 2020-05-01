def rCheckPalindrome(s):
    if len(s) <= 1:
        return True
    else:
        if s[0] == s[-1]:
            return rCheckPalindrome(s[1:-1])
        else:
            return False

def is_palindrome(s):
    s = str.lower(s)
    return rCheckPalindrome(s)

def main():
    s = 'racecar'
    if is_palindrome(s):
        print(s, 'is a palindrome.')
    else:
        print(s, "isn't a palindrome.")

if __name__ == '__main__':
    main()