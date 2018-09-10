# SensorBox

1. ArduinoYun 1代全新板子上的韌體存有bug，所以根據下列網站教學，更新到1.5.3 (本動作一塊板子僅需做一次即可，要小心過程不要斷電，會變磚)

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

    easy_install https://files.pythonhosted.org/packages/ae/e8/2340d46ecadb1692a1e455f13f75e596d4eab3d11a57446f08259dee8f02/pip-10.0.1.tar.gz#sha256=f2bd08e0cd1b06e10218feaf6fef299f473ba706582eb3bd9d52203fdbd7ee68


6. 依序執行下列指令

    pip install requests

    opkg install openssh-sftp-server


7. 用SSH FTP上傳下列連結中的  *.py 到root的home目錄下

https://github.com/IoTtalk/SensorBox


8. 修改custom.py 中第三行，X.X.X.X改為所使用的IoTtalk Server IP

    ServerIP = 'X.X.X.X'

9. 在root的home目錄下執行下列指令


    python autoStart.py


11. 用IDE將 下列連結中的 ino檔燒進 Arduino

https://github.com/IoTtalk/SensorBox/tree/master/Firmware


12. 斷電重開，等2分30秒後，板子上的紅燈亮起，表示該板子已成功註冊到IoTtalk上，已經可以使用了。



PS. Arduino Yun Rev2 安裝rquests方法如下

    opkg update
    
    opkg install openssh-sftp-server
    
    opkg install python-pip
    
    pip install requests    (重開機後執行，不然很容易記憶體不足而發生 Memory error)

