# xiaotian_Epaper

**一款语音控制的墨水屏桌面助手**

**具备时间显示、倒计时事件显示、累积事件显示、语音控制功能**

**一款动动嘴就能交互的极简风桌面摆件！**

**组成：** 墨水屏、stm32、vc02语音模块、实时时钟

**使用软件：** cubeide1.16.1、lceda专业版、solidworks2024、keyshot2024



**<font color='RedOrange'>完整资料：</font>** **已上传**github-[Xiaotian_Epaper](https://github.com/Juno-cyber/Xiaotian_Epaper)，gitee-[Xiaotian_Epaper](https://gitee.com/Juno-cyber/Xiaotian_Epaper)，oshwhub-[电路设计](https://oshwhub.com/juno_eda/xiaoshi_epaper)

**<font color='RedOrange'>视频：</font>**[[开源]墨水屏桌面备忘录！](https://www.bilibili.com/video/BV1hEdBY6EPM/?vd_source=bac4ee29cb575aa9bf0947bee030705f)

**<font color='RedOrange'>BOM清单：</font>**`1.Hadware\BOM清单2024-12-14.xlsx`

**<font color='RedOrange'>更新日志：</font>** 

1. 2025.5.16：解决了偶然出现的秒计时超出60导致计时停止问题，优化了时间自动更新（若编译时间超前当前时间或当前时间大于编译时间20年则更新为编译时间）
1. 2025.4.13：添加scene3红黑显示demo，为”时间时加一“添加边界限制；更新了3D结构文件，删除了需要内嵌螺母的我外壳版本；pcb完善了丝印；
1. 2025.2.11：首次烧录时根据系统编译时间自动更新时钟芯片时间
1. 2025.1.18：更新bom表中黑白红墨水屏器件链接，更新程序，添加二次开发教程
1. 2025.1.5：添加pcb焊接建议，bom表中增加了我使用的下载器购买链接
1. 2024.12.28：添加黑白红墨水屏供选择，版本v0.0.2
1. 2024.12.13：首次上传，版本v0.0.1

![IMG_20250413_093734](README.assets/IMG_20250413_093734.jpg)

![IMG_20250413_093706](README.assets/IMG_20250413_093706.jpg)

![微信图片_20250413101005](README.assets/微信图片_20250413101005.jpg)

| 序号 | 文件名       | 描述              |
| ---- | ------------ | ----------------- |
| 1    | Hardware     | 硬件设计，BOM清单 |
| 2    | Firmware     | 固件文件          |
| 3    | Software     | 软件程序          |
| 4    | CAD_Model    | 模型文件          |
| 5    | Docs         | 文档              |
| 6    | Tools        | 附带工具          |
| 7    | img          | 输出图片          |
| 8    | REDME.assets | REDME中的图片     |

## 控制指令

**语音控制指令集**

| 命令词             | 回复语                                                       | 备注   |
| ------------------ | ------------------------------------------------------------ | ------ |
| 请介绍你自己       | 你好我叫小天 我是一个桌面助手<br /> 你可以通过语音和我进行交互<br /> 你可以说浇过花了 浇过水了 更改时间 更换图片<br /> 有什么需要尽管给我说 | 需唤醒 |
| 你好小天\|小天小天 | 随时待命                                                     | 唤醒词 |
| 写完日记了         | 记录每一天                                                   | 需唤醒 |
| 看完书了           | 日拱一卒功不唐捐                                             | 需唤醒 |
| 加过水了           | 下次早点浇                                                   | 需唤醒 |
| 坛子加过水了       | 美味需要时间酝酿                                             | 需唤醒 |
| 吃了海底捞         | 发工资了吗又吃海底捞                                         | 需唤醒 |
| 更改时间           | 想要调整时间你可以说时间年加一或者时间年减一                 | 需唤醒 |
| 时间年加一         |                                                              | 需唤醒 |
| 时间年减一         |                                                              | 需唤醒 |
| 时间月加一         |                                                              | 需唤醒 |
| 时间月减一         |                                                              | 需唤醒 |
| 时间日加一         |                                                              | 需唤醒 |
| 时间日减一         |                                                              | 需唤醒 |
| 时间时加一         |                                                              | 需唤醒 |
| 时间时减一         |                                                              | 需唤醒 |
| 时间分加一         |                                                              | 需唤醒 |
| 时间分减一         |                                                              | 需唤醒 |
| 更换图片           | 已经更换照片                                                 | 需唤醒 |

## 器件选型

**完整的bom清单在github和gitee工程中**：`Xiaotian_Epaper\1.Hadware\BOM清单2024-12-14.xlsx`

零件可在立创商城或者淘宝购买，哪里便宜在哪里买就好了

**墨水屏[Epaper](https://item.taobao.com/item.htm?abbucket=20&id=520630517588&ns=1&pisk=g_cI30bxHMjQWFIi-HLafGQtyzPSO0OVAaa-o4CFyWFL2AgmVk8kKWk_Vcn_v68HK8ESxWeoLurUV7gocF-2gIun-72v0nRVUCjLESjR2JIzWCUUNydB_d8K-7VJ0N5J3IgnDvrwH6U8WFazzzBK2JeOBrrTJTBK2leTkrSLw7nJ55U7l9C8J6UTWzqOpzF8yl3Tuzsdp_CJ5VEgy7E-IK1_ypaxRFunZPNd6S3Lf_C-9Q2QciEgSPl_cJEYBl1-7faQdo3IT1HfiPhZ1-yNzLVtoAoL5SONpS3semMxqKWgO4HKqRiHjOZZBX082J_RiViE6qUsSMBLlWZQHXeGo10aeAG_TXKlnVu_v-NZQdxUUWiIno2pIhmS5ko-ORIBbukq7XesDh5sq8MmzziBO6nA4D54ckDFFNwcNPZ25F6lESmPtqQUVClupP4B0FT1xT2LSPZ25F6lEJUgRq865MXl.&priceTId=2147bfb017340128577698168e3e44&skuId=3863425440922&spm=a21n57.1.hoverItem.3&utparam=%7B%22aplus_abtest%22%3A%229007f57ddb131b74f319c38ba1bcda2a%22%7D&xxc=taobaoSearch)：**

分辨率296x128像素 、2.9寸、黑白

刷新方式：全屏刷新/局部刷新（4灰阶不支持局刷）

刷新时间：全刷3秒，局刷0.6秒

据说无故障刷新次数为100w次，我设置每分钟刷新一次，那这样算，能够用两年，想想也还有点短

![image-20241114215437317](README.assets/image-20241114215437317.png)

**stm32f103cbt6**

72M主频，基本外设丰富，特别的是128k flash，对于当前所选墨水屏分辨率来说

一张全屏照片大小=296x128/8=4.7k，即使考虑到用上freeRTOS也可以无压力存20来张图像，并且往往无需全屏图像，对于个人开发来说完全够用了

**vc02语音模块**

一款低成本纯离线语音识别模组，**简单说就是写好对答语句，说特定语句执行特定功能**，这里使用时，说出特定语句发送串口指令到主控进行任务控制。支持150条本地指令离线识别，支持RTOS轻量级系统，具有丰富的外围接口，以及简单友好的[客制化工具](http://voice.ai-thinker.com/#/)，该项目放弃了按键交互，完全使用语音模块进行交互，**想干嘛动动嘴就行，君子动口不动手！**

**DS1302**

一款时钟芯片，用于离线时间记录，确保断电后设备仍然能保持时间

## 软件框架

使用cubeide经过初步封装后的freeRTOS，建立了四个任务init、show、run、read，分别执行初始化、显示、主要运行计算、读取任务

为了降低不同任务抢夺共享资源，用了两个无限时间等待的信号量确保run任务正常运行，用了两个事件组分别控制时钟芯片的数据读写和墨水屏的刷新显示

<img src="README.assets/软件框架图.drawio-1734048330920-3.png" alt="软件框架图.drawio" style="zoom: 33%;" />



## 模块数据流

列出硬件组成中模块的电气连接及数据流向

<img src="README.assets/硬件信号流.drawio-1734048262367-1.png" alt="硬件信号流.drawio" style="zoom: 50%;" />

## 3D设计及安装

巧妙地外壳和屏幕壳体设计，使用Bambu的0.12mm打印刚好将屏幕壳体嵌入到外壳中，在底部使用两颗平头螺丝固定，表面外壳看不出什么安装的痕迹，对于审美的一点点强迫症，舒适了！

![keyshot.8](README.assets/keyshot.8.jpg)

安装需要准备以下零件，选购链接已经在BOM表`Xiaotian_Epaper\1.Hadware\BOM清单2024-12-14.xlsx`中给出

![2月12日](README.assets/2月12日.png)

## PCB焊接建议

电容电阻使用的0603封装，需要用到**加热台**和**烙铁**，焊接不当需要拆除的话也需要用到**热风枪**，这里给一些手工焊接的建议，如果采用SMT焊接可以不用看

1. 手工焊接建议开钢网，当然想纯白嫖也可以不开，我没开也焊接成功了，就是难度稍微高一点
2. 首先用加热台焊接元器件最多的一面，但**注意不要一开始就把引脚密集的typeC和stm32主控芯片贴上去**，因为引脚过于密集，但凡锡膏多加一点就会短接，后续用烙铁不好分开，有的同学可能说用助焊剂容易分开，但我以前用的时候发现**助焊剂加热时间久了会导电短路**，有点恐怖。我实际发现比较好的方法是在加热台上等锡膏都融化了，用镊子把粘连的锡抚顺了，然后再放上typeC和stm32主控，成功率提高很多！
3. 焊接好了可以先连接typeC测试串口，能检测到串口一般说明最难的主控和typeC焊接没什么问题，有问题的话先检查用的线是不是只能充电没有信号线，确定是焊接问题，就需要用热风枪吹热拆下来然后再焊接了

**焊接成品如下**，手工抹的锡膏，表面会有一些锡球不那么美观

![b16dd6a19d504836f2a4427307bea4e](README.assets/b16dd6a19d504836f2a4427307bea4e.jpg)

## 程序烧录

**<font color='RedOrange'>参考视频：</font>**[[开源]墨水屏桌面备忘录！](https://www.bilibili.com/video/BV1hEdBY6EPM/?vd_source=bac4ee29cb575aa9bf0947bee030705f)

## 二次开发教程

### 不同墨水屏选择

文件路径：`"Xiaotian_Epaper\3.Software\Xiaotian_Epaper\Libraries\include\EPAPER.h"`

```c
//选择屏幕类型，共适配了两种类型的显示屏，bom表中有列出链接，可以根据自己选择来做选择
#define black_white_red	//使用黑白红墨水屏
//#define black_white			//使用黑白墨水屏
```

### 自己创建新的场景（以主图为例）

1.定义场景名称，路径：`"Xiaotian_Epaper\3.Software\Xiaotian_Epaper\Libraries\include\myfreertos.h"`

```c
// 可以参考定义自己的场景
#define scene1						//显示场景1
//#define scene2						//显示场景2
```

2.在**init_show()**函数中初始化场景，路径`"Xiaotian_Epaper\3.Software\Xiaotian_Epaper\Libraries\mytasks\task_show.c"`

```
void init_show(){

	//****
	
#ifdef scene1
#ifdef black_white_red
	EPD_WhiteScreen_Black();
#else
	EPD_WhiteScreen_White();
#endif
	EPD_W21_Init();
	//white
	EPD_Dis_Part(0, 0, gImage1_white, 296, 128, NEG);
	//right
	EPD_Dis_string(186, 0, time, 32, NEG);
	EPD_Dis_string(200, 32, date, 16, NEG);
	EPD_Dis_Part(210, 48, gImage_love, 32, 32, POS);
	EPD_Dis_string(210 + 32, 56, itoa(date_diff(Time_start, Time_now),temp_itoa,10), 16, NEG);
	EPD_Dis_Part(210, 80, gImage_haidi, 32, 32, NEG);
	EPD_Dis_string(210 + 32, 88, itoa(date_diff(Time_haidilao, Time_now),temp_itoa,10), 16, NEG);
	//middle
	EPD_Dis_Part(85, 0, photo1, 110, 128, POS);
	//	left
	EPD_Dis_power(0, 0, (date_diff(event_power[0], Time_now)>4)?0:4-date_diff(event_power[0], Time_now));
	EPD_Dis_power(0, 32, (date_diff(event_power[1], Time_now)>4)?0:4-date_diff(event_power[1], Time_now));
	EPD_Dis_power(0, 64, (date_diff(event_power[2], Time_now)>4)?0:4-date_diff(event_power[2], Time_now));
	EPD_Dis_power(0, 96, (date_diff(event_power[3], Time_now)>4)?0:4-date_diff(event_power[3], Time_now));
	EPD_Dis_Part(60, 0, gImage_riji, 32, 32, NEG);
	EPD_Dis_Part(60, 32, gImage_dushu, 32, 32, POS);
	EPD_Dis_Part(60, 64, gImage_tanzi, 32, 32, POS);
	EPD_Dis_Part(60, 96, gImage_jiaoshui, 32, 32, POS);
#endif

	//****

}
```

3.在**update_show**()函数中定义更新逻辑，路径`"Xiaotian_Epaper\3.Software\Xiaotian_Epaper\Libraries\mytasks\task_show.c"`

图片数组在`"Xiaotian_Epaper\3.Software\Xiaotian_Epaper\Libraries\EPD_W21\EPAPER.c"`中定义，在`"Xiaotian_Epaper\3.Software\Xiaotian_Epaper\Libraries\include\EPAPER.h"`中使用`extern`命令进行外部声明，可参考现有图片数组更改

**注：图片数组取模具体操作参考后文中工具使用部分**

```c
void update_show()
{
    
	//****
	
#ifdef scene1
	//white
	EPD_Dis_Part(0, 0, gImage1_white, 296, 128, NEG);
	//right
	EPD_Dis_string(186, 0, time, 32, NEG);
	EPD_Dis_string(200, 32, date, 16, NEG);
	EPD_Dis_Part(210, 48, gImage_love, 32, 32, POS);
	EPD_Dis_string(210 + 32, 56, itoa(date_diff(Time_start, Time_now),temp_itoa,10), 16, NEG);
	EPD_Dis_Part(210, 80, gImage_haidi, 32, 32, NEG);
	EPD_Dis_string(210 + 32, 88, itoa(date_diff(Time_haidilao, Time_now),temp_itoa,10), 16, NEG);
	//middle
	EPD_Dis_Part(85, 0, photo1, 110, 128, POS);
	//	left
	EPD_Dis_power(0, 0, (date_diff(event_power[0], Time_now)>4)?0:4-date_diff(event_power[0], Time_now));
	EPD_Dis_power(0, 32, (date_diff(event_power[1], Time_now)>4)?0:4-date_diff(event_power[1], Time_now));
	EPD_Dis_power(0, 64, (date_diff(event_power[2], Time_now)>4)?0:4-date_diff(event_power[2], Time_now));
	EPD_Dis_power(0, 96, (date_diff(event_power[3], Time_now)>4)?0:4-date_diff(event_power[3], Time_now));
	EPD_Dis_Part(60, 0, gImage_riji, 32, 32, NEG);
	EPD_Dis_Part(60, 32, gImage_dushu, 32, 32, POS);
	EPD_Dis_Part(60, 64, gImage_tanzi, 32, 32, POS);
	EPD_Dis_Part(60, 96, gImage_jiaoshui, 32, 32, POS);
#endif

	//****

}
```

### 语音控制指令自定义

vc02的语音控制可以在[安信可平台](http://voice.ai-thinker.com/#/YzsM)进行编辑并生成固件，每条控制指令对应有一个串口发送动作，编辑功能还需要再stm32源码中对应修改

![image-20250413142411475](README.assets/image-20250413142411475.png)

![image-20250413142601448](README.assets/image-20250413142601448.png)

## 工具使用

**1.使用取模软件制作图片数组**

首先了解2.9寸墨水屏显示尺寸为296*128，x方向可按1像素平移，**而y方向只能按8像素平移**（例如设置y=0，实际y=0；设置y=1~7，实际y=7）。以封面为例，主图大小为100x128px，所有小图标为32x32px，二次开发可参考该大小进行布局

![显示布局图](README.assets/显示布局图.png)

取模工具路径：`xiaotian_Epaper\6.Tools\CharacterMatrix 3.0.2.3.exe`

由于厂家给的墨水屏demo是按照x方向排列的，现在需要以y方向排列，因此需要按照以下步骤对图片进行**镜像和旋转**

![图片取模](README.assets/图片取模.png)

得到字模二进制数据后拷贝到文件对应位置即可

![图片取模2](README.assets/图片取模2.png)

**2.vc02烧录工具**：[教程参考](https://blog.csdn.net/Boantong_/article/details/123846788)

专用下载工具路径（文件夹内有使用说明pdf）：`xiaotian_Epaper\6.Tools\hummingbird-m-production-tool\UniOneDownloadTool.exe`

串口烧录工具（测试没下载成功）：`Xiaotian_Epaper\6.Tools\hummingbird-m-update-tool\UniOneUpdateTool.exe`

固件路径：`xiaotian_Epaper\2.Firmware\uni_app_release.bin`

**3.串口助手**：`Xiaotian_Epaper\6.Tools\sscom\sscom5.13.1.exe`

## 字模压缩

### 游程编码压缩字模大小

考虑到嵌入式设备的flash容量有限，对保存的ASCII字模进行一定压缩处理，大大缩减了字模数组所占存储

取模软件取到的字模如下，在进行存储时，黑色区域存储为0x00，那么字模中就有大片的0x00存在，那么你一定能想到一种简单的思路对字模进行压缩。

如“0000000000”=”10个0“，这个思路叫做**游程编码**，其核心思想是通过减少重复数据的存储来实现压缩。在数据序列中，连续出现的相同元素组成的一段被称为一个“游程”。编码时，每个游程被替换为一个表示游程长度和游程值的二元组。例如，在字符串“AAAABBBCCDAA”中，“AAAA”是一个游程，长度为4，可以表示为(4, 'A')。

<img src="README.assets/image-20241213121832314.png" alt="image-20241213121832314" style="zoom:50%;" />

**1.num-char压缩方式**

“AAAABBBCCDAA” =》 (4, 'A')(3, 'B')(2, 'C')(1, 'D')(2, 'A')

这种方式的压缩率**大概是81.89%**

![image-20241123112642943](README.assets/image-20241123112642943.png)

**2.只压缩0x00的方式**

“00000AAAABBBCCDAA” =》 (5, 0x00)"AAAABBBCCDAA"

这种方式压缩率达到**51.19%**，**不过对应的编码和解码就麻烦一点**，这里自己写了一个`xiaotian_Epaper\6.Tools\ed_codem.m`文件进行处理，**项目也采用该方式进行字模压缩**

![image-20241124135917699](README.assets/image-20241124135917699.png)

**字模制作过程：**

先在字模工具中制作完成->生成.c文件用vscode打开->正则表达式进行替换，删除不必要的注释内容，替换成可输入到matlab中的形式->拷贝到ed_codem.m文件中进行运算->拷贝到c程序中

**字模数据处理所用正则表达式：**

```
/\*.*?\*/			搜索所有/*  */括起来的内容 
,(?![^,]*,)			选中所有行最后一个逗号
\n{2}				选中连续的两个换行符
```

## 最后

难度不是很高的一个项目，想锻炼一下贴片焊接、学习stm32设计开发、freeRTOS的同学都可以来试试，我会持续完善更新，期待大家交作业！



## 常见问题













