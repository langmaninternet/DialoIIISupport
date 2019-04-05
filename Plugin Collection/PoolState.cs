using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Turbo.Plugins.Default
{
    public class PoolState : BasePlugin, IInGameTopPainter, IAfterCollectHandler, INewAreaHandler
    {
        public int DeathsTotal { get; private set; }
        public int DeathsInRift { get; private set; }
        private SpecialArea? currentRun;
        private bool alive;

        public string DeathsTotalSymbol { get; set; }
        public string DeathsInRiftSymbol { get; set; }

        public bool IsNephalemRift { get { return riftQuest != null && (riftQuest.QuestStepId == 1 || riftQuest.QuestStepId == 3 || riftQuest.QuestStepId == 10); } }
        public bool IsGreaterRift { get { return riftQuest != null && (riftQuest.QuestStepId == 13 || riftQuest.QuestStepId == 16 || riftQuest.QuestStepId == 34 || riftQuest.QuestStepId == 46); } }
        private IQuest riftQuest { get { return Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 337492) /*rift*/ ?? Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 382695); /*gr*/ } }

        public IFont PortraitInfoFont { get; set; }
        public float OffsetXmultiplier { get; set; }
        public float OffsetYmultiplier { get; set; }

        public bool ShowDeathCounter { get; set; }
        public bool ShowGRDeathCounter { get; set; }
        public bool ShowGRSecondsCounter { get; set; }

        private readonly StringBuilder textBuilder;

        private long[] BonusPool { get; set; }
        private bool[] BonusPoolRecorded { get; set; }
        private int PlayerCount { get; set; }

        public PoolState()
        {
            Enabled = true;

            ShowDeathCounter = false;
            ShowGRDeathCounter = false;
            ShowGRSecondsCounter = false;

            textBuilder = new StringBuilder();
        }

        public override void Load(IController hud)
        {
            base.Load(hud);

            DeathsTotal = 0;
            DeathsInRift = 0;
            alive = true;

            DeathsTotalSymbol = "\u2620";
            DeathsInRiftSymbol = "\ud83d\udd48";

            PortraitInfoFont = Hud.Render.CreateFont("tahoma", 7f, 255, 180, 147, 109, false, false, true);
            OffsetXmultiplier = 0.05f;
            OffsetYmultiplier = 0.117f;

            BonusPool = new long[4];
            ResetBonusPool();
            BonusPoolRecorded = new bool[4];
        }

        public void AfterCollect()
        {
            if (riftQuest == null || (riftQuest != null && riftQuest.State == QuestState.none))
            {
                DeathsInRift = 0;
                currentRun = null;
            }

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

            if (currentRun == null)
            {
                currentRun = IsNephalemRift ? SpecialArea.Rift : SpecialArea.GreaterRift;
            }

            CheckDeathState();
            foreach (IPlayer player in Hud.Game.Players)
            {
                DrawPlayerInfo(player);
            }
        }

        private string GetPlayerInfoText(IPlayer player)
        {
            textBuilder.Clear();

            var _bonuspool = BonusPoolInfo(player);
            var _pool = BonusPoolRecorded[player.Index] ? (_bonuspool > 0 ? 10 * ((float)_bonuspool / player.ParagonExpToNextLevel) : 0f) : float.PositiveInfinity;

            if (_pool > 0) textBuilder.AppendFormat("Có {0:0.1} pool", _pool);
            else textBuilder.Append("Không có pool");

            if (player.IsMe)
            {
                textBuilder.Append("\t");

                if (ShowDeathCounter)
                    textBuilder.AppendFormat("{0} {1}  ", DeathsTotalSymbol, DeathsTotal);

                if (IsGreaterRift)
                {
                    if (ShowGRDeathCounter)
                        textBuilder.AppendFormat("{0} {1}  ", DeathsInRiftSymbol, DeathsInRift);

                    if (ShowGRSecondsCounter)
                        textBuilder.AppendFormat("{0}s", (DeathsInRift > 5 ? 30 : DeathsInRift * 5));
                }
            }

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
            var OffsetX = Hud.Window.Size.Width * OffsetXmultiplier;
            var OffsetY = Hud.Window.Size.Height * OffsetYmultiplier;
            var portraitRect = player.PortraitUiElement.Rectangle;
            var YPos = portraitRect.Y + OffsetY;
            var XPos = portraitRect.X + OffsetX;

            var Layout = PortraitInfoFont.GetTextLayout(GetPlayerInfoText(player));
            PortraitInfoFont.DrawText(Layout, XPos, YPos);
        }

        private void CheckDeathState()
        {
            var me = Hud.Game.Me; //player
            if (me.IsDeadSafeCheck && alive)
            {
                DeathsTotal++;
                if (currentRun != null)
                    DeathsInRift++;
                alive = !alive;
            }
            if (!me.IsDeadSafeCheck && !alive)
                alive = !alive;
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