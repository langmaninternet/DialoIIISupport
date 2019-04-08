using System;
using System.Linq;
using SharpDX.DirectInput;
using SharpDX;
using Turbo.Plugins.Default;
using System.Collections.Generic;

namespace Turbo.Plugins.Default
{
    public class PartyCooldownsPlugin : BasePlugin, IInGameTopPainter
    {
        public SkillPainter SkillPainter { get; set; }
        public TopLabelDecorator Label { get; set; }
        public IFont ClassFont { get; set; }
        public List<uint> WatchedSnos;

        public float SizeRatio { get; set; }
        public float StartXPos { get; set; }
        public float StartYPos { get; set; }
        public float IconSize { get; set; }
        public bool ShowSelf { get; set; }
        public bool ShowOnlyMe { get; set; }
        public bool ShowInTown { get; set; }
        public bool OnlyInGR { get; set; }

        private float _size = 0;
        private float HudWidth { get { return Hud.Window.Size.Width; } }
        private float HudHeight { get { return Hud.Window.Size.Height; } }
        private Dictionary<HeroClass, string> _classShorts;
        private readonly int[] _skillOrder = { 2, 3, 4, 5, 0, 1 };


        private bool IsZDPS(IPlayer player)
        {
            int Points = 0;

            var IllusoryBoots = player.Powers.GetBuff(318761);
            if (IllusoryBoots == null || !IllusoryBoots.Active) { } else { Points++; }

            var LeoricsCrown = player.Powers.GetBuff(442353);
            if (LeoricsCrown == null || !LeoricsCrown.Active) { } else { Points++; }

            var EfficaciousToxin = player.Powers.GetBuff(403461);
            if (EfficaciousToxin == null || !EfficaciousToxin.Active) { } else { Points++; }

            var OculusRing = player.Powers.GetBuff(402461);
            if (OculusRing == null || !OculusRing.Active) { } else { Points++; }

            var ZodiacRing = player.Powers.GetBuff(402459);
            if (ZodiacRing == null || !ZodiacRing.Active) { } else { Points++; }

            if (player.Offense.SheetDps < 500000f) Points++;
            if (player.Offense.SheetDps > 1500000f) Points--;

            if (player.Defense.EhpMax > 80000000f) Points++;

            var ConventionRing = player.Powers.GetBuff(430674);
            if (ConventionRing == null || !ConventionRing.Active) { } else { Points--; }

            var Stricken = player.Powers.GetBuff(428348);
            if (Stricken == null || !Stricken.Active) { } else { Points--; }

            if (Points >= 4) { return true; } else { return false; }

        }


        public PartyCooldownsPlugin()
        {
            Enabled = true;
        }

        public override void Load(IController hud)
        {
            ShowSelf = true;
            ShowInTown = true;
            OnlyInGR = false;
            ShowOnlyMe = false;
            base.Load(hud);
            SizeRatio = 0.02f;
            StartYPos = 0.002f;
            StartXPos = 0.555f;
            IconSize = 0.05f;


            WatchedSnos = new List<uint>
            {
                //Add skills to the watch list below
                //--- Necromancer
                465350, //Simulacrum  
                465839, //Land of the Dead
                465952 , // Final Service

                //--- Barb
                79528, //Ignore Pain
                79607, //Wrath of the Berserker
                375483, //Warcry
                217819, // Nerves of Steel

                //--- Monk
                317076, //Inner Sanctuary
                156484, //Near Death Experience

                //--- Witch Doctor
                106237, //Spirit Walk

                //--- Demon Hunter 
                365311, //Companion
                129217, //Sentry
                324770, //Awareness


                //--- Wizard
                134872, //Archon - Needs testing, dont use for now
                208474 // Unstable Anomaly
            };

            ClassFont = Hud.Render.CreateFont("tahoma", 7, 230, 255, 255, 255, true, false, 255, 0, 0, 0, true);

            _classShorts = new Dictionary<HeroClass, string>
            {
                {HeroClass.Barbarian, "Barb"},
                {HeroClass.Monk, "Monk"},
                {HeroClass.Necromancer, "Necro"},
                {HeroClass.Wizard, "Wiz"},
                {HeroClass.WitchDoctor, "WD"},
                {HeroClass.Crusader, "Sader"},
                {HeroClass.DemonHunter, "DH"}
            };

            SkillPainter = new SkillPainter(Hud, true)
            {
                TextureOpacity = 1.0f,
                EnableSkillDpsBar = true,
                EnableDetailedDpsHint = true,
                CooldownFont = Hud.Render.CreateFont("arial", 7, 255, 255, 255, 255, true, false, 255, 0, 0, 0, true),
                SkillDpsBackgroundBrushesByElementalType = new IBrush[]
                {
                    Hud.Render.CreateBrush(222, 255, 6, 0, 0),
                    Hud.Render.CreateBrush(222, 183, 57, 7, 0),
                    Hud.Render.CreateBrush(222, 0, 38, 119, 0),
                    Hud.Render.CreateBrush(222, 77, 102, 155, 0),
                    Hud.Render.CreateBrush(222, 50, 106, 21, 0),
                    Hud.Render.CreateBrush(222, 138, 0, 94, 0),
                    Hud.Render.CreateBrush(222, 190, 117, 0, 0),
                },
                SkillDpsFont = Hud.Render.CreateFont("tahoma", 7, 222, 255, 255, 255, false, false, 0, 0, 0, 0, false),
            };
        }

        public void PaintTopInGame(ClipState clipState)
        {
            if (clipState != ClipState.BeforeClip || !ShowInTown && Hud.Game.Me.IsInTown || OnlyInGR && Hud.Game.SpecialArea != SpecialArea.GreaterRift) return;
            if (_size <= 0)
                _size = HudWidth * SizeRatio;

            var xPos = HudWidth * StartXPos;

            foreach (var player in Hud.Game.Players.OrderBy(p => p.HeroId))
            {
                if (player.IsMe && !ShowSelf || !player.IsMe && ShowOnlyMe)
                    continue;
                var found = false;
                var firstIter = true;
                foreach (var i in _skillOrder)
                {
                    var skill = player.Powers.SkillSlots[i];
                    if (skill == null || !WatchedSnos.Contains(skill.SnoPower.Sno)) continue;
                    found = true;
                    if (firstIter)
                    {
                        var layout = ClassFont.GetTextLayout(player.BattleTagAbovePortrait + "\n(" + ((IsZDPS(player)) ? "Z" : "") + _classShorts[player.HeroClassDefinition.HeroClass] + ")");
                        ClassFont.DrawText(layout, xPos - (layout.Metrics.Width * 0.1f), HudHeight * StartYPos);
                        firstIter = false;
                    }

                    var rect = new RectangleF(xPos, HudHeight * (StartYPos + 0.03f), _size, _size);
                    SkillPainter.Paint(skill, rect);
                    xPos += _size * 1.1f;
                }
                if (found)
                    xPos += _size * 1.1f;
            }
        }
    }
}