

## Cteate C++ Class




### 013 Pickup Objective Actor

* `bool bIsCarryingObkective // 是否携带目标物体，公开到蓝图` 
* `Actor` 类中的`NotifyActorBeginOverlap(AActor* OtherActor)`，`OtherActor`代表经过它的`Actor`
* 逻辑：
  * 判断经过的是否是`FPSCharacter`, 设置`bIsCarryingObjective`值为真， 销毁`Objective Actor` 

### 014 Setup Objective UI with UMG

* 新建UI： `Content`->`UI`->`右击`->`User Interface`->`Widget Blueprint`->`WBP_Objectiveinfo`
* `WBP_Objectiveinfo`：
  * 添加`text`,用于像玩家提示信息`Find and Loot the objective item`
* 新建`HUD`：`Content`->`Buleprint`->`new HUD`->`FPSHUD`->`BP_HUD` 
* 蓝图中使用`Wiget`
  * `BeginPlay`->`Creat Wiget`:`Select Class` = `WBP_Objectiveinfo`
  * `Add to Viewport`
  * 新建`BP_GameMode` Set Default HUD = `BP-HUD`
  * `World` GameMode Override = `BP_GameModeBase`
* 在`BWP_Objectiveinfo`中对`text`进行`bind`=`Create New Bind`
  * `New Variables` = `Text GetObjective`
  * `Select`节点= `if else`,输入`Index(bool)` 输出两个变量，`False` 失败时，`True` 成功时。 
* 碰撞系统
  *  `Object Type` 物体类型
      > 物体类型Object Type是一个分类，一些响应同样碰撞效果的物体可以划分到同一个类中。比如地面，我们希望它对任何场景物体都阻碍（Block）（虚幻4.8把这个翻译为区块….），就是说任何物体和地面的碰撞都是地面阻止物体穿过自己（如果物体有速度的和地面碰撞，仅仅设置碰撞为block并不能产生反弹效果，需要结合物体模拟设置）。
  *  `Collision Responses` 碰撞响应
      > 碰撞响应（Collision Responses）有三种：Ignore，Overlap，Block，译为忽略，重叠，区块（这个翻译为阻碍、阻挡更加易于理解）。Block就是阻止物体穿过自己，当别的物体以一定速度撞上自己时，两者不会发生互相重叠的情况（需要两者都设置为Block），至于它们如何模拟物理反应（反弹效果），需要另外设置。<br>
      Overlap和Ignore都会让两个物体互相重叠、穿过。它们的区别是当设置为overlap时，两物体开始和结束overlap（重叠）时，可以激活事件ReceiveBeginOverlap and ReceiveEndOverlap。


### 017 Create Extraction Zone

 * `FPSExtractionZone`
   * 盒子组件`UBoxComponent`
   * 重叠事件绑定:`OnComponentBeginOverlap.AddDynamic(this, &xxx)`
  