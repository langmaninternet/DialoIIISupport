using System.Linq;
using System.Collections.Generic;
using Turbo.Plugins.Default;

namespace Turbo.Plugins.Default
{
    public class EliteBarPlugin : BasePlugin, IInGameWorldPainter
    {
		public WorldDecoratorCollection HitBoxDecorator { get; set; }                    
        public IFont LightFont { get; set; }
        public IFont RedFont { get; set; }
        public IFont NameFont { get; set; }
        public IBrush BackgroundBrush { get; set; }
        public IBrush BorderBrush { get; set; }
        public IBrush RareBrush { get; set; }
        public IBrush RareJuggerBrush { get; set; }
        public IBrush RareMinionBrush { get; set; }
        public IBrush ChampionBrush { get; set; }
        public IBrush BossBrush { get; set; }
        public bool JuggernautHighlight { get; set; }
        public bool MissingHighlight { get; set; }
        public bool ShowRareMinions { get ; set; }
        public bool ShowDebuffAndCC { get; set; }
        public bool ShowBossHitBox { get; set; }
        public bool ShowMonsterType { get; set; }
        public bool CircleNonIllusion { get; set; }
        public float XPos { get; set; }
        public float YPos { get; set; }
        public float XScaling { get; set; }
        public float YScaling { get; set; }
        public string PercentageDescriptor { get; set; }
        public Dictionary<MonsterAffix, string> DisplayAffix;
        private float px, py, h, w2;
 
        public EliteBarPlugin()
        {
            Enabled = true;
        }
 
        public override void Load(IController hud)
        {
            base.Load(hud);
            
            //Configuration
            MissingHighlight = true;
            JuggernautHighlight = true;
            CircleNonIllusion = true;
            ShowRareMinions = false;
            ShowDebuffAndCC = true;
            ShowBossHitBox = true; 
            ShowMonsterType = true;
            XScaling = 1.0f;
            YScaling = 1.0f;
            PercentageDescriptor = "0.00";
            XPos = Hud.Window.Size.Width * 0.125f;
            YPos = Hud.Window.Size.Height * 0.0333f;
            DisplayAffix = new Dictionary<MonsterAffix, string>();

            //Colorization
            LightFont = Hud.Render.CreateFont("tahoma", 6f, 160, 255, 255, 255, false, false, true);
            RedFont = Hud.Render.CreateFont("tahoma", 6f, 200, 255, 0, 0, false, false, true);
            NameFont = Hud.Render.CreateFont("tahoma", 6f, 200, 255, 255, 255, false, false, true);
            BackgroundBrush = Hud.Render.CreateBrush(255, 125, 120, 120, 0);
            BorderBrush = Hud.Render.CreateBrush(255, 255, 255, 255, 1);
            RareBrush = Hud.Render.CreateBrush(255, 255, 128, 0, 0);
            RareJuggerBrush = Hud.Render.CreateBrush(255, 225, 100, 50, 0);
            RareMinionBrush = Hud.Render.CreateBrush(220, 200, 100, 0, 0);
            ChampionBrush = Hud.Render.CreateBrush(255, 0, 128, 255, 0);
            BossBrush = Hud.Render.CreateBrush(255, 200, 20, 0, 0);
            
            //HitBoxDecorator for Bosses and NonClone-Illusionist
            HitBoxDecorator = new WorldDecoratorCollection(
				new GroundCircleDecorator(Hud) {
                    Brush = Hud.Render.CreateBrush(255, 57, 194, 29, 3),
                    Radius = -1
                }
            );
        }	
		
