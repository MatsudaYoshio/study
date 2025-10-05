import aiohttp

API_KEY = ''
FRED_API_URL = 'https://api.stlouisfed.org/fred/series/observations'


class FREDGetApiRequest(object):
    def __init__(self, payload):
        self.payload = payload.copy()
        self.payload['api_key'] = API_KEY

    async def execute(self, session: aiohttp.ClientSession):
        async with session.get(FRED_API_URL, params=self.payload) as response:
            return await response.json()
    
    async def execute_standalone(self):
        async with aiohttp.ClientSession() as session:
            return await self.execute(session)
