//css_reference C:\v9.0.dll;
// https://github.com/User5981/Resu
// Primal Ancient Probability Plugin for TurboHUD Version 13/08/2018 08:16

using System;
using System.Globalization;
using Turbo.Plugins.Default;
using System.Linq;
using System.Collections.Generic;

namespace Turbo.Plugins.Default
{
    public class PrimalAncientProbabilityPlugin : BasePlugin, IInGameTopPainter, ILootGeneratedHandler
    {
      
        public TopLabelDecorator ancientDecorator { get; set; }
        public TopLabelDecorator primalDecorator { get; set; }
        public string ancientText{ get; set; }
        public string primalText{ get; set; }
        public double ancientMarker{ get; set; }
        public double primalMarker{ get; set; }
        public double legendaryCount{ get; set; }
        public double prevInventoryLegendaryCount { get; set; }
        public double prevInventoryAncientCount { get; set; }
        public double prevInventoryPrimalCount { get; set; }
        public bool RunOnlyOnce { get; set; }
        public HashSet<string> legendaries = new HashSet<string>() {"0"};
        
        public PrimalAncientProbabilityPlugin()
        {
            Enabled = true;
        }
        
        public override void Load(IController hud)
        {
            base.Load(hud);
            ancientText = String.Empty;
            primalText = String.Empty;
            ancientMarker = 0;
            primalMarker = 0;
            legendaryCount = 0;
            prevInventoryLegendaryCount = 0;
            prevInventoryAncientCount = 0;
            prevInventoryPrimalCount = 0;
            RunOnlyOnce = true;
            
        }
        
         public void OnLootGenerated(IItem item, bool gambled)
        {
          if (item != null && item.SnoItem != null && item.SnoItem.MainGroupCode != "gems_unique" && item.SnoItem.MainGroupCode != "potion") 
           {
            string itemID = item.SnoItem.Sno.ToString() + item.CreatedAtInGameTick.ToString();   // item.SnoItem.Sno.ToString() + item.Perfection.ToString(); // item.ItemUniqueId;
            if (item.IsLegendary && !legendaries.Contains(itemID)) legendaryCount++;
            if (item.AncientRank == 1 && !legendaries.Contains(itemID)) ancientMarker = legendaryCount;
            if (item.AncientRank == 2 && !legendaries.Contains(itemID)) primalMarker = legendaryCount;
            if (item.IsLegendary && !legendaries.Contains(itemID)) legendaries.Add(itemID);
           }
        } 
        
        public void OnNewArea(bool newGame, ISnoArea area)
        {
            if (newGame)
            {
                legendaries.Clear();
                legendaries.Add("0");
            }
        }
        
