from selenium import webdriver
import time

USERNAME = ""
PASSWORD = ""
TO_ADRESS = ""
SUBJECT = "TEST"
MAIN_TEXT = "test"

def main():
    browser = webdriver.Chrome()

    # yahooアカウントにログイン
    browser.get("https://www.yahoo.co.jp/")
    browser.find_element_by_link_text("ログイン").click()
    browser.implicitly_wait(5)
    browser.find_element_by_id("username").send_keys(USERNAME)
    browser.implicitly_wait(5)
    browser.find_element_by_id("btnNext").click()
    time.sleep(2)
    browser.find_element_by_id("passwd").send_keys(PASSWORD)
    time.sleep(2)
    browser.find_element_by_id("persistency").click() # ログインしたままにするのチェックを外す
    browser.implicitly_wait(5)
    browser.find_element_by_id("btnSubmit").click()

    browser.implicitly_wait(5)

    # 新しいメールを作成して送信
    browser.find_element_by_class_name("Personalbox__noticeLink").click()
    browser.implicitly_wait(5)
    browser.find_element_by_class_name("email").click()
    browser.implicitly_wait(5)
    browser.find_element_by_id("to-field").send_keys(TO_ADRESS)
    browser.find_element_by_id("subject-field").send_keys(SUBJECT)
    browser.switch_to_frame(browser.find_element_by_xpath("//iframe[@border='0']"))
    browser.find_element_by_xpath("/html/body").send_keys(MAIN_TEXT)
    browser.switch_to.window(browser.window_handles[0])
    browser.find_element_by_xpath("//a[@href='/app/minty/sendconfirm']").click()
    time.sleep(10)
    
if __name__ == '__main__':
    main()
