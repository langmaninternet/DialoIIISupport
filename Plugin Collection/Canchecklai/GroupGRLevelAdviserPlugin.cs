//css_reference C:\v9.0.dll;
// https://github.com/User5981/Resu
// Group GR Level Adviser Plugin for TurboHUD version 12/02/2019 11:27
using Turbo.Plugins.Default;
using System;
using System.Collections.Generic;
using System.Linq;

namespace Turbo.Plugins.Default
{

    public class GroupGRLevelAdviserPlugin : BasePlugin, IInGameWorldPainter, IInGameTopPainter
    {
        public TopLabelDecorator GRLevelDecorator { get; set; }
        public TopLabelDecorator BattletagsDecorator { get; set; }
        public TopLabelDecorator ZClassesDecorator { get; set; }
        public TopLabelDecorator HighestSolosDecorator { get; set; }
        public WorldDecoratorCollection ObeliskClose { get; set; }
        public string GRLevelText { get; set; }
        public string Battletags { get; set; }
        public string ZClasses { get; set; }
        public string HighestSolos { get; set; }
        public float CircleSize { get; set; }
        public int PlayerInTownCount { get; set; }
        public WorldDecoratorCollection CircleDecorator { get; set; }
        public WorldDecoratorCollection TalkToUrshiDecorator { get; set; }
        public bool GardianIsDead { get; set; }
        public bool TalkedToUrshi { get; set; }
        public bool RedCircle { get; set; }
        
        public GroupGRLevelAdviserPlugin()
        {
            Enabled = true;
            RedCircle = true;
        }

        
        public override void Load(IController hud)
        {
         base.Load(hud);
         
         GRLevelText = string.Empty;
         CircleSize = 10;
         
         GRLevelDecorator = new TopLabelDecorator(Hud)
          {
           BackgroundBrush = Hud.Render.CreateBrush(150, 0, 0, 0, 0),
           BorderBrush = Hud.Render.CreateBrush(250, 0, 0, 0, 2),
           TextFont = Hud.Render.CreateFont("consolas", 8, 220, 255, 255, 255, true, false, 255, 0, 0, 0, true),
           TextFunc = () => "Greater Rift level advised for this" + Environment.NewLine + Hud.Game.NumberOfPlayersInGame + " player group     >   " + GRLevelText + "   <",
          };
          
         BattletagsDecorator = new TopLabelDecorator(Hud)
          {
           TextFont = Hud.Render.CreateFont("consolas", 8, 220, 255, 255, 255, true, false, 255, 0, 0, 0, true),
           TextFunc = () => Battletags,
          };
          
         ZClassesDecorator = new TopLabelDecorator(Hud)
          {
           TextFont = Hud.Render.CreateFont("consolas", 8, 220, 0, 253, 0, true, false, 255, 0, 0, 0, true),
           TextFunc = () => ZClasses,
          };
          
         HighestSolosDecorator = new TopLabelDecorator(Hud)
          {
           TextFont = Hud.Render.CreateFont("consolas", 8, 220, 255, 255, 255, true, false, 255, 0, 0, 0, true),
           TextFunc = () => HighestSolos,
          };
          
          ObeliskClose = new WorldDecoratorCollection( 
          new GroundLabelDecorator(Hud)
          {
           BackgroundBrush = Hud.Render.CreateBrush(0, 0, 0, 0, 0),
           BorderBrush = Hud.Render.CreateBrush(0, 182, 26, 255, 1),
           TextFont = Hud.Render.CreateFont("arial", 7, 200, 255, 255, 110, true, false, 255, 0, 0, 0, true)
          });

         TalkToUrshiDecorator = new WorldDecoratorCollection(
          new GroundLabelDecorator(Hud)
          {
           BackgroundBrush = Hud.Render.CreateBrush(0, 0, 0, 0, 0),
           TextFont = Hud.Render.CreateFont("tahoma", 20, 255, 255, 255, 255, true, true, true),
          });
          
        }
        
