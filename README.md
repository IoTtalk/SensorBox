# SensorBox

1. ArduinoYun全新板子上的韌體存有bug，所以根據下列網站教學，更新到1.5.3 (本動作一塊板子僅需做一次即可，要小心過程不要斷電，會變磚)
http://yehnan.blogspot.com/2016/04/arduino-yunopenwrt-yun.html


2. 設定Wifi  連到AP
教學：http://yehnan.blogspot.com/2016/04/arduino-yunwi-fi.html 


3.用Arduino IDE找IP  (電腦也要連到相同一台AP)
 

4. 用ssh軟體連入該IP (例如putty連入)  
帳號為 root   密碼是  arduino


5. 依序執行下列指令
opkg update
opkg install distribute
opkg install python-openssl
easy_install http://pcs.csie.nctu.edu.tw/pip-10.0.1.tar.gz


6. 在home目錄下新增 .pip 目錄，其下建立   pip.conf  檔案(亦即~/.pip/pip.conf)，依序執行下列指令
mkdir .pip
cd .pip
vim pip.config


內容填入  
[global]
trusted-host=mirrors.aliyun.com
index-url=http://mirrors.aliyun.com/pypi/simple/


7. 依序執行下列指令
pip install requests
opkg install openssh-sftp-server


8. 用SSH FTP上傳下列連結中的  *.py 到root的home目錄下
https://github.com/IoTtalk/SensorBox


9. 修改custom.py 中第三行，X.X.X.X改為所使用的IoTtalk Server IP
ServerIP = 'X.X.X.X'


10. 在root的home目錄下執行下列指令
python autoStart.py


11. 用IDE將 下列連結中的 ino檔燒進 Arduino
https://github.com/IoTtalk/SensorBox/tree/master/Firmware


12. 斷電重開，等2分30秒後，板子上的紅燈亮起，表示該板子已成功註冊到IoTtalk上，已經可以使用了。
