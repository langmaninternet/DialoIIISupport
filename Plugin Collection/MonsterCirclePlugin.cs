using System.Collections.Generic;
using System.Linq;

namespace Turbo.Plugins.Default
{

    public class MonsterCirclePlugin : BasePlugin, IInGameWorldPainter
    {

        public Dictionary<MonsterAffix, WorldDecoratorCollection> AffixDecorators { get; set; }
        public Dictionary<MonsterAffix, string> CustomAffixNames { get; set; }
        public WorldDecoratorCollection RareDecorator { get; set; }
        public WorldDecoratorCollection ChampionDecorator { get; set; }
        public WorldDecoratorCollection JuggernautDecorator { get; set; }
        public WorldDecoratorCollection GoblinDecorator { get; set; } // Goblin
        public WorldDecoratorCollection RareMinionDecorator { get; set; }   // Elite Minion
        public WorldDecoratorCollection UniqueDecorator { get; set; }   //Purple
        public WorldDecoratorCollection BossDecorator { get; set; }   //Boss

        public TopLabelDecorator TagDecorator { get; set; }



        public MonsterCirclePlugin()
        {
            Enabled = true;
        }

        public override void Load(IController hud)
        {
            base.Load(hud);

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
            RareMinionDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 148, 20, 3, SharpDX.Direct2D1.DashStyle.Dash),
                    Radius = 3
                },
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(180, 255, 0, 0, 6, SharpDX.Direct2D1.DashStyle.Dash),
                    Radius = 0
                },
                new MapShapeDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 192, 92, 20, 2.0f),
                    Radius = 4,
                    ShapePainter = new CircleShapePainter(Hud)
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

        }

        public void PaintWorld(WorldLayer layer)
        {
            var monsters = Hud.Game.AliveMonsters;
            var goblins = Hud.Game.AliveMonsters.Where(x => x.SnoMonster.Priority == MonsterPriority.goblin);
            foreach (var monster in goblins)
            {
                GoblinDecorator.Paint(layer, monster, monster.FloorCoordinate, null);
            }

            List<IMonster> monstersElite = new List<IMonster>();
            foreach (var monster in monsters)
            {
                if (monster.Rarity == ActorRarity.Champion || monster.Rarity == ActorRarity.Rare)
                {
                    monstersElite.Add(monster);
                }

                if (monster.Rarity == ActorRarity.RareMinion)
                {
                    RareMinionDecorator.Paint(layer, monster, monster.FloorCoordinate, monster.SnoMonster.NameLocalized);
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
                var currentHealthPercent = monster.CurHealth * 100.0 / monster.MaxHealth;

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
    }
}