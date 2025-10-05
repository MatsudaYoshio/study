import aiohttp
from FREDGetApiRequest import FREDGetApiRequest


class EconomicIndicator(object):
    def __init__(self, series_id):
        self.base_payload = {
            'file_type': 'json',
            'limit': '1',
            'series_id': series_id,
            'sort_order': 'desc'
        }

    async def get_value(self, units='lin', session: aiohttp.ClientSession = None):
        payload = self.base_payload.copy()
        payload['units'] = units

        request = FREDGetApiRequest(payload)
        
        try:
            if session:
                data = await request.execute(session)
            else:
                data = await request.execute_standalone()
            
            if data.get('observations'):
                value = data['observations'][0]['value']
                return float(value)
            else:
                print('Failed to get value.')
                return None
                
        except aiohttp.ClientResponseError as e:
            if e.status == 429:
                print('Too many requests.')
            else:
                print(f'Failed to get response: {e.status}')
            return None
        except Exception as e:
            print(f'Error occurred: {e}')
            return None
