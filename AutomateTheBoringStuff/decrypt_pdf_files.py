from pathlib import Path
import os
import getpass
import PyPDF2

DIR_PATH = Path.home()/"---"/"~~~"

def main():
    for folder_name, sub_folders, file_names in os.walk(DIR_PATH):
        for file_name in file_names:
            if not file_name.endswith(".pdf"): continue
            
            full_file_name = os.path.join(folder_name, file_name)
            
            pdf_reader = PyPDF2.PdfFileReader(open(full_file_name, "rb"))
            if not pdf_reader.isEncrypted: continue

            print("Open a file "+full_file_name)
            password = str(getpass.getpass("Please Enter Password:"))
            if pdf_reader.decrypt(password):
                pdf_writer = PyPDF2.PdfFileWriter()
                for page_num in range(pdf_reader.numPages):
                    pdf_writer.addPage(pdf_reader.getPage(page_num))

                with open(full_file_name.replace("_encrypted", ""), 'wb') as decrypted_pdf:
                    pdf_writer.write(decrypted_pdf)  

                print("Decrypted the file!")
            else:
                print("Wrong password! Can't open the file.")

if __name__ == '__main__':
    main()