         public void PaintWorld(WorldLayer layer)
         {
             // Talking Obelisk part
             string ObeliskMessage = "";
             int TenSeconds = ((int)(Hud.Game.CurrentRealTimeMilliseconds/10000)) % 10;
             int OtherPlayers = Hud.Game.NumberOfPlayersInGame-1;
             string OPSentence = "";
             string GenderSentence = "";
             if (OtherPlayers == 1) OPSentence = "The other player is in town..."; else OPSentence = "The " + OtherPlayers + " other players are in town...";
             if (Hud.Game.Me.HeroIsMale) GenderSentence = "Hep! ... Young lad..."; else GenderSentence = "Hep! ... Young lady...";
             
             switch (TenSeconds)
                  {
                   case 0:
                   ObeliskMessage = "Close me!";
                   break;
                   
                   case 1:
                   ObeliskMessage = OPSentence;
                   break;
                   
                   case 2:
                   ObeliskMessage = "Please!";
                   break;
                   
                   case 3:
                   ObeliskMessage = "It's " + DateTime.Now.ToShortTimeString() + " now...";
                   break;

                   case 4:
                   ObeliskMessage = "Everybody is back!";
                   break;
                   
                   case 5:
                   ObeliskMessage = "You can close!";
                   break;
                   
                   case 6:
                   ObeliskMessage = "Psssst! ... " + Hud.Game.Me.Hero.Name + "!";
                   break;
                   
                   case 7:
                   ObeliskMessage = "There's a draught from the rift!";
                   break;
                   
                   case 8:
                   ObeliskMessage = "Close me, Nephalem!";
                   break;
                   
                   case 9:
                   ObeliskMessage = GenderSentence;
                   break;
                   
                  }

                 var Rift = Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 337492);
                 var GRift = Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 382695);
                 
                 GardianIsDead = false;
                 
                 if (Rift != null) 
                  {
                   if (Rift.QuestStepId == 5 || Rift.QuestStepId == 10 || Rift.QuestStepId == 34 || Rift.QuestStepId == 46) GardianIsDead = true;
                  }
                 else if (GRift != null)
                 {
                  if (GRift.QuestStepId == 5 || GRift.QuestStepId == 10 || GRift.QuestStepId == 34 || GRift.QuestStepId == 46) GardianIsDead = true;
                 }
                 else return; 
                       
                       
            if (PlayerInTownCount == Hud.Game.NumberOfPlayersInGame && Hud.Game.RiftPercentage == 100 && Hud.Game.IsInTown && GardianIsDead && Hud.Game.NumberOfPlayersInGame != 1)
             {
               var Obelisk = Hud.Game.Actors.FirstOrDefault(x => x.SnoActor.Sno == ActorSnoEnum._x1_openworld_lootrunportal); // 345935
               if (Obelisk != null) ObeliskClose.Paint(layer, Obelisk, Obelisk.FloorCoordinate, ObeliskMessage);
             }


           // 5% of Rift circle part
           CircleDecorator = new WorldDecoratorCollection( 
              new MapShapeDecorator(Hud)
            {
                Brush = Hud.Render.CreateBrush(255, 255, 0, 0, 2),
                ShapePainter = new CircleShapePainter(Hud),
                Radius = CircleSize,
            }
            );
           
