namespace Turbo.Plugins.Default
{
    public class PlayerSkillPlugin : BasePlugin, IInGameWorldPainter
    {
        public WorldDecoratorCollection HydraDecorator { get; set; }
        public WorldDecoratorCollection SentryDecorator { get; set; }
        public WorldDecoratorCollection SentryWithCustomEngineeringDecorator { get; set; }
        public WorldDecoratorCollection BlackHoleDecorator { get; set; }
        public WorldDecoratorCollection PiranhadoDecorator { get; set; }
        public WorldDecoratorCollection SpiritWalkDecorator { get; set; }
        public WorldDecoratorCollection SpiritWalkWithJauntDecorator { get; set; }
        public WorldDecoratorCollection BigBadVoodooDecorator { get; set; }
        public WorldDecoratorCollection BigBadVoodooWithJungleDrumsDecorator { get; set; }
        public WorldDecoratorCollection InnerSanctuaryDefaultDecorator { get; set; }
        public WorldDecoratorCollection InnerSanctuaryTempleOfProtecteionDecorator { get; set; }
        public WorldDecoratorCollection InnerSanctuarySafeHavenDecorator { get; set; }
        public WorldDecoratorCollection InnerSanctuarySanctifiedGroundDecorator { get; set; }

        public PlayerSkillPlugin()
        {
            Enabled = true;
        }

