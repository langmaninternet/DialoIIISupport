# Tổng hợp các plugin hay cho TurboHUD
Đã sửa lại code để tương thích với version mới nhất của TurboHUD

Link download
------------
https://github.com/langmaninternet/DialoIIISupport/archive/master.zip



Mọi người copy vào các plugin đã fix lại thư mục TurboHUD\plugins\Default
------------

+ EliteCirclePlugin : Vẽ vòng tròn dưới chân Elite, Hiện thống kê về các Elite 
(Xóa MonsterCirclePlugin,DiadrasFirstGemPlugin, trước khi dùng plugin này)

+ MonstersCountPlugin : Đếm số quái vật trong 120yard/50yard ( Bấm Ctrl để đổi chế độ 120/50)

+ PylonLabelsPlugin : Cảnh báo việc mang Nemesis. Nếu bạn mang nems, nó sẽ bảo bạn ăn, nếu ko nó sẽ báo tên người mang nems

+ PoolState : Hiện thông tin pool của mọi người

+ PartyCooldownsPlugin : Hiện Cooldowns của Ignore Pain và Land of Death của đồng đội

+ BattleTagAboveBannerPlugin : Hiện tên người chơi trên cái cờ ở home town. Rất tiện dụng

+ CraftCountPlugin : thông báo nhỏ khi thay đổi tài nguyên hoặc Rift/GRift progress . Rất tiện dụng, ở nhà cũng biết được tiến trình của Rift/GRift

+ StrickenPlugin : Hiện số stack của Stricken của mình và đồng đội khi đánh Greater Rift Guardian

+ HuntersVengeancePlugin : Hiện tác dụng của viên Zei's stone of vengeance 

+ BattleTagAboveBannerPlugin : Hiện tên người chơi trên cái cờ ở home town. Rất tiện dụng

+ CraftCountPlugin : thông báo nhỏ khi thay đổi tài nguyên hoặc Rift/GRift progress . Rất tiện dụng, ở nhà cũng biết được tiến trình của Rift/GRift

+ GRiftPlugin : hiện thời gian giết Rift Guardian




Thông tin về 1 số plugin có sẵn nên xóa bỏ (nếu muốn)
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




