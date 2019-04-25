using System;
using System.Collections.Generic;
using System.Linq;

namespace Turbo.Plugins.Default
{
    public class EliteCirclePlugin : BasePlugin, IInGameWorldPainter
    {
        /************************************************************************/
        /* MonsterCirclePlugin                                                  */
        /* https://github.com/coreyblackgh/HUD-Plugins                          */
        /* and                                                                  */
        /* DiadrasFirstGemPlugin                                                */
        /* https://github.com/User5981/Resu                                     */
        /************************************************************************/
        public Dictionary<MonsterAffix, WorldDecoratorCollection> AffixDecorators { get; set; }
        public Dictionary<MonsterAffix, string> CustomAffixNames { get; set; }
        public WorldDecoratorCollection RareDecorator { get; set; }
        public WorldDecoratorCollection ChampionDecorator { get; set; }
        public WorldDecoratorCollection JuggernautDecorator { get; set; }
        public WorldDecoratorCollection GoblinDecorator { get; set; } // Goblin
        public WorldDecoratorCollection UniqueDecorator { get; set; }   //Purple
        public WorldDecoratorCollection BossDecorator { get; set; }   //Boss
        public TopLabelDecorator EliteHealthDecorator { get; set; }
        public int EliteHealthBlockSize;
        public int StrickenPropSquare { get; set; }
        public bool StrickenInCooldown { get; set; }
        public int StrickenMonsterCount { get; set; }
        public TopLabelDecorator StrickenStackDecorator { get; set; }
        public Dictionary<uint, Tuple<double, int>> StrickenMonsterStatus { get; set; }  // AcdId, Health, Stacks
        public void LoadEliteCirclePlugin()
        {
            EliteHealthDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("tahoma", 10, 255, 255, 255, 255, true, false, true),
            };
            EliteHealthBlockSize = (int)(Hud.Window.Size.Width / 50);

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




            StrickenMonsterStatus = new Dictionary<uint, Tuple<double, int>>();
            StrickenPropSquare = (int)(Hud.Window.Size.Width / 53.333);
            StrickenInCooldown = false;
            StrickenMonsterCount = 0;

            StrickenStackDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("tahoma", 7, 255, 0, 0, 0, true, false, 250, 255, 255, 255, true),
            };



        }
        public void OnNewAreaEliteCirclePlugin(bool newGame, ISnoArea area)
        {
            if (newGame)
            {
                StrickenMonsterStatus.Clear();
            }
        }
        public void DrawEliteCirclePlugin(WorldLayer layer)
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
                if (monster.SummonerAcdDynamicId == 0)
                {
                    var currentMonsterHealthPercent = monster.CurHealth * 100.0 / monster.MaxHealth;

                    bool flagIsNotJuggernaut = true;
                    foreach (var snoMonsterAffix in monster.AffixSnoList)
                    {
                        string affixName = null;
                        if (CustomAffixNames.ContainsKey(snoMonsterAffix.Affix))
                        {
                            affixName = CustomAffixNames[snoMonsterAffix.Affix];
                        }
                        else affixName = snoMonsterAffix.NameLocalized;
                        if (snoMonsterAffix.Affix == MonsterAffix.Juggernaut) flagIsNotJuggernaut = false;

                        WorldDecoratorCollection decorator;
                        if (!AffixDecorators.TryGetValue(snoMonsterAffix.Affix, out decorator)) continue;
                        decorator.Paint(layer, monster, monster.FloorCoordinate, affixName);
                    }
                    if (monster.Rarity == ActorRarity.Rare)
                    {
                        if (flagIsNotJuggernaut) RareDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
                        else JuggernautDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
                    }
                    if (monster.Rarity == ActorRarity.Champion) ChampionDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);

                    var monsterScreenCoordinate = monster.FloorCoordinate.ToScreenCoordinate();
                    if (currentMonsterHealthPercent < 40.0)
                    {
                        string monsterHealthPercentStr = "HP:" + currentMonsterHealthPercent.ToString("0.0") + "%";
                        EliteHealthDecorator.TextFunc = () => monsterHealthPercentStr;
                        EliteHealthDecorator.Paint(monsterScreenCoordinate.X, monsterScreenCoordinate.Y - EliteHealthBlockSize, EliteHealthBlockSize, EliteHealthBlockSize, HorizontalAlign.Center);
                    }
                    if (currentMonsterHealthPercent < 20.0)
                    {
                        Hud.Render.CreateBrush(192, 255, 255, 55, -1).DrawLine(monsterScreenCoordinate.X, monsterScreenCoordinate.Y, Hud.Game.Me.ScreenCoordinate.X, Hud.Game.Me.ScreenCoordinate.Y + 60, 1.0f);
                    }
                }
            }

            bool StrickenActive = false;
            foreach (var StrickenLocation in Hud.Game.Items.Where(x => x.Location == ItemLocation.LeftRing || x.Location == ItemLocation.RightRing || x.Location == ItemLocation.Neck))
            {
                if (StrickenLocation.SocketCount != 1 || StrickenLocation.ItemsInSocket == null) continue;
                var Stricken = StrickenLocation.ItemsInSocket.FirstOrDefault();
                if (Stricken == null) continue;
                if (Stricken.SnoItem.Sno == 3249948847) { StrickenActive = true; break; } else { continue; }
            }
            if (StrickenActive)
            {
                var Texture = Hud.Texture.GetItemTexture(Hud.Sno.SnoItems.Unique_Gem_018_x1);
                foreach (var monster in monstersElite)
                {
                    if (monster.IsAlive)
                    {
                        var monsterScreenCoordinate = monster.FloorCoordinate.ToScreenCoordinate();
                        Tuple<double, int> valuesOut;
                        if (StrickenMonsterStatus.TryGetValue(monster.AcdId, out valuesOut))
                        {
                            double monHealth = monster.CurHealth;
                            double prevHealth = valuesOut.Item1;
                            int prevStacks = valuesOut.Item2;

                            if (prevHealth > monHealth && Hud.Game.Me.Powers.BuffIsActive(Hud.Sno.SnoPowers.BaneOfTheStrickenPrimary.Sno, 2) && StrickenMonsterCount == 0 && !StrickenInCooldown)
                            {
                                int Stacks = (int)(prevStacks + 1);
                                Tuple<double, int> updateValues = new Tuple<double, int>(monster.CurHealth, Stacks);
                                StrickenMonsterStatus[monster.AcdId] = updateValues;
                                StrickenMonsterCount++;
                                StrickenInCooldown = true;
                            }

                            else if (!Hud.Game.Me.Powers.BuffIsActive(Hud.Sno.SnoPowers.BaneOfTheStrickenPrimary.Sno, 2) && StrickenInCooldown)
                            {
                                StrickenInCooldown = false;
                                StrickenMonsterCount = 0;
                                if (prevHealth > monHealth)
                                {
                                    int Stacks = (int)(prevStacks);
                                    Tuple<double, int> updateValues = new Tuple<double, int>(monster.CurHealth, Stacks);
                                    StrickenMonsterStatus[monster.AcdId] = updateValues;
                                }
                            }
                            if (prevStacks > 0)
                            {
                                Texture.Draw(monsterScreenCoordinate.X, monsterScreenCoordinate.Y, StrickenPropSquare, StrickenPropSquare);
                                StrickenStackDecorator.TextFunc = () => prevStacks.ToString();
                                StrickenStackDecorator.Paint(monsterScreenCoordinate.X, monsterScreenCoordinate.Y, StrickenPropSquare, StrickenPropSquare, HorizontalAlign.Center);
                            }
                        }
                        else
                        {
                            Tuple<double, int> valuesIn = new Tuple<double, int>(monster.CurHealth, (int)(0));
                            StrickenMonsterStatus.Add(monster.AcdId, valuesIn);
                        }
                    }
                    else
                    {
                        StrickenMonsterStatus.Remove(monster.AcdId);
                    }
                }
            }


            var shrines = Hud.Game.Shrines.Where(s => (s.Type == ShrineType.PoolOfReflection || s.Type == ShrineType.BanditShrine));
            foreach (var shrine in shrines)
            {
                if (shrine.IsDisabled == false && shrine.IsOperated == false)
                {
                    var monsterScreenCoordinate = shrine.FloorCoordinate.ToScreenCoordinate();
                    Hud.Render.CreateBrush(192, 255, 255, 55, -1).DrawLine(monsterScreenCoordinate.X, monsterScreenCoordinate.Y, Hud.Game.Me.ScreenCoordinate.X, Hud.Game.Me.ScreenCoordinate.Y + 60, 1.0f);
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
        }
        public override void Load(IController hud)
        {
            base.Load(hud);
            LoadEliteCirclePlugin();
        }
        public void OnNewArea(bool newGame, ISnoArea area)
        {
            OnNewAreaEliteCirclePlugin(newGame, area);
        }
        public void PaintWorld(WorldLayer layer)
        {
            DrawEliteCirclePlugin(layer);
        }
    }
}