        public override void Load(IController hud)
        {
            base.Load(hud);

            HydraDecorator = new WorldDecoratorCollection(
                new MapShapeDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 100, 100, 2),
                    ShadowBrush = Hud.Render.CreateBrush(96, 0, 0, 0, 1),
                    ShapePainter = new TriangleShapePainter(Hud),
                    Radius = 4f,
                },
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 15,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 255, 200, 200, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 15,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(230, 255, 50, 50, 0),
                    Radius = 30,
                }
                );

            SentryDecorator = new WorldDecoratorCollection(
                new MapShapeDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 240, 148, 32, 2),
                    ShadowBrush = Hud.Render.CreateBrush(96, 0, 0, 0, 1),
                    ShapePainter = new TriangleShapePainter(Hud),
                    Radius = 4f,
                },
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 30,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 240, 148, 32, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 30,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(160, 240, 148, 32, 0),
                    Radius = 30,
                }
                );

            SentryWithCustomEngineeringDecorator = new WorldDecoratorCollection(
                new MapShapeDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 240, 148, 32, 2),
                    ShadowBrush = Hud.Render.CreateBrush(96, 0, 0, 0, 1),
                    ShapePainter = new TriangleShapePainter(Hud),
                    Radius = 4f,
                },
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 60,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 240, 148, 32, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 60,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(160, 240, 148, 32, 0),
                    Radius = 30,
                }
                );

            BlackHoleDecorator = new WorldDecoratorCollection(
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 2,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 255, 200, 200, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 2,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(230, 255, 50, 50, 0),
                    Radius = 30,
                }
                );

            PiranhadoDecorator = new WorldDecoratorCollection(
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 4,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 100, 255, 150, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 4,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(160, 100, 255, 150, 0),
                    Radius = 30,
                }
                );

            SpiritWalkDecorator = new WorldDecoratorCollection(
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 2,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 255, 150, 255, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 2,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(160, 255, 150, 255, 0),
                    Radius = 30,
                }
                );

            SpiritWalkWithJauntDecorator = new WorldDecoratorCollection(
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 3,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 255, 150, 255, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 3,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(160, 255, 150, 255, 0),
                    Radius = 30,
                }
                );

            BigBadVoodooDecorator = new WorldDecoratorCollection(
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 20,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 100, 200, 100, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 20,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(160, 100, 200, 100, 0),
                    Radius = 30,
                }
                );

            BigBadVoodooWithJungleDrumsDecorator = new WorldDecoratorCollection(
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 30,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 100, 200, 100, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 30,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(160, 100, 200, 100, 0),
                    Radius = 30,
                }
                );

            InnerSanctuaryDefaultDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 30, 30, 10),
                    Radius = 11,
                },
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 6,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 100, 255, 150, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 6,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(100, 255, 30, 30, 0),
                    Radius = 35,
                }
            );

            InnerSanctuarySanctifiedGroundDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 30, 30, 10),
                    Radius = 11,
                },
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 8,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 100, 255, 150, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 8,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(100, 255, 30, 30, 0),
                    Radius = 35,
                }
            );

            InnerSanctuaryTempleOfProtecteionDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(255, 255, 204, 0, 4),
                    Radius = 11,
                },
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 6,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 100, 255, 150, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 6,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(100, 255, 204, 0, 0),
                    Radius = 35,
                }
            );

            InnerSanctuarySafeHavenDecorator = new WorldDecoratorCollection(
                new GroundCircleDecorator(Hud)
                {
                    Brush = Hud.Render.CreateBrush(100, 255, 26, 179, 4),
                    Radius = 11,
                },
                new GroundLabelDecorator(Hud)
                {
                    CountDownFrom = 6,
                    TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 100, 255, 150, true, false, 128, 0, 0, 0, true),
                },
                new GroundTimerDecorator(Hud)
                {
                    CountDownFrom = 6,
                    BackgroundBrushEmpty = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                    BackgroundBrushFill = Hud.Render.CreateBrush(100, 255, 26, 179, 0),
                    Radius = 35,
                }
            );
        }

        public void PaintWorld(WorldLayer layer)
        {
            var actors = Hud.Game.Actors;
            foreach (var actor in actors)
            {
                if (actor.SummonerAcdDynamicId == Hud.Game.Me.SummonerId)
                {
                    switch (actor.SnoActor.Sno)
                    {
                        case ActorSnoEnum._wizard_hydrahead_lightning_3: // light
                        case ActorSnoEnum._wizard_hydrahead_arcane_3: // arcane
                        case ActorSnoEnum._wizard_hydrahead_fire2_1:
                        case ActorSnoEnum._wizard_hydrahead_frost_2:
                            HydraDecorator.Paint(layer, actor, actor.FloorCoordinate.Offset(2f, 2f, 0), null);
                            break;
                        case ActorSnoEnum._wizard_hydrahead_big: // mammoth
                            HydraDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                            break;
                        case ActorSnoEnum._dh_sentry:
                        case ActorSnoEnum._dh_sentry_addsmissiles:
                        case ActorSnoEnum._dh_sentry_addsduration:
                        case ActorSnoEnum._dh_sentry_tether:
                        case ActorSnoEnum._dh_sentry_addsheals:
                        case ActorSnoEnum._dh_sentry_addsshield:
                            if (!Hud.Game.Me.Powers.BuffIsActive(208610, 0))
                            {
                                SentryDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                            }
                            else
                            {
                                SentryWithCustomEngineeringDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                            }

                            break;
                        case ActorSnoEnum._x1_wizard_blackhole_cosmicgate_proxy:
                        case ActorSnoEnum._x1_wizard_blackhole_eventhorizon_proxy:
                        case ActorSnoEnum._x1_wizard_blackhole_supermassive_proxy:
                        case ActorSnoEnum._x1_wizard_blackhole_absolutezero_proxy:
                        case ActorSnoEnum._x1_wizard_blackhole_spellsteal_proxy:
                            BlackHoleDecorator.Paint(layer, actor, actor.FloorCoordinate.Offset(0, 0, 5.2f), null);
                            break;
                        case ActorSnoEnum._witchdoctor_spiritwalk_dummy_female:
                        case ActorSnoEnum._witchdoctor_spiritwalk_dummy:
                            {
                                var skill = Hud.Game.Me.Powers.UsedWitchDoctorPowers.SpiritWalk;
                                if (skill != null)
                                {
                                    if (skill.Rune == 1)
                                    {
                                        SpiritWalkWithJauntDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                                    }
                                    else
                                    {
                                        SpiritWalkDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                                    }
                                }
                            }

                            break;
                        case ActorSnoEnum._witchdoctor_bigbadvoodoo_fetish:
                        case ActorSnoEnum._witchdoctor_bigbadvoodoo_fetish_blue:
                        case ActorSnoEnum._witchdoctor_bigbadvoodoo_fetish_purple:
                        case ActorSnoEnum._witchdoctor_bigbadvoodoo_fetish_red:
                        case ActorSnoEnum._witchdoctor_bigbadvoodoo_fetish_yellow:
                            {
                                var skill = Hud.Game.Me.Powers.UsedWitchDoctorPowers.BigBadVoodoo;
                                if (skill != null)
                                {
                                    if (skill.Rune == 1)
                                    {
                                        BigBadVoodooWithJungleDrumsDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                                    }
                                    else
                                    {
                                        BigBadVoodooDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                                    }
                                }
                            }

                            break;
                    }
                }

                switch (actor.SnoActor.Sno)
                {
                    case ActorSnoEnum._x1_wd_piranha_tornado_proxy:
                        PiranhadoDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                        break;
                    case ActorSnoEnum._monk_innersanctuaryrune_duration_proxy:
                        InnerSanctuarySanctifiedGroundDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                        break;
                    case ActorSnoEnum._x1_monk_innersanctuaryrune_forbidden_proxy:
                    case ActorSnoEnum._x1_monk_innersanctuaryrune_intervene_proxy:
                    case ActorSnoEnum._x1_monk_innersanctuary_proxy:
                        InnerSanctuaryDefaultDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                        break;
                    case ActorSnoEnum._x1_monk_innersanctuaryrune_healing_proxy:
                        InnerSanctuarySafeHavenDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                        break;
                    case ActorSnoEnum._x1_monk_innersanctuaryrune_protect_proxy:
                        InnerSanctuaryTempleOfProtecteionDecorator.Paint(layer, actor, actor.FloorCoordinate, null);
                        break;
                }
            }
        }
    }
}