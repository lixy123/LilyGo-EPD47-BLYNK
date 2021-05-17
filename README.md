# LilyGo-EPD47-BLYNK
利用BLYNK 技术进行手机/电脑到墨水屏留言

一.功能：   
   利用BLYNK 技术进行手机/电脑到墨水屏留言
   思路:
   1.手机APP与BLYNK服务器相连,将信息发到BLYNK服务器.
   2.保持网络连接的ESP32连接blynk服务器，实时接收blynk服务器发来的文字信息,通过蓝牙唤醒并转发信息给墨水屏
   3.墨水屏平时休眠,当收到ble蓝牙信号后唤醒，收到的文字进行显示, 显示完成立即休眠.
     
   技术特性：
   1.能用手机在任意地方发出信息,实时将文字信息推送并显示到墨水屏
   2.留言用的墨水屏需要足够大,单字能在1米外看清,至少能显示 6行,每行20字左右. 
   3.最适合墨水屏摆放处多半没有市电,最好是电池供电,不要经常充电.最好3个月或半年充一次电.
   
   经过一段时间的硬件选型和尝试,基本达到了预期.

二.主要硬件清单
   1.lilygo-epd47*1 + HC08 *1 + 电池*1 (显示终端)
     指标:
       休眠时整体电流<1ma
       唤醒时间<2秒
       显示文字用时 <3秒
       用电: 1500ma的电池, 供电约3月
       
   2.ESP32模块 *1 (信息转发器)
     指标:
       稳定性：信息转发成功率>99%
       用电： 不考虑用电池，市电

三.软件
1.epd47_blue_waker (蓝牙从机-外设)
烧录到LilyGo-EPD47墨水屏，实现墨水屏电池供电情境下, 平时休眠,按需显示。
软件: arduino 1.8.13
库文件:
https://github.com/espressif/arduino-esp32 版本:1.0.6
https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library 最新版本, 仅为了用到它定义的开发板
https://github.com/Xinyuan-LilyGO/LilyGo-EPD47 最新版本
https://github.com/bblanchon/ArduinoJson 版本: 6
https://github.com/ivanseidel/LinkedList 最新版本
开发板选择：TTGO-T-WATCH

2.epd47_blue_waker_center_blynk (blynk技术将消息文字推送到墨水屏显示)
烧录到普通的ESP32模块上, 
软件: arduino 1.8.13
库文件:
https://github.com/espressif/arduino-esp32 版本:1.0.6
开发板选择：ESP32 DEV Module
编译分区：HUGE APP

四.用法
1.手机APP安装blynk,并配置项目
  新建项目,硬件:esp32，连接:wifi,添加如下2个小部件
  V4: Text Input, 字长限制改成200
  V6：Labeled Value, PUSH
2.烧录完程序1的LilyGo-EPD47墨水屏接电池,上电
3.烧录完程序2的esp32上电
  首次运行时ESP32需要配置配置wifi连接，代码中用到了 ESP32 SmartConfig 配网技术,
  参考:https://www.zhangtaidong.cn/archives/124/ 微信扫描配置wifi网络.否则会每120秒重启,无法进入主功能.
  以上如果均正常，手机APP上启动新建的项目会发现esp32处于上线状态，在输入部件输入文字并回车，约5秒左右，文字会显示到墨水屏
注： 
  手机APP不需要与esp32在同一个局域网内。
  LilyGo-EPD47墨水屏与esp32是蓝牙通讯,距离在2-5内
  常供电的esp32电流约40-80ma左右
  LilyGo-EPD47墨水屏平时休眠时电流约0.5ma左右(估算)
  
五.其它
blynk服务器在国外，偶尔会连接不上，用起来不可靠，可考虑自建国内的blynk云服务器，稳定性和速度会更好