        public void PaintTopInGame(ClipState clipState)
        {
                
            if (Hud.Game.Me.CurrentLevelNormal != 70 && Hud.Game.Me.CurrentLevelNormal > 0)  {ancientMarker = legendaryCount; return;}
            if (Hud.Game.Me.HighestSoloRiftLevel < 70 && Hud.Game.Me.HighestSoloRiftLevel > 0) primalMarker = legendaryCount;
            
            if(RunOnlyOnce)
            {
             if (Hud.Tracker.CurrentAccountToday.DropLegendary != 0 && Hud.Tracker.CurrentAccountYesterday.DropPrimalAncient > 0) 
             {
               legendaryCount = Hud.Tracker.CurrentAccountToday.DropLegendary;
               if (Hud.Tracker.CurrentAccountToday.DropAncient <= 1 && (legendaryCount - Hud.Tracker.CurrentAccountToday.DropAncient) > 100) ancientMarker = 0;
               else 
                   {
                    long DropAncientToday = Hud.Tracker.CurrentAccountToday.DropAncient;
                    if (DropAncientToday == 0) DropAncientToday = 1;
                    ancientMarker = (int)(Hud.Tracker.CurrentAccountToday.DropLegendary - (Hud.Tracker.CurrentAccountToday.DropLegendary/DropAncientToday));
                   }
               if (Hud.Tracker.CurrentAccountToday.DropPrimalAncient <= 1) primalMarker = 0;
               else 
                   {
                    long DropPrimalAncientToday = Hud.Tracker.CurrentAccountToday.DropPrimalAncient;
                    if (DropPrimalAncientToday == 0) DropPrimalAncientToday = 1;   
                    primalMarker = (int)(Hud.Tracker.CurrentAccountToday.DropLegendary - (Hud.Tracker.CurrentAccountToday.DropLegendary/DropPrimalAncientToday));
                   }
             } 
             else if (Hud.Tracker.CurrentAccountYesterday.DropLegendary != 0)
             {
               legendaryCount = Hud.Tracker.CurrentAccountYesterday.DropLegendary + Hud.Tracker.CurrentAccountToday.DropLegendary;
               var TodayYesterdayDropAncient = Hud.Tracker.CurrentAccountYesterday.DropAncient + Hud.Tracker.CurrentAccountToday.DropAncient;
               var TodayYesterdayDropPrimalAncient = Hud.Tracker.CurrentAccountYesterday.DropPrimalAncient + Hud.Tracker.CurrentAccountToday.DropPrimalAncient;
               if (TodayYesterdayDropAncient <= 1) {ancientMarker = 0; TodayYesterdayDropAncient = 1;}
               else ancientMarker = (int)(legendaryCount - (legendaryCount / TodayYesterdayDropAncient));
               if (TodayYesterdayDropPrimalAncient <= 1) {primalMarker = 0; TodayYesterdayDropPrimalAncient = 1;}
               else primalMarker = (int)(legendaryCount - (legendaryCount / TodayYesterdayDropPrimalAncient));  
             }
             RunOnlyOnce = false;
            }

            long PrimalAncientTotal = Hud.Tracker.CurrentAccountTotal.DropPrimalAncient;
            long AncientTotal = Hud.Tracker.CurrentAccountTotal.DropAncient;
            long LegendariesTotal = Hud.Tracker.CurrentAccountTotal.DropLegendary;
            string TotalPercPrimal = ((float)PrimalAncientTotal / (float)LegendariesTotal).ToString("0.00%");
            string TotalPercAncient = ((float)AncientTotal / (float)LegendariesTotal).ToString("0.00%");
                    
             ancientDecorator = new TopLabelDecorator(Hud)
            {
                 TextFont = Hud.Render.CreateFont("arial", 7, 220, 227, 153, 25, true, false, 255, 0, 0, 0, true),
                 TextFunc = () => ancientText,
                 HintFunc = () => "Chance for the next Legendary drop to be Ancient." + Environment.NewLine + "Total Ancient drops : " + AncientTotal + " (" + TotalPercAncient + ") of Legendary drops",
              
            };
            
             primalDecorator = new TopLabelDecorator(Hud)
            {
                 TextFont = Hud.Render.CreateFont("arial", 7, 180, 255, 64, 64, true, false, 255, 0, 0, 0, true),
                 TextFunc = () => primalText,
                 HintFunc = () => "Chance for the next Legendary drop to be Primal Ancient." + Environment.NewLine + "Total Primal Ancient drops : " + PrimalAncientTotal + " (" + TotalPercPrimal + ") of Legendary drops",
              
            };
            
           
            double probaAncient = 0;
            double probaPrimal = 0;
            double powAncient = legendaryCount-ancientMarker;
            double powPrimal = legendaryCount-primalMarker;
            double ancientMaths = 90.2246666/100; // previous : 90.00
            double primalMaths = 99.7753334/100; // previous : 99.78
                        
            if (powAncient == 0) powAncient = 1;
            if (powPrimal == 0) powPrimal = 1;
            
            probaAncient = (1 - Math.Pow(ancientMaths, powAncient))*100;
            probaPrimal = (1 - Math.Pow(primalMaths, powPrimal))*100;
                           
            probaAncient = Math.Round(probaAncient, 2);   
            probaPrimal = Math.Round(probaPrimal, 2);   
            
                
            ancientText = "A: " + probaAncient  + "%";
            primalText =  "P: " + probaPrimal  + "%";

            var uiRect = Hud.Render.GetUiElement("Root.NormalLayer.game_dialog_backgroundScreenPC.game_progressBar_manaBall").Rectangle;
            
            ancientDecorator.Paint(uiRect.Left - (uiRect.Width/3f), uiRect.Bottom - (uiRect.Height/5.7f), 50f, 50f, HorizontalAlign.Left);
            
            if (Hud.Game.Me.HighestSoloRiftLevel >= 70)
            {
            primalDecorator.Paint(uiRect.Left + (uiRect.Width/10f), uiRect.Bottom - (uiRect.Height/5.7f), 50f, 50f, HorizontalAlign.Left);
            }
            
            bool KanaiRecipe = Hud.Render.GetUiElement("Root.NormalLayer.Kanais_Recipes_main").Visible;
            double InventoryLegendaryCount = 0;
            double InventoryAncientCount = 0;
            double InventoryPrimalCount = 0;
            
            foreach (var item in Hud.Inventory.ItemsInInventory)
                    {
                     if (item != null) 
                      {
                       if (item.SnoItem == null || item.SnoItem.MainGroupCode == "gems_unique" || item.SnoItem.MainGroupCode == "potion") continue;
                                              
                       string itemID = item.SnoItem.Sno.ToString() + item.CreatedAtInGameTick.ToString();
                       if (item.IsLegendary && !legendaries.Contains(itemID)) InventoryLegendaryCount++;
                       if (item.AncientRank == 1 && !legendaries.Contains(itemID)) InventoryAncientCount++;
                       if (item.AncientRank == 2 && !legendaries.Contains(itemID)) InventoryPrimalCount++;
                       if (item.IsLegendary && !legendaries.Contains(itemID)) legendaries.Add(itemID);
                      }
                    }
            
            if (KanaiRecipe)
               {
                if (InventoryLegendaryCount > prevInventoryLegendaryCount) legendaryCount++; prevInventoryLegendaryCount = InventoryLegendaryCount;
                if (InventoryAncientCount > prevInventoryAncientCount) ancientMarker = legendaryCount; prevInventoryAncientCount = InventoryAncientCount;
                if (InventoryPrimalCount > prevInventoryPrimalCount) primalMarker = legendaryCount; prevInventoryPrimalCount = InventoryPrimalCount;
               }
            else prevInventoryLegendaryCount = InventoryLegendaryCount; prevInventoryAncientCount = InventoryAncientCount; prevInventoryPrimalCount = InventoryPrimalCount;
           

        }
    }
}