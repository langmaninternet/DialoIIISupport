//css_reference C:\v9.0.dll;
// https://github.com/User5981/Resu
// BattleTag Above Banner Plugin for TurboHUD Version 12/02/2019 11:27

using System;
using System.Collections.Generic;
using System.Linq;
using Turbo.Plugins.Default;

namespace Turbo.Plugins.Default
{
    public class BattleTagAboveBanner : BasePlugin, IInGameWorldPainter
    {
       public bool SeePlayersInTown { get; set; }
        public TopLabelDecorator TagDecorator { get; set; }
        // Dictionary<ACT_INDEX, Dictionary<PLAYER_INDEX, COORDINATE>>
        private Dictionary<int, Dictionary<int, IWorldCoordinate>> coordinates;
        
        public BattleTagAboveBanner()
        {
            Enabled = true;
            coordinates = new Dictionary<int, Dictionary<int, IWorldCoordinate>>();
            SeePlayersInTown = false;
        }
        
                  
        public override void Load(IController hud)
        {
            base.Load(hud);
            TagDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("tahoma", 8, 200, 255, 255, 255, true, false, false),
            };

            // Act 1
            coordinates.Add(1, new Dictionary<int, IWorldCoordinate>()
            {
                { 0, Hud.Window.CreateWorldCoordinate(381.154f, 551.850f, 33.3f) }, // Top of North East Banner  Act 1
                { 1, Hud.Window.CreateWorldCoordinate(397.500f, 568.030f, 31.5f) }, // Top of South East Banner  Act 1
                { 2, Hud.Window.CreateWorldCoordinate(403.000f, 539.500f, 37.3f) }, // Top of North West Banner  Act 1
                { 3, Hud.Window.CreateWorldCoordinate(413.500f, 548.450f, 28.9f) }, // Top of South West Banner  Act 1
            });
            // Act 2
            coordinates.Add(2, new Dictionary<int, IWorldCoordinate>()
            {
                { 0, Hud.Window.CreateWorldCoordinate(318.500f, 263.600f, 4.5f) }, // Top of North West Banner  Act 2
                { 1, Hud.Window.CreateWorldCoordinate(300.000f, 285.500f, 6.5f) }, // Top of North East Banner  Act 2
                { 2, Hud.Window.CreateWorldCoordinate(319.000f, 304.900f, 7.6f) }, // Top of South East Banner  Act 2
                { 3, Hud.Window.CreateWorldCoordinate(338.500f, 285.300f, 7.0f) }, // Top of South West Banner  Act 2
            });
            // Act 3 & 4
            var act34Coordinates = new Dictionary<int, IWorldCoordinate>()
            {
                { 0, Hud.Window.CreateWorldCoordinate(382.500f, 411.900f, 10.2f) }, // Top of North East Banner  Act 3 & 4
                { 1, Hud.Window.CreateWorldCoordinate(398.500f, 428.500f, 9.2f) },  // Top of South East Banner  Act 3 & 4
                { 2, Hud.Window.CreateWorldCoordinate(408.500f, 405.800f, 19.4f) }, // Top of North West Banner  Act 3 & 4
                { 3, Hud.Window.CreateWorldCoordinate(414.500f, 408.100f, 6.4f) },  // Top of South West Banner  Act 3 & 4
            };
            coordinates.Add(3, act34Coordinates);
            coordinates.Add(4, act34Coordinates);
            // Act 5
            coordinates.Add(5, new Dictionary<int, IWorldCoordinate>()
            {
                { 0, Hud.Window.CreateWorldCoordinate(571.000f, 756.600f, 6.1f) }, // Top of South West Banner  Act 5
                { 1, Hud.Window.CreateWorldCoordinate(550.000f, 779.000f, 7.4f) }, // Top of South East Banner  Act 5
                { 2, Hud.Window.CreateWorldCoordinate(551.500f, 739.000f, 9.5f) }, // Top of North West Banner  Act 5
                { 3, Hud.Window.CreateWorldCoordinate(530.000f, 759.000f, 9.1f) }, // Top of North East Banner  Act 5
            });
        }


