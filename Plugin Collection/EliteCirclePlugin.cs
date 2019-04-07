using System;
using System.Collections.Generic;
using System.Linq;

namespace Turbo.Plugins.Default
{

    public class EliteCirclePlugin : BasePlugin, IInGameWorldPainter
    {

        /************************************************************************/
        /* StrickenPlugin                                                       */
        /************************************************************************/
        public int StrickenRank { get; set; }
        public int propSquare { get; set; }
        public bool cooldown { get; set; }
        public int monsterCount { get; set; }
        public int offsetX { get; set; }
        public int offsetY { get; set; }
        public TopLabelDecorator StrickenStackDecorator { get; set; }
        public TopLabelDecorator StrickenPercentDecorator { get; set; }
        public Dictionary<uint, Tuple<double, int>> MonsterStatus { get; set; }  // AcdId, Health, Stacks
        public void InitStrickenPlugin()
        {
            offsetX = 0;
            offsetY = 0;
            MonsterStatus = new Dictionary<uint, Tuple<double, int>>();
        }
        public void LoadStrickenPlugin()
        {
            StrickenRank = 0;
            propSquare = (int)(Hud.Window.Size.Width / 53.333);
            cooldown = false;
            monsterCount = 0;

            StrickenStackDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("tahoma", 7, 255, 0, 0, 0, true, false, 250, 255, 255, 255, true),
            };

            StrickenPercentDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("tahoma", 6, 255, 255, 255, 255, false, false, 250, 0, 0, 0, true),
            };


        }
        public void OnNewAreaStrickenPlugin(bool newGame, ISnoArea area)
        {
            if (newGame)
            {
                MonsterStatus.Clear();
            }
        }
        public void DrawStrickenPlugin(WorldLayer layer)
        {

            bool StrickenActive = false;
            var jewelsLocations = Hud.Game.Items.Where(x => x.Location == ItemLocation.LeftRing || x.Location == ItemLocation.RightRing || x.Location == ItemLocation.Neck);
            foreach (var StrickenLocation in jewelsLocations)
            {
                if (StrickenLocation.SocketCount != 1 || StrickenLocation.ItemsInSocket == null) continue;
                var Stricken = StrickenLocation.ItemsInSocket.FirstOrDefault();
                if (Stricken == null) continue;
                if (Stricken.SnoItem.Sno == 3249948847) { StrickenActive = true; StrickenRank = Stricken.JewelRank; break; } else { continue; }
            }
            if (StrickenActive == false) return;
            float gemMaths = 0.8f + (0.01f * (float)StrickenRank);
            var Texture = Hud.Texture.GetItemTexture(Hud.Sno.SnoItems.Unique_Gem_018_x1);
            var monsters = Hud.Game.Monsters.OrderBy(i => i.NormalizedXyDistanceToMe);
            foreach (var monster in monsters)
            {
                if (monster.IsAlive && monster.Rarity != ActorRarity.RareMinion && (monster.IsElite || monster.Rarity == ActorRarity.Boss || monster.Rarity == ActorRarity.Champion || monster.Rarity == ActorRarity.Rare))
                {
                    var monsterScreenCoordinate = monster.FloorCoordinate.ToScreenCoordinate();
                    Tuple<double, int> valuesOut;
                    if (MonsterStatus.TryGetValue(monster.AcdId, out valuesOut))
                    {
                        double Health = monster.CurHealth;
                        double prevHealth = valuesOut.Item1;
                        int prevStacks = valuesOut.Item2;

                        if (prevHealth > Health && Hud.Game.Me.Powers.BuffIsActive(Hud.Sno.SnoPowers.BaneOfTheStrickenPrimary.Sno, 2) && monsterCount == 0 && !cooldown)
                        {
                            int Stacks = (int)(prevStacks + 1);
                            Tuple<double, int> updateValues = new Tuple<double, int>(monster.CurHealth, Stacks);
                            MonsterStatus[monster.AcdId] = updateValues;
                            monsterCount++;
                            cooldown = true;
                        }

                        else if (!Hud.Game.Me.Powers.BuffIsActive(Hud.Sno.SnoPowers.BaneOfTheStrickenPrimary.Sno, 2) && cooldown)
                        {
                            cooldown = false;
                            monsterCount = 0;
                            if (prevHealth > Health)
                            {
                                int Stacks = (int)(prevStacks);
                                Tuple<double, int> updateValues = new Tuple<double, int>(monster.CurHealth, Stacks);
                                MonsterStatus[monster.AcdId] = updateValues;
                            }
                        }


                        if (prevStacks > 0)
                        {
                            int bossPerc = 0;
                            if (monster.SnoMonster.Priority == MonsterPriority.boss) { bossPerc = 25; }
                            else { bossPerc = 0; }
                            float StrickenDamagePercent = (float)(bossPerc + (prevStacks * gemMaths));
                            string percentDamageBonus = "+" + StrickenDamagePercent.ToString("0.00") + "%";
                            Texture.Draw(monsterScreenCoordinate.X + offsetX, monsterScreenCoordinate.Y + offsetY, propSquare, propSquare);
                            StrickenStackDecorator.TextFunc = () => prevStacks.ToString();
                            StrickenPercentDecorator.TextFunc = () => percentDamageBonus;
                            StrickenStackDecorator.Paint(monsterScreenCoordinate.X + offsetX, monsterScreenCoordinate.Y + offsetY, propSquare, propSquare, HorizontalAlign.Center);
                            //StrickenPercentDecorator.Paint(monsterScreenCoordinate.X + offsetX, (float)(monsterScreenCoordinate.Y + offsetY + (propSquare / 2.5)), propSquare, propSquare, HorizontalAlign.Right);
                            if (cooldown)
                            {
                                StrickenPercentDecorator.TextFunc = () => "\u231B";
                                StrickenPercentDecorator.Paint((float)(monsterScreenCoordinate.X + offsetX + (propSquare / 2)), monsterScreenCoordinate.Y + offsetY, propSquare, propSquare, HorizontalAlign.Center);
                            }

                        }
                    }
                    else
                    {
                        Tuple<double, int> valuesIn = new Tuple<double, int>(monster.CurHealth, (int)(0));
                        MonsterStatus.Add(monster.AcdId, valuesIn);
                    }

                }
                else
                {
                    MonsterStatus.Remove(monster.AcdId);
                }
            }
        }



        /************************************************************************/
        /* EliteCirclePlugin                                                    */
        /************************************************************************/
        public Dictionary<MonsterAffix, WorldDecoratorCollection> AffixDecorators { get; set; }
        public Dictionary<MonsterAffix, string> CustomAffixNames { get; set; }
        public WorldDecoratorCollection RareDecorator { get; set; }
        public WorldDecoratorCollection ChampionDecorator { get; set; }
        public WorldDecoratorCollection JuggernautDecorator { get; set; }
        public WorldDecoratorCollection GoblinDecorator { get; set; } // Goblin
        //public WorldDecoratorCollection RareMinionDecorator { get; set; }   // Elite Minion
        public WorldDecoratorCollection UniqueDecorator { get; set; }   //Purple
        public WorldDecoratorCollection BossDecorator { get; set; }   //Boss
        public TopLabelDecorator TagDecorator { get; set; }
        public void LoadElitePlugin()
        {


            TagDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("tahoma", 8, 200, 255, 255, 255, true, false, false),
            };

            var shadowBrush = Hud.Render.CreateBrush(96, 0, 0, 0, 1);

            GoblinDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 57, 194, 29, 3),
                    Radius = 3
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 240, 213, 10, 5),
                    Radius = 2
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(180, 255, 0, 0, 6),
                    Radius = 0.3f
                }
            );

            RareDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 148, 20, 3),
                    Radius = 3
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 148, 20, 5),
                    Radius = 2
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(180, 255, 0, 0, 6),
                    Radius = 0.3f
                },
                new MapShapeDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 148, 20, 0),
                    Radius = 6,
                    ShapePainter = new CircleShapePainter(Hud)
                }
            );
            ChampionDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 64, 128, 255, 3),
                    Radius = 3
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 64, 128, 255, 5),
                    Radius = 2
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(180, 255, 0, 0, 6),
                    Radius = 0.3f
                },
                new MapShapeDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 64, 128, 255, 0),
                    Radius = 6,
                    ShapePainter = new CircleShapePainter(Hud)
                }
            );
            JuggernautDecorator = new WorldDecoratorCollection(
                new MapShapeDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 50, 0, 0),
                    ShadowBrush = shadowBrush,
                    Radius = 6,
                    ShapePainter = new CircleShapePainter(Hud),
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 50, 0, 3),
                    Radius = 3,
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 148, 20, 5),
                    Radius = 2
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(180, 255, 0, 0, 6),
                    Radius = 0.3f
                }
                );
            //	RareMinionDecorator = new WorldDecoratorCollection(
            //	    new GroundCircleDecorator(Hud)
            //	    {
            //	        Brush = Hud.Render.CreateBrush(255, 255, 148, 20, 3, SharpDX.Direct2D1.DashStyle.Dash),
            //	        Radius = 3
            //	    },
            //	    new GroundCircleDecorator(Hud)
            //	    {
            //	        Brush = Hud.Render.CreateBrush(180, 255, 0, 0, 6, SharpDX.Direct2D1.DashStyle.Dash),
            //	        Radius = 0
            //	    },
            //	    new MapShapeDecorator(Hud)
            //	    {
            //	        Brush = Hud.Render.CreateBrush(255, 192, 92, 20, 2.0f),
            //	        Radius = 4,
            //	        ShapePainter = new CircleShapePainter(Hud)
            //	    }
            //	);

            UniqueDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 140, 255, 3),
                    Radius = 3
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 140, 255, 5),
                    Radius = 2
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(180, 255, 0, 0, 6),
                    Radius = 0.3f
                },
                new MapShapeDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 140, 255, 0),
                    Radius = 6,
                    ShapePainter = new CircleShapePainter(Hud)
                }
            );

            BossDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 96, 0, 4),
                    Radius = 4
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 96, 0, 5),
                    Radius = 2
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(180, 255, 0, 0, 6),
                    Radius = 0.3f
                },
                new MapShapeDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 96, 0, 0),
                    Radius = 6,
                    ShapePainter = new CircleShapePainter(Hud)
                }
            );

            CustomAffixNames = new Dictionary<MonsterAffix, string>();

            AffixDecorators = new Dictionary<MonsterAffix, WorldDecoratorCollection>();

        }
        public void DrawElitePlugin(WorldLayer layer)
        {
            var alivemonsters = Hud.Game.AliveMonsters;
            var goblins = Hud.Game.AliveMonsters.Where(x => x.SnoMonster.Priority == MonsterPriority.goblin);
            foreach (var monster in goblins)
            {
                GoblinDecorator.Paint(layer, monster, monster.FloorCoordinate, null);
            }
            List<IMonster> monstersElite = new List<IMonster>();
            foreach (var monster in alivemonsters)
            {
                if (monster.Rarity == ActorRarity.Champion || monster.Rarity == ActorRarity.Rare)
                {
                    monstersElite.Add(monster);
                }

                //	if (monster.Rarity == ActorRarity.RareMinion)
                //	{
                //	    RareMinionDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
                //	}

                if (monster.Rarity == ActorRarity.Unique)
                {
                    UniqueDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
                }

                if (monster.Rarity == ActorRarity.Boss)
                {
                    BossDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
                }
            }
            foreach (var monster in monstersElite)
            {
                var currentMonsterHealthPercent = monster.CurHealth * 100.0 / monster.MaxHealth;

                if (monster.SummonerAcdDynamicId == 0)
                {
                    bool flag = true;
                    foreach (var snoMonsterAffix in monster.AffixSnoList)
                    {
                        string affixName = null;
                        if (CustomAffixNames.ContainsKey(snoMonsterAffix.Affix))
                        {
                            affixName = CustomAffixNames[snoMonsterAffix.Affix];
                        }
                        else affixName = snoMonsterAffix.NameLocalized;
                        if (snoMonsterAffix.Affix == MonsterAffix.Juggernaut) flag = false;

                        WorldDecoratorCollection decorator;
                        if (!AffixDecorators.TryGetValue(snoMonsterAffix.Affix, out decorator)) continue;
                        decorator.Paint(layer, monster, monster.FloorCoordinate, affixName);
                    }
                    if (monster.Rarity == ActorRarity.Rare)
                    {
                        if (flag) RareDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
                        else JuggernautDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
                    }
                    if (monster.Rarity == ActorRarity.Champion) ChampionDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);

                }

            }
            monstersElite.Clear();
        }








        /************************************************************************/
        /*                                                                      */
        /************************************************************************/

        public EliteCirclePlugin()
        {
            Enabled = true;
            InitStrickenPlugin();
        }
        public override void Load(IController hud)
        {
            base.Load(hud);
            LoadElitePlugin();
            LoadStrickenPlugin();
        }
        public void OnNewArea(bool newGame, ISnoArea area)
        {
            OnNewAreaStrickenPlugin(newGame, area);
        }
        public void PaintWorld(WorldLayer layer)
        {
            DrawElitePlugin(layer);
            DrawStrickenPlugin(layer);
        }
    }
}