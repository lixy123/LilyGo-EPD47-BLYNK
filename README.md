# LilyGo-EPD47-BLYNK
 <b>利用BLYNK 技术实现墨水屏信息留言及播报语音 </b><br/>
   我们身边的信息无处不在，逛商场，坐地铁，电梯内，看手机视频，办公室等处都会被动接收到大量信息，然而，这些大部分信息对我们何用？<br/>
   信息只在合适的时间，地点，人身上才能发挥最大化的价值, 否则与垃圾无异。我设计打造了一个个人专属的信息接收系统，自由配置对个人预期有价值的信息源，在合适的时间，地点发送给自己。地点包括家里，办公室等等. 这样才是发挥信息价值的最佳选择。 <br/>
同时，虽然也可以将信息接收端用手机APP实现，但考虑到手机承载功能太多，并不是一个选择。 <br/>

   <b>技术方案及功能:</b> <br/>
        功能划分为消息显示，消息发送两部分。 技术上用了非常经济高效的blynk协议，该协议能让消息无阻碍， 不用考虑内网，外网问题。 该协议开放性很好，可以采用HTTP协议与第三方互联，可以很容易和消息推送云服务集成.

   <b>硬件及需求:</b> <br/>
         墨水屏, 信息发送器，消息源 <br/>
         A.墨水屏主控要求支持休眠节能模式，这样不需频繁充电，且大小合适，外表要好看，能随意摆放，例如磁吸在门背后，冰箱门，放置床头等.  <br/>
         B.消息发送器是处理blynk信息的部件，夹在墨水屏与信息源中间，起到承上启下作用。设计这一部件是为了帮助墨水屏降低能耗。如果墨水屏一直联网，则电池可能支持不了1天。墨水屏随处摆放会成问题。采用它后，墨水屏就能在大部分时间休眠状态（耗电也存在，但极少），仅在需要显示信息时才唤醒耗电，几个月才需一次电池充电。  <br/>
         C.消息源可以是我们平时拿的手机，网上的云服务器, 甚至是树莓派等。特别一提的是云服务器中的 IFTTT,它的全称是 If this then that，意思是“如果这样，那么就那样",  可以将信息在合适时机发送给你，例如天气异常变化了，家里的门在不正常时间打开了，到了该起床或上班的时间。以上条件达到后可以发送电子邮件，短信息，手机消息提醒，墨水屏显示提醒，甚至让墨水屏朗读出文字。 <br/>
         
<b>用户使用深度发展预测：</b> <br/>
随着本系统的使用，一些用户使用深度会加深，也有一些用户会认为本系统没有价值而放弃。<br/>
<b>1. 初级，偶尔记事留言</b> <br/>
利用手机输入文字，推送需要提醒记事的文字到墨水屏显示，甚至文字播放。<br/>
慢慢体会熟悉此系统的好处，并向下一需求发展。<br/>

<b>2. 中级，信息自动化推送显示</b> <br/>
利用blynk的HTTP协议，利用云服务器或树莓派设计一些自动化消息发送器。尝试推送一些格言警钟，天气变化，生日提醒，健身计划，英文单词学习，记事安排等到墨水屏.<br/>
享受完自动化信息的好处后，有可能会感觉到1个显示屏不够用，因为显示屏放在不同的地点有不同的场景，需要显示的内容会不一样。同时可能会期望有更多的定制化自动化信息服务.<br/>

<b>3.高级，IFTTT</b> <br/>
能更容易的设计出更多的 “如果，那么” 的信息规则。有很多人提供了易用性很好的规则。可通过webhooks通过云服务将信息推送到墨水屏显示.<br/>

注：因为用户懒得购物，促进了电商的兴起。因为用户懒得出门用餐，促进了外卖快递的兴起。未来有无可能因为用户懒得对生活计划，会出现生活计划安排师的职业角色啊？<br/>


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
   
   关于如何用树莓派或云服务器和手机一样推送信息至墨水屏参考： <br/>
   https://blynkapi.docs.apiary.io/#reference/0/set-widget-property-via-get <br/>

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

   4.迅飞TTS模块（可选）<br/>
   如果有连接，则支持在收到sp:打头文字信息时播放文字的功能。否则不支持此功能.<br/>
   
<b>三.软件</b><br/>
1.epd47_blue_waker_show_txt_speaker_i2c (蓝牙从机-外设)<br/>
烧录到LilyGo-EPD47墨水屏，实现墨水屏电池供电情境下, 平时休眠,按需显示<br/>
软件: arduino 1.8.13<br/>
库文件:<br/>
https://github.com/espressif/arduino-esp32 版本:1.0.6<br/>
https://github.com/Xinyuan-LilyGO/LilyGo-EPD47 最新版本<br/>
https://github.com/bblanchon/ArduinoJson 版本: 6<br/>
https://github.com/ivanseidel/LinkedList 最新版本<br/>
开发板选择：ESP32 Dev Module<br/>
分区：Huge APP<br/>

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
4.如果播放出文字<br/>
   如果墨水屏连接了i2c的迅飞TTS模块，当接收到 sp:打头的文字，会播放sp:后的文字，而不是显示<br/>
  
<b>五.补充</b> <br/>
1.手机APP不需要与esp32在同一个局域网内。<br/>
2.LilyGo-EPD47墨水屏与esp32蓝牙通讯,建议两者距离在2-5米内<br/>
3.常供电的esp32工作时电流约40-80ma<br/>
4.LilyGo-EPD47墨水屏平时休眠电流约0.5ma左右(估算)<br/>
5.blynk服务器在国外，偶尔会连接不上，用起来不可靠，可考虑自建国内的blynk云服务器，稳定性和速度会更好<br/>


