using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Turbo.Plugins.Default
{
    public class PoolState : BasePlugin, IInGameTopPainter, IAfterCollectHandler, INewAreaHandler
    {


        public IFont PortraitInfoFont { get; set; }

        private readonly StringBuilder textBuilder;

        private long[] BonusPool { get; set; }
        private bool[] BonusPoolRecorded { get; set; }
        private int PlayerCount { get; set; }

        public PoolState()
        {
            Enabled = true;

            textBuilder = new StringBuilder();
        }

        public override void Load(IController hud)
        {
            base.Load(hud);

            PortraitInfoFont = Hud.Render.CreateFont("tahoma", 7f, 255, 180, 147, 109, false, false, true);

            BonusPool = new long[4];
            ResetBonusPool();
            BonusPoolRecorded = new bool[4];
        }

        public void AfterCollect()
        {

            //resets not used BonusPool
            if (PlayerCount != Hud.Game.Players.Count())
            {
                List<int> l = new List<int> { 0, 1, 2, 3 };
                foreach (var player in Hud.Game.Players)
                    l.Remove(player.Index);

                foreach (int i in l)
                    BonusPool[i] = long.MinValue;

                PlayerCount = Hud.Game.Players.Count();
            }
        }

        public void PaintTopInGame(ClipState clipState)
        {
            if (clipState != ClipState.BeforeClip) return;       

            foreach (IPlayer player in Hud.Game.Players)
            {
                DrawPlayerInfo(player);
            }
        }

        private string GetPlayerInfoText(IPlayer player)
        {
            textBuilder.Clear();

            var _bonuspool = BonusPoolInfo(player);
            double _paragonExpToNextLevel = player.ParagonExpToNextLevel;
            if (_paragonExpToNextLevel <= 1.0) _paragonExpToNextLevel = 1.0;
            double _pool = BonusPoolRecorded[player.Index] ? (_bonuspool > 0 ? 10.0 * ((double)_bonuspool / _paragonExpToNextLevel) : 0.0) : 99.0;

            if (_pool > 0.0f && _pool < 10.0f) textBuilder.AppendFormat("Có {0:0.0} pool", _pool);
            else if (_pool == 0.0f) textBuilder.Append("Không có pool");

            return textBuilder.ToString();
        }

        private long BonusPoolInfo(IPlayer player)
        {
            if (player.IsMe || (player.NormalizedXyDistanceToMe > 0 && player.NormalizedXyDistanceToMe < 80))
            {
                BonusPool[player.Index] = player.BonusPoolRemaining;
                BonusPoolRecorded[player.Index] = true;
            }

            return BonusPool[player.Index];
        }

        private void DrawPlayerInfo(IPlayer player)
        {
            var OffsetX = Hud.Window.Size.Width * 0.05f /*OffsetXmultiplier*/;
            var OffsetY = Hud.Window.Size.Height * 0.117f /*OffsetYmultiplier*/;
            var portraitRect = player.PortraitUiElement.Rectangle;
            var YPos = portraitRect.Y + OffsetY;
            var XPos = portraitRect.X + OffsetX;

            var Layout = PortraitInfoFont.GetTextLayout(GetPlayerInfoText(player));
            PortraitInfoFont.DrawText(Layout, XPos, YPos);
        }



        public void OnNewArea(bool newGame, ISnoArea area)
        {
            if (newGame)
            {
                PlayerCount = Hud.Game.Players.Count();

                //reset
                ResetBonusPool();
            }
        }

        private void ResetBonusPool()
        {
            for (int i = 0; i < 4; i++)
            {
                BonusPool[i] = long.MinValue;
            }
            BonusPool[Hud.Game.Me.Index] = Hud.Game.Me.BonusPoolRemaining;
        }
    }
}