using System;
using System.Globalization;
using System.Linq;
using System.Text;


namespace Turbo.Plugins.Default
{


    public class GRiftPlugin : BasePlugin, IInGameTopPainter, IAfterCollectHandler, ICustomizer
    {
        public IFont ProgressBarTimerFont { get; set; }
        public IFont ObjectiveProgressFont { get; set; }

        public string ObjectiveProgressSymbol { get; set; }
        public string GuardianAliveSymbol { get; set; }
        public string GuardianDeadSymbol { get; set; }

        public string SecondsFormat { get; set; }
        public string MinutesSecondsFormat { get; set; }
        public string ProgressPercentFormat { get; set; }
        public string ClosingSecondsFormat { get; set; }

        public bool GreaterRiftCountdown { get; set; }
        public bool ShowGreaterRiftTimer { get; set; }
        public bool ShowGreaterRiftCompletedTimer { get; set; }
        public bool ShowClosingTimer { get; set; }

        public int CompletionDisplayLimit { get; set; }
        public Func<string> RiftCompletionTitleFunc { get; set; }
        public TopLabelWithTitleDecorator CompletionLabelDecorator { get; set; }

        public bool IsGuardianAlive
        {
            get
            {
                return riftQuest != null && (riftQuest.QuestStepId == 3 || riftQuest.QuestStepId == 16);
            }
        }

        public bool IsGuardianDead
        {
            get
            {
                if (Hud.Game.Monsters.Any(m => m.Rarity == ActorRarity.Boss && !m.IsAlive))
                    return true;

                return riftQuest != null && (riftQuest.QuestStepId == 5 || riftQuest.QuestStepId == 10 || riftQuest.QuestStepId == 34 || riftQuest.QuestStepId == 46);
            }
        }

        public bool IsNephalemRift
        {
            get
            {
                return riftQuest != null && (riftQuest.QuestStepId == 1 || riftQuest.QuestStepId == 3 || riftQuest.QuestStepId == 10);
            }
        }

        public bool IsGreaterRift
        {
            get
            {
                return riftQuest != null &&
                       (riftQuest.QuestStepId == 13 || riftQuest.QuestStepId == 16 || riftQuest.QuestStepId == 34 ||
                        riftQuest.QuestStepId == 46);
            }
        }

        private bool show
        {
            get
            {
                if (riftQuest == null) return false;
                if (riftQuest.State == QuestState.none) return false;
                if (Hud.Inventory.InventoryMainUiElement.Visible) return false;

                return true;
            }
        }

        private const uint riftClosingMilliseconds = 30000;
        private SpecialArea? currentRun;

