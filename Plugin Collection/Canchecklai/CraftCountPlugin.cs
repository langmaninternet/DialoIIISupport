//css_reference C:\v9.0.dll;
// https://github.com/User5981/Resu
// Craft Count Plugin for TurboHUD Version 17/01/2019 12:02

using System;
using System.Globalization;
using Turbo.Plugins.Default;
using System.Linq;

namespace Turbo.Plugins.Default
{
    public class CraftCountPlugin : BasePlugin, IInGameTopPainter, ICustomizer
    {
        
        
        public TopLabelDecorator CraftCountDecorator { get; set; }
        public TopLabelDecorator BountiesDecorator { get; set; }
        public TopLabelDecorator RiftCompletionDecorator { get; set; }
        public float opacity { get; set; }
        public float itemOpacity { get; set; }
        public long craftCount { get; set; }
        public long deathsBreathCount { get; set; }
        public long prevDeathsBreathCount { get; set; }
        public long reusablePartsCount { get; set; }
        public long prevReusablePartsCount { get; set; }
        public long arcaneDustCount { get; set; }
        public long prevArcaneDustCount { get; set; }
        public long veiledCrystalCount { get; set; }
        public long prevVeiledCrystalCount { get; set; }
        public long forgottenSoulCount { get; set; }
        public long prevForgottenSoulCount { get; set; }
        public long bloodShardCount { get; set; }
        public long prevBloodShardCount { get; set; }
        public long grkCount { get; set; }
        public long prevGrkCount { get; set; }
        public long bovineBardicheCount { get; set; }
        public long prevBovineBardicheCount { get; set; } 
        public long puzzleRingCount { get; set; }
        public long prevPuzzleRingCount { get; set; }
        public long khanduranRuneCount { get; set; }
        public long prevKhanduranRuneCount { get; set; }
        public long caldeumNightShadeCount { get; set; }
        public long prevCaldeumNightShadeCount { get; set; }
        public long arreatWarTapestryCount { get; set; }
        public long prevArreatWarTapestryCount { get; set; }
        public long corruptedAngelFleshCount { get; set; }
        public long prevCorruptedAngelFleshCount { get; set; }
        public long westmarchHolyWaterCount { get; set; }
        public long prevWestmarchHolyWaterCount { get; set; }
        public long leoricsRegretCount { get; set; }
        public long prevLeoricsRegretCount { get; set; }
        public long idolOfTerrorCount { get; set; }
        public long prevIdolOfTerrorCount { get; set; }
        public long vialOfPutridnessCount { get; set; }
        public long prevVialOfPutridnessCount { get; set; }
        public long heartOfFrightCount { get; set; }
        public long prevHeartOfFrightCount { get; set; }
        public float itemSizeX { get; set; }
        public float itemSizeY { get; set; }
        public uint itemSno { get; set; }
        public int maxX { get; set; }
        public int maxY { get; set; }
        public long BountiesCompletion { get; set; }
        public long prevBountiesCompletion { get; set; }
        public int BountiesLeft { get; set; }
        public double prevRiftPercentage { get; set; }       
         
        public CraftCountPlugin()
        {
            Enabled = true;
        }
        
