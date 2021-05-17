# LilyGo-EPD47-BLYNK
利用BLYNK 技术进行手机/电脑到墨水屏留言

<b>一.功能 </b> 
   利用BLYNK 技术进行手机/电脑到墨水屏留言<br/>
   思路:<br/>
   1.手机APP与BLYNK服务器相连,将信息发到BLYNK服务器.<br/>
   2.保持网络连接的ESP32连接blynk服务器，实时接收blynk服务器发来的文字信息,通过蓝牙唤醒并转发信息给墨水屏<br/>
   3.墨水屏平时休眠,当收到ble蓝牙信号后唤醒，收到的文字进行显示, 显示完成立即休眠.<br/>
     
   技术特性：<br/>
   1.能用手机在任意地方发出信息,实时将文字信息推送并显示到墨水屏<br/>
   2.留言用的墨水屏需要足够大,单字能在1米外看清,至少能显示 6行,每行20字左右. <br/>
   3.最适合墨水屏摆放处多半没有市电,最好是电池供电,不要经常充电.最好3个月或半年充一次电.<br/>
   
   经过一段时间的硬件选型和尝试,基本达到了预期.<br/>

<b>二.硬件</b><br/>
   1.lilygo-epd47 1块 + HC08 1块 + 电池 1块 (一套显示终端 )<br/>
     hc08 要双晶振版本，否则不支持一级节能模式
     引脚连接:<br/>
     lilygo-epd47  hc-08<br/>
       VCC         VCC<br/>
       14          TX<br/>
       15          RX<br/>
       GND         GND<br/>
     注：lilygo-epd47墨水屏进入节能休眠模式后，墨水屏顶端VCC,14，15,GND 插槽处的VCC的3.3V电压输出会中断，不能在此插槽处取电，要从ph2.0或18650处取电<br/>   
     hc08 AT命令预处理:<br/>
     AT+MODE=1        //设置成一级节能模式(必须)<br/>
     AT+NAME=INK_047  //修改蓝牙名称，用于客户端查找蓝牙用<br/>
     AT+LED=0          //关闭led灯，省电 <br/>    
     指标:<br/>
       hc08：一级节能模式电流约 6μA ~2.6mA （待机） /1.6mA（工作）
       整体休眠电流<1ma <br/>
       唤醒时间<2秒<br/>
       显示文字用时 <3秒<br/>
       用电: 1500ma的电池, 供电约3月 <br/>
       
       
   2.ESP32模块 1块 (信息转发器) <br/>
     指标:<br/>
       稳定性：信息转发成功率>99%<br/>
       用电：不考虑用电池，市电供电<br/>
       
   3.手机 (安装blynk APP) <br/>
   
   <img src= 'https://github.com/lixy123/LilyGo-EPD47-HC08/blob/main/blynk_1.jpg?raw=true' /> <br/>
   <img src= 'https://github.com/lixy123/LilyGo-EPD47-HC08/blob/main/blynk_2.jpg?raw=true' /> <br/>
   <img src= 'https://github.com/lixy123/LilyGo-EPD47-BLYNK/blob/main/blynk_3.jpg?raw=true' /> <br/>


<b>三.软件</b><br/>
1.epd47_blue_waker (蓝牙从机-外设)<br/>
烧录到LilyGo-EPD47墨水屏，实现墨水屏电池供电情境下, 平时休眠,按需显示。<br/>
软件: arduino 1.8.13<br/>
库文件:<br/>
https://github.com/espressif/arduino-esp32 版本:1.0.6<br/>
https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library 最新版本, 仅为了用到它定义的开发板<br/>
https://github.com/Xinyuan-LilyGO/LilyGo-EPD47 最新版本<br/>
https://github.com/bblanchon/ArduinoJson 版本: 6<br/>
https://github.com/ivanseidel/LinkedList 最新版本<br/>
开发板选择：TTGO-T-WATCH<br/>

2.epd47_blue_waker_center_blynk (blynk技术将消息文字推送到墨水屏显示)<br/>
烧录到普通的ESP32模块上, <br/>
软件: arduino 1.8.13<br/>
库文件:<br/>
https://github.com/espressif/arduino-esp32 版本:1.0.6<br/>
开发板选择：ESP32 DEV Module<br/>
编译分区：HUGE APP<br/>

<b>四.用法</b><br/>
1.手机APP安装blynk,并配置项目<br/>
  新建项目,硬件:esp32，连接:wifi,添加如下2个小部件<br/>
  V4: Text Input, 字长限制改成200<br/>
  V6：Labeled Value, PUSH<br/>
2.烧录完程序1的LilyGo-EPD47墨水屏接电池,上电<br/>
3.烧录完程序2的esp32上电<br/>
  首次运行时ESP32需要配置配置wifi连接，代码中用到了 ESP32 SmartConfig 配网技术,<br/>
  参考:https://www.zhangtaidong.cn/archives/124/ 微信扫描配置wifi网络.否则会每120秒重启,无法进入主功能.<br/>
  以上如果均正常，手机APP上启动新建的项目会发现esp32处于上线状态，在输入部件输入文字并回车，约5秒左右，文字会显示到墨水屏<br/>
  
<b>五.补充</b> <br/>
1.手机APP不需要与esp32在同一个局域网内。<br/>
2.LilyGo-EPD47墨水屏与esp32是蓝牙通讯,距离在2-5内<br/>
3.常供电的esp32电流约40-80ma左右<br/>
4.LilyGo-EPD47墨水屏平时休眠时电流约0.5ma左右(估算)<br/>
5.blynk服务器在国外，偶尔会连接不上，用起来不可靠，可考虑自建国内的blynk云服务器，稳定性和速度会更好<br/>