        private IQuest riftQuest
        {
            get
            {
                return Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 337492) ?? // rift
                       Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 382695);   // gr
            }
        }

        private IUiElement uiProgressBar
        {
            get
            {
                return IsNephalemRift ? Hud.Render.NephalemRiftBarUiElement : Hud.Render.GreaterRiftBarUiElement;
            }
        }

        private IWatch riftTimer;
        private IWatch guardianTimer;
        private IWatch pauseTimer;

        private const long greaterRiftMaxTime = 15 * 60 * 1000;

        private readonly StringBuilder textBuilder;

        public GRiftPlugin()
        {
            Enabled = true;

            textBuilder = new StringBuilder();
        }

        private IBrush brus;
        public override void Load(IController hud)
        {
            base.Load(hud);

            brus = Hud.Render.CreateBrush(255, 0, 0, 0, 0);
            ShowClosingTimer = false;
            GreaterRiftCountdown = false;
            ShowGreaterRiftTimer = true;
            ShowGreaterRiftCompletedTimer = true;
            CompletionDisplayLimit = 90;

            ObjectiveProgressSymbol = "\u2694"; //⚔
            GuardianAliveSymbol = "\uD83D\uDC7F"; //👿
            GuardianDeadSymbol = "\uD83D\uDC80"; //💀

            ObjectiveProgressSymbol = "";
            GuardianAliveSymbol = "\uD83D\uDC7F"; //??
            GuardianDeadSymbol = "\uD83D\uDC80"; //??uDC80"; //??

            MinutesSecondsFormat = "{0:%m}:{0:ss}";
            SecondsFormat = "{0:%s}";

            ProgressPercentFormat = "({0:F1}%)";
            ClosingSecondsFormat = "({0:%s})";

            ProgressBarTimerFont = Hud.Render.CreateFont("tahoma", 7, 255, 255, 210, 150, true, false, 160, 0, 0, 0, true);

            ObjectiveProgressFont = Hud.Render.CreateFont("tahoma", 8, 224, 240, 240, 240, false, false, false);
            ObjectiveProgressFont.SetShadowBrush(222, 0, 0, 0, true);

            RiftCompletionTitleFunc = () => riftQuest.QuestStep.SplashLocalized.Trim();
            CompletionLabelDecorator = new TopLabelWithTitleDecorator(Hud)
            {
                BorderBrush = Hud.Render.CreateBrush(255, 180, 147, 109, -1),
                BackgroundBrush = Hud.Render.CreateBrush(128, 0, 0, 0, 0),
                TextFont = Hud.Render.CreateFont("tahoma", 9, 255, 255, 210, 150, true, false, false),
                TitleFont = Hud.Render.CreateFont("tahoma", 6, 255, 180, 147, 109, true, false, false),
            };

            pauseTimer = Hud.Time.CreateWatch();
            riftTimer = Hud.Time.CreateWatch();
            guardianTimer = Hud.Time.CreateWatch();
        }

        public void Customize()
        {
            Hud.TogglePlugin<NotifyAtRiftPercentagePlugin>(false);
        }

        public void PaintTopInGame(ClipState clipState)
        {
            if (clipState != ClipState.BeforeClip) return;
            if (!show) return;
            if (currentRun == null)
            {
                currentRun = IsNephalemRift ? SpecialArea.Rift : SpecialArea.GreaterRift;
            }

            if (Hud.Game.RiftPercentage >= CompletionDisplayLimit && Hud.Game.RiftPercentage < 100)
            {
                var text = Hud.Game.RiftPercentage.ToString("F1", CultureInfo.InvariantCulture) + "%";
                var title = RiftCompletionTitleFunc.Invoke();
                var layout = CompletionLabelDecorator.TextFont.GetTextLayout(title);
                var w = layout.Metrics.Width * 0.8f;
                var h = Hud.Window.Size.Height * 0.04f;
                CompletionLabelDecorator.Paint(Hud.Window.Size.Width * 0.5f - w / 2, Hud.Window.Size.Height * 0.18f - h / 2, w, h, text, title);
            }

            if (IsNephalemRift && uiProgressBar.Visible)
            {
                var layout = ProgressBarTimerFont.GetTextLayout(GetText(true));
                var x = uiProgressBar.Rectangle.Left - layout.Metrics.Width / 2 + uiProgressBar.Rectangle.Width * (float)Hud.Game.RiftPercentage / 100.0f;
                var y = uiProgressBar.Rectangle.Bottom + uiProgressBar.Rectangle.Height * 0.1f;

                ProgressBarTimerFont.DrawText(layout, x, y);
            }
            else
            {
                var layout = ObjectiveProgressFont.GetTextLayout(GetText(false));
                var x = Hud.Render.MinimapUiElement.Rectangle.Right - layout.Metrics.Width - Hud.Window.Size.Height * 0.033f;
                var y = Hud.Render.MinimapUiElement.Rectangle.Bottom + Hud.Window.Size.Height * 0.0033f;
                //brus.DrawRectangle(x, y, 100, 100);
                ObjectiveProgressFont.DrawText(layout, x, y);

                var texture = Hud.Texture.GetTexture(currentRun == SpecialArea.Rift ? 1528804216 : 3075014090);
                texture.Draw(x - texture.Width * 0.75f, Hud.Render.MinimapUiElement.Rectangle.Bottom - texture.Height / 4, texture.Width, texture.Height);
            }
        }

        public void AfterCollect()
        {
            if (ResetTimers()) return;

            GuardianTimers();

            if (GamePauseTimers()) return;

            RestartStopTimers();
        }

        private void RestartStopTimers()
        {
            // (re)start/stop timers if needed
            if (!riftTimer.IsRunning && !IsGuardianDead)
                riftTimer.Start();

            if (!guardianTimer.IsRunning && IsGuardianAlive)
                guardianTimer.Start();

            if (pauseTimer.IsRunning)
                pauseTimer.Stop();

            if (IsGreaterRift && IsGuardianDead && riftTimer.IsRunning)
                riftTimer.Stop();

            if (IsNephalemRift && riftQuest.State == QuestState.completed && riftTimer.IsRunning)
                riftTimer.Stop();
        }

        private bool GamePauseTimers()
        {
            // game pause
            if (Hud.Game.IsPaused || (IsGreaterRift && Hud.Game.NumberOfPlayersInGame == 1 && Hud.Game.IsLoading))
            {
                if (!pauseTimer.IsRunning)
                    pauseTimer.Start();

                if (riftTimer.IsRunning)
                    riftTimer.Stop();

                if (guardianTimer.IsRunning)
                    guardianTimer.Stop();

                return true;
            }
            return false;
        }

        private void GuardianTimers()
        {
            // guardian
            if (IsGuardianAlive)
            {
                if (!guardianTimer.IsRunning)
                    guardianTimer.Start();
            }
            else if (IsGuardianDead && guardianTimer.IsRunning)
            {
                guardianTimer.Stop();
            }
        }

        private bool ResetTimers()
        {
            // reset states if needed
            if (riftQuest == null || (riftQuest != null && riftQuest.State == QuestState.none))
            {
                if (riftTimer.IsRunning || riftTimer.ElapsedMilliseconds > 0)
                {
                    riftTimer.Reset();
                }
                if (guardianTimer.IsRunning || guardianTimer.ElapsedMilliseconds > 0)
                {
                    guardianTimer.Reset();
                }
                if (pauseTimer.IsRunning || pauseTimer.ElapsedMilliseconds > 0)
                {
                    pauseTimer.Reset();
                }

                currentRun = null;

                return true;
            }
            return false;
        }

        private string GetText(bool onlyTimer)
        {
            textBuilder.Clear();

            SetTimerText(onlyTimer);

            if (onlyTimer)
                return textBuilder.ToString();

            SetProgessText();

            SetClosingTimerText();

            return textBuilder.ToString();
        }

        private void SetClosingTimerText()
        {
            if (!ShowClosingTimer || IsGreaterRift || riftQuest.State != QuestState.completed) return;

            textBuilder.Append(" ");
            textBuilder.AppendFormat(ClosingSecondsFormat, TimeSpan.FromMilliseconds(riftClosingMilliseconds - riftQuest.CompletedOn.ElapsedMilliseconds));
        }

        private void SetProgessText()
        {
            if (Hud.Game.RiftPercentage < 100)
            {
                if ((!IsNephalemRift && uiProgressBar.Visible) || !(Hud.Game.RiftPercentage > 0.1)) return;

                textBuilder.Append(" ");
                textBuilder.AppendFormat(CultureInfo.InvariantCulture, ProgressPercentFormat, Hud.Game.RiftPercentage);
            }
            else if (IsGuardianAlive || IsGuardianDead || !guardianTimer.IsRunning)
            {
                textBuilder.Append(" ");
                textBuilder.Append(IsGuardianAlive ? GuardianAliveSymbol : GuardianDeadSymbol);

                var guardianTimeSpan = TimeSpan.FromMilliseconds(guardianTimer.ElapsedMilliseconds);
                textBuilder.Append(" ");
                textBuilder.AppendFormat(CultureInfo.InvariantCulture, (guardianTimeSpan.Minutes < 1) ? SecondsFormat : MinutesSecondsFormat, guardianTimeSpan);
            }
        }

        private void SetTimerText(bool onlyTimer)
        {
            if (!onlyTimer && !string.IsNullOrWhiteSpace(ObjectiveProgressSymbol))
            {
                if (currentRun == SpecialArea.Rift)
                {
                    textBuilder.Append(ObjectiveProgressSymbol);
                    textBuilder.Append(" ");
                }
                else if (currentRun == SpecialArea.GreaterRift &&
                         (ShowGreaterRiftTimer || !uiProgressBar.Visible || (ShowGreaterRiftCompletedTimer && IsGuardianDead)))
                {
                    textBuilder.Append(ObjectiveProgressSymbol);
                    textBuilder.Append(" ");
                }
            }

            if (currentRun == SpecialArea.GreaterRift)
            {
                if (ShowGreaterRiftTimer || !uiProgressBar.Visible || (ShowGreaterRiftCompletedTimer && IsGuardianDead))
                {
                    var timeSpan = GreaterRiftCountdown && !IsGuardianDead
                        ? TimeSpan.FromMilliseconds(greaterRiftMaxTime - riftTimer.ElapsedMilliseconds)
                        : TimeSpan.FromMilliseconds(riftTimer.ElapsedMilliseconds);

                    textBuilder.AppendFormat(CultureInfo.InvariantCulture, (timeSpan.Minutes < 1) ? SecondsFormat : MinutesSecondsFormat, timeSpan);
                }
            }
            else
            {
                var timeSpan = TimeSpan.FromMilliseconds(riftQuest.StartedOn.ElapsedMilliseconds - riftQuest.CompletedOn.ElapsedMilliseconds - pauseTimer.ElapsedMilliseconds);
                textBuilder.AppendFormat(CultureInfo.InvariantCulture, (timeSpan.Minutes < 1) ? SecondsFormat : MinutesSecondsFormat, timeSpan);
            }
        }
    }
}