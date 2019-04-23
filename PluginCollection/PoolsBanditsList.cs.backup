// To change the language of TH and also the one of this plugin :
// Rename the file data\selected_language_example.txt to selected_language.txt and edit it after to
// change the last line (example: replace enUS by esES for Spanish/Spain). 
// Note: The esES language is only supported as of version 19.2.13.0 of TH
using System.Linq;
using System.Collections.Generic;
using SharpDX.DirectInput;
using Turbo.Plugins.Default;
using System.Windows.Forms;

namespace Turbo.Plugins.Default
{
    public class PoolsBanditsList : BasePlugin, IInGameTopPainter, IAfterCollectHandler, INewAreaHandler, IKeyEventHandler
    {				
		private Dictionary<int, List<string>> ActoArea_List { get; set; }
		private Dictionary<string, List<string>> AreaPool_List { get; set; }
		private Dictionary<string, int> PoolEstado { get; set; }
		private Dictionary<string, int> PoolReappears { get; set; }
		
		private Dictionary<uint, int> ActFix { get; set; }
		private Dictionary<string, string> AreaFix { get; set; }

		private IFont VerdeFont { get; set; }
		private IFont VerdeFontm { get; set; }
		private IFont AmarilloFont { get; set; }
		private IFont AmarilloFontm { get; set; }
		private IFont SelecFont { get; set; }
		private bool Show { get; set; }

		public float xpos { get; set; }
		public float ypos { get; set; }

		public bool TurnOffWhenNewGameStarts { get; set; }

		public IKeyEvent ToggleKeyEvent { get; set; }
		public Key Hot_Key {
            get { return ToggleKeyEvent.Key; }
            set { ToggleKeyEvent = Hud.Input.CreateKeyEvent(true, value, false, false, false); }
        }
		
		public bool Debug { get; set; }

        public PoolsBanditsList()
        {
            Enabled = true;		
        }
        public override void Load(IController hud)
        {
            base.Load(hud);
			
			xpos = 0.25f;
			ypos = 0.01f;
			TurnOffWhenNewGameStarts = false;
			Hot_Key = Key.End;		

			Debug = false;
			
			VerdeFont = Hud.Render.CreateFont("tahoma", 8f, 250, 0, 250, 0, false, false, false);
			VerdeFontm = Hud.Render.CreateFont("tahoma", 8f, 120, 0, 250, 0, false, false, true);
			AmarilloFont = Hud.Render.CreateFont("tahoma", 8f, 250, 255, 250, 0, false, false,false);
			AmarilloFontm = Hud.Render.CreateFont("tahoma", 8f, 120, 255, 250, 0, false, false, true);
			Show = false;
			ActoArea_List = new Dictionary<int, List<string>>();
			AreaPool_List = new Dictionary<string, List<string>>();
			PoolEstado = new Dictionary<string, int>();
			PoolReappears = new Dictionary<string, int>();
			
			ActFix = new Dictionary<uint, int>();
			AreaFix = new Dictionary<string, string>();

			for (int i = 0; i < 6; i++) {	ActoArea_List.Add(i, new List<string>() ); }
			
			AreaFix.Add("855.431, 1411.451, 197.8","Alcarnus"); AreaFix.Add("951.572, 1302.670, 197.3","Alcarnus");
	
	 	     // (SnoArea.Sno,act) para conocer el acto al que pertenecen los mapas nuevos, al parecer no tienen asociado un acto en TH
			ActFix.Add(63666, 1); ActFix.Add(445426, 1);

			ActFix.Add(456638, 2); ActFix.Add(460671, 2);  ActFix.Add(464092, 2); ActFix.Add(464830, 2); ActFix.Add(465885, 2); ActFix.Add(467383, 2);

			ActFix.Add(444307, 3); ActFix.Add(445762, 3);

			ActFix.Add(444396, 4); ActFix.Add(445792, 4); ActFix.Add(446367, 4); ActFix.Add(446550, 4);  ActFix.Add(448011, 4);  ActFix.Add(448039, 4); 
			ActFix.Add(464063, 4); ActFix.Add(464065, 4); ActFix.Add(464066, 4);                                   
			ActFix.Add(464810, 4); ActFix.Add(464820, 4); ActFix.Add(464821, 4); ActFix.Add(464822, 4); ActFix.Add(464857, 4); ActFix.Add(464858, 4);                   
			ActFix.Add(464865, 4); ActFix.Add(464867, 4); ActFix.Add(464868, 4); ActFix.Add(464870, 4); ActFix.Add(464871, 4); ActFix.Add(464873, 4);
			ActFix.Add(464874, 4); ActFix.Add(464875, 4); ActFix.Add(464882, 4); ActFix.Add(464886, 4); ActFix.Add(464889, 4); ActFix.Add(464890, 4);                        
			ActFix.Add(464940, 4); ActFix.Add(464941, 4); ActFix.Add(464942, 4); ActFix.Add(464943, 4); ActFix.Add(464944, 4);
			ActFix.Add(475854, 4); ActFix.Add(475856, 4); 

			ActFix.Add(448391, 5); ActFix.Add(448368, 5); ActFix.Add(448375, 5); ActFix.Add(448398, 5); ActFix.Add(448404,5); ActFix.Add(448411,5);
        }
		
