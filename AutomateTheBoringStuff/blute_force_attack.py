import sys
import os
import PyPDF2

def main():
    if len(sys.argv) != 2 or not os.path.isfile(sys.argv[1]): sys.exit(1)
    
    with open("dictionary.txt", 'r') as dictionary_data:
        words = dictionary_data.readlines()
        
        pdf_reader = PyPDF2.PdfFileReader(open(sys.argv[1], "rb"))
        for word in words:
            word = word.replace('\n','')
            passwords = [word.upper(), word.lower()]
            for password in passwords:
                if pdf_reader.decrypt(password):
                    print("Password ---> \""+password+"\"")
                    sys.exit(0)    
            
if __name__ == '__main__':
    main()
