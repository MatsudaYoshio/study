from pathlib import Path
import requests, os, bs4

SEARCH_WORD = "pikachu"
SAVE_PATH = Path.home()/"~~~"/"---"

def main():
    res = requests.get("https://imgur.com/search/score?q=" + SEARCH_WORD)
    res.raise_for_status()

    soup = bs4.BeautifulSoup(res.text)

    elements = soup.find_all("img")

    for e in elements:
        image_url = "https:" + str(e["src"])
        res = requests.get(image_url)
        res.raise_for_status()

        print("Downloading from " +  image_url)
        
        with open(os.path.join(SAVE_PATH, os.path.basename(image_url)), 'wb') as image_file:
            for chunk in res.iter_content(100000):
                image_file.write(chunk)
        
if __name__ == '__main__':
    main()
