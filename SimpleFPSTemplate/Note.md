

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
  




## 游戏规则

### 设置任务结束
  
* 目标：任务结束后，我们不希望继续玩家控制器继续控制角色，所以在任务结束之后我们将禁止玩家继续控制角色

``` C++
//FPSExtractionZone.cpp
AFPSCharacter * MyPawn = Cast<AFPSCharacter>(OtherActor);
if(MyPawn && MyPawn->bIsCarryingObjective) {
  AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
  if(GM) {
    GM->CompleteMission(MyPawn);
  }
}
//GetAuthGameMode仅在服务器上有效
```

``` C++ 
// FPSGameMode.h
void CompleteMission(APawn* InstigatorPawn); 

// 函数公开到蓝图实现和处理，可以当作蓝图中的节点使用
UFUNCTION(BlueprintImplementableEvent, Categor = "GameMode")
void OnMissionCompleted(APawn* IstigatorPawn);

// FPSGameMode.cpp
void APFSGameMode::CompleteMission(APawn* InstigatorPawn) {
  if(InstigatorPawn) {
    // 禁用Charactar输入
    InstigatorPawn->DisableInput(nullptr); // Alt+G 观察DisableInput源码
  }
  OnMissionCompleted(InstigatorPawn);
  
}

// Charactor 控制pawn
```

### 添加Extraction反馈
* 添加反馈字样：
* 在`UI`中新建一个控件，命名为`WBP_GameOver` ， 放置一个`Text Box`
* 将`Text Box`放置在屏幕中央，设置一个`Anchors`(锚)， 选择中央。
* `Size To Content` 相对位置
* 添加`Widget`的方法：`BeginPlay`(`OnMissionCompleted`)->`CreateWidgetGameWidget`->`AddtoViewport`

* 添加反馈声音：
``` C++
// FPSExtractionZone.h
UPROPERTY(EditDefaultsOnly, Category = "Sounds")
USoundBase* ObjectiveMissingSound;// 目标物体缺失声音控件


//FPSExtractionZone.cpp
#include "Kismet/GameplayStatics.h"

void HandleOverlap() {
  AFPSCharacter* MyPawn = Case<AFPSCharacter>(OtherActor);
  if(MyPawn == nullptr) {
    return;
  }
  if(Pawn->bIsCarryingObjective) {
  AFPSGameMode* GM = Case<AFPSGameMode>(GetWrold()->GetAuthGameMode());
    if(GM) {
      GM->CompleteMission(MyPawn);
    }
  }
  else {
    // 静态函数， 不属于对象实例， 属于这个类
    UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
  }
}


```
* `Edit->Advanced->Format Selection` 自动代码排版 
* 在蓝图中设置音效文件，即可完成

### 视角切换
> 目标： 在完成任务时，把视角切换到上帝视角
* 蓝图实现：
  * 此时在触发`OnMissionCompleted`函数时，应该完成两件事：
    * 输出提示
    * 切换视角
  * 所以我们在`BP_GameMode`->`OnMissionCompleted`后面添加一个`Sequence`节点,以便完成两件事
  * 获取旧视角：在`BP_GameMode`,我们需要`GetController`并且将其转换为`PlayerController`,以获取旧的视角
  * 添加另外一个视角：创建一个新的Actor命名为`BP_SpectatingViewpoint`设置`StaticMesh`为`Matinee`,选择在游戏中隐藏`Hidden in Game`, 拖入世界中，右键使用`Pilot`调整视角位置
  * 设置视角切换：在`BP_GameMode`使用`GetAllActorOfClass`获得我们创建的`BP_SpectatingViewpoint`,然后用`SetViewTargetwithBlend`节点切换视角:`Target`是目前的视角，`New View Target`是新视角
  
  
* C++ 实现
  ``` C++ 
  //protected:
      UPROPERTY(EditDefaultsOnly, Category = "Spectating")
      TSubclassOf<AActor> SpectatingViewpointClass;



  //FPSGameMode.cpp
  void AFPSGameMode::CompleteMission(APawn* InstigatorPawn) {
    // 传过来的是pawn
    if(InstigatorPawn) {
      InstigatorPawn->DisableInput(InstigatorPawn);
      if(SpectetingViewpointClass) {
        TArray<AActor*> ReturnedActors;
        UGameplayStatics::GetAllActorsOfClass(this, SpactatingViewpointClass, RetrunedActors);

      }
    }
    OnMissionCompleted(InstigatorPawn); 
  }

  ```






### Others
* ConstructorHelpers 静态绑定

### 调用顺序
我们把actor蓝图直接拖入ue关卡中的话，应该会走从磁盘加载的流程。
已位于关卡中的 Actor 使用此路径，如 LoadMap 发生时、或 AddToWorld（从流关卡或子关卡）被调用时。

* 首先调用构造函数，包/关卡中的 Actor 从磁盘中进行加载。
* PostLoad - 在序列化 Actor 从磁盘加载完成后被调用。
* InitializeActorsForPlay
* 为未初始化的 Actor 执行 RouteActorInitialize（包含无缝行程携带）
  * PreInitializeComponents - 在 Actor 的组件上调用
  * InitializeComponent 之前进行调用
  * InitializeComponent - Actor 上定义的每个组件的创建辅助函数。
  * PostInitializeComponents - Actor 的组件初始化后调用
* BeginPlay - 关卡开始后调用