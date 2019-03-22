//css_reference C:\v9.0.dll;
// https://github.com/User5981/Resu
// Ariadne's Thread plugin for TurboHUD version 12/02/2019 11:27
// Shamelessly contains Xenthalon's AdvancedMarkerPlugin ^^;

using System;
using System.Collections.Generic;
using System.Linq;
using Turbo.Plugins.Default;

namespace Turbo.Plugins.Default
{
    public class AriadnesThreadPlugin : BasePlugin, IInGameWorldPainter, ICustomizer, INewAreaHandler, IInGameTopPainter
    {
        public TopLabelDecorator StrengthBuffDecorator { get; set; }
        public string StrengthBuffText { get; set; }
        public string bossText { get; set; }
        public IWorldCoordinate Other1 { get; set; }
        public IWorldCoordinate Other2 { get; set; }
        public IWorldCoordinate Other3 { get; set; }
        public IWorldCoordinate RealOther1 { get; set; }
        public IWorldCoordinate RealOther2 { get; set; }
        public IWorldCoordinate RealOther3 { get; set; }
        public IWorldCoordinate OldPos { get; set; }
        public IWorldCoordinate NewPos { get; set; }
        public string AreaOther1 { get; set; }
        public string AreaOther2 { get; set; }
        public string AreaOther3 { get; set; }
        public string NameOther1 { get; set; }
        public string NameOther2 { get; set; }
        public string NameOther3 { get; set; }
        public IBrush WhiteBrush { get; set; }
        public WorldDecoratorCollection QuestDecorator { get; set; }
        public WorldDecoratorCollection PoolDecorator { get; set; }
        public WorldDecoratorCollection KeywardenDecorator { get; set; }
        public WorldDecoratorCollection BossDecorator { get; set; }
        public WorldDecoratorCollection BannerDecorator { get; set; }
        public TopLabelDecorator DistanceDecorator { get; set; }
        public TopLabelDecorator SpeedDecorator { get; set; }
        private Dictionary<IWorldCoordinate, long> BannersList;
        private Dictionary<IWorldCoordinate, string> BannersAreas;
        private Dictionary<double, IWorldCoordinate> SpeedPos;
        public int BannerTimeSeconds { get; set; }
        public bool ThreadBetweenPlayers { get; set; }
        public bool Pools { get; set; }
        public int DistYards { get; set; }
        public bool MetricSystem { get; set; }
        public string DistString { get; set; }
        public string Speed { get; set; }
        public float DistanceFromLastSecond { get; set; }
        public float SpeedCooler { get; set; }

        private readonly HashSet<ActorSnoEnum> _actorList = new HashSet<ActorSnoEnum>(new List<uint>()
        {
            432770, 430733, 432885, 433051, 432259, 433246, 433385, 433295, 433316, 434366, 433124, 433184, 433402, 432331, 435703
        }.Select(x => (ActorSnoEnum)x));

        public AriadnesThreadPlugin()
        {
            Enabled = true;
            BannersList = new Dictionary<IWorldCoordinate, long>();
            BannersAreas = new Dictionary<IWorldCoordinate, string>();
            SpeedPos = new Dictionary<double, IWorldCoordinate>();
            BannerTimeSeconds = 30;
            ThreadBetweenPlayers = true;
            Pools = false;
            MetricSystem = false;
        }

