using System.Linq;
using System.Collections.Generic;
using System;
using Turbo.Plugins.Default;
 
namespace Turbo.Plugins.Default
{
 
    public class ImpalePlugin : BasePlugin, IInGameWorldPainter
    {   
        public WorldDecoratorCollection RedHitBoxDecorator { get; set; }
        public WorldDecoratorCollection GreenHitBoxDecorator { get; set; }
        public WorldDecoratorCollection BlueHitBoxDecorator { get; set; }
        private WorldLayer _layer { get; set; }
        public IBrush GreyBrush { get; set; }
        public IBrush GreenBrush { get; set; }
        public IBrush RedBrush { get; set; }
        public IBrush BlueBrush { get; set; }
        public float HitYards { get; set; }
        public float AnimationYards { get; set; }
        private float AdjacentYards { get; set; }
        private float OppositeYards { get; set; }

        public ImpalePlugin()
        {
            Enabled = true;
        }
 
        public override void Load(IController hud)
        {
            base.Load(hud);
            HitYards = 35.0f;
            AdjacentYards = 70.0f;
            OppositeYards = 19.75f;
            AnimationYards = 7.0f;

            GreyBrush = Hud.Render.CreateBrush(125, 80, 80, 80, 0);
            GreenBrush = Hud.Render.CreateBrush(125, 25, 155, 25, 0);
            RedBrush = Hud.Render.CreateBrush(125, 155, 25, 25, 0);
            BlueBrush = Hud.Render.CreateBrush(125, 25, 25, 155, 0);

            RedHitBoxDecorator = new WorldDecoratorCollection(
				new GroundCircleDecorator(Hud) {
                    Brush = Hud.Render.CreateBrush(175, 220, 29, 29, 3),
                    Radius = -1
                }
            );
            GreenHitBoxDecorator = new WorldDecoratorCollection(
				new GroundCircleDecorator(Hud) {
                    Brush = Hud.Render.CreateBrush(175, 29, 220, 29, 3),
                    Radius = -1
                }
            );         
            BlueHitBoxDecorator = new WorldDecoratorCollection(
				new GroundCircleDecorator(Hud) {
                    Brush = Hud.Render.CreateBrush(175, 29, 29, 175, 3),
                    Radius = -1
                }
            );         
        }

        public void DrawSplit(IWorldCoordinate pwc, IWorldCoordinate mwc, IWorldCoordinate awc, IMonster target, List<IMonster> obstacles){
            //get middle impale 
            IWorldCoordinate middlewc = PointOnLine(awc, mwc, AdjacentYards);            

            //get left and right impales
            IWorldCoordinate[] lr = PointOnOrthogonal(awc, middlewc, OppositeYards);

            //sort obstacles by distance
            if (target != null)
                obstacles.Add(target);
            if (obstacles.Any())
                obstacles.Sort((x,y) => x.NormalizedXyDistanceToMe.CompareTo(y.NormalizedXyDistanceToMe));

            //get first target for each impale projectile
            float distance = (target != null) ? (float)target.NormalizedXyDistanceToMe+2*target.RadiusBottom : 0;
            IMonster tm = FirstTarget(pwc, middlewc, obstacles, distance);
            IMonster tlr0 = FirstTarget(pwc, lr[0], obstacles, distance);
            IMonster tlr1 = FirstTarget(pwc, lr[1], obstacles, distance); 

            //draw targetline for each impale and for maintarge
            if (target != null)
                BlueBrush.DrawLineWorld(awc, target.FloorCoordinate, 4f);
            DrawTargetLine(awc, middlewc, tm, target);
            DrawTargetLine(awc, lr[0], tlr0, target);
            DrawTargetLine(awc, lr[1], tlr1, target);

            //draw target hitbox
            if (target != null && tm != null && tlr0 != null && tlr1 != null && target.AnnId == tm.AnnId && target.AnnId == tlr0.AnnId && target.AnnId == tlr1.AnnId)
                GreenHitBoxDecorator.Paint(_layer, target, target.FloorCoordinate, string.Empty);
            else if (target != null)
                    BlueHitBoxDecorator.Paint(_layer, target, target.FloorCoordinate, string.Empty);
        }

        private void DrawTargetLine(IWorldCoordinate awc, IWorldCoordinate twc, IMonster m, IMonster target){
            IBrush cBrush = GreyBrush;
            if (m != null && target != null){
                if (m.AnnId == target.AnnId){
                    cBrush = GreenBrush;
                }else{
                    cBrush = RedBrush;
                    RedHitBoxDecorator.Paint(_layer, m, m.FloorCoordinate, string.Empty);
                }
            }
            cBrush.DrawLineWorld(awc, PointOnLine(awc, twc, HitYards), 4f);
        }

