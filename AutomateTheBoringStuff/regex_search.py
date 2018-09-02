import sys
import re
import os

def main():
    if len(sys.argv) == 3:
        try:
            ld = os.listdir(sys.argv[1])
        except FileNotFoundError as e:
            print(e)

        input_regex = re.compile("%s" % sys.argv[2])
        
        text_files = [f for f in ld if re.match(".*\.txt$", f)]

        print("Result:\n")
        for fn in text_files:
            with open(fn, 'r') as f:
                for l in f.readlines():
                    if input_regex.match(l):
                        print(l)
                
if __name__ == '__main__':
    main()