        public override void Load(IController hud)
        {
            base.Load(hud);
            Other1 = Hud.Window.CreateWorldCoordinate(381.154f, 551.850f, 33.3f);
            Other2 = Hud.Window.CreateWorldCoordinate(381.154f, 551.850f, 33.3f);
            Other3 = Hud.Window.CreateWorldCoordinate(381.154f, 551.850f, 33.3f);
            RealOther1 = Hud.Window.CreateWorldCoordinate(381.154f, 551.850f, 33.3f);
            RealOther2 = Hud.Window.CreateWorldCoordinate(381.154f, 551.850f, 33.3f);
            RealOther3 = Hud.Window.CreateWorldCoordinate(381.154f, 551.850f, 33.3f);
            NameOther1 = string.Empty;
            NameOther2 = string.Empty;
            NameOther3 = string.Empty;
            AreaOther1 = string.Empty;
            AreaOther2 = string.Empty;
            AreaOther3 = string.Empty;
            StrengthBuffText = string.Empty;
            DistString = string.Empty;
            Speed = string.Empty;
            OldPos = Hud.Window.CreateWorldCoordinate(381.154f, 551.850f, 33.3f);
            NewPos = Hud.Window.CreateWorldCoordinate(381.154f, 551.850f, 33.3f);
            DistanceFromLastSecond = 0;
            SpeedCooler = 0;
            WhiteBrush = Hud.Render.CreateBrush(125, 255, 255, 255, 1, SharpDX.Direct2D1.DashStyle.Dash, SharpDX.Direct2D1.CapStyle.Flat, SharpDX.Direct2D1.CapStyle.Triangle);

            StrengthBuffDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("arial", 7, 220, 198, 174, 49, true, false, 255, 0, 0, 0, true),
                TextFunc = () => StrengthBuffText,
            };