        private IMonster FirstTarget(IWorldCoordinate s, IWorldCoordinate t, List<IMonster> obstacles, float distance){
            IMonster r = null;
            IWorldCoordinate c = null;
            foreach(IMonster m in obstacles){
                float d = 0f;
                while(d <= distance){
                    c = PointOnLine(s, t, d);
                    if (m.FloorCoordinate.XYDistanceTo(c) <= m.RadiusBottom){
                        r = m;
                        break;
                    }
                    d += 0.1f;
                }
            }
            return r;
        }

        private IWorldCoordinate PointOnLine(IWorldCoordinate s, IWorldCoordinate t, float yards){
            float distance = (float)Math.Sqrt(Math.Pow((t.X - s.X), 2) + Math.Pow((t.Y - s.Y), 2));
            float ratio = yards / distance;

            float x3 = ratio * t.X + (1 - ratio) * s.X;
            float y3 = ratio * t.Y + (1 - ratio) * s.Y;
            return Hud.Window.CreateWorldCoordinate(x3, y3, Hud.Game.Me.FloorCoordinate.Z);
        }

        private IWorldCoordinate[] PointOnOrthogonal(IWorldCoordinate swc, IWorldCoordinate twc, float offset){
            float m = (twc.Y-swc.Y)/(twc.X-swc.X);
            float orthm = -1 * (1/m);
            float yoff = twc.Y - orthm * twc.X;

            float x3 = (float)((twc.X*Math.Pow(orthm, 2) + twc.X - Math.Sqrt(Math.Pow(offset, 2)*Math.Pow(orthm, 2) + Math.Pow(offset, 2))) / (Math.Pow(orthm, 2) + 1));
            float x4 = (float)((twc.X*Math.Pow(orthm, 2) + twc.X + Math.Sqrt(Math.Pow(offset, 2)*Math.Pow(orthm, 2) + Math.Pow(offset, 2))) / (Math.Pow(orthm, 2) + 1));
            float y3 = orthm * x3 + yoff;
            float y4 = orthm * x4 + yoff;
            IWorldCoordinate[] x = {
                Hud.Window.CreateWorldCoordinate(x3, y3, Hud.Game.Me.FloorCoordinate.Z),
                Hud.Window.CreateWorldCoordinate(x4, y4, Hud.Game.Me.FloorCoordinate.Z)
            };
            return x;
        }


        public void PaintWorld(WorldLayer layer)
        {  
            //if (!IsNephalemRift || !IsGreaterRift || Hud.Game.Me.HeroClassDefinition.HeroClass != HeroClass.DemonHunter) return;
            if (Hud.Game.Me.HeroClassDefinition.HeroClass != HeroClass.DemonHunter) return;
            _layer = layer;

            //get player, mouse, animation-start coordinates
            IWorldCoordinate player  = Hud.Game.Me.ScreenCoordinate.ToWorldCoordinate();
            IWorldCoordinate mouse = Hud.Window.CreateScreenCoordinate(Hud.Window.CursorX, Hud.Window.CursorY).ToWorldCoordinate();
            IWorldCoordinate anim = PointOnLine(player, mouse, AnimationYards);

            //get closest elite/boss target
            var elites = Hud.Game.AliveMonsters.Where(x => (x.Rarity == ActorRarity.Boss || x.Rarity == ActorRarity.Champion || x.Rarity == ActorRarity.Rare) &&
                                                            x.IsOnScreen &&
                                                            x.NormalizedXyDistanceToMe <= HitYards
            ).ToList();
            elites.Sort((x,y) => x.NormalizedXyDistanceToMe.CompareTo(y.NormalizedXyDistanceToMe));
            var target = elites.FirstOrDefault();

            //no targets in area
            if (target == null || !target.FloorCoordinate.IsValid) return;

            //get all possible intercepting obstacles
            var trash = Hud.Game.AliveMonsters.Where(x =>   x.FloorCoordinate.IsValid && 
                                                            x.IsOnScreen && 
                                                            !(x.Rarity == ActorRarity.Boss || x.Rarity == ActorRarity.Champion || x.Rarity == ActorRarity.Rare) &&
                                                            x.NormalizedXyDistanceToMe <= target.NormalizedXyDistanceToMe &&  
                                                            target.FloorCoordinate.XYDistanceTo(x.FloorCoordinate) <= target.NormalizedXyDistanceToMe
            );       
            //draw split            
            DrawSplit(player, mouse, anim, target, trash.ToList());

        }
    }
}