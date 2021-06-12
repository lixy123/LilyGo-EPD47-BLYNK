# LilyGo-EPD47-BLYNK
 <b>利用BLYNK 技术打造个人专属的信息显示专用机 </b><br/>

   信息无处不在，比如在我们逛商场，坐地铁，电梯内，看手机视频，办公室，餐厅被动听他人聊天等。无疑，这些信息大半都是无用的垃圾信息。几乎对我们没有用处。<br/>
所以我设计打造了一个个人专属的信息接收机. 可以随处摆放在个人空间，例如家里，办公室. 充分发挥信息价值。 <br/>
虽然按目前的技术可以将此功能做成手机APP，考虑到手机承载功能太多，不是一个好的载体。 <br/>

   <b>技术方案及功能:</b> <br/>
        功能上分为消息显示，消息发送。 目前较经济的方式是用 blynk协议来让消息无阻碍传送. 此协议将内网，外网完全打通。 开放的协议， 可通过HTTP协议与外部互联，可以很容易和一些消息推送云服务集成.

   <b>硬件清单:</b> <br/>
         墨水屏, 蓝牙唤醒器,ESP32信息发送器 <br/>
         A.墨水屏要求大小合适，便于随处摆放，例如门背后，冰箱门，床头，且最好不需频繁充电.  <br/>
         B.消息发送器可以是手机，云服务器,树莓派等。特别一提的是IFTTT,它的全称是 If this then that，意思是“如果这样，那么就那样",  可以将信息在合适时机发送给你，例如天气异常变化了，家里的门在不正常时间打开了，到了该起床或上班的时间, 指定发封邮件，短信息，手机提醒，甚至提醒到墨水屏，让墨水屏读出文字等。 <br/>
         
<b>使用深度预测：</b> <br/>
<b>1. 初级，偶尔记事留言</b> <br/>
利用手机输入文字，推送需要提醒记事的文字到墨水屏显示，甚至文字播放。
慢慢体会熟悉此系统的好处，并向下一需求发展.。
<b>2. 中级，信息自动化推送显示</b> <br/>
利用blynk的HTTP协议，利用云服务器或树莓派设计一些自动化消息发送器。尝试推送一些格言警钟，天气变化，生日提醒，健身计划，英文单词学习，记事安排等到墨水屏.
享受完自动化信息的好处后，有可能会感觉到1个显示屏不够用，因为显示屏放在不同的地点有不同的场景，需要显示的内容会不一样。同时可能会期望有更多的定制化自动化信息服务.
<b>3.高级，IFTTT</b> <br/>
能更容易的设计出更多的“如果，那么”的信息规则。有很多人提供了易用性很好的规则。可通过webhooks通过云服务将信息推送到墨水屏显示.
<b>一.功能 </b> <br/>
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
   1.手机 (安装blynk APP) <br/>   
   <img src= 'https://github.com/lixy123/LilyGo-EPD47-HC08/blob/main/blynk_1.jpg?raw=true' /> 
   
   2.ESP32模块 1块 (信息转发器) <br/>
     一般的ESP32模块均可，我用的是这一块:<br/>
      <img src= 'https://github.com/lixy123/LilyGo-EPD47-BLYNK/blob/main/ESP32.jpg?raw=true' />    
     指标:<br/>
       稳定性：信息转发成功率>99%<br/>
       用电：不考虑用电池，市电供电<br/>
       
   3.LILYGO® T5-4.7 inch E-paper ESP32 1块 + HC08 1块 + 电池 1块 (一套显示终端 )<br/>
   <img src= 'https://github.com/lixy123/LilyGo-EPD47-BLYNK/blob/main/blynk_3.jpg?raw=true' />   <br/>
   <img src= 'https://github.com/lixy123/LilyGo-EPD47-HC08/blob/main/blynk_2.jpg?raw=true' />  <br/>
     <b>hc08资料:</b><br/>
     要双晶振版本，否则不支持一级节能模式,省电效果打折扣<br/>
     https://item.taobao.com/item.htm?spm=a1z09.2.0.0.7ff42e8dvTCkln&id=565758589107&_u=hntkjuse1ad<br/>
     http://www.hc01.com/products/6<br/>
     <b>T5-4.7 inch E-paper资料:</b><br/>
     https://item.taobao.com/item.htm?spm=a1z0d.6639537.1997196601.49.2ad47484934hJw&id=634979479882<br/>
     https://github.com/Xinyuan-LilyGO/LilyGo-EPD47 <br/>      
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
       hc08：一级节能模式电流约 6μA ~2.6mA （待机） /1.6mA（工作）<br/>
       T5-4.7 inch E-paper墨水屏待机电流:约0.17ma <br/>
       2模块均休眠时,整体电流实测约 0.3-0.5ma左右 <br/>
       唤醒时间<2秒<br/>
       显示文字用时 <3秒<br/>
       用电: 1500ma的电池, 供电约3月 <br/>

<b>三.软件</b><br/>
1.epd47_blue_waker (蓝牙从机-外设)<br/>
烧录到LilyGo-EPD47墨水屏，实现墨水屏电池供电情境下, 平时休眠,按需显示<br/>
注: 这源码是另一项目:https://github.com/lixy123/LilyGo-EPD47-HC08 的一部分, 包括显示天气,显示日历等功能, 用不着的功能可精简掉. <br/>
软件: arduino 1.8.13<br/>
库文件:<br/>
https://github.com/espressif/arduino-esp32 版本:1.0.6<br/>
https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library 最新版本, 仅为了用到它定义的开发板<br/>
https://github.com/Xinyuan-LilyGO/LilyGo-EPD47 最新版本<br/>
https://github.com/bblanchon/ArduinoJson 版本: 6<br/>
https://github.com/ivanseidel/LinkedList 最新版本<br/>
开发板选择：TTGO-T-WATCH<br/>

2.epd47_blue_waker_center_blynk (blynk技术将消息文字推送到墨水屏显示)<br/>
烧录到普通的ESP32模块上 <br/>
软件: arduino 1.8.13<br/>
库文件:<br/>
https://github.com/espressif/arduino-esp32 版本:1.0.6<br/>
库管理器查找并安装 blynk<br/>
开发板选择：ESP32 DEV Module<br/>
编译分区：HUGE APP<br/>
注：编译代码前，需要用手机APP安装blynk后创建项目获得控制ESP32唯一硬件的key, 赋值这个变量 char auth[] = ""; <br/>
    方法参考:http://m.elecfans.com/article/1003098.html <br/>


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
2.LilyGo-EPD47墨水屏与esp32蓝牙通讯,建议两者距离在2-5米内<br/>
3.常供电的esp32工作时电流约40-80ma<br/>
4.LilyGo-EPD47墨水屏平时休眠电流约0.5ma左右(估算)<br/>
5.blynk服务器在国外，偶尔会连接不上，用起来不可靠，可考虑自建国内的blynk云服务器，稳定性和速度会更好<br/>