	public void OnKeyEvent(IKeyEvent keyEvent)  {
		if (keyEvent.IsPressed && ToggleKeyEvent.Matches(keyEvent))  {  Show = !Show; }
	}

	public void OnNewArea(bool newGame, ISnoArea area)  {
		if (newGame)  {
			if (TurnOffWhenNewGameStarts) Show = false;		
			for (int i = 0; i < 6; i++)  ActoArea_List[i].Clear(); 
			foreach (string keyarea in AreaPool_List.Keys)  AreaPool_List[keyarea].Clear(); 			      	
			AreaPool_List.Clear();                                
			PoolEstado.Clear();
			PoolReappears.Clear();
		}
	}
		
	public void AfterCollect()  {
		if (Hud.Game.Me.SnoArea == null || Hud.Game.Me.SnoArea.Code == null || Hud.Game.Me.SnoArea.Code.Contains("x1_lr_level")) return;
		var shrines = Hud.Game.Shrines.Where(s => (s.Type == ShrineType.PoolOfReflection || s.Type == ShrineType.BanditShrine) && s.FloorCoordinate.IsValid ); 
		foreach (var shrine in shrines)  {
			if ((shrine.Scene.SnoArea == null) || (shrine.Scene.SnoArea.NameLocalized == null)) continue;
			string coord = shrine.FloorCoordinate.ToString() ;
			int activo =  ((shrine.Type == ShrineType.PoolOfReflection)? 0 : 2) + ((shrine.IsDisabled || shrine.IsOperated)? 0 : 1) ;
			if  (PoolEstado.Keys.Contains(coord)) {
				if ( (activo % 2 == 0) && (PoolEstado[coord] % 2 == 1) )  PoolEstado[coord] = activo;  // Añadida Comprobación por bug extraño en D3: en raras ocasiones, pozos vacios se rellenan y,
				if ((PoolReappears[coord]) < 100)  PoolReappears[coord] = PoolReappears[coord] + 1;   // al instante se vacían solos. Ahora no podrán confundir al plugin.
			}
			else  {
				
				string area = (AreaFix.Keys.Contains(coord))? AreaFix[coord]: shrine.Scene.SnoArea.NameLocalized; 	
				PoolEstado.Add(coord, activo) ; PoolReappears.Add(coord,0);
				if  (AreaPool_List.Keys.Contains(area)) { AreaPool_List[area].Add(coord); }
				else { 
					int acto = 0;
					if ((shrine.Scene.SnoArea.Act > 0) && ( shrine.Scene.SnoArea.Act < 6))  acto = shrine.Scene.SnoArea.Act; 
					else if (ActFix.Keys.Contains(shrine.Scene.SnoArea.Sno)) acto = ActFix[shrine.Scene.SnoArea.Sno] ;
					AreaPool_List.Add(area, new List<string>()); AreaPool_List[area].Add(coord);
					if  (ActoArea_List.Keys.Contains(acto)) {  ActoArea_List[acto].Add(area);  }
					else { ActoArea_List.Add(acto, new List<string>()); ActoArea_List[acto].Add(area); }
				}
			}    			
	    }
	}
 
