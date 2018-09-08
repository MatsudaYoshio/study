import os
from operator import itemgetter

DIR_PATH = "/"+os.path.join("---", "~~~")

def main():
    big_files = []
    for folder_name, sub_folders, file_names in os.walk(DIR_PATH):
        for file_name in file_names:
            big_files.append([file_name, os.path.getsize(os.path.join(folder_name, file_name))])      
            
            if len(big_files) >= 11:
                big_files = sorted(big_files, key=itemgetter(1), reverse=True)
                del big_files[-1]
                
    for i, big_file in enumerate(big_files):
        print(("[" + str(i+1) + "]:").ljust(6) + big_file[0].ljust(33) + " " + str(big_file[1]) + " bytes")

if __name__ == '__main__':
    main()
