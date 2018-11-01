from pathlib import Path
import os
import datetime
import logging

TARGET_PATH = Path.home()/"~~~"/"---"
LOG_PATH = Path.home()/"~~~"/"---"

def main():
    # ログ書き出しのための準備
    logger = logging.getLogger("DeleteLog")
    logger.setLevel(20)

    fh = logging.FileHandler("delete_log_{0:%Y%m}.log".format(datetime.datetime.now()))
    logger.addHandler(fh)

    sh = logging.StreamHandler()
    logger.addHandler(sh)

    formatter = logging.Formatter('%(asctime)s:%(lineno)d:%(levelname)s:%(message)s')
    fh.setFormatter(formatter)
    sh.setFormatter(formatter)
    
    now = datetime.date.today() # 今日の日付
    
    for folder_name, sub_folders, file_names in os.walk(TARGET_PATH):
        for file_name in file_names:
            f = os.path.join(folder_name, file_name)
            mtime = datetime.date.fromtimestamp(int(os.path.getmtime(f)))
            if (now - mtime).days >= 7: # ファイルの最終更新時刻が一週間前だったら
                os.remove(f)
                logger.info("[Delete file] {}".format(f))

    # ディレクトリリストの取得
    dirs = []
    for folder_name, sub_folders, file_names in os.walk(TARGET_PATH):
        for dir_name in sub_folders:
            dirs.append(os.path.join(folder_name, dir_name))

    # 空のディレクトリを削除
    for d in dirs[::-1]:
        try:
            os.rmdir(d)
            logger.info("[Delete directory] {}".format(d))
        except OSError:
            pass

if __name__ == '__main__':
    main()
