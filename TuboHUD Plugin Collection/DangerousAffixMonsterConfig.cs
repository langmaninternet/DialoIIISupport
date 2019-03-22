namespace Turbo.Plugins.Default
{
    using System;
    using Turbo.Plugins.Default;

    public class DangerousAffixMonsterConfig : BasePlugin, ICustomizer
    {
        public DangerousAffixMonsterConfig()
        {
            Enabled = true;
        }

        public void Customize()
        {
            //Debug(); return;
            Hud.RunOnPlugin<DangerousAffixMonsterPlugin>(plugin =>
            {
                ////////////////////////////////////////////////
                // first, redefine plugin defaults if you want :
                ////////////////////////////////////////////////
                // DEFAULTS //
                //////////////
                // plugin.DefaultMapShapePainter = new CircleShapePainter(Hud);
                // plugin.DefaultRadiusTransformator = new StandardPingRadiusTransformator(Hud, 500);
                // plugin.DefaultBackgroundBrush = Hud.Render.CreateBrush(255, 0, 0, 0, 0);
                // plugin.DefaultForegroundBrush = Hud.Render.CreateBrush(255, 255, 0, 0, 0);
                plugin.DefaultEliteAffixesFont = Hud.Render.CreateFont("tahoma", 6f, 200, 255, 255, 0, false, false, 128, 0, 0, 0, true);
                plugin.DefaultMinionAffixesFont = Hud.Render.CreateFont("tahoma", 2f, 200, 255, 255, 0, false, false, 128, 0, 0, 0, true);
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                // A complete example for Juggernaut overriding all defaults
                // You don't need to redefine everything, it's just for the sake of the example ;p
                /*
                plugin.DefineDangerousAffix(MonsterAffix.Juggernaut,
                    (a) => a.NameLocalized.Substring(0, 3), // or a string like "Jug"
                    priority: 420, // higher first
                    // decorator background
                    bgBrush: Hud.Render.CreateBrush(255, 0, 0, 0, 0), // default
                    bgShapePainter: new CircleShapePainter(Hud), // default new CircleShapePainter(Hud)
                    bgPing: true, // default false
                    bgRadiusTransformator: new StandardPingRadiusTransformator(Hud, 500), // default
                    bgEliteRadius: 8, // default 8
                    bgMinionRadius: 6, // default 6
                    // decorator foreground
                    fgBrush: Hud.Render.CreateBrush(255, 255, 0, 0, 1), // default
                    fgShapePainter: new RotatingTriangleShapePainter(Hud), // default new CircleShapePainter(Hud)
                    fgPing: true, // default false
                    fgRadiusTransformator: new StandardPingRadiusTransformator(Hud, 500), // default
                    fgEliteRadius: 6, // default 6
                    fgMinionRadius: 2, // default 2
                    // labels fonts
                    eliteFont: Hud.Render.CreateFont("tahoma", 10f, 200, 255, 0, 0, false, false, 128, 0, 0, 0, true),
                    minionFont: Hud.Render.CreateFont("tahoma", 7f, 200, 255, 0, 0, false, false, 128, 0, 0, 0, true),
                    // minions
                    showMinionDecorators: false, // default false
                    showMinionAffixesNames: false // default false
                );
                plugin.DefineDangerousAffix(MonsterAffix.Illusionist, 
                (a) => a.NameLocalized.Substring(0, 1),

                    fgEliteRadius: 2, // default 6
                    bgEliteRadius: 4, // default 8

                    eliteFont: Hud.Render.CreateFont("tahoma", 8f, 200, 255, 0, 0, false, false, 128, 0, 0, 0, true)
                );
             //   plugin.DefineDangerousAffix(MonsterAffix.Reflect, (a) => a.NameLocalized.Substring(0, 1));
            //    plugin.DefineDangerousAffix(MonsterAffix.Poison, (a) => a.NameLocalized.Substring(0, 1),
            //        fgBrush: Hud.Render.CreateBrush(255, 0, 250, 0, 0),
            //        eliteFont: Hud.Render.CreateFont("tahoma", 10f, 200, 0, 250, 0, false, false, 128, 0, 0, 0, true),
            //        minionFont: Hud.Render.CreateFont("tahoma", 7f, 200, 0, 250, 0, false, false, 128, 0, 0, 0, true)
             //   );
            //    plugin.DefineDangerousAffix(MonsterAffix.Arcane, (a) => a.NameLocalized.Substring(0, 2));
            //    plugin.DefineDangerousAffix(MonsterAffix.Shielding, (a) => a.NameLocalized.Substring(0, 4));
                //plugin.DefineDangerousAffix(MonsterAffix.Molten, (a) => a.NameLocalized.Substring(0, 4));
                */
            plugin.DefineDangerousAffix(MonsterAffix.Teleporter, (a) => a.NameLocalized.Substring(0, 1),

                    fgEliteRadius: 2, // default 6
                    bgEliteRadius: 4 // default 8
                    );

                plugin.DefineDangerousAffix(MonsterAffix.Wormhole, (a) => a.NameLocalized.Substring(0, 1),
                    priority: 520, // higher first

// decorator background
                    bgBrush: Hud.Render.CreateBrush(255, 0, 0, 0, 0), // default
                    bgShapePainter: new CircleShapePainter(Hud), // default new CircleShapePainter(Hud)
                    bgPing: false, // default false
                    bgRadiusTransformator: new StandardPingRadiusTransformator(Hud, 500), // default
                    bgEliteRadius: 7, // default 8
                    bgMinionRadius: 6, // default 6
                    // decorator foreground
                    fgBrush: Hud.Render.CreateBrush(255, 255, 0, 0, 1), // default
                    fgShapePainter: new RotatingTriangleShapePainter(Hud), // default new CircleShapePainter(Hud)
                    fgPing: true, // default false
                    fgRadiusTransformator: new StandardPingRadiusTransformator(Hud, 500), // default
                    fgEliteRadius: 5, // default 6
                    fgMinionRadius: 2 // default 2
                    );

           //     plugin.DefineDangerousAffix(MonsterAffix.Waller, string.Empty);
//
                // disable all MapShapeDecorators
                //foreach (MonsterAffix affix in Enum.GetValues(typeof(MonsterAffix)))
                //{
                //    if (plugin.Affixes.ContainsKey(affix))
                //        plugin.Affixes[affix].EliteDecorators.ToggleDecorators<MapShapeDecorator>(false);
                //}
            });

            // the config is done, disable this plugin
            Enabled = false;
        }

        public void Debug()
        {
            Hud.RunOnPlugin<DangerousAffixMonsterPlugin>(plugin =>
            {
                var p = 420;
                foreach (MonsterAffix affix in Enum.GetValues(typeof(MonsterAffix)))
                {
                    plugin.DefineDangerousAffix(affix,
                        (a) => a.NameLocalized.Substring(0, 3), // or a string like "Jug"
                        priority: p--, // higher first
                        // decorator background
                        bgBrush: Hud.Render.CreateBrush(255, 0, 0, 0, 0),
                        bgShapePainter: new CircleShapePainter(Hud), // default new CircleShapePainter(Hud)
                        bgPing: true, // default false
                        bgRadiusTransformator: new StandardPingRadiusTransformator(Hud, 666),
                        bgEliteRadius: 8, // default 8
                        bgMinionRadius: 6, // default 6
                        // decorator foreground
                        fgBrush: Hud.Render.CreateBrush(255, 255, 0, 0, 1),
                        fgShapePainter: new RotatingTriangleShapePainter(Hud), // default new CircleShapePainter(Hud)
                        fgPing: false, // default false
                        fgRadiusTransformator: new StandardPingRadiusTransformator(Hud, 666),
                        fgEliteRadius: 6, // default 6
                        fgMinionRadius: 2, // default 2
                        // labels fonts
                        eliteFont: Hud.Render.CreateFont("tahoma", 10f, 200, 255, 0, 0, false, false, 128, 0, 0, 0, true),
                        minionFont: Hud.Render.CreateFont("tahoma", 7f, 200, 255, 0, 0, false, false, 128, 0, 0, 0, true),
                        // minions
                        showMinionDecorators: true, // default false
                        showMinionAffixesNames: true // default false
                        );
                }
            });
        }
    }
}