          if ((Hud.Game.Me.InGreaterRift || Hud.Game.SpecialArea == SpecialArea.Rift || Hud.Game.SpecialArea == SpecialArea.ChallengeRift) && Hud.Game.RiftPercentage < 100 && RedCircle)
           {
            var monsters = Hud.Game.AliveMonsters.OrderByDescending(x => x.SnoMonster.RiftProgression);
            foreach (var monster in monsters)
                  {
                   CircleSize = 10;
                   NewLoop:
                   var CircleSizeYardMonsters = monsters.Where(x => x.FloorCoordinate.XYDistanceTo(monster.FloorCoordinate) <= CircleSize);
                   float RiftPercentage = 0f; 
                   foreach (var CircleSizeYardMonster in CircleSizeYardMonsters)
                         {
                          RiftPercentage = RiftPercentage + CircleSizeYardMonster.SnoMonster.RiftProgression;
                          if (CircleSizeYardMonster.Rarity == ActorRarity.Rare) RiftPercentage = RiftPercentage + 28.6f; // 4.4% of 650 (4 progression orb drops per yellow)
                          else if (CircleSizeYardMonster.Rarity == ActorRarity.Champion) RiftPercentage = RiftPercentage + 7.15f; // 1.1% of 650 (1 progression orb drop per blue)
                         }
                     
                   float PercentOfRift = 32.5f; // 5% of 650
                   if (Hud.Game.RiftPercentage > 95) PercentOfRift = (float)(((100-Hud.Game.RiftPercentage)/100)*650); // if less than 5% rift completion left, use that percentage instead.
                       
                   if (RiftPercentage >= PercentOfRift) 
                    {
                     CircleDecorator.Paint(layer, null, monster.FloorCoordinate, null);
                     break;
                    } 
                   else if (CircleSize < 56) // Within 55 yards max
                    {
                     CircleSize++;
                     goto NewLoop;
                    }
                   
                  }
           }
           