        private void DrawHealthBar(WorldLayer layer, IMonster m, ref float yref){
            if (m.Rarity == ActorRarity.RareMinion && !ShowRareMinions) return;     //no minions
            if (m.SummonerAcdDynamicId != 0) return;                                //no clones
            var w = m.CurHealth * w2 / m.MaxHealth;
            var per = LightFont.GetTextLayout((m.CurHealth * 100 / m.MaxHealth).ToString(PercentageDescriptor)+ "%");
            var y = YPos + py * 8 * yref;
            IBrush cBrush = null;
            IFont cFont = null;

            //Brush selection
            switch(m.Rarity){
                case ActorRarity.Boss:
                    cBrush = BossBrush;
                    break;
                case ActorRarity.Champion:
                    cBrush = ChampionBrush;
                    break;
                case ActorRarity.Rare:
                    cBrush = RareBrush;
                    break;
                case ActorRarity.RareMinion:
                    cBrush = RareMinionBrush;
                    break;
                default:
                    cBrush = BackgroundBrush;
                    break;
            }

            //Jugger Highlight
            if (JuggernautHighlight && m.Rarity == ActorRarity.Rare && HasAffix(m, MonsterAffix.Juggernaut)){
                cFont = RedFont;
                cBrush = RareJuggerBrush;
            }
            else
                cFont = NameFont;

            //Missing Highlight
            if (MissingHighlight && (m.Rarity == ActorRarity.Champion || m.Rarity == ActorRarity.Rare) && !m.IsOnScreen){
                var missing = RedFont.GetTextLayout("\u26A0");
                RedFont.DrawText(missing, XPos - 17, y - py);
            }

            //Circle Non-Clones and Boss
            if (CircleNonIllusion && m.SummonerAcdDynamicId == 0 && HasAffix(m, MonsterAffix.Illusionist) || m.Rarity == ActorRarity.Boss && ShowBossHitBox)
                    HitBoxDecorator.Paint(layer, m, m.FloorCoordinate, string.Empty);
            
            //Show Debuffs on Monster
            if (ShowDebuffAndCC){            
                string textDebuff = null;
                if (m.Locust) textDebuff += (textDebuff == null ? "" : ", ") + "Locust";
                if (m.Palmed) textDebuff += (textDebuff == null ? "" : ", ") + "Palm";
                if (m.Haunted) textDebuff += (textDebuff == null ? "" : ", ") + "Haunt";
                if (m.MarkedForDeath) textDebuff += (textDebuff == null ? "" : ", ") + "Mark";
                if (m.Strongarmed) textDebuff += (textDebuff == null ? "" : ", ") + "Strongarm";
                string textCC = null;
                if (m.Frozen) textCC += (textCC == null ? "" : ", ") + "Frozen";
                if (m.Chilled) textCC += (textCC == null ? "" : ", ") + "Chill";
                if (m.Slow) textCC += (textCC == null ? "" : ", ") + "Slow";
                if (m.Stunned) textCC += (textCC == null ? "" : ", ") + "Stun";
                if (m.Invulnerable) textCC += (textCC == null ? "" : ", ") + "Invulnerable";
                if (m.Blind) textCC += (textCC == null ? "" : ", ") + "Blind";
                var d = LightFont.GetTextLayout(textDebuff + (textDebuff != null && textCC != null ? " | " : "") + textCC);
                LightFont.DrawText(d, XPos + 65 + w2, y - py);
            }

            //Draw Rectangles
            BackgroundBrush.DrawRectangle(XPos, y, w2, h);
            BorderBrush.DrawRectangle(XPos, y, w2, h);
            cBrush.DrawRectangle(XPos, y, (float)w, h);
            LightFont.DrawText(per, XPos + 8 + w2, y - py);
            
            //Draw MonsterType
            if (ShowMonsterType){
                var name = cFont.GetTextLayout(m.SnoMonster.NameLocalized);
                cFont.DrawText(name, XPos + 3, y - py);
            }

            //increase linecount
            yref += 1.0f;
        }

        private void DrawPack(WorldLayer layer, IMonsterPack p, ref float yref){
            //Check if any affixes are wished to be displayed
            if (DisplayAffix.Any()){
                string dAffix = "";                               
                foreach(ISnoMonsterAffix afx in p.AffixSnoList){        //iterate affix list
                    if (DisplayAffix.Keys.Contains(afx.Affix))          //if affix is an key
                        dAffix += DisplayAffix[afx.Affix] + " ";        //add to output
                }
                if (!string.IsNullOrEmpty(dAffix)){
                    var d = LightFont.GetTextLayout(dAffix);
                    var y = YPos + py * 8 * yref;
                    LightFont.DrawText(d, XPos, y - py);
                    yref += 1.0f;
                }
            }
            //iterate all alive monsters of pack and print healthbars
            foreach(IMonster m in p.MonstersAlive)
                DrawHealthBar(layer, m, ref yref);
        }

        private bool HasAffix(IMonster m, MonsterAffix afx){
            return m.AffixSnoList.Any(a => a.Affix == afx);
        }

        public void PaintWorld(WorldLayer layer)
        {
            //Spacing
            px = Hud.Window.Size.Width *  0.00155f * XScaling;
            py = Hud.Window.Size.Height * 0.001667f * YScaling;
            h = py * 6;
            w2 = px * 60;

            var packs = Hud.Game.MonsterPacks.Where(x => x.MonstersAlive.Any());
            var bosses = Hud.Game.AliveMonsters.Where(m => m.Rarity == ActorRarity.Boss);

            float yref = 0f;
            foreach(IMonster m in bosses)
                DrawHealthBar(layer, m, ref yref);
            yref += 0.5f;                                           //spacing between RG and Elites
            foreach(IMonsterPack p in packs){
                DrawPack(layer, p, ref yref);
                yref += 0.5f;                                       //spacing between Elites
            }
		}
    }
 
}