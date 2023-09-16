from FREDGetApiRequest import FREDGetApiRequest, requests

class EconomicIndicator(object):
    def __init__(self, series_id):
        self.base_payload = {
            'file_type': 'json',
            'limit': '1',
            'series_id': series_id,
            'sort_order': 'desc'
        }
    
    def get_value(self, units='lin'):
        payload = self.base_payload.copy()
        payload['units'] = units

        api_response = FREDGetApiRequest(payload).excute()

        value = None
        if api_response.status_code == requests.codes.ok:
            if api_response.json()['observations']:
                value = api_response.json()['observations'][0]['value']
            else:
                print('Failed to get value.')
        elif api_response.status_code == requests.codes.too_many_requests:
            print('Too many requests.')
        else:
            print('Failed to get response.')

        return float(value)