           // Talked to Urshi part
           bool UrshiPanel = Hud.Render.GetUiElement("Root.NormalLayer.vendor_dialog_mainPage.riftReward_dialog.LayoutRoot.gemUpgradePane.items_list._content").Visible;
           if (UrshiPanel) TalkedToUrshi = true;
           if (Hud.Game.Me.IsInTown) TalkedToUrshi = false;
          if (Hud.Game.Me.InGreaterRift && Hud.Game.RiftPercentage == 100 && GardianIsDead && Hud.Game.Me.AnimationState == AcdAnimationState.CastingPortal && !TalkedToUrshi && Hud.Game.SpecialArea == SpecialArea.GreaterRift )
           {
            TalkToUrshiDecorator.Paint(layer, null, Hud.Game.Me.FloorCoordinate, "Talk to Urshi!");
           }
        }
        
        
        public void PaintTopInGame(ClipState clipState)
        {
            int maxGRlevel = 0;
            PlayerInTownCount = 0;
            int NonZPlayerCount = 0;
            Battletags = string.Empty;
            ZClasses = string.Empty;
            HighestSolos = string.Empty;
            
            foreach (var player in Hud.Game.Players)
                  {
                   if (!IsZDPS(player)) 
                    {
                     maxGRlevel +=  player.HighestHeroSoloRiftLevel;
                     NonZPlayerCount++;
                    }
                   if (player.IsInTown) PlayerInTownCount++;
                   string Battletag = player.BattleTagAbovePortrait;
                   
                   string DPS = string.Empty;
                   if (player.Offense.SheetDps >= 3000000f) DPS = ValueToString((long)player.Offense.SheetDps, ValueFormat.LongNumber);
                   int WhiteSpaceNumber = 12 - player.HeroClassDefinition.HeroClass.ToString().Length;
                   string WhiteSpaces = new String(' ', WhiteSpaceNumber);
                   
                   string ZClass = (IsZDPS(player)) ? "Z " + player.HeroClassDefinition.HeroClass  : player.HeroClassDefinition.HeroClass + WhiteSpaces + DPS;
                   string HighestSolo = player.HighestHeroSoloRiftLevel.ToString().PadLeft(3);
                   if (player.SnoArea.Sno != Hud.Game.Me.SnoArea.Sno && player.HighestHeroSoloRiftLevel == 0) HighestSolo = "???".PadLeft(3);
                   Battletags = (Battletags.Length == 0) ? Battletag : Battletags + Environment.NewLine + Battletag ;
                   ZClasses = (ZClasses.Length == 0) ? ZClass : ZClasses + Environment.NewLine + ZClass;
                   HighestSolos = (HighestSolos.Length == 0) ? HighestSolo : HighestSolos + Environment.NewLine + HighestSolo ;
                  }
                  
            if (Hud.Render.GetUiElement("Root.NormalLayer.rift_dialog_mainPage").Visible)
             {
              if (NonZPlayerCount == 0) NonZPlayerCount = 1;
              int GRAverage = Convert.ToInt32(Convert.ToDouble(maxGRlevel / NonZPlayerCount + (((1 + Math.Sqrt(5)) / 2) * (Hud.Game.NumberOfPlayersInGame - 1))));
              GRLevelText = GRAverage.ToString();
              var uiRect = Hud.Render.GetUiElement("Root.NormalLayer.rift_dialog_mainPage").Rectangle;
              if (Hud.Window.CursorY >= uiRect.Top && Hud.Window.CursorY <= (uiRect.Top + uiRect.Height) && Hud.Window.CursorX >= uiRect.Left && Hud.Window.CursorX <= (uiRect.Left + uiRect.Width)) 
               {
                float WeirdMathMagic = 2.8f;
                if (Hud.Game.NumberOfPlayersInGame == 4) WeirdMathMagic = 2.7f;
                else if (Hud.Game.NumberOfPlayersInGame == 3) WeirdMathMagic = 2.766f;
                else if (Hud.Game.NumberOfPlayersInGame == 2) WeirdMathMagic = 2.833f;
                else if (Hud.Game.NumberOfPlayersInGame == 1) WeirdMathMagic = 2.9f;
                BattletagsDecorator.Paint((int)(uiRect.Right/4), (int)(uiRect.Bottom/WeirdMathMagic), 50, 50, HorizontalAlign.Left);
                ZClassesDecorator.Paint((int)(uiRect.Right/2.1), (int)(uiRect.Bottom/WeirdMathMagic), 50, 50, HorizontalAlign.Left);
                HighestSolosDecorator.Paint((int)(uiRect.Right/1.38), (int)(uiRect.Bottom/WeirdMathMagic), 50, 50, HorizontalAlign.Left);
                if (Hud.Game.NumberOfPlayersInGame != 1) GRLevelDecorator.Paint((int)(uiRect.Right/4), (int)(uiRect.Bottom/2.15), 230, 38, HorizontalAlign.Left);
               }
              
             }
        }
        
        private bool IsZDPS(IPlayer player)
        {
         int Points = 0;
         
         var IllusoryBoots = player.Powers.GetBuff(318761);
         if (IllusoryBoots == null || !IllusoryBoots.Active) {} else {Points++;}
         
         var LeoricsCrown = player.Powers.GetBuff(442353);
         if (LeoricsCrown == null || !LeoricsCrown.Active) {} else {Points++;}
         
         var EfficaciousToxin = player.Powers.GetBuff(403461);
         if (EfficaciousToxin == null || !EfficaciousToxin.Active) {} else {Points++;}
         
         var OculusRing = player.Powers.GetBuff(402461);
         if (OculusRing == null || !OculusRing.Active) {} else {Points++;}
         
         var ZodiacRing = player.Powers.GetBuff(402459);
         if (ZodiacRing == null || !ZodiacRing.Active) {} else {Points++;}
         
         if (player.Offense.SheetDps < 500000f) Points++;
         if (player.Offense.SheetDps > 1500000f) Points--;
         
         if (player.Defense.EhpMax > 80000000f) Points++;
         
         var ConventionRing = player.Powers.GetBuff(430674);
         if (ConventionRing == null || !ConventionRing.Active) {} else {Points--;}
         
         var Stricken = player.Powers.GetBuff(428348);
         if (Stricken == null || !Stricken.Active) {} else {Points--;}
        
        if (Points >= 4) {return true;} else {return false;}
         
        }
    }

}