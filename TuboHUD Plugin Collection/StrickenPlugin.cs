// http://www.ownedcore.com/forums/diablo-3/turbohud/turbohud-plugin-review-zone/635586-v7-3-english-glq-baneofthestrickenplugin.html
 
using Turbo.Plugins.Default;
using System;
using System.Linq;
using System.Drawing;
using System.Collections.Generic;
 
namespace Turbo.Plugins.Default
{
    public class GLQ_BaneOfTheStrickenPlugin : BasePlugin, IInGameTopPainter, INewAreaHandler
    {
        public bool DrawClassOnIcons { get; set; }      //Draw ClassNames per Dafault on every Stricken Icon
       
        public IFont TextFont { get; set; }
        private int[] StackCount { get; set; }
        private bool[] cooling { get; set; }
        public TopLabelDecorator StackCountDecorator { get; set; }
        public float xPos { get; set; }
        public float XWidth { get; set; }
        public float YHeight { get; set; }
        private IBrush StackBrush;
        private Dictionary<HeroClass, string> classShorts;
        public IFont ClassFont { get; set; }
       
        public bool IsGuardianAlive
        {
            get
            {
                return riftQuest != null && (riftQuest.QuestStepId == 3 || riftQuest.QuestStepId == 16);
            }
        }
       
        private IQuest riftQuest
        {
            get
            {
                return Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 337492) ?? // rift
                       Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 382695);   // gr
            }
        }
       
        public GLQ_BaneOfTheStrickenPlugin()
        {
            Enabled = true;
           
            DrawClassOnIcons = false;
        }
 
        public override void Load(IController hud)
        {
            base.Load(hud);
           
            StackCountDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("tahoma", 7, 255, 255, 255, 255, false, false, 250, 0, 0, 0, true),
                HintFunc = () => "Bane Of The Stricken Count of trigger times(The monomeric BOSS is accurate)"
            };
           
            StackCount = new int[4];
            cooling = new bool[4];
           
            StackBrush = Hud.Render.CreateBrush(255, 0, 0, 0, 0);
           
            classShorts = new Dictionary<HeroClass, string>();
            classShorts.Add(HeroClass.Barbarian, "Barb");
            classShorts.Add(HeroClass.Monk, "Monk");
            classShorts.Add(HeroClass.Necromancer, "Necro");
            classShorts.Add(HeroClass.Wizard, "Wiz");
            classShorts.Add(HeroClass.WitchDoctor, "WD");
            classShorts.Add(HeroClass.Crusader, "Sader");
            classShorts.Add(HeroClass.DemonHunter, "DH");  
            ClassFont = Hud.Render.CreateFont("tahoma", 7, 230, 255, 255, 255, true, false, 255, 0, 0, 0, true);
        }
       
        public void OnNewArea(bool newGame, ISnoArea area)
        {
            if (newGame)
            {
                for (int i = 0; i < 4; i++)
                {
                    StackCount[i] = 0;
                }
            }
        }
       
        public void DrawStackCount(IPlayer player)
        {
            if (!player.Powers.BuffIsActive(Hud.Sno.SnoPowers.BaneOfTheStrickenPrimary.Sno, 0)) return;
            int count = Hud.Game.AliveMonsters.Count(m => m.SnoMonster.Priority == MonsterPriority.boss);
            if (count == 0) return;
           
            var uiBar = Hud.Render.MonsterHpBarUiElement;
            var monster = Hud.Game.SelectedMonster2 ?? Hud.Game.SelectedMonster1;
            if ((monster == null) || (uiBar == null) || (monster.SnoMonster.Priority != MonsterPriority.boss)) return;
            int HitnRng = 1;
            int _count = 0;
 
            _count = Hud.Game.AliveMonsters.Count(m => (player.FloorCoordinate.XYZDistanceTo(m.FloorCoordinate)) <= 10);
            if (_count < 1) _count = 1;
            Random rng;
            rng = new Random(Hud.Game.CurrentGameTick);
            HitnRng = rng.Next(1, _count);
           
            var w = uiBar.Rectangle.Height * 2;
            var h = uiBar.Rectangle.Height;
            var x = uiBar.Rectangle.Right + uiBar.Rectangle.Height * 5;
            var y = uiBar.Rectangle.Y + uiBar.Rectangle.Height * 0.3f + 10;
           
            var bgTex = Hud.Texture.GetTexture(3166997520);
            var tex = Hud.Texture.GetItemTexture(Hud.Sno.SnoItems.Unique_Gem_018_x1);
            var rect = new RectangleF(uiBar.Rectangle.Right + uiBar.Rectangle.Height * 5f + xPos, uiBar.Rectangle.Y - uiBar.Rectangle.Height * 1.5f / 6, uiBar.Rectangle.Height * 1.5f, uiBar.Rectangle.Height * 1.5f);
           
            var index = player.PortraitIndex;
            if (player.Powers.BuffIsActive(Hud.Sno.SnoPowers.BaneOfTheStrickenPrimary.Sno, 2))
            {
                if (!cooling[index])
                {
                    cooling[index] = true;
                    if(HitnRng == 1) StackCount[index]++;
                }
            }
            else
            {
                cooling[index] = false;
            }
           
            StackCountDecorator.TextFunc = () => StackCount[index].ToString();
            StackBrush.DrawRectangle(rect);
            bgTex.Draw(rect.Left, rect.Top, rect.Width, rect.Height);
            tex.Draw(rect.Left, rect.Top, rect.Width, rect.Height);
            var layout = ClassFont.GetTextLayout(player.BattleTagAbovePortrait + "\n(" + classShorts[player.HeroClassDefinition.HeroClass] + ")");
           
            if (DrawClassOnIcons || Hud.Window.CursorInsideRect(rect.X, rect.Y, rect.Width, rect.Height))
            {
                ClassFont.DrawText(layout, x - (layout.Metrics.Width * 0.1f) + xPos, y - h * 3);
            }
            StackCountDecorator.Paint(x + xPos, y, w, h, HorizontalAlign.Center);
            xPos += rect.Width + h;
        }
 
        public void PaintTopInGame(ClipState clipState)
        {
            if (clipState != ClipState.BeforeClip) return;
           
            if (!IsGuardianAlive)
            {
                for (int i = 0; i < 4; i++)
                {
                    StackCount[i] = 0;
                }
               
                return;
            }
           
            foreach (IPlayer player in Hud.Game.Players)
            {
                DrawStackCount(player);
            }
           
            xPos = 0;
        }
    }
}