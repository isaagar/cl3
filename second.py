from selenium import webdriver
from selenium.webdriver.common.keys import Keys

f=open("file1.txt",'w')
f.write("My name is husen bhagat")
f.close()

driver = webdriver.Firefox()
driver.get("http://127.0.0.1:5000/")
elem1 = driver.find_element_by_name("text1")
elem1.send_keys("My name  is husen Chawla")
elem2 = driver.find_element_by_name("but")
elem2.send_keys(Keys.ENTER)
assert "100" in driver.page_source
driver.close()	
