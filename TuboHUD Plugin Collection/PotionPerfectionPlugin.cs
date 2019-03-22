//css_reference C:\v9.0.dll;
// https://github.com/User5981/Resu
// Potion Perfection plugin for TurboHUD version 17/01/2018 14:32
 
using System;
using System.Globalization;
using System.Linq;
using Turbo.Plugins.Default;
using System.Collections.Generic;

namespace Turbo.Plugins.Default
{
    public class PotionPerfectionPlugin : BasePlugin, IInGameTopPainter
    {
        public bool InventoryNumbers { get; set; }
       
        public IBrush ShadowBrush { get; set; }
        public IFont PotionPerfectionFont { get; set; }
       
       
        public PotionPerfectionPlugin()
        {
            Enabled = true;

        }
 
        public override void Load(IController hud)
        {
            base.Load(hud);
            
            
            ShadowBrush = Hud.Render.CreateBrush(175, 0, 0, 0, -1.6f);
            PotionPerfectionFont = Hud.Render.CreateFont("arial", 7, 255, 0, 0, 0, true, false, false);
            PotionPerfectionFont.SetShadowBrush(200, 255, 255, 255, true);

        }
 
        private int stashTabAbs;
 
        public void PaintTopInGame(ClipState clipState)
        {
           
            if (clipState == ClipState.Inventory)
            {
                stashTabAbs = Hud.Inventory.SelectedStashTabIndex + Hud.Inventory.SelectedStashPageIndex * Hud.Inventory.MaxStashTabCountPerPage;
 
                foreach (var item in Hud.Game.Items)
                {
                    if (item.SnoItem.MainGroupCode != "potion") continue;
                    if (item.Location == ItemLocation.Stash)
                    {
                        if ((item.InventoryY / 10) != stashTabAbs) continue;
                    }
                    if ((item.InventoryX < 0) || (item.InventoryY < 0)) continue;
     
                    var rect = Hud.Inventory.GetItemRect(item);
                    if (rect == System.Drawing.RectangleF.Empty) continue;
     
                    DrawPotionPerfection(item, rect);
                }
            }
                
                
        }
 
 
        private void DrawPotionPerfection(IItem item, System.Drawing.RectangleF rect)
        {

         foreach (var perfection in item.Perfections)
                
                {
                 var CurStat = perfection.Cur;
                 var MaxStat = perfection.Max;
                 var Percentage = Math.Truncate( (( CurStat / MaxStat )*100)*10)/10;
                 var text = Percentage.ToString();
                 var layout = PotionPerfectionFont.GetTextLayout(text); 
                 if (Percentage != 100) PotionPerfectionFont.DrawText(layout, rect.Right - layout.Metrics.Width - 3, rect.Bottom - layout.Metrics.Height - 3);
                }
        }
    }
}
