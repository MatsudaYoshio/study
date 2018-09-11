from pathlib import Path
from operator import itemgetter
import os
import re

NUMBER_REGEX = re.compile(r"\d+")
FILE_REGEX = re.compile(r"^spam\d+\.txt$")
DIR_PATH = Path.home()/"---"/"~~~"

def main():
    files = [[x.name, int(NUMBER_REGEX.search(x.name).group())] for x in list(DIR_PATH.glob("*")) if os.path.isfile(x) and FILE_REGEX.match(x.name)]
    
    files = sorted(files, key=itemgetter(1))

    for i, f in enumerate(files):
        Path(DIR_PATH/f[0]).rename(Path(DIR_PATH/NUMBER_REGEX.sub(str(i+1), f[0])))
    
if __name__ == '__main__':
    main()
