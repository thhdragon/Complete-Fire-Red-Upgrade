#include "defines.h"
#include "helper_functions.h"
#include "catching.h"
#include "Vanilla_Functions.h"

/*
NOTES: 
	1. a lot of specials will not work unless you have chosen to expand the save block!
	2. PC selection hack allows a lot all of the attribute getter/setter specials to reference boxed pokemon via var8003
		-var8003 = 1: boxed pokemon (output from pc selection: box num in var8000, slot in var8001)
		-else: menu pokemon (and slot in var8004, etc)
	
*/

//Pokemon Specials//
///////////////////////////////////////////////////////////////////////////////////

/*


enum EVStatChecker
{
	CheckEVs_HP,
	CheckEVs_Atk,
	CheckEVs_Def,
	CheckEVs_Spd,
	CheckEVs_SpAtk,
	CheckEVs_SpDef,
	CheckEVs_Coolness,
	CheckEVs_Beauty,
	CheckEVs_Cuteness,
	CheckEVs_Smartness,
	CheckEVs_Toughness,
	CheckEVs_Luster
};

enum IVStatChecker
{
	CheckIVs_HP,
	CheckIVs_Atk,
	CheckIVs_Def,
	CheckIVs_Spd,
	CheckIVs_SpAtk,
	CheckIVs_SpDef,
	SetAllIVs
};

#ifdef SELECT_FROM_PC
u32 getAttrFromVar8003(u8 dataRequest) {
	u32 attr;
	if (Var8003 == 1)
		attr = getAttrFromAnyBox(Var8000, Var8001, dataRequest);
	else
		attr = get_attr($gPlayerParty[Var8004], dataRequest, 0);
	return attr;
};

u32 setAttrFromVar8003(u8 dataRequest) {
	if (Var8003 == 1)
		attr = setAttrFromAnyBox(Var8000, Var8001, dataRequest, $Var8005);
	else
		attr = set_attr($gPlayerParty[Var8004], dataRequest, $Var8005);
	return attr;
};

u32* getBoxedMonAddr(void) {
	u32 *addr = (u32*) &(gPokemonStoragePtr->boxes[Var8000][Var8001]);
	return addr;
};


#endif


u8 sp007_PokemonEVContestStatsChecker(void) {
	u16 mon = Var8004;
	u16 stat = Var8005;
	
	if (mon >= 6)
		return 0;
	
	switch(stat) {
		
	#ifdef SELECT_FROM_PC
		case CheckEVs_HP:
			return getAttrFromVar8003(MON_DATA_HP_EV);
		case CheckEVs_Atk:
			return getAttrFromVar8003(MON_DATA_ATK_EV);
		case CheckEVs_Def:
			return getAttrFromVar8003(MON_DATA_DEF_EV);
		case CheckEVs_Spd:
			return getAttrFromVar8003(MON_DATA_SPEED_EV);
		case CheckEVs_SpAtk:
			return getAttrFromVar8003(MON_DATA_SPATK_EV);
		case CheckEVs_SpDef:
			return getAttrFromVar8003(MON_DATA_SPDEF_EV);
		case CheckEVs_Coolness:
			return getAttrFromVar8003(MON_DATA_COOL);
		case CheckEVs_Beauty:
			return getAttrFromVar8003(MON_DATA_BEAUTY);
		case CheckEVs_Cuteness:
			return getAttrFromVar8003(MON_DATA_CUTE);
		case CheckEVs_Smartness:
			return getAttrFromVar8003(MON_DATA_SMART);
		case CheckEVs_Toughness:
			return getAttrFromVar8003(MON_DATA_TOUGH);
		case CheckEVs_Luster:
			return getAttrFromVar8003(MON_DATA_SHEEN);
	#else	
		case CheckEVs_HP:
			return gPlayerParty[mon].hpEv;
		case CheckEVs_Atk:
			return gPlayerParty[mon].atkEv;
		case CheckEVs_Def:
			return gPlayerParty[mon].defEv;
		case CheckEVs_Spd:
			return gPlayerParty[mon].spdEv;
		case CheckEVs_SpAtk:
			return gPlayerParty[mon].spAtkEv;
		case CheckEVs_SpDef:
			return gPlayerParty[mon].spDefEv;
		case CheckEVs_Coolness:
			return gPlayerParty[mon].coolness;
		case CheckEVs_Beauty:
			return gPlayerParty[mon].beauty;
		case CheckEVs_Cuteness:
			return gPlayerParty[mon].cuteness;
		case CheckEVs_Smartness:
			return gPlayerParty[mon].smartness;
		case CheckEVs_Toughness:
			return gPlayerParty[mon].toughness;
		case CheckEVs_Luster:
			return gPlayerParty[mon].feel;
	#endif
		default:
			return 0;
	}
};

u8 sp008_PokemonIVChecker(void) {
	u16 mon = Var8004;
	u16 stat = Var8005;
	
	if (mon >= 6)
		return 0;
	
	switch(stat) {
	#ifdef SELECT_FROM_PC
		case CheckIVs_HP:
			return getAttrFromVar8003(MON_DATA_HP_IV);
		case CheckIVs_Atk:
			return getAttrFromVar8003(MON_DATA_ATK_IV);
		case CheckIVs_Def:
			return getAttrFromVar8003(MON_DATA_DEF_IV);
		case CheckIVs_Spd:
			return getAttrFromVar8003(MON_DATA_SPEED_IV);
		case CheckIVs_SpAtk:
			return getAttrFromVar8003(MON_DATA_SPATK_IV);
		case CheckIVs_SpDef:
			return getAttrFromVar8003(MON_DATA_SPDEF_IV);	
	#else
		case CheckIVs_HP:
			return gPlayerParty[mon].hpIV;
		case CheckIVs_Atk:
			return gPlayerParty[mon].attackIV;
		case CheckIVs_Def:
			return gPlayerParty[mon].defenseIV;
		case CheckIVs_Spd:
			return gPlayerParty[mon].speedIV;
		case CheckIVs_SpAtk:
			return gPlayerParty[mon].spAttackIV;
		case CheckIVs_SpDef:
			return gPlayerParty[mon].spDefenseIV;
	#endif
		default:
			return 0;
	}
};

bool8 sp009_PokemonRibbonChecker(void) {
	u16 mon = Var8004;
	u16 ribbon = Var8005;
	
	if (mon >= 6)
		return FALSE;
	
	if (ribbon > 0x1F)
		return FALSE;
		
	#ifdef SELECT_FROM_PC
		if (Var8003 == 1)
			u32 *pointer = getBoxedMonAddr;
		else
			u32 *pointer = (u32*) &gPlayerParty[mon];
	#else
		u32 *pointer = (u32*) &gPlayerParty[mon];
	#endif
		pointer += (76 / sizeof(u32));
		u32 data = *pointer;
		
		if (data & gBitTable[ribbon])
			return TRUE;
		else
			return FALSE;
};

#define POKERUS_CURED 0x10

u8 sp00A_CheckPokerusTimer(void) {
	u16 mon = Var8004;
	
	if (mon >= 6)
		return 0;
		
	if (gPlayerParty[mon].pokerusDays == 0
	&&  gPlayerParty[mon].pokerusStrain != 0)
		return POKERUS_CURED;
		
	else
		return gPlayerParty[mon].pokerusDays == 0;
};

u16 sp00B_CheckPokeball(void) {
	u16 mon = Var8004;
	
	if (mon >= 6)
		return 0;
		
	return GetMonData(&gPlayerParty[mon], REQ_POKEBALL, 0);
};

u8 sp00C_CheckCaptureLocation(void) {
	u16 mon = Var8004;
	
	if (mon >= 6)
		return 0;
		
	return gPlayerParty[mon].metLocation;
};

u8 sp00D_CheckHappiness(void) {
	u16 mon = Var8004;
	
	if (mon >= 6)
		return 0;
		
	return gPlayerParty[mon].friendship;
};

item_t sp00E_CheckHeldItem(void) {
	u16 mon = Var8004;
	
	if (mon >= 6)
		return 0;
		
	return gPlayerParty[mon].item;
};

void sp00F_EVAdderSubtracter(void) {
	u16 mon = Var8004;
	u16 stat = Var8005;
	u16 amount = Var8006;
	u8* modify;
	s32 calc;
	
	if (amount & 0x100) 
	{
		amount ^= 0x100;
		amount *= -1;
		if (amount < -255)
			amount = -255;
	}
	else if (amount > 255)
		amount = 255;
	
	if (mon >= 6)
		return;
	
	switch(stat) {
		case CheckEVs_HP:
			modify = &gPlayerParty[mon].hpEv;
			break;
		case CheckEVs_Atk:
			modify = &gPlayerParty[mon].atkEv;
			break;
		case CheckEVs_Def:
			modify = &gPlayerParty[mon].defEv;
			break;
		case CheckEVs_Spd:
			modify = &gPlayerParty[mon].spdEv;
			break;
		case CheckEVs_SpAtk:
			modify = &gPlayerParty[mon].spAtkEv;
			break;
		case CheckEVs_SpDef:
			modify = &gPlayerParty[mon].spDefEv;
			break;
		case CheckEVs_Coolness:
			modify = &gPlayerParty[mon].coolness;
			break;
		case CheckEVs_Beauty:
			modify = &gPlayerParty[mon].beauty;
			break;
		case CheckEVs_Cuteness:
			modify = &gPlayerParty[mon].cuteness;
			break;
		case CheckEVs_Smartness:
			modify = &gPlayerParty[mon].smartness;
			break;
		case CheckEVs_Toughness:
			modify = &gPlayerParty[mon].toughness;
			break;
		case CheckEVs_Luster:
			modify = &gPlayerParty[mon].feel;
			break;
		default:
			return;
		
		calc = *modify;
		calc += amount;
		
		if (calc < 0)
			calc = 0;
		
		if (calc > 255)
			calc = 255;
			
		*modify = calc;
	}
	return;
};

void sp010_IVSetter(void) {
	u16 mon = Var8004;
	u16 stat = Var8005;
	u16 amount = Var8006;
	
	if (amount > 31)
		amount = 31;
	
	if (mon >= 6)
		return;
	
	switch(stat) {
		case CheckIVs_HP:
			gPlayerParty[mon].hpIV = amount;
			break;
		case CheckIVs_Atk:
			gPlayerParty[mon].attackIV = amount;
			break;
		case CheckIVs_Def:
			gPlayerParty[mon].defenseIV = amount;
			break;
		case CheckIVs_Spd:
			gPlayerParty[mon].speedIV = amount;
			break;
		case CheckIVs_SpAtk:
			gPlayerParty[mon].spAttackIV = amount;
			break;
		case CheckIVs_SpDef:
			gPlayerParty[mon].spDefenseIV = amount;
			break;
		case SetAllIVs:
			gPlayerParty[mon].hpIV = amount;
			gPlayerParty[mon].attackIV = amount;
			gPlayerParty[mon].defenseIV = amount;
			gPlayerParty[mon].speedIV = amount;
			gPlayerParty[mon].spAttackIV = amount;
			gPlayerParty[mon].spDefenseIV = amount;
	}
	return;
};

void sp011_RibbonSetterCleaner(void) {
	u16 mon = Var8004;
	u16 ribbon = Var8005;
	bool8 clear = FALSE;
	
	if (mon >= 6)
		return;
		
	if (ribbon & 0x100) {
		ribbon ^= 0x100;
		clear = TRUE;
	}
	
	if (ribbon > 0x1F)
		return;
		
	u32 pointer = (u32*) &gPlayerParty[mon];
	pointer += (76 / sizeof(u32));
	
	if (clear)
		*pointer &= ~(gBitTable[ribbon]);
	else
		*pointer |= gBitTable[ribbon];
	return;
};

void sp012_PokerusSetter(void) {
	u16 mon = Var8004;
	u16 timer = Var8005;
	u8 strain;
	
	if (mon >= 6)
		return;
		
	if (timer > 0x10) 
	{
		gPlayerParty[mon].pokerusDays = 0;
		gPlayerParty[mon].pokerusStrain = 1;
	}
	else 
	{
		gPlayerParty[mon].pokerusDays = timer;
		
		//Get appropriate strain depending on the timer
		switch (timer) {
			case 0:
			case 4:
			case 8:
			case 12:
				strain = (1 << 0);
				break;
			case 1:
			case 5:
			case 9:
			case 13:
				strain = (1 << 1);
				break;
			case 2:
			case 6:
			case 10:
			case 14:
				strain = (1 << 2);
				break;
			default:
				strain = (1 << 3);
				break;
		}
		
		gPlayerParty[mon].pokerusStrain = strain;
	}
	return;
};

void sp013_IncreaseDecreaseHappiness(void) {
	u16 mon = Var8004;
	u16 amount = Var8005;
	u8* modify;
	s32 calc;

	if (mon >= 6)
		return;
		
	if (amount & 0x100) {
		amount ^= 0x100;
		amount = -1 * MathMax(amount, 255);
	}
	
	u8* modify = (u8*) &gPlayerParty[mon].friendship;
	calc = *modify + amount;
	
	if (calc < 0)
		calc = 0;
	else if (calc > 255)
		calc = 255
		
	*modify = calc;
	return;
};

void sp014_ChangeCapturedBall(void) {
	u16 mon = Var8004;
	u16 ball = Var8005;
	
	if (mon >= 6)
		return;
		
	if (ball > NUM_BALLS)
		return;
		
	gPlayerParty[mon].pokeball = ball;
	return;
};

void sp015_ModifyHeldItem(void) {
	u16 mon = Var8004;
	u16 item = Var8005;
	Var800D = 1;
	
	if (mon >= 6)
		return;
	
	//Can't be used if mon already has item
	if (gPlayerParty[mon].item && item)
		return;
	
	gPlayerParty[mon].item = item;
	Var800D = 0;
	return;
};

void sp016_ChangePokemonSpecies(void) {
	u16 mon = Var8004;
	u16 species = Var8005;

	if (mon >= 6)
		return;

	gPlayerParty[mon].species = species;
	return;
};

void sp017_ChangePokemonAttacks(void) {
	u16 mon = Var8004;
	u16 slot = Var8005;
	u16 move = Var8006;
	int i;

	if (mon >= 6)
		return;

	if (move != 0)
	{
		for (int i = 0; i < MAX_MON_MOVES; ++i) {
			if (gPlayerParty[mon].moves[i] == 0) {
				gPlayerParty[mon].moves[i] = move;
				gPlayerParty[mon].pp[i] = gBattleMoves[move].pp;
				return;
			}
		}
	}
	
	gPlayerParty[mon].moves[slot] = move;
	gPlayerParty[mon].pp[slot] = gBattleMoves[move].pp;
	gPlayerParty[mon].pp_bonuses &= ~(gBitTable[slot * 2] | gBitTable[slot * 2 + 1])
	
	//Clean Up Moves
	u8 moves[4] = {0};
	u8 pps[4] = {0};
	u8 pp_bonuses = 0;
	u8 availableSlot = 0;
	
	for (i = 0; i < MAX_MON_MOVES; ++i) {
		if (gPlayerParty[mon].moves[i] != 0) {
			moves[availableSlot] = gPlayerParty[mon].moves[i];
			pps[availableSlot] = gPlayerParty[mon].pp[i];
			pp_bonuses |= (((gBitTable[i * 2] & gPlayerParty[mon].pp_bonuses) | (gBitTable[i * 2 + 1] & gPlayerParty[mon].pp_bonuses)) << (availableSlot *2));
		}
	}
	
	for (i = 0; i < MAX_MON_MOVES; ++i) {
		gPlayerParty[mon].moves[i] = moves[i];
		gPlayerParty[mon].pp[i] = pps[i];
		gPlayerParty[mon].pp_bonuses = pp_bonuses;
	}
	return;
};

species_t sp018_CheckPokemonSpecies(void) {
	u16 mon = Var8004;

	if (mon >= 6)
		return;

	return gPlayerParty[mon].species;
};

//Add pp bonus calc?
void sp019_CheckAttackPP(void) {
	u16 mon = Var8004;
	u16 slot = Var8005;

	if (mon >= 6)
		return;

	if (slot >= MAX_MON_MOVES)
		return;
	
	return gPlayerParty[mon].pp[slot];
};



//Party Specials//
///////////////////////////////////////////////////////////////////////////////////

// erase pokemon from party, or entire party
void sp062_PokemonEraser(void) {
	u8 slot = Var8004;
	if (slot == 0xf)
		ZeroPlayerPartyMons();
	else
	{
		pokemon_slot_purge(&gPlayerParty[slot]);
		gPlayerPartyCount -= 1;
		// shift later slots up one
		for (u8 i = slot; i <= gPlayerPartyCount-1; ++i)
		{
			// copy slot+i+1 to slot+i up to numPokes - 2
			CopyMon(&gPlayerParty[i],&gPlayerParty[i+1],100);
		}
	}
	return;
};


// check status of pokemon in slot var8004
u8 sp063_StatusChecker(void) {
	u8 slot = Var8004;	
	return (get_attr(&gPlayerParty[slot], MON_DATA_STATUS, 0));
};


// Inflict a status to affect a party member or entire party
void sp064_InflictStatus(void) {
	u8 slot = Var8004;
	if (Var8005 == 0xf)
		for (i = 0; i <= gPlayerPartyCount-1; ++i)
		{
			set_attr(&gPlayerParty[i], MON_DATA_STATUS, &Var8005);
		}
	else
		set_attr(&gPlayerParty[slot], MON_DATA_STATUS, &Var8005);
	return;
};


// check slot pokemon's HP
u16 sp065_CheckMonHP(void) {
	u8 slot = Var8004;
	return get_attr(&gPlayerParty[slot], MON_DATA_HP, 0);
};


// inflict damage on a party pokemon, or entire party
void sp066_InflictPartyDamage(void) {
	u8 slot = Var8004;
	s16 dmg = Var8005;
	u8 switcher = Var8006;	//1 to heal, else damage
	u16 currHP;
	if (slot == 0xf)
	{
		for (i = 0; i <= gPlayerPartyCount-1; ++i)
		{
			currHP = get_attr(&gPlayerParty[slot], MON_DATA_HP, 0);
			if (switcher == 1)
				Var8006 = currHP + dmg;
			else
				Var8006 = currHP - dmg;
			set_attr(&gPlayerParty[slot], MON_DATA_HP, Var8006);
		}
	}
	return;
};


//Key Specials//
///////////////////////////////////////////////////////////////////////////////////

//Special 0x2b checks for the A and B keys. Returns
//0x0 if none pressed
//0x1 if A pressed
//0x2 if B pressed
//0x3 if both are pressed
u16 sp02B_CheckABButtons(void) {
	return (~(gKeyReg) & 3);
};

//Special 0x2c checks for the D-pad. Returns
//0x0 if no direction is pressed
//0x1 if up is pressed
//0x2 if left is pressed 
//0x3 if down is pressed
//0x4 if right is pressed
//0x5 if up-left is pressed
//0x6 if up-right is pressed
//0x7 if down-left is pressed
//0x8 if down-right is pressed
u16 sp02C_CheckDPad(void) {
	
	switch(~(gKeyReg) & 0xFF) {
		case DPAD_UP:
			return 1;
		case DPAD_LEFT:
			return 2;
		case DPAD_DOWN:
			return 3;
		case DPAD_RIGHT:
			return 4;
		case DPAD_UP | DPAD_LEFT:
			return 5;
		case DPAD_UP | DPAD_RIGHT:
			return 6;
		case DPAD_DOWN | DPAD_LEFT:
			return 7;
		case DPAD_DOWN | DPAD_RIGHT:
			return 8;
		default:
			return 0;
	}
	return;
};

//Special 0x2d checks for the start select buttons
//0x0 if none is pressed
//0x1 if select is pressed
//0x2 if start is pressed
//0x3 if both are pressed
u16 sp02D_CheckStartSelect(void) {
	return ((~(gKeyReg) >> 2) & 3);
};

//Special 0x2e checks for the L-R buttons
//0x0 if none is pressed
//0x1 if R is pressed
//0x2 if L is pressed
//0x3 if both are pressed
u16 sp02E_CheckLRButtons(void) {
	return (~(gKeyReg) >> 8) & 3;
};

void sp02F_KeyDump(void) {
	Var800D = ~(gKeyReg) & 0x3FF;
};

void sp0C9_ForceOneKeyInput(void) {
	u8 key = Var8004;	// 
	u16 num = Var8005;	// num times to press keys
	(u32*) pointer = (u32*) 0x0203f4de;
	*pointer = key;
	
	
	return;
};

void sp0CA_IgnoreKeys(void) {
	return;
};

void sp0CB_PlaceKeyScript(void) {
	return;
};

//Variable Math Specials//
///////////////////////////////////////////////////////////////////////////////////

u16 sp03E_AddVariables(void) {
	var1 = Var8004; //Var contained in Var8004
	var2 = Var8005; //Var contained in Var8005
	bool8 overflow = FALSE;
	u32 sum;
	
	u16 var1 = VarGet(var1);
	u16 var2 = VarGet(var2);
	
	sum = var1 + var2;
	
	if (sum > 0xFFFF) {
		overflow = TRUE;
		sum = 0xFFFF
	}
	
	VarSet(Var8004, sum); //Set var in Var8004
	return overflow;
};

u16 sp03F_SubtractVariables(void) {
	u16 var1 = Var8004; //Var contained in Var8004
	u16 var2 = Var8005; //Var contained in Var8005
	bool8 overflow = FALSE;
	u32 diff;
	
	var1 = VarGet(var1);
	var2 = VarGet(var2);
	
	if (var2 > var1) {
		overflow = TRUE;
		diff = 0;
	}
	else
		diff = var1 - var2;
	
	VarSet(Var8004, diff); //Set var in Var8004
	return overflow;
};

u16 sp040_MultiplyVariables(void) {
	u16 var1 = Var8004; //Var contained in Var8004
	u16 var2 = Var8005; //Var contained in Var8005
	bool8 overflow = FALSE;
	u32 prod;
	
	var1 = VarGet(var1);
	var2 = VarGet(var2);
	
	prod = var1 * var2;
	
	if (prod > 0xFFFF) {
		prod = 0xFFFF;
		overflow = TRUE;
	}
	
	VarSet(Var8004, prod); //Set var in Var8004
	return overflow;
};


u16 sp041_DivideVariables(void) {
	Var8004 = udivsi(Var8004, Var8005);
	return (umodsi(Var8004, Var8005));
};


u16 sp042_ANDVariables(void) {
	return (Var8004 & Var8005);
};

u16 sp043_ORVariables(void) {	
	return (Var8004 | Var8005);
};

u16 sp044_XORVariables(void) {
	return (Var8004 ^ Var8005);
};

//Other Specials//
///////////////////////////////////////////////////////////////////////////////////




// add a string to custom multichoice box by vars 0x8004 and 0x8005
// eg:
//		setvar 0x8004 0x0890
//		setvar 0x8005 0x5040
//		special 0x24
// would load a multichoice pointer to 0x8905040
// personally, special 0x25 is much better/easier to use
void sp024_AddTextByVariable(void) {
#ifdef SAVE_BLOCK_EXPANSION
	u8 multiIndex = Var8006;
	u32 stringPointer = ((Var8004 << 16) | Var8005);
	if (multiIndex > 6)
		return;
	gMultiChoice[multiIndex].stringPointer = stringPointer;
#endif
};



// add a string to custom multichoice box by loadpointer
// eg.
//		setvar 0x8006 0x0
//		loadpointer 0x0 @string
//		special 0x25
void sp025_AddTextByPointer(void) {
#ifdef SAVE_BLOCK_EXPANSION
	u8 multiIndex = Var8006;
	if (multiIndex > 6)
		return;
	gMultiChoice[multiIndex].stringPointer = gLoadPointer;
#endif
};


// special to buffer a pokemon species and size
// Inputs: 	Var8005: variable to get measurements from/store to
// 			Var8006: species to measure
void sp075_MeasurePokemon1(void) {
	u32 varAddr = (u32*) VarGetAddress(Var8005);	// decrypt var ram loc
	u16 species = Var8006;
	bufferPokeNameSize(species, varAddr);	
};


// measure pokemon special
// Inputs: 
// 		var8005: variable the measurement was in (from special 0x75)
// 		var8006: species
// Output:
//		Returns 1 if the pokémon is not of the selected type
//		Returns 2 if the pokémon is smaller
//		Returns 3 if bigger, and also stores the biggest value in the variable
//		Returns 4 if equal in length
u8 sp076_MeasurePokemon2(void) {
	u32 varAddr = (u32*) VarGetAddress(Var8005);	// decrypt var ram loc
	u16 species = Var8006;
	u8 result = CalculateHeight(
	return result;
};



// old man battle with given species/level
// Inputs:
//		var8004: species
//		var8005: level
void sp09C_OldManBattleModifier(void) {
	createMaleMon(&gEnemyParty[0], Var8004, Var8005);
	ScriptContext2_Enable;
	gMain.savedCallback = ReturnToFieldContinueScriptPlayMapMusic;
	gBattleTypeFlags = BATTLE_TYPE_OLD_MAN;
	CreateBattleStartTask(8, 0);
};



void sp18B_DisplayImagesFromTable(void) {
	return;
};

//Battle Specials//
///////////////////////////////////////////////////////////////////////////////////

void sp051_WildShinyBattle(void) {
	return;
};

void sp052_TemporaryStatusInducer(void) {
	return;
};

void sp053_TemporaryStatusCanceller(void) {
	return;
};

void sp054_PermanentStatusInducer(void) {
	return;
};

void sp055_PermanentStatusCanceller(void) {
	return;
};

void sp056_RoamChanger(void) {
	return;
};

void sp057_RoamCanceller(void) {
	return;
};

void sp058_WildDataSwitch(void) {
	return;
};

void sp059_WildDataSwitchCanceller(void) {
	return;
};


//Timer Specials//
///////////////////////////////////////////////////////////////////////////////////

//@Details: Starts the timer
void sp046_StartTimer(void) {
	GBATimer[3] = 0x84;
	GBATimer[2] = 0x0;
	GBATimer[1] = 0x83;
	GBATimer[0] = 0x0;
	return;
};

//@Details: Pauses the timer
void sp047_HaltTimer(void) {
	GBATimer[3] = 0x4;
	GBATimer[1] = 0x3;
	return;
};

//@Details: Unpauses the timer
void sp048_ResumeTimer(void) {
	GBATimer[2] = GBATimer[2];
	GBATimer[3] = 0x84;
	GBATimer[1] = 0x83;
	return;
};

//@Details:	Stops the timer.
//@Returns: The time on the timer.
u16 sp049_StopTimer(void) {
	u16 time = GBATimer[2];
	GBATimer[3] = 0;
	GBATimer[1] = 0;
	GBATimer[0] = 0;
	GBATimer[2] = 0;
	
	return time;
};

//@Returns: The time on the timer.
u16 sp04A_GetTimerValue(void) {
	return GBATimer[2] = 0;
};

void sp04B_StopAndUpdatePlaytime(void) {
	return;
};

void sp04C_UpdatePlaytime(void) {
	return;
};

//@Details: Checks if the timer has reached a value
//			sorted in var 0x8010.
//@Returns: True or False
void sp04D_TimerValueReached(void) {
	u16 time = GBATimer[2];
	
	if (time < Var8010)
		return FALSE;
		
	return TRUE;
};


//@Details: Saves the value in the seconds timer to a 
//			specific memory address.
void sp04E_SaveTimerValue(void) {
	ScriptSpecialsStruct.savedTimer = sp049_StopTimer();
	return;
};

//@Details: Starts the timer with the value stored by
//			Special 0x4E.
void sp04F_StartTimerAtTime(void) {
	StartTimer();
	GBATimer[3] = 0;
	GBATimer[2] = ScriptSpecialsStruct.savedTimer;
	GBATimer[3] = 0x84;
	return;
};

//@Details: Stores the timer value stored by
//			Special 0x4E.
//@Returns: Var 0x8006 - Timer time.
void sp050_StoreTimerToVariable(void) {
	u16 var = Var8006; //Var in Var8006
	VarSet(var, ScriptSpecialsStruct.savedTimer);
	return;
};

//@Details: Loads the value at a given variable and stores
//			it to the saved timer.
//@Input:	Var 0x8006 - Timer value.
void sp061_LoadTimerFromVariable(void) {
	u16 var = Var8006; //Var in Var8006
	ScriptSpecialsStruct.savedTimer = var;
	return;
};

//Safari Specials//
///////////////////////////////////////////////////////////////////////////////////


//@Details: The check Safari ball quantity. 
//@Returns: 1. Var 0x8004 - Normal Safari Ball number.
//		  2. Var 0x8005 - The extra ball slot number
//		  3. To a given variable the number as a full integer. Max value is 0x63FF
u16 sp086_GetSafariBalls(void) {
	Var8004 = gSafariBallNumber;
	Var8005 = *(&gSafariBallNumber + 1);
	return (Var8004 + Var8005);
};


//@Details: An increase\decrease safari balls code.
//		  This code doesn't allow people to go over 100 max balls 
//		  as a safety measure.
//@Input: Var 0x8004 as the number to increase or decrease the balls by. 
//	    0x1aa decreases the balls by aa, and 0x0aa increases them by aa. 
//@Returns: None
void sp087_ChangeSafariBalls(void) {
	u16 input = Var8004;
	s32 calc;
	
	if (input & 0x100)
	{
		input ^= 0x100;
		input = MathMax(100, input);
		input *= -1;
	}
	else
		input = MathMax(100, input);
	
	calc = gSafariBallNumber + input;
	if (calc > 100)
		calc = 100;
	else if (calc < 0)
		calc = 0;
	gSafariBallNumber = calc;
	return;
};

//@Details: The get safari pedometer special.
//@Returns: To a given variable the number of remaining steps
u16 sp088_GetSafariCounter(void) {
	return gSafariSteps;
};

//@Details: The Set Safari steps special. 
//	      It allows you to set a specific ammount of steps 
//		  until the safari handler is called.
//Input: Var 0x8004 is the amount of steps to place.
void sp089_SetSafariCounter(void) {
	u16 input = Var8004;
	gSafariSteps = input;
};

//Walking Specials//
///////////////////////////////////////////////////////////////////////////////////


//@Details: Tile Number getter, gets the tile's number at (0x8004, 0x8005) location. 
//@Input: 1. Var 0x8004 - X-Coordinate
//	    2. Var 0x8005 - Y-Coordinate
//@Returns: Returns to a given variable the desired tile number
u16 sp07E_GetTileNumber(void) {
	u16 x = Var8004;
	u16 y = Var8005;
	return MapGridGetMetatileIdAt(x + 7, y + 7);
};

//@Details: The Tile Attribute getter. Designed to be used with 
//		  special 0x8f before it (to get the positions) and to 
//		  be possible to use the required wild battle randomizer afterwards.'
//@Input: 1. Var 0x8004 - X-Coordinate
//	    2. Var 0x8005 - Y-Coordinate
//@Returns: 1. Var 0x8004 - The tile's background byte
//		  2. Var 0x8005 - The tile's behaviour bytes.
//		  3. To a given variable the background byte.
u16 sp07F_GetTileBehaviour(void) {
	u16 x = Var8004;
	u16 y = Var8005;
	u32 field = MapGridGetMetatileField(x + 7, y + 7, field);
	
	Var8004 = (field & 0xFF000000) >> 0x18;
	Var8005 = (field & 0xFFFF);
	return Var8004 & 3;
};

void sp097_StartGroundBattle(void) {
	return;
};

void sp098_StartWaterBattle(void) {
	return;
};

void sp081_SetWalkingScript(void) {
	return;
};



*/

