import abc

import pandas as pd
import pathlib


class Conversation(metaclass=abc.ABCMeta):
    @abc.abstractmethod
    def interact(self, interaction_info):
        pass

    @staticmethod
    def add_separation(str) -> str:
        separation = '='*50 + '\n'
        return f'{separation}{str}{separation}'


class InteractionInfomation(object):
    def __init__(self, your_name='', favorite_restraunt=''):
        self.your_name = your_name
        self.favorite_restraunt = favorite_restraunt


class MemoryIo(object):
    MEMORY_DATA_PATH = 'roboko_memory.csv'
    COLUMNS = ['NAME', 'COUNT']
    CSV_ENCODING = 'utf-8'

    def __init__(self):
        if not pathlib.Path(MemoryIo.MEMORY_DATA_PATH).exists():
            pd.DataFrame(columns=MemoryIo.COLUMNS).to_csv(
                MemoryIo.MEMORY_DATA_PATH, index=False, encoding=MemoryIo.CSV_ENCODING
            )

    def get_data(self):
        return pd.read_csv(MemoryIo.MEMORY_DATA_PATH, encoding=MemoryIo.CSV_ENCODING)

    def write_data(self, df):
        df.to_csv(MemoryIo.MEMORY_DATA_PATH, index=False, encoding=MemoryIo.CSV_ENCODING)


class FirstVoice(Conversation):
    def interact(self, interaction_info):
        interaction_info.your_name = self.speak(self.generate_message())

    def speak(self, message):
        return input(message)

    @staticmethod
    def generate_message():
        return Conversation.add_separation('こんにちは！私はRobokoです。あなたの名前は何ですか？\n')


class ClosedQuestion(Conversation):
    VALID_RESPONSE = ['y', 'yes', 'Yes', 'YES', 'n', 'no', 'No', 'NO']

    def interact(self, _):
        df = MemoryIo().get_data()
        df.sort_values(by='COUNT', ascending=False, inplace=True)
        for name in df['NAME']:
            message = self.generate_message(name)
            while self.speak(message) not in ClosedQuestion.VALID_RESPONSE:
                message = 'Yes or Noで答えてください。\n'

    def speak(self, message):
        return input(message)

    def generate_message(self, recommend_restraunt):
        return Conversation.add_separation(f'私のオススメのレストランは、{recommend_restraunt}です。\nこのレストランは好きですか？[Yes/No]\n')


class WhatQuestion(Conversation):
    def interact(self, interaction_info):
        interaction_info.favorite_restraunt = self.speak(self.generate_message(interaction_info.your_name)).title()
        self.update_memory(interaction_info.favorite_restraunt)

    def speak(self, message):
        return input(message)

    def generate_message(self, your_name):
        return Conversation.add_separation(f'{your_name}さん、どこのレストランが好きですか？\n')

    def update_memory(self, favorite_restraunt):
        memory_io = MemoryIo()
        df = memory_io.get_data()

        target_restaurant_postion = df.loc[df[df['NAME'] == favorite_restraunt].index, 'COUNT']

        if target_restaurant_postion.empty:
            df = df.append(
                {'NAME': favorite_restraunt, 'COUNT': 1},
                ignore_index=True
            )
        else:
            df.loc[df.index[target_restaurant_postion.keys()[0]], ['COUNT']] += 1

        memory_io.write_data(df)


class PartingShot(Conversation):
    def interact(self, interaction_info):
        self.speak(self.generate_massage(interaction_info.your_name))

    def speak(self, message):
        return print(message)

    def generate_massage(self, your_name):
        return Conversation.add_separation(f'{your_name}さん、ありがとうございました。\nよい一日を！さようなら。\n')


class Roboter(object):
    def __init__(self):
        self.interaction_info = InteractionInfomation()

    def interact(self):
        conversation = [
            FirstVoice(),
            ClosedQuestion(),
            WhatQuestion(),
            PartingShot()
        ]

        for c in conversation:
            c.interact(self.interaction_info)