        public void PaintWorld(WorldLayer layer)
        {
            if (Hud.Render.UiHidden) return;
            if (!Hud.Game.IsInTown) return;
            if (Hud.Game.NumberOfPlayersInGame == 1) return;

            var bannerAround = Hud.Game.Actors.Any(x => x.SnoActor.Sno == ActorSnoEnum._invisboxcollision_flippy && !x.IsDisabled && !x.IsOperated && x.IsOnScreen); // 375094 
            if (!bannerAround) return;

            foreach (var player in Hud.Game.Players) 
            {
                if (player == null) continue; 
                if (player.IsInTown && !SeePlayersInTown) continue;
                if (SeePlayersInTown && player.IsMe) continue;
                string battleTag = player.BattleTagAbovePortrait;
                if (battleTag == null) continue;
                TagDecorator.TextFunc = () => battleTag.ToString();
                var currentAct = Hud.Game.Me.SnoArea.Act;
                var playerIndex = player.Index;
                var HeroTexture = Hud.Texture.GetTexture(890155253);
                var ScreenWidth = Hud.Window.Size.Width; 
                var ScreenHeight = Hud.Window.Size.Height;
                

                if (!coordinates.ContainsKey(currentAct)) return;
                if (!coordinates[currentAct].ContainsKey(playerIndex)) return;
                
                
                if (player.HeroClassDefinition.HeroClass.ToString() == "Barbarian")
                   {
                     if (player.HeroClassDefinition.MaleActorSno != 0) HeroTexture = Hud.Texture.GetTexture(3921484788); // male/female can't be determined, let's keep it for later...
                     else HeroTexture = Hud.Texture.GetTexture(1030273087); 
                   }
                else if (player.HeroClassDefinition.HeroClass.ToString() == "Crusader")
                   {
                    if (player.HeroClassDefinition.MaleActorSno != 0) HeroTexture = Hud.Texture.GetTexture(3742271755);
                    else HeroTexture = Hud.Texture.GetTexture(3435775766);  
                   } 
                else if (player.HeroClassDefinition.HeroClass.ToString() == "DemonHunter")
                   {
                    if (player.HeroClassDefinition.MaleActorSno != 0) HeroTexture = Hud.Texture.GetTexture(3785199803);
                    else HeroTexture = Hud.Texture.GetTexture(2939779782);  
                   } 
                else if (player.HeroClassDefinition.HeroClass.ToString() == "Monk")
                   {
                    if (player.HeroClassDefinition.MaleActorSno != 0) HeroTexture = Hud.Texture.GetTexture(2227317895);
                    else HeroTexture = Hud.Texture.GetTexture(2918463890);  
                   } 
                else if (player.HeroClassDefinition.HeroClass.ToString() == "Necromancer")
                   {
                    if (player.HeroClassDefinition.MaleActorSno != 0) HeroTexture = Hud.Texture.GetTexture(3285997023); 
                    else HeroTexture = Hud.Texture.GetTexture(473831658);   
                   }
                else if (player.HeroClassDefinition.HeroClass.ToString() == "WitchDoctor")
                   {
                    if (player.HeroClassDefinition.MaleActorSno != 0) HeroTexture = Hud.Texture.GetTexture(3925954876);
                    else HeroTexture = Hud.Texture.GetTexture(1603231623);  
                   }
                else if (player.HeroClassDefinition.HeroClass.ToString() == "Wizard")
                   {
                    if (player.HeroClassDefinition.MaleActorSno != 0) HeroTexture = Hud.Texture.GetTexture(44435619);
                    else HeroTexture = Hud.Texture.GetTexture(876580014);   
                   }
                

                var BattleTagTexture = Hud.Texture.GetTexture(3098562643);
                var TownTexture = Hud.Texture.GetTexture(3153923970);
                var ToScreenPos = coordinates[currentAct][playerIndex].ToScreenCoordinate();

                BattleTagTexture.Draw((float)(ToScreenPos.X-(ScreenWidth/32.653)), (float)(ToScreenPos.Y-(ScreenHeight/52.941)), (float)(ScreenWidth/10), (float)(ScreenHeight/28), 0.7843f); 
                HeroTexture.Draw((float)(ToScreenPos.X-(ScreenWidth/28.769)), (float)(ToScreenPos.Y-(ScreenHeight/52.941)), (float)(ScreenWidth/56), (float)(ScreenHeight/31), 0.7843f);
                TagDecorator.Paint((float)(ToScreenPos.X - (ScreenWidth / 41)), (float)(ToScreenPos.Y - (ScreenHeight / 100)), (float)(ScreenWidth / 11.5), (float)(ScreenHeight / 45), HorizontalAlign.Center);
                if (player.IsInTown && SeePlayersInTown) 
                   {
                       TownTexture.Draw((float)(ToScreenPos.X+(ScreenWidth/20)), (float)(ToScreenPos.Y-(ScreenHeight/52.941)), (float)(ScreenHeight/27), (float)(ScreenHeight/26), 0.7843f);
                   }
                   
                
                
            }
        }
    }
}