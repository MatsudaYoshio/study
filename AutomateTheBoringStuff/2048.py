from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time

def main():
    browser = webdriver.Chrome()
    
    browser.get("https://gabrielecirulli.github.io/2048/")

    elm = browser.find_element_by_tag_name("html")

    while True :
        elm.send_keys(Keys.ARROW_UP)
        time.sleep(0.1)
        elm.send_keys(Keys.ARROW_RIGHT)
        time.sleep(0.1)
        elm.send_keys(Keys.ARROW_DOWN)
        time.sleep(0.1)
        elm.send_keys(Keys.ARROW_LEFT)
        time.sleep(0.1)
         
        try:
            browser.find_element_by_class_name('game-over')
            break
        except:
            pass
        
if __name__ == '__main__':
    main()
