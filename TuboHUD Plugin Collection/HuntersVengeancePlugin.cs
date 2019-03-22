//css_reference C:\v9.0.dll;
// https://github.com/User5981/Resu
// Hunter's Vengeance Plugin for TurboHUD Version 15/01/2019 22:59

using System;
using System.Collections.Generic;
using Turbo.Plugins.Default;
using System.Linq;

namespace Turbo.Plugins.Default
{

    public class HuntersVengeancePlugin : BasePlugin, ITransparentCollection, IInGameWorldPainter
    {

        public IFont TextFont { get; set; }
        public IBrush OutlineBrush { get; set; }
        public IFader Fader { get; set; }
        public bool permanentCircle { get; set; }
        public string percentDamageBonus { get; set; }
        public int ZeiRank { get; set; }
        public bool ElitesOnlyNumbers { get; set; }
        public int midX { get; set; }
        public int midY { get; set; }
        public WorldDecoratorCollection ZeiMiniMapDecorator { get; set; }
        public WorldDecoratorCollection MiniMapVisorDecorator { get; set; }
        public bool TargetForAll { get; set; }
        
        public HuntersVengeancePlugin()
        {
            Enabled = true;
            permanentCircle = true;
            ElitesOnlyNumbers = true;
            TargetForAll = true;
        }

        public override void Load(IController hud)
        {
            base.Load(hud);
            
            TextFont = Hud.Render.CreateFont("tahoma", 12, 150, 252, 126, 0, true, false, 150, 0, 0, 0, false); // 100
            OutlineBrush = Hud.Render.CreateBrush(30, 252, 126, 0, 3); 
            Fader = new StandardFader(hud, this);
            midX = Hud.Window.Size.Width/2; 
            midY = Hud.Window.Size.Height/2;
            
              ZeiMiniMapDecorator = new WorldDecoratorCollection( 
              new MapShapeDecorator(Hud)
            {
                Brush = Hud.Render.CreateBrush(70, 252, 126, 0, 1),
                ShapePainter = new CircleShapePainter(Hud),
                Radius = 50,
            }
            );
            
            
             MiniMapVisorDecorator = new WorldDecoratorCollection( 
              new MapShapeDecorator(Hud)
            {
                Brush = Hud.Render.CreateBrush(255, 255, 255, 255, 1),
                ShapePainter = new PlusShapePainter(Hud),
                Radius = 10,
            },
            
              new MapShapeDecorator(Hud)
            {
                Brush = Hud.Render.CreateBrush(255, 255, 255, 255, 1),
                ShapePainter = new CircleShapePainter(Hud),
                Radius = 5,
            }
            );
        
            
        }
        
        
        public void PaintWorld(WorldLayer layer)
        {
        //   var hedPlugin = Hud.GetPlugin<HotEnablerDisablerPlugin>();
        //   bool GoOn = hedPlugin.CanIRun(Hud.Game.Me,this.GetType().Name); 
        //   if (!GoOn) return;
            
          bool ZeiActive = false;
          ZeiRank = 0;
          var jewelsLocations = Hud.Game.Items.Where(x => x.Location == ItemLocation.LeftRing || x.Location == ItemLocation.RightRing || x.Location == ItemLocation.Neck);
          foreach (var ZeiLocation in jewelsLocations)
          {
            if (ZeiLocation.SocketCount != 1 || ZeiLocation.ItemsInSocket == null) continue; 
            var Zei = ZeiLocation.ItemsInSocket.FirstOrDefault(); 
            if (Zei == null) continue;
            if (Zei.SnoItem.Sno == 3249733225) {ZeiActive = true; ZeiRank = Zei.JewelRank; break;} else {continue;}
            
          }
          
         
           if (ZeiActive == false) 
            {
             if (TargetForAll)
              {
               if (Hud.Game.IsInTown) return;
               goto TargetOnMinimap;
              }
             else return;
            }
           
           
           
           if (permanentCircle) { if (Hud.Game.IsInTown) return;}
           else
            {
           if (!Hud.Game.Me.InCombat) goto MiniMapCircle;
           else goto TargetOnMinimap;
            }
            

            OutlineBrush.DrawWorldEllipse(50, -1, Hud.Game.Me.FloorCoordinate);
            
             var Smonster = Hud.Game.SelectedMonster2 ?? Hud.Game.SelectedMonster1;
             if ((Smonster == null)) return;
             
             var monsters = Hud.Game.AliveMonsters.Where(monster => monster.Attackable && monster == Smonster);
                foreach (var monster in monsters)
                {
                    if (ElitesOnlyNumbers && !monster.IsElite) continue;
                    var monsterScreenCoordinate = monster.FloorCoordinate.ToScreenCoordinate();
                    percentDamageBonus = "";
                    float gemMaths = 4f + (0.08f*(float)ZeiRank);
                                    
                    if (monster.NormalizedXyDistanceToMe < 50) {percentDamageBonus = "+" + (gemMaths*((float)monster.NormalizedXyDistanceToMe/10)).ToString("0.00") + "%";}  
                    else {percentDamageBonus = "+" + (gemMaths*5f).ToString("0.00") + "% Max!";}
                  
                   float visibleX;
                   float visibleY;
                   float MidX = (float)midX;
                   float MidY = (float)midY;
          
                   if (monsterScreenCoordinate.X > MidX) {visibleX = monsterScreenCoordinate.X - 60f;} else  {visibleX = monsterScreenCoordinate.X + 50f;} 
                   if (monsterScreenCoordinate.Y > MidY) {visibleY = monsterScreenCoordinate.Y - 150f;} else  {visibleY = monsterScreenCoordinate.Y + 50f;}
                  
                   var layout = TextFont.GetTextLayout(percentDamageBonus);
                   TextFont.DrawText(layout, visibleX, visibleY);
                
                }
            
            MiniMapCircle:
            if (Hud.Game.IsInTown) return;
            ZeiMiniMapDecorator.Paint(layer, null, Hud.Game.Me.FloorCoordinate, null);
            TargetOnMinimap:
            var cursorScreenCoord = Hud.Window.CreateScreenCoordinate(Hud.Window.CursorX, Hud.Window.CursorY);
            var visorWorldCoord = cursorScreenCoord.ToWorldCoordinate();
            MiniMapVisorDecorator.Paint(layer, null, visorWorldCoord, null);
           
        }

        public IEnumerable<ITransparent> GetTransparents()
        {
            
            yield return OutlineBrush;
        }
    }

}