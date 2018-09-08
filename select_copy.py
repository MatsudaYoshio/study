import os
import re
import shutil

REGEX = re.compile(r".*\.cpp$")
DIR_PATH = {
    "SEARCH": "/"+os.path.join("~~~", "---"),
    "COPY": "/"+os.path.join("~~~", "---")
}

def main():
    for folder_name, sub_folders, file_names in os.walk(DIR_PATH["SEARCH"]):
        for file_name in file_names:
            if REGEX.match(file_name):
                shutil.copy(os.path.join(folder_name, file_name), DIR_PATH["COPY"])
    
if __name__ == '__main__':
    main()
