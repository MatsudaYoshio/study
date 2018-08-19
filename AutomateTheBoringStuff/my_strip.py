import sys, re

def my_strip(src_str, strip_str=" "):
    return re.sub(r"^[%s]+|[%s]+$" % (strip_str, strip_str), "", src_str)

def main():
    if len(sys.argv) == 2:
        print(my_strip(sys.argv[1]))
    elif len(sys.argv) == 3:
        print(my_strip(sys.argv[1], sys.argv[2]))
    
if __name__ == '__main__':
    main()