        public void Customize()
        {
         Hud.TogglePlugin<NotifyAtRiftPercentagePlugin>(false);
        }
        
        
        public override void Load(IController hud)
        {
            base.Load(hud);
            opacity = 0f;
            itemOpacity = 0;
            craftCount = 0;
            prevDeathsBreathCount = 0;
            deathsBreathCount = 0;
            prevReusablePartsCount = 0;
            reusablePartsCount = 0;
            prevArcaneDustCount = 0;
            arcaneDustCount = 0;
            prevVeiledCrystalCount = 0;
            veiledCrystalCount = 0;
            prevForgottenSoulCount = 0;
            forgottenSoulCount = 0;
            prevBloodShardCount = 0;
            bloodShardCount = 0;
            prevGrkCount = 0;
            grkCount = 0;
            prevBovineBardicheCount = 0;
            bovineBardicheCount = 0;
            prevPuzzleRingCount = 0;
            puzzleRingCount = 0;
            khanduranRuneCount = 0;
            prevKhanduranRuneCount = 0;
            caldeumNightShadeCount = 0;
            prevCaldeumNightShadeCount = 0;
            arreatWarTapestryCount = 0;
            prevArreatWarTapestryCount = 0;
            corruptedAngelFleshCount = 0;
            prevCorruptedAngelFleshCount = 0;
            westmarchHolyWaterCount = 0;
            prevWestmarchHolyWaterCount = 0;
            leoricsRegretCount = 0;
            prevLeoricsRegretCount = 0;
            idolOfTerrorCount = 0;
            prevIdolOfTerrorCount = 0;
            vialOfPutridnessCount = 0;
            prevVialOfPutridnessCount = 0;
            heartOfFrightCount = 0;
            prevHeartOfFrightCount = 0;
            itemSizeX = 0f;
            itemSizeY = 0f;
            itemSno = 0;
            BountiesCompletion = 0;
            prevBountiesCompletion = 0;
            BountiesLeft = 0; 
            prevRiftPercentage = 0;
            
             CraftCountDecorator = new TopLabelDecorator(Hud)
            {
                 TextFont = Hud.Render.CreateFont("Microsoft Sans Serif", 10, 200, 255, 255, 255, true, true, 25, 0, 0, 0, true),
                 TextFunc = () => craftCount.ToString("N0") + " owneth", 
            };
            
             BountiesDecorator = new TopLabelDecorator(Hud)
            {
                 TextFont = Hud.Render.CreateFont("Microsoft Sans Serif", 10, 200, 255, 255, 255, true, true, 25, 0, 0, 0, true),
                 TextFunc = () => (BountiesLeft == 0) ? "Bounties completed!" : (BountiesLeft == 1) ? BountiesLeft.ToString("N0") + " bounty left!" : BountiesLeft.ToString("N0") + " bounties left", 
            };
            
             RiftCompletionDecorator = new TopLabelDecorator(Hud)
            {
                 TextFont = Hud.Render.CreateFont("Microsoft Sans Serif", 10, 200, 255, 255, 255, true, true, 25, 0, 0, 0, true),
                 TextFunc = () => (Hud.Game.RiftPercentage >= 100) ? "Boss fight!" : "Rift: " + Hud.Game.RiftPercentage.ToString("F1", CultureInfo.InvariantCulture) + "%", 
            };
            
        }

