

## Cteate C++ Class




### 013 Pickup Objective Actor

* `bool bIsCarryingObkective // 是否携带目标物体，公开到蓝图` 
* `Actor` 类中的`NotifyActorBeginOverlap(AActor* OtherActor)`，`OtherActor`代表经过它的`Actor`
* 逻辑：
  * 判断经过的是否是`FPSCharacter`, 设置`bIsCarryingObkective`值为真， 销毁`Objective Actor` 

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