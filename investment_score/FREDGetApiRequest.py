import requests

API_KEY = ''
FRED_API_URL = 'https://api.stlouisfed.org/fred/series/observations'


class FREDGetApiRequest(object):
    def __init__(self, payload):
        self.payload = payload.copy()
        self.payload['api_key'] = API_KEY

    def excute(self):
        return requests.get(FRED_API_URL, self.payload)
