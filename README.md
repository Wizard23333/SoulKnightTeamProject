# Soul Knight Project 项目说明文档

> 同济大学2019级c++面向对象荣誉课课程项目

## 项目信息

- 选题：**元气骑士**

- 项目成员：

  - 1953981 吴昊天
  - 1950072 郑柯凡
  - 1952728 杨梓浩
  - 1951326 赵敏
 
- 项目地址：<https://github.com/Wizard23333/SoulKnightTeamProject>
-小组贡献比例：
   
   -吴昊天：
   -郑柯凡：
   -赵敏：
   -杨梓浩：
-项目进度时间线：

   

## 项目开发相关

- 游戏引擎：**coco2d-x 3.17.2/4.0**

- 小组分工：

|   姓名   |                     分工内容                      |
| :----: | :------------------------------------------------------: |
|  吴昊天  |  Actor基类及其子类设计、精灵怪物设计、战斗信息设计     |
|   赵敏   |  安全地图设计、素材收集、音效系统                      |
|  杨梓浩  |  冒险地图设计                                          |
|  郑柯凡  |  游戏道具设计                                          |



- 类的设计及继承关系：
  
  | 基类  |                   子类                     |
  |:-----:|:------------------------------------------:|
  |       |   |
  |       |   | 



- 评分项完成度

  - 基础功能

    - [x] 游戏开始界面、背景音乐、音量控制、暂停及恢复功能、退出功能

    - [x] 键盘控制

    - [x] 支持两类武器：包括近战武器和远程武器、两种近战武器、两种远程武器

    - [x] 支持近程、远程小兵

    - [x] 支持两种道具：回复生命、回复法力；可通过击败怪物获取

    - [x] 支持宝箱机制，开启后可获得道具

    - [x] 支持安全地图和冒险地图

    - [x] 支持安全地图查看武器和敌人信息

    - [x] 支持小兵ai

    - [x] 主角死亡返回安全地图

    - [x] 包含三个普通关卡和一个boss关卡

  - 进阶功能

    - [x] 支持金币机制，击败怪物即可获得金币

    - [x] 支持boss型敌人

    - [x] 支持秘籍机制



  - C++新特性

    - [x] 类型推断

    - [x] 基于范围的for循环

    - [x] 智能指针

  - 其他亮点



    - [x] 游戏还原度高

      - 英雄形象、怪物形象等与元气骑士游戏还原度高（多为原始模型图）






    - [x] 细节丰富、逻辑正确


      - 玩家在拾取道具、查看信息同时无法移动

      - 玩家及小兵普通攻击的投掷物始终指向目标

      - 释放攻击鼠标出现辅助瞄准点，武器释放的方位由英雄->鼠标瞄准点向量方向决定

      - 英雄及小兵普通攻击及释放技能时保证英雄及小兵始终朝向攻击目标

      - 优化我方精灵撞击墙面时的自动回弹



    
```c++
/*
- 代码亮点







  1. Const.h头文件的使用







     将游戏里关于英雄、小兵、防御塔等常量属性放在`Const.h`头文件中







  ```c++



    #define TOWER_MIN_ATTACK_INTERVAL	  2



    #define TOWER_HP					      8000



    #define TOWER_ATTACK_RADIUS            500



    #define TOWER_ARMOR				      300



    #define TOWER_MAGIC_DEFNESE            100



    #define TOWER_ATTACK				      470



  ```







  2. LoadingScene 类的使用







     将游戏中需要播放的动画在打开游戏时预加载，减少游戏时的卡顿。







  ```c++



   auto animation_02 = Animation::create();



   	for (int i = 1; i < 4; ++i)



   	{



   		animation_02->addSpriteFrameWithFileName



               (StringUtils::format("pictures\\hero\\%s\\%supRight%d.png", 



                                    heroName.getCString(), 



                                    heroName.getCString(), i));



   	}



   	AnimationCache::getInstance()->addAnimation(animation_02, 



                        StringUtils::format("%sMoveUpRight", heroName.getCString()));



  ```







  3. AI路径的标注工具







  ```python



       if mode == 0 and event == cv2.EVENT_LBUTTONDOWN:



           if (img[y][x].tolist()== COLOR_AVAI):



               print("Point左键点击", img[y][x].tolist())



               if pnts.count([x//MULTIPLE,y//MULTIPLE]) == 0:



                   pnts.append([x//MULTIPLE,y//MULTIPLE])



                   print(pnts)



                   #print(Graph[:len(pnts)][:len(pnts)])



                   cv2.rectangle(img, (x//MULTIPLE*MULTIPLE, y//MULTIPLE*MULTIPLE), (x//MULTIPLE*MULTIPLE+MULTIPLE, y//MULTIPLE*MULTIPLE+MULTIPLE), COLOR_POINT, -1)



                   SaveHis()



  ```







  4. 多线程的使用







  ```c++



   		boost::thread t(boost::bind(&boost::asio::io_context::run, io_context));



   		t.detach();



  ```







  5. PLIST文件的使用







  ```xml



           <key>HouYi</key>



           <dict>



               <key>HPRecoverRate</key>



               <integer>9</integer>



               <key>MPRecoverRate</key>



               <integer>4</integer>



               <key>MovingSpeed</key>



               <integer>360</integer>



           </dict>



  ```
  ```
  */







