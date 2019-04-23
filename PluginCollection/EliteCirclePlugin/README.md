# EliteCirclePlugin

Modification and combination of MonsterCirclePlugin (https://github.com/coreyblackgh/HUD-Plugins) and DiadrasFirstGemPlugin (https://github.com/User5981/Resu)

https://www.ownedcore.com/forums/diablo-3/turbohud/turbohud-community-plugins/612786-international-cb-monstercircleplugin.html

https://www.ownedcore.com/forums/diablo-3/turbohud/turbohud-community-plugins/653210-v7-6-international-resu-diadrasfirstgemplugin.html




Installation
------------
Copy **EliteCirclePlugin.cs** to TurboHUD\plugins\Default\

To use this plugin, you need **remove original** version of MonsterCirclePlugin and DiadrasFirstGemPlugin.


Original Features
------------
+ Show circle at elite
+ Shows stacks when you have Bane of the Stricken equipped


Mod Features
------------
+ Remove unnecessary display information
+ Show HP of elite when Elite's HP < 40%
+ Show direction Direction Line to elite when Elite's HP < 20%
+ Code optimization



Screenshot
------------
![](EliteCirclePluginSS.png)




Thông tin về 1 số plugin của TurboHD có sẵn nên xóa
------------

+ (Nếu muốn) Bỏ chụp ảnh khi lên level cho đỡ chật ổ 
Xóa file TurboHUD\plugins\Default\ParagonCapturePlugin.cs

+ (Nếu muốn) Bỏ cái khung thống kê dưới cùng bên phải 
Xóa file TurboHUD\config\ui_default\ui_default_labels_run_stats.xml 
 
+ (Nếu muốn) Bỏ tính năng xem trước thùng đồ cho đỡ rối mắt 
Xóa file TurboHUD\plugins\Default\Inventory\StashPreviewPlugin.cs

+ (Nếu muốn) Bỏ mấy dòng chữ cạnh con boss cho đỡ rối mắt 
Xóa file TurboHUD\plugins\Default\Monsters\EliteMonsterAffixPlugin.cs
Xóa file TurboHUD\plugins\Default\Monsters\DangerousMonsterPlugin.cs

+ (Nếu muốn) Bỏ thông tin bên trên skill bar, nhưng chả bao giờ xem đến
Xóa file  TurboHUD\plugins\Default\LabelLists\AttributeLabelListPlugin.cs : 

+ (Nếu muốn) Bỏ thanh bar thống kê về Exp (Giữa màn hình, bên trên cùng) 
Xóa file  TurboHUD\plugins\Default\LabelLists\TopExperienceStatistics.cs

+ (Nếu muốn) Bỏ mấy cái linh tinh chả bao giờ cần xem
Bỏ cả thư mục TurboHUD\plugins\Default\LabelLists

+ (Nếu muốn) Bỏ mấy ô vuông màu mè linh tinh dưới bình máu
Xóa file  TurboHUD\plugins\Default\DamageBonusPlugin.cs

+ (Nếu muốn) Bỏ việc hiện số đếm ô trống trong Inventory, vì nhìn cái là thấy, chả để làm gì
Xóa file  TurboHUD\plugins\Default\Inventory\InventoryFreeSpacePlugin.cs

+ (Nếu muốn) Bỏ việc đếm BloodShard, vì nhìn cái là thấy, chả để làm gì
Xóa file  TurboHUD\plugins\Default\Inventory\BloodShardPlugin.cs

+ (Nếu muốn) Bỏ ExperienceOverBar ( Cái mặc định của D3 quá ngon rồi, ko cần thay đổi gì cả )
Xóa file  TurboHUD\plugins\Default\ExperienceOverBarPlugin.cs

+ (Nếu muốn) Bỏ Bounty Table, cái này không có ý nghĩa gì cả
Xóa file  TurboHUD\plugins\Default\BountyTablePlugin.cs


+ (Nếu muốn) Bỏ vòng tròng độc, băng, lửa dưới đất, rối mắt, mà đi meta ko cần
Xóa file  TurboHUD\plugins\Default\Monsters\EliteMonsterSkillPlugin.cs


Các hot-key trong TurboHUD
------------
+ F4 bật/tắt TurboHUD
+ F5 bật/tắt bảng thống kê thông tin account
+ F6  bật/tắt bảng thông tin bounty
+ Ctrl + End : Exit TurboHUD
+ Alt + Ctrl + R : Reload