	public void PaintTopInGame(ClipState clipState)    {
		if ( (clipState != ClipState.BeforeClip) || !Hud.Game.IsInGame || !Show ) return;
		if ((Hud.Game.SpecialArea == SpecialArea.GreaterRift) || (Hud.Game.SpecialArea == SpecialArea.Rift))  return;
		int h = 1; int PoolNum = 0; int BanditNum = 0; int w = 1; string texto = string.Empty ;
		for (int acto = 0; acto < 6; acto++) {     
			foreach (string area in ActoArea_List[acto]) {
				int  PozosActivos = 0; int PozosTotales = 0; int BanditsActivos = 0; int BanditsTotales = 0;
				foreach (string pozo in AreaPool_List[area]) {
					if (PoolReappears[pozo] > 0) {  
						if (PoolEstado[pozo] == 0) { PozosTotales++; }
						else if (PoolEstado[pozo] == 1) { PozosActivos++ ; PozosTotales++; }
						else if (PoolEstado[pozo] == 2) { BanditsTotales++; }
						else if (PoolEstado[pozo] == 3) { BanditsActivos++; BanditsTotales++; }
					}
					if (Debug) {
						w++;
						texto = string.Format("A{0} <{1}> [{2}]  S{3}  P{4}/{5}  B{6}/{7}  #  Reappears= {8} {9}",
							acto, area,	pozo, PoolEstado[pozo],	PozosActivos, PozosTotales,	BanditsActivos,	BanditsTotales, PoolReappears[pozo],
							(PoolReappears[pozo] == 0)? " -> BUG? (fake shrine)":"(limited to 100)" 
						);
						VerdeFont.DrawText(VerdeFont.GetTextLayout( texto), 150, 400 + ( w * 20) );
					}
				}
				if (PozosTotales > 0)  {
					var SelecFont = (PozosActivos > 0)? AmarilloFont: AmarilloFontm;
					texto = ( (acto == 0)? "A?": "A" + acto) + " - " + area + ( (PozosTotales > 1)? " (" + ((PozosActivos > 0 && PozosActivos != PozosTotales)? PozosActivos + "/": "") + PozosTotales + ")" : "") ;
					SelecFont.DrawText(SelecFont.GetTextLayout( texto ), Hud.Window.Size.Width * xpos, Hud.Window.Size.Height * (ypos +  (float ) h * 0.018f) ); 
					h++;
					PoolNum = PoolNum + PozosTotales ;
				}
				if (BanditsTotales > 0)  {
					var SelecFont = (BanditsActivos > 0)? VerdeFont: VerdeFontm;
					texto =  ( (acto == 0)? "A?": "A" + acto) + " - " + area +  ( (BanditsTotales > 1)? " (" + ( (BanditsActivos > 0 && BanditsActivos != BanditsTotales )? BanditsActivos + "/": "") + BanditsTotales + ")" : "") ;
					SelecFont.DrawText(SelecFont.GetTextLayout( texto ), Hud.Window.Size.Width * xpos, Hud.Window.Size.Height * (ypos +  (float ) h * 0.018f) ); 
					h++;
					BanditNum = BanditNum + BanditsTotales ;
				} 			
			}
		}
		if (Debug) {			
			texto = string.Format("{0} ({4})  <{1}>  [{2}]  {3}",
				Hud.Game.Me.SnoArea.Sno.ToString(), Hud.Game.Me.SnoArea.NameLocalized, Hud.Game.Me.FloorCoordinate.ToString(), Hud.Game.Me.HeroClassDefinition.Name,
				"A" +  ((Hud.Game.Me.SnoArea.Act > 0)? Hud.Game.Me.SnoArea.Act.ToString(): ((ActFix.ContainsKey(Hud.Game.Me.SnoArea.Sno))? ActFix[Hud.Game.Me.SnoArea.Sno] + "?" : "0" )) 				
			);
			VerdeFont.DrawText(VerdeFont.GetTextLayout( texto), 150, 400 );
		}
		var xposr = Hud.Window.Size.Width * xpos ;
		texto = "[ Pools = " +  PoolNum + "  , " ;
		AmarilloFont.DrawText(AmarilloFont.GetTextLayout(texto),xposr,Hud.Window.Size.Height * ypos); 
		xposr += AmarilloFont.GetTextLayout(texto).Metrics.Width ;
		texto = "  Bandits = " + BanditNum ;
		VerdeFont.DrawText(VerdeFont.GetTextLayout(texto ) , xposr, Hud.Window.Size.Height * ypos ); 
		xposr += VerdeFont.GetTextLayout(texto).Metrics.Width ;
		AmarilloFont.DrawText(AmarilloFont.GetTextLayout(" ]"),xposr,Hud.Window.Size.Height * ypos); 
        }		
    }
}