from selenium import webdriver
from selenium.webdriver.common.keys import Keys

driver = webdriver.Firefox()
driver.get("http://127.0.0.2:5000/")
elem = driver.find_element_by_name("text1")
elem.send_keys("4")
elem = driver.find_element_by_name("text2")
elem.send_keys("4")
	elem.send_keys(Keys.RETURN)
print Keys.RETURN
assert "16" in driver.page_source
driver.close()	