            QuestDecorator = new WorldDecoratorCollection
             (
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(192, 255, 255, 55, -1),
                       ShadowBrush = Hud.Render.CreateBrush(96, 0, 0, 0, 1),
                       Radius = 10.0f,
                       ShapePainter = new CircleShapePainter(Hud),
                   },
                   new MapLabelDecorator(Hud)
                   {
                       LabelFont = Hud.Render.CreateFont("tahoma", 6f, 200, 255, 255, 0, false, false, 128, 0, 0, 0, true),
                       RadiusOffset = 10,
                       Up = true,
                   },
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(192, 255, 255, 55, -1),
                       ShapePainter = new LineFromMeShapePainter(Hud)
                   }
             );

            KeywardenDecorator = new WorldDecoratorCollection
             (
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(192, 238, 130, 238, -1),
                       ShadowBrush = Hud.Render.CreateBrush(96, 0, 0, 0, 1),
                       Radius = 10.0f,
                       ShapePainter = new CircleShapePainter(Hud),
                   },
                   new MapLabelDecorator(Hud)
                   {
                       LabelFont = Hud.Render.CreateFont("tahoma", 6f, 200, 255, 20, 255, false, false, 128, 0, 0, 0, true),
                       RadiusOffset = 10,
                       Up = true,
                   },
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(192, 238, 130, 238, -1),
                       ShapePainter = new LineFromMeShapePainter(Hud)
                   }
             );

            BossDecorator = new WorldDecoratorCollection
             (
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(192, 0, 255, 255, -1),
                       ShadowBrush = Hud.Render.CreateBrush(96, 0, 0, 0, 1),
                       Radius = 10.0f,
                       ShapePainter = new CircleShapePainter(Hud),
                   },
                   new MapLabelDecorator(Hud)
                   {
                       LabelFont = Hud.Render.CreateFont("tahoma", 6f, 200, 0, 255, 255, false, false, 128, 0, 0, 0, true),
                       RadiusOffset = 10,
                       Up = true,
                   },
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(192, 0, 255, 255, -1),
                       ShapePainter = new LineFromMeShapePainter(Hud)
                   }
             );

            PoolDecorator = new WorldDecoratorCollection
             (
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(255, 255, 255, 255, -1),
                       ShadowBrush = Hud.Render.CreateBrush(255, 0, 0, 0, 1),
                       Radius = 10.0f,
                       ShapePainter = new CircleShapePainter(Hud),
                   },
                   new MapLabelDecorator(Hud)
                   {
                       LabelFont = Hud.Render.CreateFont("tahoma", 6f, 255, 255, 255, 255, false, false, 255, 0, 0, 0, true),
                       RadiusOffset = 10,
                       Up = true,
                   },
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(255, 255, 255, 255, -1),
                       ShapePainter = new LineFromMeShapePainter(Hud)
                   }
             );

            BannerDecorator = new WorldDecoratorCollection(
                   new GroundLabelDecorator(Hud)
                   {
                       BackgroundBrush = Hud.Render.CreateBrush(255, 127, 255, 0, 0),
                       BorderBrush = Hud.Render.CreateBrush(192, 0, 0, 0, 1),
                       TextFont = Hud.Render.CreateFont("tahoma", 6.5f, 255, 0, 0, 0, true, false, false),
                   },
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(192, 27, 255, 0, -1),
                       ShadowBrush = Hud.Render.CreateBrush(96, 0, 0, 0, 1),
                       Radius = 10.0f,
                       ShapePainter = new CircleShapePainter(Hud),
                   },
                   new MapLabelDecorator(Hud)
                   {
                       LabelFont = Hud.Render.CreateFont("tahoma", 6f, 200, 27, 255, 0, false, false, 128, 0, 0, 0, true),
                       RadiusOffset = 10,
                       Up = true,
                   },
                   new MapShapeDecorator(Hud)
                   {
                       Brush = Hud.Render.CreateBrush(192, 27, 255, 0, -1),
                       ShapePainter = new LineFromMeShapePainter(Hud)
                   }
                   );

            DistanceDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("Microsoft Sans Serif", 9, 255, 222, 203, 120, false, false, 100, 0, 0, 0, true),
                TextFunc = () => DistString,
            };

            SpeedDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("Microsoft Sans Serif", 9, 255, 222, 203, 120, false, false, 100, 0, 0, 0, true),
                TextFunc = () => Speed,
            };
        }

        public void PaintWorld(WorldLayer layer)
        {
            DistYards = 0;
            var firstQuestMarker = true;
            var actors = Hud.Game.Actors.Where(a => _actorList.Contains(a.SnoActor.Sno));

            foreach (var Actor in actors)
            {
                if (Actor == null) continue;
                if (Actor.FloorCoordinate == null) continue;
                if (Actor.IsDisabled || Actor.IsOperated) continue;

                uint ThatQuest = 0;
                string Name = string.Empty;
                switch (Actor.SnoActor.Sno)
                {
                    case ActorSnoEnum._px_spidercaves_camp_cocoon /*432770*/: Name = "Royal Cocoon"; ThatQuest = 432784; break;
                    case ActorSnoEnum._px_wilderness_camp_templarprisoners /*430733*/: Name = "Captured Villager"; ThatQuest = 430723; break;
                    case ActorSnoEnum._a2dun_zolt_ibstone_a_portalroulette_mini /*432885*/: Name = "Ancient Device"; ThatQuest = 433025; break;
                    case ActorSnoEnum._px_caout_cage_bountycamp /*433051*/: Name = "Caldeum Villager"; ThatQuest = 433053; break;
                    case ActorSnoEnum._px_ruins_frost_camp_cage /*435703*/: Name = "Captured Barbarian"; ThatQuest = 436280; break;
                    case ActorSnoEnum._px_highlands_camp_resurgentcult_totem /*432259*/: Name = "Triune Monument"; ThatQuest = 432293; break;
                    case ActorSnoEnum._px_bounty_death_orb_little /*433246*/: Name = "Death Orb"; ThatQuest = 433256; break;
                    case ActorSnoEnum._px_bounty_ramparts_camp_switch /*433385*/: Name = "Catapult Winch"; ThatQuest = 433392; break;
                    case ActorSnoEnum._px_bounty_camp_azmodan_fight_spawner /*433295*/: Name = "Demon Gate"; ThatQuest = 433309; break;
                    case ActorSnoEnum._x1_westm_necro_jar_of_souls_camp_graveyard /*433316*/: Name = "Death Prison"; ThatQuest = 433339; break;
                    case ActorSnoEnum._px_leorics_camp_worthammilitia_ex /*434366*/: Name = "Tortured Wortham Militia"; ThatQuest = 434378; break;
                    case ActorSnoEnum._px_bridge_camp_lostpatrol /*433184*/: Name = "Captured Guard"; ThatQuest = 433217; break;
                    case ActorSnoEnum._px_bounty_camp_trappedangels /*433124*/: Name = "Bone Cage"; ThatQuest = 433099; break;
                    case ActorSnoEnum._px_bounty_camp_hellportals_frame /*433402*/: Name = "Hell Portal"; ThatQuest = 433422; break;
                    case ActorSnoEnum._px_oasis_camp_ironwolves /*432331*/: Name = "Captured Iron Wolf"; ThatQuest = 432334; break;
                    default: Name = string.Empty; break;
                }
                var quest = Hud.Game.Bounties.FirstOrDefault(x => x.SnoQuest.Sno == ThatQuest);
                if ((quest != null) && quest.State != QuestState.completed)
                {
                    QuestDecorator.Paint(layer, null, Actor.FloorCoordinate, Name);
                    firstQuestMarker = false;
                }
            }

            // modified Xenthalon's AdvancedMarkerPlugin
            var markers = Hud.Game.Markers.OrderBy(i => Hud.Game.Me.FloorCoordinate.XYDistanceTo(i.FloorCoordinate));
            if (markers != null)
            {
                foreach (var marker in markers)
                {
                    if (marker == null) continue;
                    if (marker.FloorCoordinate == null) continue;
                    if (marker.Name == null) continue;

                    var OnScreen = marker.FloorCoordinate.IsOnScreen(1);
                    QuestDecorator.ToggleDecorators<GroundLabelDecorator>(!OnScreen); // do not display ground labels when the marker is on the screen
                    KeywardenDecorator.ToggleDecorators<GroundLabelDecorator>(!OnScreen);
                    BossDecorator.ToggleDecorators<GroundLabelDecorator>(!OnScreen);

                    if (marker.SnoQuest != null && firstQuestMarker)
                    {
                        DistYards = (int)(marker.FloorCoordinate.XYDistanceTo(Hud.Game.Me.FloorCoordinate));
                        QuestDecorator.Paint(layer, null, marker.FloorCoordinate, marker.Name);
                        firstQuestMarker = false;
                    }
                    else if (marker.SnoActor != null)
                    {
                        if (marker.SnoActor.Code.Contains("_Boss_"))
                        {
                            BossDecorator.Paint(layer, null, marker.FloorCoordinate, marker.Name);
                        }
                        else if (marker.FloorCoordinate.XYDistanceTo(Hud.Game.Me.FloorCoordinate) < 500)
                        {
                            KeywardenDecorator.Paint(layer, null, marker.FloorCoordinate, marker.Name);
                        }
                    }
                }
            }

            if (Hud.Game.NumberOfPlayersInGame == 1)
            {
                NameOther3 = string.Empty; Other3 = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate); AreaOther3 = string.Empty;
                NameOther2 = string.Empty; Other2 = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate); AreaOther2 = string.Empty;
                NameOther1 = string.Empty; Other1 = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate); AreaOther1 = string.Empty;
                return;
            }

            // Pools of reflection
            if (Pools)
            {
                var PoolsOfReflection = Hud.Game.Shrines.Where(p => !p.IsDisabled && !p.IsOperated && p.Type == ShrineType.PoolOfReflection);
                //var PoolsOfReflection = Hud.Game.Actors.Where(x => !x.IsDisabled && !x.IsOperated && x.SnoActor.Sno == 373463);

                foreach (var PoolOfReflection in PoolsOfReflection)
                {
                    PoolDecorator.Paint(layer, null, PoolOfReflection.FloorCoordinate, PoolOfReflection.SnoActor.NameLocalized);
                }
            }

            // Strengh in numbers buff indicator
            var SiNBuff = Hud.Game.Me.Powers.GetBuff(258199);
            int StrengthBuff = SiNBuff.IconCounts[0] * 10;

            if (StrengthBuff != 0 && !Hud.Game.Me.IsDead)
            {
                StrengthBuffText = "+" + StrengthBuff + "%";
                var uiRect = Hud.Render.GetUiElement("Root.NormalLayer.minimap_dialog_backgroundScreen.minimap_dialog_pve.BoostWrapper.BoostsDifficultyStackPanel.clock").Rectangle;
                if (Hud.Game.Me.Hero.Seasonal) StrengthBuffDecorator.Paint(uiRect.Left - uiRect.Width * 1.14f, uiRect.Top + uiRect.Height * 1f, uiRect.Width, uiRect.Height, HorizontalAlign.Right);
                else StrengthBuffDecorator.Paint(uiRect.Left - uiRect.Width * 0.96f, uiRect.Top + uiRect.Height * 1f, uiRect.Width, uiRect.Height, HorizontalAlign.Right);
            }

            // Thread between players
            var players = Hud.Game.Players.Where(player => !player.IsMe).OrderBy(player => player.PortraitIndex);
            if (players != null)
            {
                foreach (var player in players)
                {
                    if (player == null) continue;
                    else if (player.BattleTagAbovePortrait == null) continue;
                    else if (player.FloorCoordinate == null) continue;
                    else if (player.SnoArea == null) continue;
                    else if (player.SnoArea.NameEnglish == null) continue;
                    else if (double.IsNaN(player.NormalizedXyDistanceToMe)) continue;
                    else if (player.PortraitIndex == 1)
                    {
                        NameOther1 = player.BattleTagAbovePortrait; RealOther1 = player.FloorCoordinate; AreaOther1 = player.SnoArea.NameEnglish;
                        if (Hud.Game.NumberOfPlayersInGame == 2) NameOther3 = string.Empty; Other3 = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate); AreaOther3 = string.Empty; NameOther2 = string.Empty; Other2 = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate); AreaOther2 = string.Empty;
                        if (Hud.Game.Me.SnoArea.Sno == player.SnoArea.Sno && player.CoordinateKnown)
                        {
                            Other1 = player.FloorCoordinate;
                        }
                        else
                        {
                            Other1 = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate);
                        }
                    }
                    else if (player.PortraitIndex == 2)
                    {
                        NameOther2 = player.BattleTagAbovePortrait; RealOther2 = player.FloorCoordinate; AreaOther2 = player.SnoArea.NameEnglish;
                        if (Hud.Game.NumberOfPlayersInGame == 3) NameOther3 = string.Empty; Other3 = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate); AreaOther3 = string.Empty;
                        if (Hud.Game.Me.SnoArea.Sno == player.SnoArea.Sno && player.CoordinateKnown)
                        {
                            Other2 = player.FloorCoordinate;
                        }
                        else
                        {
                            Other2 = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate);
                        }
                    }
                    else if (player.PortraitIndex == 3)
                    {
                        NameOther3 = player.BattleTagAbovePortrait; RealOther3 = player.FloorCoordinate; AreaOther3 = player.SnoArea.NameEnglish;
                        if (Hud.Game.Me.SnoArea.Sno == player.SnoArea.Sno && player.CoordinateKnown)
                        {
                            Other3 = player.FloorCoordinate;
                        }
                        else
                        {
                            Other3 = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate);
                        }
                    }
                }
            }

            Hud.Render.GetMinimapCoordinates(Other1.X, Other1.Y, out float Other1OnMapX, out float Other1OnMapY);
            Hud.Render.GetMinimapCoordinates(Other2.X, Other2.Y, out float Other2OnMapX, out float Other2OnMapY);
            Hud.Render.GetMinimapCoordinates(Other3.X, Other3.Y, out float Other3OnMapX, out float Other3OnMapY);

            if (!Hud.Game.IsInTown && ThreadBetweenPlayers)
            {
                WhiteBrush.DrawLine(Other1OnMapX, Other1OnMapY, Other2OnMapX, Other2OnMapY);
                WhiteBrush.DrawLine(Other1OnMapX, Other1OnMapY, Other3OnMapX, Other3OnMapY);
                WhiteBrush.DrawLine(Other3OnMapX, Other3OnMapY, Other2OnMapX, Other2OnMapY);
            }

            // banners
            var banners = Hud.Game.Banners;
            if (banners != null)
            {
                foreach (var banner in banners)
                {
                    if (banner == null || banner.FloorCoordinate == null || !banner.FloorCoordinate.IsValid) continue;
                    if (!BannersList.ContainsKey(banner.FloorCoordinate)) BannersList.Add(banner.FloorCoordinate, Hud.Game.CurrentRealTimeMilliseconds);
                }
            }

            float DistOther1;
            float DistOther2;
            float DistOther3;
            float ZDistOther1;
            float ZDistOther2;
            float ZDistOther3;
            float DistMe;
            float ZDistMe;

            if (BannersList != null)
            {
                foreach (var ListedBanner in BannersList.Where(b => Hud.Game.CurrentRealTimeMilliseconds < b.Value + 30000).OrderBy(b => b.Value).Take(5))
                {
                    var BanCoord = ListedBanner.Key;
                    long Timeleft = ((ListedBanner.Value + (BannerTimeSeconds * 1000) - Hud.Game.CurrentRealTimeMilliseconds) / 1000);
                    string Countdown = " " + Timeleft.ToString("f0") + "s";

                    var onScreen = BanCoord.IsOnScreen();
                    if (onScreen) BannerDecorator.ToggleDecorators<GroundLabelDecorator>(false);
                    else BannerDecorator.ToggleDecorators<GroundLabelDecorator>(true);

                    if (RealOther1 != null && Hud.Game.NumberOfPlayersInGame >= 2) { DistOther1 = RealOther1.XYDistanceTo(BanCoord); ZDistOther1 = RealOther1.ZDiffTo(BanCoord); } else { DistOther1 = float.MaxValue; ZDistOther1 = float.MaxValue; }
                    if (RealOther2 != null && Hud.Game.NumberOfPlayersInGame >= 3) { DistOther2 = RealOther2.XYDistanceTo(BanCoord); ZDistOther2 = RealOther2.ZDiffTo(BanCoord); } else { DistOther2 = float.MaxValue; ZDistOther2 = float.MaxValue; }
                    if (RealOther3 != null && Hud.Game.NumberOfPlayersInGame == 4) { DistOther3 = RealOther3.XYDistanceTo(BanCoord); ZDistOther3 = RealOther3.ZDiffTo(BanCoord); } else { DistOther3 = float.MaxValue; ZDistOther3 = float.MaxValue; }
                    DistMe = Hud.Game.Me.FloorCoordinate.XYDistanceTo(BanCoord);
                    ZDistMe = Hud.Game.Me.FloorCoordinate.ZDiffTo(BanCoord);

                    string NearestPlayer = string.Empty;
                    string BannerArea = string.Empty;

                    if (!BannersAreas.ContainsKey(BanCoord))
                    {
                        if (DistOther1 < DistOther2 && DistOther1 < DistOther3 && DistOther1 < DistMe && DistOther1 < 200f && ZDistOther1 < 6f && NameOther1 != null) { NearestPlayer = "banner near " + NameOther1; BannerArea = AreaOther1; }
                        else if (DistOther2 < DistOther1 && DistOther2 < DistOther3 && DistOther2 < DistMe && DistOther2 < 200f && ZDistOther2 < 6f && NameOther2 != null) { NearestPlayer = "banner near " + NameOther2; BannerArea = AreaOther2; }
                        else if (DistOther3 < DistOther1 && DistOther3 < DistOther2 && DistOther3 < DistMe && DistOther3 < 200f && ZDistOther3 < 6f && NameOther3 != null) { NearestPlayer = "banner near " + NameOther3; BannerArea = AreaOther3; }
                        else { NearestPlayer = "banner"; BannerArea = Hud.Game.Me.SnoArea.NameEnglish; }
                    }
                    else
                    {
                        if (DistOther1 < DistOther2 && DistOther1 < DistOther3 && DistOther1 < DistMe && DistOther1 < 200f && ZDistOther1 < 6f && BannersAreas[BanCoord] == AreaOther1 && NameOther1 != null) { NearestPlayer = "banner near " + NameOther1; }
                        else if (DistOther2 < DistOther1 && DistOther2 < DistOther3 && DistOther2 < DistMe && DistOther2 < 200f && ZDistOther2 < 6f && BannersAreas[BanCoord] == AreaOther2 && NameOther2 != null) { NearestPlayer = "banner near " + NameOther2; }
                        else if (DistOther3 < DistOther1 && DistOther3 < DistOther2 && DistOther3 < DistMe && DistOther3 < 200f && ZDistOther3 < 6f && BannersAreas[BanCoord] == AreaOther3 && NameOther3 != null) { NearestPlayer = "banner near " + NameOther3; }
                        else { NearestPlayer = "banner"; }
                    }

                    string RealBannerArea = string.Empty;
                    if (!BannersAreas.ContainsKey(BanCoord)) BannersAreas.Add(BanCoord, BannerArea);
                    else
                    {
                        RealBannerArea = BannersAreas[BanCoord];
                    }
                    bool SameArea = false;
                    if (Hud.Game.Me.SnoArea.NameEnglish == RealBannerArea) { SameArea = true; } else { SameArea = false; }
                    if (!SameArea || Hud.Game.Me.IsInTown) BannerDecorator.ToggleDecorators<MapShapeDecorator>(false);
                    else if (SameArea) BannerDecorator.ToggleDecorators<MapShapeDecorator>(true);

                    if (NearestPlayer == "banner near ") NearestPlayer = "banner";
                    if (RealBannerArea.Contains("[TEMP]")) RealBannerArea = RealBannerArea.Replace("[TEMP]", string.Empty).Trim();
                    if (RealBannerArea.Contains("Loot Run")) RealBannerArea = RealBannerArea.Replace("Loot Run", "Rift").Trim();

                    if (NearestPlayer != null && RealBannerArea != string.Empty)
                    {
                        if (SameArea) { BannerDecorator.Paint(layer, null, BanCoord, NearestPlayer + Countdown); }
                        else if (NearestPlayer != "banner")
                        {
                            BannerDecorator.Paint(layer, null, BanCoord, NearestPlayer + " in " + RealBannerArea + Environment.NewLine + "teleport!" + Countdown);
                        }
                        else
                        {
                            BannerDecorator.Paint(layer, null, BanCoord, NearestPlayer + " in " + RealBannerArea + Countdown);
                        }
                    }
                }
            }
        }

        public void PaintTopInGame(ClipState clipState)
        {
            if (Hud.Render.UiHidden) return;
            if (clipState != ClipState.BeforeClip) return;

            var uiRect = Hud.Render.GetUiElement("Root.NormalLayer.minimap_dialog_backgroundScreen.minimap_dialog_pve.minimap_pve_main").Rectangle;

            NewPos = Hud.Window.CreateWorldCoordinate(Hud.Game.Me.FloorCoordinate);
            double DatSecond = Math.Truncate((double)(Hud.Game.CurrentRealTimeMilliseconds / 1000));

            if (!SpeedPos.ContainsKey(DatSecond)) SpeedPos.Add(DatSecond, NewPos);

            int DictCount = SpeedPos.Count;

            if (DictCount >= 2)
            {
                var NextToLast = SpeedPos.OrderByDescending(b => b.Key).Skip(1).First();
                OldPos = NextToLast.Value;
            }
            if (DictCount >= 3)
            {
                var First = SpeedPos.OrderBy(b => b.Key).First();
                SpeedPos.Remove(First.Key);
            }

            DistanceFromLastSecond = OldPos.XYDistanceTo(Hud.Game.Me.FloorCoordinate);

            if (DistanceFromLastSecond > SpeedCooler) SpeedCooler = SpeedCooler + (float)((DistanceFromLastSecond - SpeedCooler) / (DistanceFromLastSecond + 1));
            else if (DistanceFromLastSecond < SpeedCooler) SpeedCooler = SpeedCooler - (float)((SpeedCooler - DistanceFromLastSecond) / (DistanceFromLastSecond + 1));

            double mph = Math.Round(SpeedCooler * 0.49);
            double kmh = Math.Round(SpeedCooler * 0.30);

            if (MetricSystem)
            {
                Speed = kmh + " km/h";
                var Meters = (int)(DistYards * 1.0936);
                if (Meters >= 1000) DistString = Math.Round((float)Meters / 1000, 1) + " km";
                else DistString = Meters + " m";
            }
            else
            {
                Speed = mph + " mph";
                if (DistYards >= 1760) DistString = Math.Round((float)DistYards / 1760, 1) + " mi";
                else DistString = DistYards + " yd";
            }

            if (DistYards > 49) DistanceDecorator.Paint(uiRect.Right - 30f, uiRect.Bottom + 10f, 50f, 50f, HorizontalAlign.Left);

            if (mph > 0) SpeedDecorator.Paint(uiRect.Left, uiRect.Bottom - 35f, 50f, 50f, HorizontalAlign.Left);
        }

        public void OnNewArea(bool newGame, ISnoArea area)
        {
            if (newGame)
            {
                BannersList.Clear();
                BannersAreas.Clear();
            }
        }

        public void Customize()
        {
            Hud.TogglePlugin<MarkerPlugin>(false);  // disable default MarkerPlugin
            Hud.TogglePlugin<BannerPlugin>(false);  // disable default BannerPlugin
        }
    }
}