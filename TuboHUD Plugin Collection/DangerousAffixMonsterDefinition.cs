namespace Turbo.Plugins.Default
{
    using Turbo.Plugins.Default;

    public class DangerousAffixMonsterDefinition
    {
        public MonsterAffix Affix { get; private set; }
        public int Priority { get; set; }

        public string AffixName { get; set; }
        public AffixNameFunc AffixNameFunc { get; set; }

        public WorldDecoratorCollection EliteDecorators { get; set; }
        public IFont EliteLabelFont { get; set; }

        public WorldDecoratorCollection MinionDecorators { get; set; }
        public IFont MinionLabelFont { get; set; }
        public bool ShowMinionDecorators { get; set; }
        public bool ShowMinionAffixesNames { get; set; }

        public DangerousAffixMonsterDefinition(MonsterAffix affix)
        {
            Affix = affix;
            AffixNameFunc = (a) => string.Empty;
        }
    }
}