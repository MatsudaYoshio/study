import pandas as pd
import pyodbc


class AccessDbConnection(object):
    __connectSetting = {
        'DB1': (
            r'DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};'
            r'DBQ=~\~\~\~~.accdb;'
        ),
        'DB2': (
            r'DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};'
            r'DBQ=~\~\~\~~.mdb;'
        )
    }

    def __init__(self):
        self._connection = {
            'DB1': pyodbc.connect(self.__connectSetting['DB1']),
            'DB2': pyodbc.connect(self.__connectSetting['DB2'])
        }

    @property
    def connection(self):
        return self._connection

    def __del__(self):
        for connection in self._connection.values():
            connection.close()

    def main():
        adc = AccessDbConnection()
        df = pd.read_sql('SELECT * FROM TABLE1', adc.connection['DB1'])