       public void PaintTopInGame(ClipState clipState)
        {
                deathsBreathCount = Hud.Game.Me.Materials.DeathsBreath;
                reusablePartsCount = Hud.Game.Me.Materials.ReusableParts;
                arcaneDustCount = Hud.Game.Me.Materials.ArcaneDust;
                veiledCrystalCount = Hud.Game.Me.Materials.VeiledCrystal;
                forgottenSoulCount = Hud.Game.Me.Materials.ForgottenSoul;
                bloodShardCount = Hud.Game.Me.Materials.BloodShard;
                khanduranRuneCount = Hud.Game.Me.Materials.KhanduranRune;
                caldeumNightShadeCount = Hud.Game.Me.Materials.CaldeumNightShade;
                arreatWarTapestryCount = Hud.Game.Me.Materials.ArreatWarTapestry;
                corruptedAngelFleshCount = Hud.Game.Me.Materials.CorruptedAngelFlesh;
                westmarchHolyWaterCount = Hud.Game.Me.Materials.WestmarchHolyWater;
                leoricsRegretCount = Hud.Game.Me.Materials.LeoricsRegret;
                idolOfTerrorCount = Hud.Game.Me.Materials.IdolOfTerror;
                vialOfPutridnessCount = Hud.Game.Me.Materials.VialOfPutridness;
                heartOfFrightCount = Hud.Game.Me.Materials.HeartOfFright;
                grkCount = Hud.Game.Me.Materials.GreaterRiftKeystone;

                int TotalBounties = 0;
                int Completed = 0;
                var Bounties = Hud.Game.Bounties;
                if (Bounties != null)
                 {
                  foreach (var Bounty in Bounties)
                        {
                         TotalBounties++;
                         if (Bounty.State == QuestState.completed) Completed++;
                        }
                 }
                BountiesCompletion = Completed;
                BountiesLeft = (int)(TotalBounties-BountiesCompletion);
                
                
                var puzzleRingLoopCount = 0;
                var bovineBardicheLoopCount = 0;
                
                foreach (var item in Hud.Inventory.ItemsInStash)
            {
                if (item.SnoItem.Sno == 2346057823) bovineBardicheLoopCount += (int)item.Quantity; // Bovine Bardiche
                if (item.SnoItem.Sno == 3106130529) puzzleRingLoopCount += (int)item.Quantity; // Puzzle Ring
                
            }

            foreach (var item in Hud.Inventory.ItemsInInventory)
            {
                if (item.SnoItem.Sno == 2346057823) bovineBardicheLoopCount += (int)item.Quantity; // Bovine Bardiche
                if (item.SnoItem.Sno == 3106130529) puzzleRingLoopCount += (int)item.Quantity; // Puzzle Ring
                
            }
                puzzleRingCount = Math.Abs(puzzleRingLoopCount);
                bovineBardicheCount = Math.Abs(bovineBardicheLoopCount);
                
                var craftCountX = (Hud.Window.Size.Width/2)-(Hud.Window.Size.Width/48);
                var craftCountY = (Hud.Window.Size.Height/2)-(Hud.Window.Size.Height/6);
                
              if (Hud.Tracker.Session.ElapsedMilliseconds < 10000)
              {
               prevDeathsBreathCount = deathsBreathCount;
               prevReusablePartsCount = reusablePartsCount;
               prevArcaneDustCount = arcaneDustCount;
               prevVeiledCrystalCount = veiledCrystalCount;
               prevForgottenSoulCount = forgottenSoulCount;
               prevBloodShardCount = bloodShardCount;
               prevGrkCount = grkCount;
               prevBovineBardicheCount = bovineBardicheCount;
               prevPuzzleRingCount = puzzleRingCount;
               prevKhanduranRuneCount = khanduranRuneCount;
               prevCaldeumNightShadeCount = caldeumNightShadeCount;
               prevArreatWarTapestryCount = arreatWarTapestryCount;
               prevCorruptedAngelFleshCount = corruptedAngelFleshCount;
               prevWestmarchHolyWaterCount = westmarchHolyWaterCount;
               prevLeoricsRegretCount = leoricsRegretCount;
               prevIdolOfTerrorCount = idolOfTerrorCount;
               prevVialOfPutridnessCount = vialOfPutridnessCount;
               prevHeartOfFrightCount = heartOfFrightCount;
               prevBountiesCompletion = BountiesCompletion;
               prevGrkCount = grkCount;
              }
              
              CraftCountDecorator.TextFont.Opacity = opacity;
              BountiesDecorator.TextFont.Opacity = opacity;
              RiftCompletionDecorator.TextFont.Opacity = opacity;
             
            if (deathsBreathCount > prevDeathsBreathCount || deathsBreathCount < prevDeathsBreathCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevDeathsBreathCount = deathsBreathCount;} 
             
            itemSno = 2087837753;
            var DeathsBreath = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(DeathsBreath);
            craftCount = deathsBreathCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity);  
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left); 
            }
            else if (reusablePartsCount > prevReusablePartsCount || reusablePartsCount < prevReusablePartsCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevReusablePartsCount = reusablePartsCount;}
             
            itemSno = 3931359676;
            var ReusableParts = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(ReusableParts);
            craftCount = reusablePartsCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (arcaneDustCount > prevArcaneDustCount || arcaneDustCount < prevArcaneDustCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevArcaneDustCount = arcaneDustCount;}
             
            itemSno = 2709165134;
            var ArcaneDust = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(ArcaneDust);
            craftCount = arcaneDustCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (veiledCrystalCount > prevVeiledCrystalCount || veiledCrystalCount < prevVeiledCrystalCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevVeiledCrystalCount = veiledCrystalCount;}
             
            itemSno = 3689019703;
            var VeiledCrystal = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(VeiledCrystal);
            craftCount = veiledCrystalCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (forgottenSoulCount > prevForgottenSoulCount || forgottenSoulCount < prevForgottenSoulCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevForgottenSoulCount = forgottenSoulCount;}
             
            itemSno = 2073430088;
            var ForgottenSoul = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(ForgottenSoul);
            craftCount = forgottenSoulCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (bloodShardCount > prevBloodShardCount || bloodShardCount < prevBloodShardCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevBloodShardCount = bloodShardCount;}
             
            itemSno = 2603730171;
            var BloodShard = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(BloodShard);
            craftCount = bloodShardCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (grkCount > prevGrkCount || grkCount < prevGrkCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevGrkCount = grkCount;}
             
            itemSno = 2835237830;
            var grk = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(grk);
            craftCount = grkCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (bovineBardicheCount > prevBovineBardicheCount || bovineBardicheCount < prevBovineBardicheCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevBovineBardicheCount = bovineBardicheCount;}
             
            itemSno = 2346057823;
            var bovineBardiche = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(bovineBardiche);
            craftCount = bovineBardicheCount;
            itemSizeX = 23f;
            itemSizeY = 46f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (puzzleRingCount > prevPuzzleRingCount || puzzleRingCount < prevPuzzleRingCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevPuzzleRingCount = puzzleRingCount;}
             
            itemSno = 3106130529;
            var puzzleRing = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(puzzleRing);
            craftCount = puzzleRingCount;
            itemSizeX = 33f;
            itemSizeY = 33f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (khanduranRuneCount > prevKhanduranRuneCount || khanduranRuneCount < prevKhanduranRuneCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevKhanduranRuneCount = khanduranRuneCount;}
             
            itemSno = 1948629088;
            var khanduranRune = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(khanduranRune);
            craftCount = khanduranRuneCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (caldeumNightShadeCount > prevCaldeumNightShadeCount || caldeumNightShadeCount < prevCaldeumNightShadeCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevCaldeumNightShadeCount = caldeumNightShadeCount;}
             
            itemSno = 1948629089;
            var caldeumNightShade = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(caldeumNightShade);
            craftCount = caldeumNightShadeCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (arreatWarTapestryCount > prevArreatWarTapestryCount || arreatWarTapestryCount < prevArreatWarTapestryCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevArreatWarTapestryCount = arreatWarTapestryCount;}
             
            itemSno = 1948629090;
            var arreatWarTapestry = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(arreatWarTapestry);
            craftCount = arreatWarTapestryCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (corruptedAngelFleshCount > prevCorruptedAngelFleshCount || corruptedAngelFleshCount < prevCorruptedAngelFleshCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevCorruptedAngelFleshCount = corruptedAngelFleshCount;}
             
            itemSno = 1948629091;
            var corruptedAngelFlesh = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(corruptedAngelFlesh);
            craftCount = corruptedAngelFleshCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (westmarchHolyWaterCount > prevWestmarchHolyWaterCount || westmarchHolyWaterCount < prevWestmarchHolyWaterCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevWestmarchHolyWaterCount = westmarchHolyWaterCount;}
             
            itemSno = 1948629092;
            var westmarchHolyWater = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(westmarchHolyWater);
            craftCount = westmarchHolyWaterCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (leoricsRegretCount > prevLeoricsRegretCount || leoricsRegretCount < prevLeoricsRegretCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevLeoricsRegretCount = leoricsRegretCount;}
             
            itemSno = 1102953247;
            var leoricsRegret = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(leoricsRegret);
            craftCount = leoricsRegretCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (idolOfTerrorCount > prevIdolOfTerrorCount || idolOfTerrorCount < prevIdolOfTerrorCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevIdolOfTerrorCount = idolOfTerrorCount;}
             
            itemSno = 2670343450;
            var idolOfTerror = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(idolOfTerror);
            craftCount = idolOfTerrorCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (vialOfPutridnessCount > prevVialOfPutridnessCount || vialOfPutridnessCount < prevVialOfPutridnessCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevVialOfPutridnessCount = vialOfPutridnessCount;}
             
            itemSno = 2029265596;
            var vialOfPutridness = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(vialOfPutridness);
            craftCount = vialOfPutridnessCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (heartOfFrightCount > prevHeartOfFrightCount || heartOfFrightCount < prevHeartOfFrightCount)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevHeartOfFrightCount = heartOfFrightCount;}
             
            itemSno = 3336787100;
            var heartOfFright = Hud.Inventory.GetSnoItem(itemSno);
            var texture = Hud.Texture.GetItemTexture(heartOfFright);
            craftCount = heartOfFrightCount;
            itemSizeX = 23f;
            itemSizeY = 23f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            CraftCountDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if (BountiesCompletion > prevBountiesCompletion || BountiesCompletion < prevBountiesCompletion)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);}   else {prevBountiesCompletion = BountiesCompletion;}
             
            itemSno = 0;
            var texture = Hud.Texture.GetTexture(2854193535); 
            itemSizeX = 34f;
            itemSizeY = 34f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            BountiesDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else if ((Hud.Game.RiftPercentage >= 23 && Hud.Game.RiftPercentage <= 27 || Hud.Game.RiftPercentage >= 48 && Hud.Game.RiftPercentage <= 52 || Hud.Game.RiftPercentage >= 73 && Hud.Game.RiftPercentage <= 77 || Hud.Game.RiftPercentage >= 90 && Hud.Game.RiftPercentage < 100) && prevRiftPercentage != Hud.Game.RiftPercentage)
            {
            if (opacity < 1.0f) {opacity += 0.01f; itemOpacity += 0.01f; craftCountY = (int)(craftCountY - opacity*100);} else {prevRiftPercentage = Hud.Game.RiftPercentage;}
             
            itemSno = uint.MaxValue;
            var texture = Hud.Texture.GetTexture(3153276977); 
            itemSizeX = 40f;
            itemSizeY = 40f;
            texture.Draw(craftCountX-24, craftCountY+12, itemSizeX, itemSizeY, itemOpacity); 
            RiftCompletionDecorator.Paint(craftCountX, craftCountY, 50f, 50f, HorizontalAlign.Left);
            }
            else
            {   
            if (opacity >= 0f) 
               {
                opacity -= 0.010f;
                itemOpacity -= 0.010f;
                ISnoItem Fadeout = null;
                ITexture texture = null;
                if (itemSno == 0) {texture = Hud.Texture.GetTexture(2854193535);}
                else if (itemSno == uint.MaxValue) {texture = Hud.Texture.GetTexture(3153276977);}
                else {Fadeout = Hud.Inventory.GetSnoItem(itemSno); texture = Hud.Texture.GetItemTexture(Fadeout);}
                
                texture.Draw(craftCountX-24, craftCountY+12-100, itemSizeX, itemSizeY, itemOpacity); 
                if (itemSno == 0) BountiesDecorator.Paint(craftCountX, craftCountY-100, 50f, 50f, HorizontalAlign.Left);
                else if (itemSno == uint.MaxValue) RiftCompletionDecorator.Paint(craftCountX, craftCountY-100, 50f, 50f, HorizontalAlign.Left);
                else CraftCountDecorator.Paint(craftCountX, craftCountY-100, 50f, 50f, HorizontalAlign.Left);
                }   
            
            }
            
            
            
        }
    }
}