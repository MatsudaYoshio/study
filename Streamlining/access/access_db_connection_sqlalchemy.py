import pandas as pd
import pyodbc
from sqlalchemy import create_engine
from urllib.parse import quote_plus


class AccessDbConnection(object):
    __DB_PATH = r'~\~\~~.accdb;'

    __connectSetting = {
        r'DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};'
        r'DBQ=~\~\~\~~.accdb;'
        r'DBQ=~\~\~\~~.mdb;'
    }

    def __init__(self):
        self._connection = pyodbc.connect(self.__connectSetting)
        self._cursor = self._connection.cursor()
        self._engine = self.alchemy_engine(self.__DB_PATH)

    def alchemy_engine(self, db_path):
        con_str = 'DRIVER=' + \
                  'DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};' + \
                  f'DBQ={db_path};'
        con_str = quote_plus(con_str)
        engine = create_engine(
            f'access+pyodbc:///?odbc_connect={con_str}', echo=True)

        return engine

    @property
    def connection(self):
        return self._connection

    @property
    def cursor(self):
        return self._cursor

    @property
    def engine(self):
        return self._engine

    def __del__(self):
        self._cursor.close()
        self._connection.close()


def main():
    df = pd.read_csv('~~\~~.csv')

    adc = AccessDbConnection()

    # insert
    adc.cursor.executemany(
        'INSERT INTO TABLE1 (VALUE1, VALUE2, VALUE3) VALUES (?, ?, ?)', df.itertuples(index=False)
    )
    adc.connection.commit()

    # update
    adc.cursor.execute('UPDATE TABLE1 SET COLUMN1 = NULL')
    adc.connection.commit()

    # delete
    adc.cursor.execute('DELETE FROM TABLE1 WHERE COLUMN1 = NULL')
    adc.connection.commit()
