# Tổng hợp các plugin hay cho TurboHUD
Đã sửa lại code để tương thích với version mới nhất của TurboHUD

Link download
------------
https://github.com/langmaninternet/DialoIIISupport/archive/master.zip



Mọi người copy vào các plugin đã fix lại thư mục TurboHUD\plugins\Default
------------
+ ElliteBarplugin : Hiện thống kê về các Elite trong vòng 120yard


+ MonstersCountPlugin : Đếm số quái vật trong 120yard/50yard ( Bấm Ctrl để đổi chế độ 120/50)


+ PartyCooldownsPlugin : Hiện Cooldowns của Ignore Pain và Land of Death của đồng đội


+ StrickenPlugin : Hiện số stack của Stricken của mình và đồng đội khi đánh Greater Rift Guardian


+ HuntersVengeancePlugin : Hiện tác dụng của viên Zei's stone of vengeance 


+ PotionPerfectionPlugin : Hiện chất lượng của các bình máu theo phần trăm (Không cần identify)


+ PrimalAncientProbabilityPlugin : Tạm tính tỉ lệ drop Primal hiện tại, không chính xác nhưng có tính tham khảo cao


+ DeluxeShrineLabelsPlugin : Cảnh báo việc mang Nemesis. Nếu bạn mang nems, nó sẽ bảo bạn ăn, nếu ko nó sẽ báo tên người mang nems


+ BattleTagAboveBannerPlugin : Hiện tên người chơi trên cái cờ ở home town. Rất tiện dụng


+ CraftCountPlugin : thông báo nhỏ khi thay đổi tài nguyên hoặc Rift/GRift progress . Rất tiện dụng, ở nhà cũng biết được tiến trình của Rift/GRift


+ GroupGRLevelAdviserPlugin : Lúc mở Rift/GRift thì biết được ai trong Party đã solo được GR bao nhiêu


+ DiadrasFirstGemPlugin : Hiện thông tin của Bane of the Stricken đối với từng con quái


+ ImpalePlugin : Hiện vòng tròn Steady Aim khi di chuyển, đứng im thì mất. Rất tiện dụng


+ PoolState : Hiện thông tin pool của mọi người


+ AriadnesThreadPlugin : Vẽ đường line trên mini map, rất tiện dụng, đặc biệt khi chạy bounty

+ MonsterCirclePlugin : Vẽ vòng tròn dưới chân Elite


Thông tin về 1 số plugin có sẵn
------------

+ (Nếu muốn) Bỏ chụp ảnh khi lên level cho đỡ chật ổ 
Xóa file TurboHUD\plugins\Default\ParagonCapturePlugin.cs

+ (Nếu muốn) Bỏ cái khung thống kê dưới cùng bên phải 
Xóa file TurboHUD\config\ui_default\ui_default_labels_run_stats.xml 
 
+ (Nếu muốn) Bỏ tính năng xem trước thùng đồ cho đỡ rối mắt 
Xóa file TurboHUD\plugins\Default\Inventory\StashPreviewPlugin.cs

+ (Nếu muốn) Bỏ mấy dòng chữ cạnh con boss cho đỡ rối mắt 
TurboHUD\plugins\Default\Monsters\EliteMonsterAffixPlugin.cs

+ (Nếu muốn) Bỏ thông tin bên trên skill bar, nhưng chả bao giờ xem đến
File TurboHUD\plugins\Default\LabelLists\AttributeLabelListPlugin.cs : 

+ (Nếu muốn) Bỏ thanh bar thống kê về Exp (Giữa màn hình, bên trên cùng) 
File TurboHUD\plugins\Default\LabelLists\TopExperienceStatistics.cs

+ (Nếu muốn) Bỏ mấy cái linh tinh
Bỏ cả thư mục TurboHUD\plugins\Default\LabelLists


+ (Nếu muốn) Bỏ mấy ô vuông màu mè linh tinh dưới bình máu
Bỏ cả thư mục TurboHUD\plugins\Default\DamageBonusPlugin.cs




Các hot-key trong TurboHUD
------------
+ F4 bật/tắt TurboHUD
+ F6  bật/tắt bảng thông tin bounty





