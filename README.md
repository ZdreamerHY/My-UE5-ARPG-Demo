#  ARPG 战斗Demo

> UE 5.6 + GAS 的第三人称动作战斗Demo，覆盖以下功能：连击、受击、弹刀、死亡、索敌锁定、翻滚、行为树敌人 AI、处决。

**演示视频地址**


---

## 核心系统

- **轻攻击四段连击**：`WaitGameplayEvent` 双监听（ComboCut 开窗 / ComboInput 切段），`bWindowOpen` + `bIsComboSwitching` 状态保护，动画 Notify 驱动窗口，支持输入缓冲与提前输入。
- **GAS 全链路**：GA / AttributeSet / GameplayEffect / GameplayEvent / SetByCaller / ExecutionCalculation 全打通。伤害链路：Overlap → 委托 → 事件 → GA → GE → ExecutionCalc → AttributeSet。
- **锁定 / 索敌**：toggleable GA 管理状态 tag，角色组件 Tick 管理转向；翻滚期间通过状态 tag 暂停锁定转向；BlendSpace 方向轴 Wrap Input 解决八向移动 。
- **翻滚 + Motion Warping**：WarpTarget 的 Location / Rotation 分离控制；正确处理 Rotation Type（Facing 会忽略传入 Rotation）；落点支持"前方有怪提前停"。
- **敌人 AI**：行为树（侧滑走位 + 攻击），BlendSpace 方向/速度双轴驱动。
- **弹刀 / 受击 / 死亡**：弹刀事件正确发送给防御者；死亡 = AttributeSet 广播 Dead tag → GA_Death（AbilityTrigger `OwnedTagAdded` 触发）。
- **处决系统**：眩晕状态检测 → 可处决目标过滤（BoxTrace + HasMatchingGameplayTag）→ 处决蒙太奇。
- **UI**：血条通过 PawnUIInterface 委托广播 + Widget 绑定。


## 技术栈

UE 5.6 / C++/ GAS / 行为树 / Motion Warping / 蓝图与 C++ 混合开发



## 参考与资源声明

- 动画资产与部分音效资产网上找到的，弹刀等音效为AI生成
- 整体架构设计参考一个主题为Warrior的课程

