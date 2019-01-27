import requests
import json
from twilio.rest import Client

CITY = "Tokyo"
API_KEY = ""
ACCOUNT_SID = ""
AUTH_TOKEN = ""
MY_TWILIO_NUMBER = ""
MY_CELL_PHONE = ""

def main():
    url = "http://api.openweathermap.org/data/2.5/weather?q={}&APPID={}".format(CITY, API_KEY)
    response = requests.get(url)
    data = json.loads(response.text)

    weather_id = data["weather"][0]["id"]
    if weather_id >= 500 and weather_id < 600:
        twilio_cli = Client(ACCOUNT_SID, AUTH_TOKEN)
        message = twilio_cli.messages.create(body="It's raining("+data["weather"][0]["description"]+"). Don't forget an umbrella.", from_=MY_TWILIO_NUMBER, to=MY_CELL_PHONE)
    
if __name__ == '__main__':
    main()
