using System;
using System.Collections.Generic;
using System.Linq;

namespace Turbo.Plugins.Default
{
    public class EliteCirclePlugin : BasePlugin, IInGameWorldPainter, IAfterCollectHandler, ICustomizer
    {
        /************************************************************************/
        /* MonsterCirclePlugin                                                  */
        /* https://github.com/coreyblackgh/HUD-Plugins                          */
        /* and                                                                  */
        /* DiadrasFirstGemPlugin                                                */
        /* https://github.com/User5981/Resu                                     */
        /************************************************************************/
        //public WorldDecoratorCollection ReflectDecorator { get; set; }
        public WorldDecoratorCollection RareDecorator { get; set; }
        public WorldDecoratorCollection ChampionDecorator { get; set; }
        public WorldDecoratorCollection JuggernautDecorator { get; set; }
        public WorldDecoratorCollection GoblinDecorator { get; set; } // Goblin
        public WorldDecoratorCollection UniqueDecorator { get; set; }   //Purple
        public WorldDecoratorCollection BossDecorator { get; set; }   //Boss
        public TopLabelDecorator EliteHealthDecorator { get; set; }
        public WorldDecoratorCollection WormholeDecorator { get; set; }
        public WorldDecoratorCollection WormholeWarningDecorator { get; set; }
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
                TextFont = Hud.Render.CreateFont("tahoma", 10, 255, 0, 0, 0, true, false, 250, 255, 255, 255, true),
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


            var importantBorderBrush = Hud.Render.CreateBrush(128, 0, 0, 0, 2);
            var importantLabelFont = Hud.Render.CreateFont("tahoma", 6f, 255, 255, 255, 255, true, false, false);




            //  ReflectDecorator = new WorldDecoratorCollection(
            //     new GroundLabelDecorator(Hud)
            //     {
            //         BackgroundBrush = Hud.Render.CreateBrush(255, 50, 50, 50, 0),
            //         BorderBrush = Hud.Render.CreateBrush(128, 0, 0, 0, 2),
            //         TextFont = Hud.Render.CreateFont("tahoma", 5f, 200, 220, 120, 0, false, false, false)
            //     }
            //  );



            StrickenMonsterStatus = new Dictionary<uint, Tuple<double, int>>();
            StrickenPropSquare = (int)(Hud.Window.Size.Width / 53.333);
            StrickenInCooldown = false;
            StrickenMonsterCount = 0;

            StrickenStackDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("tahoma", 7, 255, 0, 0, 0, true, false, 250, 255, 255, 255, true),
            };


            WormholeWarningDecorator = new WorldDecoratorCollection(
                 new GroundCircleDecorator(Hud)
                 {
                     Brush = Hud.Render.CreateBrush(205, 255, 50, 255, 3, SharpDX.Direct2D1.DashStyle.Dash),
                     Radius = 5f,
                 },
                 new GroundCircleDecorator(Hud)
                 {
                     Brush = Hud.Render.CreateBrush(205, 255, 50, 255, 0),
                     Radius = 4f,
                 },
                 new GroundLabelDecorator(Hud)
                 {
                     BackgroundBrush = Hud.Render.CreateBrush(0, 0, 0, 0, 0),
                     TextFont = Hud.Render.CreateFont("tahoma", 20, 255, 255, 255, 255, true, true, true),
                 }
             );

            WormholeDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(160, 255, 50, 255, 3, SharpDX.Direct2D1.DashStyle.Dash),
                    Radius = 5f,
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(160, 255, 50, 255, 0),
                    Radius = 4f,
                },
                new GroundLabelDecorator(Hud)
                {
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 255, 255, 255, true, false, 128, 0, 0, 0, true),
                }
            );



        }
        public void OnNewAreaEliteCirclePlugin(bool newGame, ISnoArea area)
        {
            if (newGame)
            {
                StrickenMonsterStatus.Clear();
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
        public bool IsGuardianAlive()
        {
            return riftQuest != null && (riftQuest.QuestStepId == 3 || riftQuest.QuestStepId == 16);
        }
        public void DrawEliteCirclePlugin(WorldLayer layer)
        {
            bool flagNeedShowSteadyAimYard = false;
            if (Hud.Game.Me.HeroClassDefinition.HeroClass == HeroClass.DemonHunter)
            {
                var dhSteadyAimBuff = Hud.Game.Me.Powers.GetBuff(Hud.Sno.SnoPowers.DemonHunter_Passive_SteadyAim.Sno);
                if (dhSteadyAimBuff != null)
                {
                    flagNeedShowSteadyAimYard = true;
                }

                //??
            }



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
                        affixName = snoMonsterAffix.NameLocalized;
                        if (snoMonsterAffix.Affix == MonsterAffix.Juggernaut) flagIsNotJuggernaut = false;
                    }
                    if (monster.Rarity == ActorRarity.Rare)
                    {
                        if (flagIsNotJuggernaut) RareDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
                        else JuggernautDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
                    }
                    if (monster.Rarity == ActorRarity.Champion) ChampionDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);

                    var monsterScreenCoordinate = monster.FloorCoordinate.ToScreenCoordinate();

                    if (IsGuardianAlive())
                    {
                        if (flagNeedShowSteadyAimYard)
                        {
                            string yardStr = monster.NormalizedXyDistanceToMe.ToString("0") + "Yard";
                            EliteHealthDecorator.TextFunc = () => yardStr;
                            EliteHealthDecorator.Paint(monsterScreenCoordinate.X, monsterScreenCoordinate.Y - EliteHealthBlockSize, EliteHealthBlockSize, EliteHealthBlockSize, HorizontalAlign.Center);
                        }
                    }
                    else
                    {
                        if (currentMonsterHealthPercent < 40.0)
                        {
                            string monsterHealthPercentStr = "HP:" + currentMonsterHealthPercent.ToString("0.0") + "%";
                            EliteHealthDecorator.TextFunc = () => monsterHealthPercentStr;
                            EliteHealthDecorator.Paint(monsterScreenCoordinate.X, monsterScreenCoordinate.Y - EliteHealthBlockSize, EliteHealthBlockSize, EliteHealthBlockSize, HorizontalAlign.Center);
                        }
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

            double minDistanceToMe = 999999.0;
            var oculusActors = Hud.Game.Actors.Where(x => x.SnoActor.Sno == ActorSnoEnum._generic_proxy && x.GetAttributeValueAsInt(Hud.Sno.Attributes.Power_Buff_1_Visual_Effect_None, Hud.Sno.SnoPowers.OculusRing.Sno) == 1);
            foreach (var actor in oculusActors)
            {
                if (minDistanceToMe > actor.NormalizedXyDistanceToMe)
                {
                    minDistanceToMe = actor.NormalizedXyDistanceToMe;
                }
            }
            foreach (var actor in oculusActors)
            {
                if (minDistanceToMe == actor.NormalizedXyDistanceToMe && actor.NormalizedXyDistanceToMe < 100)
                {
                    var actorScreenCoordinate = actor.FloorCoordinate.ToScreenCoordinate();
                    Hud.Render.CreateBrush(192, 234, 60, 83, -1).DrawLine(actorScreenCoordinate.X, actorScreenCoordinate.Y, Hud.Game.Me.ScreenCoordinate.X, Hud.Game.Me.ScreenCoordinate.Y + 60, 1.0f);


                    //  StrickenStackDecorator.TextFunc = () => ("(" + (int)(actorScreenCoordinate.X) + "," + (int)(actorScreenCoordinate.Y) + ")");
                    //  StrickenStackDecorator.Paint(actorScreenCoordinate.X, actorScreenCoordinate.Y, StrickenPropSquare, StrickenPropSquare, HorizontalAlign.Center);

                }
            }


            foreach (var actor in Hud.Game.Actors)
            {
                switch (actor.SnoActor.Sno)
                {
                    case ActorSnoEnum._x1_monsteraffix_teleportmines:
                        if (actor.NormalizedXyDistanceToMe <= 6) WormholeWarningDecorator.Paint(layer, actor, actor.FloorCoordinate, "Wormhole!");
                        else WormholeDecorator.Paint(layer, actor, actor.FloorCoordinate, "Wormhole");
                        break;
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
        public void AfterCollect()
        {

        }
        public void Customize()
        {
        }
    }
}