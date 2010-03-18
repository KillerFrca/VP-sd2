/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Freya
SD%Complete: 80
SDComment: TODO: Brightleaf, Freya with Brightleaf, 3wave adds, nature bomb, correct mushroom
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"
enum
{
    //freya yells
    SAY_AGGRO							= -1700152,
    SAY_AGGRO_HARD                      = -1700153,
    SAY_WAVE_1                          = -1700154,
    SAY_WAVE_3                          = -1700155,
    SAY_WAVE_10                         = -1700156,
    SAY_SLAY_1                          = -1700157,
    SAY_SLAY_2                          = -1700158,
    SAY_BERSERK                         = -1700159,
    SAY_DEATH                           = -1700160,
    SAY_YOGGSARON                       = -1700161,
    
    //stonebark yells
    SAY_STONE_AGGRO                     = -1700166,
    SAY_STONE_SLAY_1                    = -1700167,
    SAY_STONE_SLAY_2                    = -1700168,
    SAY_STONE_DEATH                     = -1700169,

    //ironbranch yells
    SAY_IRON_AGGRO                      = -1700170,
    SAY_IRON_SLAY_1                     = -1700171,
    SAY_IRON_SLAY_2                     = -1700172,
    SAY_IRON_DEATH                      = -1700173,

    //brightleaf yells
    SAY_BRIGHT_AGGRO                     = -1700162,
    SAY_BRIGHT_SLAY_1                    = -1700163,
    SAY_BRIGHT_SLAY_2                    = -1700164,
    SAY_BRIGHT_DEATH                     = -1700165,
    
    //freya
    //general abilities
    SPELL_SUNBEAM                       = 62623,
    H_SPELL_SUNBEAM                     = 62872,
    SPELL_ATTUNED_TO_NATURE             = 62519,
    SPELL_TOUCH_OF_EONAR                = 62528,
    H_SPELL_TOUCH_OF_EONAR              = 62892,
    SPELL_LIFEBINDER_GIFT               = 62584,
    H_SPELL_LIFEBINDER_GIFT             = 62619,
    SPELL_NATURE_BOMB                   = 64587,
    H_SPELL_NATURE_BOMB                 = 64650,
    SPELL_BERSERK                       = 47008,

    SPELL_PHEROMONES_LG                 = 62619,
    SPELL_POTENT_PHEROMONES             = 64321,

    SPELL_SUMMON_ALLIES_OF_NATURE     = 62678, //better do that in sd2
    SPELL_SUMMON_WAVE_10                = 62688,
    SPELL_SUMMON_WAVE_3                 = 62686,
    SPELL_SUMMON_WAVE_1                 = 62685,
    SPELL_LIFEBINDERS_GIFT_SUMMON       = 62869,
    SPELL_NATURE_BOMB_SUMMON            = 64606,
    SPELL_HEALTHY_SPORES_SUMMON         = 62593,

    //abilities with Elder Brightleaf
    SPELL_UNSTABLE_ENERGY_FREYA         = 62451,
    H_SPELL_UNSTABLE_ENERGY_FREYA       = 62865,
    SPELL_BRIGHTLEAFS_ESSENCE           = 62385,
    SPELL_EFFECT_BRIGHTLEAF             = 63294,

    //abilities with Elder Ironbranch
    SPELL_IRON_ROOTS_FREYA              = 62283,
    H_SPELL_IRON_ROOTS_FREYA            = 62930,
    SPELL_IRONBRANCHS_ESSENCE           = 62387,
    SPELL_EFFECT_IRONBRANCH             = 63292,
    
    SPELL_STRENGTHENED_IRON_ROOTS_SUMM  = 63601, //better way to do that through SummonCreature for better control with summoned creature
    
    //abilities with Elder Stonebark 
    SPELL_GROUND_TREMOR_FREYA           = 62437,
    H_SPELL_GROUND_TREMOR_FREYA         = 62859,
    SPELL_STONEBARKS_ESSENCE            = 62386,
    SPELL_EFFECT_STONEBARK              = 63295,

    //elders
    SPELL_DRAINED_OF_POWER              = 62467,
    
    //Elder Brightleaf
    SPELL_BRIGHTLEAFS_FLUX              = 62262,
    SPELL_BRIGHTLEAFS_FLUXP             = 62251,
    SPELL_BRIGHTLEAFS_FLUXM             = 62252,
    SPELL_SOLAR_FLARE                   = 62240,
    H_SPELL_SOLAR_FLARE                 = 62920,
    SPELL_UNSTABLE_SUN_BEAM             = 62243,
    SPELL_UNSTABLE_ENERGY               = 62217,
    H_SPELL_UNSTABLE_ENERGY             = 62922,
    SPELL_PHOTOSYNTHESIS                = 62209,

    //Elder Ironbranch
    SPELL_IMPALE                        = 62310,
    H_SPELL_IMPALE                      = 62928,
    SPELL_IRON_ROOTS                    = 62438,
    H_SPELL_IRON_ROOTS                  = 62861,
    SPELL_THORN_SWARM                   = 62285,
    H_SPELL_THORN_SWARM                 = 62931,
    
    SPELL_IRON_ROOTS_SUMM               = 65160, // same as strengthened roots

    //Elder Stonebark
    SPELL_FIST_OF_STONE                 = 62344,
    //SPELL_BROKEN_BONES                  = 62356, probably unused
    SPELL_GROUND_TREMOR                 = 62325,
    H_SPELL_GROUND_TREMOR               = 62932,
    SPELL_PETRIFIED_BARK                = 62337,
    H_SPELL_PETRIFIED_BARK              = 62933,

    //waves
    SPELL_DETONATE                      = 62598,
    H_SPELL_DETONATE                    = 62937,
    SPELL_FLAME_LASH                    = 62608,

    SPELL_CONSERVATORS_GRIP             = 62532,
    SPELL_NATURES_FURY                  = 62589,
    H_SPELL_NATURES_FURY                = 63571,

    SPELL_TIDAL_WAVE                    = 62653,
    H_SPELL_TIDAL_WAVE                  = 62935,

    SPELL_LIFEBINDERS_VISUAL            = 62579,
    SPELL_LIFEBINDER_GROW               = 44833,

    SPELL_SUMMON_CHEST_1                = 62950,
    SPELL_SUMMON_CHEST_2                = 62952,
    SPELL_SUMMON_CHEST_3                = 62953,
    SPELL_SUMMON_CHEST_4                = 62954,
    //SPELL_SUMMON_CHEST_5                = 62955,       four chests is enough :)
    //SPELL_SUMMON_CHEST_6                = 62956,
    //SPELL_SUMMON_CHEST_7                = 62957,
    //SPELL_SUMMON_CHEST_8                = 62958,

    NPC_NATURE_BOMB                     = 34129,
    NPC_EONARS_GIFT                     = 33228,
    NPC_HEALTHY_SPORE                   = 33215,
    NPC_IRON_ROOTS                      = 33008,
    NPC_STRENGTHENED_IRON_ROOTS         = 33168,

    NPC_ELDER_BRIGHTLEAF                = 32915,
    NPC_ELDER_IRONBRANCH                = 32913,
    NPC_ELDER_STONEBARK                 = 32914,

    NPC_WAVE_1                          = 33203,
    NPC_WAVE_3_WATER                    = 33202,
    NPC_WAVE_3_SNAPLASHER               = 32916,
    NPC_WAVE_3_STORM                    = 32919,
    NPC_WAVE_10                         = 32918,

    ACHI_KNOCK_1_NORM                   = 3177,
    ACHI_KNOCK_2_NORM                   = 3178,
    ACHI_KNOCK_3_NORM                   = 3179,
    ACHI_KNOCK_1_HC                     = 3185,
    ACHI_KNOCK_2_HC                     = 3186,
    ACHI_KNOCK_3_HC                     = 3187,
};


Creature* GetFreya(Creature* pCreature, ScriptedInstance* instance){return (Creature*)Unit::GetUnit((*pCreature), instance->GetData64(DATA_FREYA));}

///////////////////////////////////////////
/// iron roots / strenghtend iron roots ///
///////////////////////////////////////////
struct MANGOS_DLL_DECL mob_iron_rootsAI : public ScriptedAI
{
    mob_iron_rootsAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }
    
    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool NpcIronRoots;
    bool NpcStrengthenedIronRoots;

    uint64 m_uiVictimGUID;

    void Reset()
    {
        m_uiVictimGUID = 0;
        NpcStrengthenedIronRoots = false;
        NpcIronRoots = false;
        switch(m_creature->GetEntry())
        {
            case NPC_STRENGTHENED_IRON_ROOTS : NpcStrengthenedIronRoots = true; break;
            case NPC_IRON_ROOTS: NpcIronRoots = true; break;
        }
    }
    void AttackStart(Unit* pWho){return;}
    void SetVictim(uint64 victim)
    {
        if (victim)
        {
            m_uiVictimGUID = victim;
            if (Unit* pVictim = Unit::GetUnit((*m_creature), m_uiVictimGUID))
            {
                if (NpcStrengthenedIronRoots)
                    pVictim->CastSpell(pVictim, m_bIsRegularMode ? SPELL_IRON_ROOTS_FREYA : H_SPELL_IRON_ROOTS_FREYA, true);
                if (NpcIronRoots)
                    pVictim->CastSpell(pVictim, m_bIsRegularMode ? SPELL_IRON_ROOTS : H_SPELL_IRON_ROOTS, true);
            }
        }
    }

    void JustDied(Unit* Killer)
    {
        if (Unit* pVictim = Unit::GetUnit((*m_creature), m_uiVictimGUID))
        {
            if (NpcStrengthenedIronRoots)
                pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_IRON_ROOTS_FREYA : H_SPELL_IRON_ROOTS_FREYA);
            if (NpcIronRoots)
                pVictim->RemoveAurasDueToSpell(m_bIsRegularMode ? SPELL_IRON_ROOTS : H_SPELL_IRON_ROOTS);
        }
    }

    void MoveInLineOfSight(Unit* pWho) { }
    void UpdateAI(const uint32 uiDiff) { }
};

///////////////
//// Freya ////
///////////////
struct MANGOS_DLL_DECL boss_freyaAI : public ScriptedAI
{
    boss_freyaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 Wave_Timer;
    uint32 LifebinderGift_Timer;
    uint32 Sunbeam_Timer;
    uint32 Wave_Count;
    uint32 spellId1;
    uint32 spellId2;
    uint32 spellId3;
    uint32 spellIdCast;
    uint32 yell;
    uint32 Berserk_Timer;
    uint32 ChangeFaction_Timer;
    uint32 EndPhaseDespawn_Timer;
    uint32 GroundTremor_Timer;
    uint32 IronRoots_Timer;

    bool EndPhase;
    bool HardMode;
    bool Knock1;
    bool Knock2;
    bool FactionChanged;

    bool BrightleafAlive;
    bool StonebarkAlive;
    bool IronbranchAlive;

    void Reset()
    {
        Wave_Timer = urand(9,12)*IN_MILISECONDS;
        LifebinderGift_Timer = urand(19,23)*IN_MILISECONDS;
        Sunbeam_Timer = urand(44,49)*IN_MILISECONDS;
        Wave_Count = 0;
        Berserk_Timer = 10*MINUTE*IN_MILISECONDS;
        ChangeFaction_Timer = 5*IN_MILISECONDS;
        EndPhaseDespawn_Timer = 10*IN_MILISECONDS;
        GroundTremor_Timer = urand(20,25)*IN_MILISECONDS;
        IronRoots_Timer = urand(35,40)*IN_MILISECONDS;

        FactionChanged = false;
        HardMode = false;
        EndPhase = false;
        Knock1 = false;
        Knock2 = false;
        BrightleafAlive = true;
        StonebarkAlive = true;
        IronbranchAlive = true;

        m_creature->setFaction(16);
    }

    void KilledUnit(Unit *victim)
    {
        DoScriptText(urand(0,1) ? SAY_SLAY_1 : SAY_SLAY_2, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(m_bIsRegularMode ? SAY_AGGRO : SAY_AGGRO_HARD, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FREYA, IN_PROGRESS);
        
        BuffOnAggro();
    }
    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (EndPhase)
            return;
        
        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            if (IsCombatMovement())
                m_creature->GetMotionMaster()->MoveChase(pWho);
        }
    }
    
    void CompleteAchievement(uint16 entry)
    {
        //Map* pMap = m_creature->GetMap();
        //AchievementEntry const *Achievement = GetAchievementStore()->LookupEntry(entry);
        //if(Achievement && pMap)
        //{
        //    Map::PlayerList const &lPlayers = pMap->GetPlayers();
        //    if (!lPlayers.isEmpty())
        //    {
        //        for(Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
        //        {
        //            if (Player* pPlayer = itr->getSource())
        //                pPlayer->GetAchievementMgr().CompletedAchievement(Achievement);
        //        }
        //    }
        //}
    }
    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (damage > m_creature->GetHealth())
        {
            damage = 0;
            m_creature->SetHealth(1);
            EndPhase = true;
        }
    }

    void JustReachedHome()
    {
        DespawnAllCreaturesWithEntry(NPC_NATURE_BOMB);
        DespawnAllCreaturesWithEntry(NPC_IRON_ROOTS);
        DespawnAllCreaturesWithEntry(NPC_STRENGTHENED_IRON_ROOTS);
        DespawnAllCreaturesWithEntry(NPC_WAVE_1);
        DespawnAllCreaturesWithEntry(NPC_WAVE_3_WATER);
        DespawnAllCreaturesWithEntry(NPC_WAVE_3_SNAPLASHER);
        DespawnAllCreaturesWithEntry(NPC_WAVE_3_STORM);
        DespawnAllCreaturesWithEntry(NPC_WAVE_10);
        DespawnAllCreaturesWithEntry(NPC_EONARS_GIFT);

        for(uint32 i = NPC_ELDER_IRONBRANCH; i <= NPC_ELDER_BRIGHTLEAF; i++)
            if(Creature* pTemp = GetClosestCreatureWithEntry(m_creature, i, 180.0f))
                pTemp->RemoveAllAuras();
    }


    void BuffOnAggro()
    {
        m_creature->CastSpell(m_creature, SPELL_ATTUNED_TO_NATURE, true);
        if(Aura *pAura = m_creature->GetAura(SPELL_ATTUNED_TO_NATURE, EFFECT_INDEX_0))
            pAura->SetStackAmount(150);
        m_creature->CastSpell(m_creature, m_bIsRegularMode ? SPELL_TOUCH_OF_EONAR : H_SPELL_TOUCH_OF_EONAR, true);

        if(Creature* pBright = GetClosestCreatureWithEntry(m_creature, NPC_ELDER_BRIGHTLEAF, 180.0f))
        {
            m_creature->CastSpell(m_creature, SPELL_BRIGHTLEAFS_ESSENCE, true);
            pBright->CastSpell(m_creature, SPELL_EFFECT_BRIGHTLEAF, true);
            pBright->CastSpell(pBright, SPELL_DRAINED_OF_POWER, true);
            BrightleafAlive = true;
        }else BrightleafAlive = false;

        if(Creature* pIron = GetClosestCreatureWithEntry(m_creature, NPC_ELDER_IRONBRANCH, 180.0f))
        {
            m_creature->CastSpell(m_creature, SPELL_IRONBRANCHS_ESSENCE, true);
            pIron->CastSpell(m_creature, SPELL_EFFECT_IRONBRANCH, true);
            pIron->CastSpell(pIron, SPELL_DRAINED_OF_POWER, true);
            IronbranchAlive = true;
        }else IronbranchAlive = false;

        if(Creature* pStone = GetClosestCreatureWithEntry(m_creature, NPC_ELDER_STONEBARK, 180.0f))
        {
            m_creature->CastSpell(m_creature, SPELL_STONEBARKS_ESSENCE, true);
            pStone->CastSpell(m_creature, SPELL_EFFECT_STONEBARK, true);
            pStone->CastSpell(pStone, SPELL_DRAINED_OF_POWER, true);
            StonebarkAlive = true;
        }else StonebarkAlive = false;

        if(BrightleafAlive && IronbranchAlive && StonebarkAlive)
            HardMode = true;
        if(BrightleafAlive || IronbranchAlive || StonebarkAlive)
            Knock1 = true;
        if((BrightleafAlive && IronbranchAlive) || 
            (BrightleafAlive && StonebarkAlive) || 
            (IronbranchAlive && StonebarkAlive))
            Knock2 = true;

        m_creature->SetHealth(m_creature->GetMaxHealth());
    }

    void DespawnAllCreaturesWithEntry(uint32 entry)
    {
        std::list<Creature*> m_pCreatures;
        GetCreatureListWithEntryInGrid(m_pCreatures, m_creature, entry, 150.0f);
 
        if (m_pCreatures.empty())
            return;
 
        for(std::list<Creature*>::iterator iter = m_pCreatures.begin(); iter != m_pCreatures.end(); ++iter)
            (*iter)->ForcedDespawn();
    }

    void HandleRoots(int8 times)
    {
        for(int8 i = 0; i != times; )
        {
            if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM,1))
            {
                if(target->HasAura(SPELL_IRON_ROOTS_FREYA || H_SPELL_IRON_ROOTS_FREYA))
                    return;

                float x = target->GetPositionX();
                float y = target->GetPositionY();
                float z = target->GetPositionZ();
                if(Creature* pRoots = m_creature->SummonCreature(NPC_STRENGTHENED_IRON_ROOTS, x, y, z, 0, TEMPSUMMON_DEAD_DESPAWN, 0))
                    ((mob_iron_rootsAI*)pRoots->AI())->SetVictim(target->GetGUID());
                DoTeleportPlayer(target, x, y, z, target->GetOrientation());
                i++;
            }else break;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if(EndPhase)
        {
            if(ChangeFaction_Timer < diff && !FactionChanged)
            {
                DoScriptText(SAY_DEATH, m_creature);
                m_creature->AttackStop();
                m_creature->RemoveAllAuras();
                m_creature->CastSpell(SelectUnit(SELECT_TARGET_RANDOM,0), m_bIsRegularMode ? (HardMode ? SPELL_SUMMON_CHEST_2 : SPELL_SUMMON_CHEST_1) : (HardMode ? SPELL_SUMMON_CHEST_4 : SPELL_SUMMON_CHEST_3), true);
                
                if(HardMode)
                    CompleteAchievement(m_bIsRegularMode ? ACHI_KNOCK_3_NORM : ACHI_KNOCK_3_HC);
                else if(Knock2)
                    CompleteAchievement(m_bIsRegularMode ? ACHI_KNOCK_2_NORM : ACHI_KNOCK_2_HC);
                else if(Knock1)
                    CompleteAchievement(m_bIsRegularMode ? ACHI_KNOCK_1_NORM : ACHI_KNOCK_1_HC);				
                m_creature->ClearInCombat();
                m_creature->setFaction(m_creature->getVictim()->getFaction());
                SetCombatMovement(false);
                m_creature->GetMotionMaster()->Clear(false);
                FactionChanged = true;
            }else ChangeFaction_Timer -= diff;

            if(EndPhaseDespawn_Timer < diff)
            {
                m_creature->ForcedDespawn();
            }else EndPhaseDespawn_Timer -= diff;
            return;
        }
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(Wave_Timer < diff && Wave_Count < 6)
        {
            if (Wave_Count == 0 || Wave_Count == 3)
            {
                switch(urand(0,5))
                {
                    case 0: spellId1 = 62685; spellId2 = 62686; spellId3 = 62688; break;
                    case 1: spellId1 = 62685; spellId2 = 62688; spellId3 = 62686; break;
                    case 2: spellId1 = 62686; spellId2 = 62685; spellId3 = 62688; break;
                    case 3: spellId1 = 62686; spellId2 = 62688; spellId3 = 62685; break;
                    case 4: spellId1 = 62688; spellId2 = 62685; spellId3 = 62686; break;
                    case 5: spellId1 = 62688; spellId2 = 62686; spellId3 = 62685; break;
                }
            }
            if(Wave_Count == 0 || Wave_Count == 3)
                spellIdCast = spellId1;
            if(Wave_Count == 1 || Wave_Count == 4)
                spellIdCast = spellId2;
            if(Wave_Count == 2 || Wave_Count == 5)
                spellIdCast = spellId3;
            m_creature->CastSpell(m_creature, spellIdCast, true);
            
            switch(spellIdCast)
            {
                case 62685: yell = SAY_WAVE_1; break;
                case 62686: yell = SAY_WAVE_3; break;
                case 62688: yell = SAY_WAVE_10; break;
            }
            DoScriptText(yell, m_creature);

            Wave_Timer = MINUTE*IN_MILISECONDS;
            Wave_Count++;
        }else Wave_Timer -= diff;

        if (LifebinderGift_Timer < diff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), SPELL_LIFEBINDERS_GIFT_SUMMON);
            LifebinderGift_Timer = urand(38, 42)*1000;
        }else LifebinderGift_Timer -= diff;

        if(Sunbeam_Timer < diff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), m_bIsRegularMode ? SPELL_SUNBEAM : H_SPELL_SUNBEAM);
            Sunbeam_Timer = urand(15,20)*IN_MILISECONDS;		
        }else Sunbeam_Timer -= diff;

        if(StonebarkAlive)
        {
            if(GroundTremor_Timer < diff)
            {
                DoCast(m_creature, m_bIsRegularMode ? SPELL_GROUND_TREMOR_FREYA : H_SPELL_GROUND_TREMOR_FREYA);
                GroundTremor_Timer = urand(26,29)*IN_MILISECONDS;
            }else GroundTremor_Timer -= diff;
        }
        if(IronbranchAlive)
        {
            if(IronRoots_Timer < diff)
            {
                HandleRoots(m_bIsRegularMode ? 1 : 2);              //not sure about how many times roots should be summoned
                IronRoots_Timer = urand(50,70)*IN_MILISECONDS;
            }else IronRoots_Timer -= diff;
        }
        

        if(Wave_Count == 6)
        {
        }

        if(Berserk_Timer < diff)
        {
            DoCast(m_creature, SPELL_BERSERK);
            DoScriptText(SAY_BERSERK, m_creature);
            Berserk_Timer = 60*IN_MILISECONDS;		
        }else Berserk_Timer -= diff;
        
        DoMeleeAttackIfReady();

    }

};

/////////////////////////////////////////////////
/// nature bomb / eonar's gift / healthy spore///
/////////////////////////////////////////////////
struct MANGOS_DLL_DECL mob_freya_groundAI : public ScriptedAI
{
     mob_freya_groundAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 NatureBomb_Timer;
    uint32 EonarsGift_Timer;
    uint32 NonSelectable_Timer;
    uint32 Grow_Timer;
    float size;

    bool NpcNatureBomb;
    bool NpcEonarsGift;
    bool NpcHealthySpore;

    void Reset()
    {
        NatureBomb_Timer = urand(9,11)*IN_MILISECONDS;
        EonarsGift_Timer = urand(11,13)*IN_MILISECONDS;
        NonSelectable_Timer = 5*IN_MILISECONDS;
        Grow_Timer = 0;
        size = float(0.1);
        NpcNatureBomb = false;
        NpcEonarsGift = false;
        NpcHealthySpore = false;
        if(m_creature->GetEntry() == NPC_NATURE_BOMB)
            NpcNatureBomb = true;
        if(m_creature->GetEntry() == NPC_EONARS_GIFT)
            NpcEonarsGift = true;
        if(m_creature->GetEntry() == NPC_HEALTHY_SPORE)
            NpcHealthySpore = true;

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        if(NpcEonarsGift)
            m_creature->CastSpell(m_creature, SPELL_LIFEBINDERS_VISUAL, true);
        if(NpcHealthySpore)
            m_creature->CastSpell(m_creature, SPELL_POTENT_PHEROMONES, true);
    }
    void AttackStart(Unit* pWho){return;}

    void UpdateAI(const uint32 diff)
    {
        if(!m_creature->isAlive())
            return;

        if(NpcNatureBomb)
            if(NatureBomb_Timer < diff)
            {
                m_creature->CastSpell(m_creature, m_bIsRegularMode ? SPELL_NATURE_BOMB : H_SPELL_NATURE_BOMB, true);
                m_creature->ForcedDespawn();
            }else NatureBomb_Timer -= diff;

        if(NpcEonarsGift)
        {
            if (Grow_Timer > 500 && size < 1.5)
            {
                size += float(diff)/Grow_Timer;
                m_creature->SetFloatValue(OBJECT_FIELD_SCALE_X, size);
                Grow_Timer = 0;
                error_log("size = %f", size);
                error_log("grow_timer = %u", Grow_Timer);
            }else Grow_Timer += diff;

            if(EonarsGift_Timer < diff)
            {
                m_creature->CastSpell(GetFreya(m_creature, m_pInstance), m_bIsRegularMode ? SPELL_LIFEBINDER_GIFT : H_SPELL_LIFEBINDER_GIFT, true);
                EonarsGift_Timer = IN_MILISECONDS;
            }else EonarsGift_Timer -= diff;

            if(NonSelectable_Timer < diff && m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
            {
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->CastSpell(m_creature, SPELL_PHEROMONES_LG, true);
            }else NonSelectable_Timer -= diff;
        }
    }
};

////////////////////////
/// Elder Brightleaf ///
////////////////////////
struct MANGOS_DLL_DECL boss_elder_brightleafAI : public ScriptedAI
{
    boss_elder_brightleafAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }
    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 BrightleafsFlux_Timer;
    uint32 SolarFlare_Timer;
    uint32 UnstableSunBeam_Timer;

    void Reset()
    {
        BrightleafsFlux_Timer = 2*IN_MILISECONDS;
        UnstableSunBeam_Timer = 3*IN_MILISECONDS;
        SolarFlare_Timer = urand(50,60)*IN_MILISECONDS;

    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_BRIGHT_AGGRO, m_creature);
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(SAY_BRIGHT_DEATH, m_creature);
    }

    void KilledUnit(Unit *victim)
    {
        DoScriptText(urand(0,1) ? SAY_BRIGHT_SLAY_1 : SAY_BRIGHT_SLAY_2, m_creature);
    }


    void UpdateAI(const uint32 diff)
    {
        if(!m_creature->isAlive())
            return;

        if (BrightleafsFlux_Timer < diff)
        {
            DoCast(m_creature, SPELL_BRIGHTLEAFS_FLUX);
            BrightleafsFlux_Timer = 5*IN_MILISECONDS;
        }else BrightleafsFlux_Timer -= diff;

        if(UnstableSunBeam_Timer < diff)
        {
            DoCast(m_creature, SPELL_UNSTABLE_SUN_BEAM);
            UnstableSunBeam_Timer = 5*IN_MILISECONDS;
        }else UnstableSunBeam_Timer -= diff;

        if (SolarFlare_Timer < diff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), m_bIsRegularMode ? SPELL_SOLAR_FLARE : H_SPELL_SOLAR_FLARE);
            SolarFlare_Timer = urand(40,50)*IN_MILISECONDS;
        }else SolarFlare_Timer -= diff;

         DoMeleeAttackIfReady();
    }
};

////////////////////////
/// Elder Ironbranch ///
////////////////////////
struct MANGOS_DLL_DECL boss_elder_ironbranchAI : public ScriptedAI
{
    boss_elder_ironbranchAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 IronRoots_Timer;
    uint32 ThronSwarm_Timer;
    uint32 Impale_Timer;
    
    void Reset()
    {
        IronRoots_Timer = urand(8,10)*IN_MILISECONDS;
        ThronSwarm_Timer = urand(4,6)*IN_MILISECONDS;
        Impale_Timer = urand(40,50)*IN_MILISECONDS;;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_IRON_AGGRO, m_creature);
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(SAY_IRON_DEATH, m_creature);
    }

    void KilledUnit(Unit *victim)
    {
        DoScriptText(urand(0,1) ? SAY_IRON_SLAY_1 : SAY_IRON_SLAY_2, m_creature);
    }

    
    void HandleRoots(int8 times)
    {
        for(int8 i = 0; i != times; )
        {
            if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM,1))
            {
                if(target->HasAura(SPELL_IRON_ROOTS || H_SPELL_IRON_ROOTS))
                    return;

                float x = target->GetPositionX();
                float y = target->GetPositionY();
                float z = target->GetPositionZ();
                if(Creature* pRoots = m_creature->SummonCreature(NPC_IRON_ROOTS, x, y, z, 0, TEMPSUMMON_DEAD_DESPAWN, 0))
                    ((mob_iron_rootsAI*)pRoots->AI())->SetVictim(target->GetGUID());
                DoTeleportPlayer(target, x, y, z, target->GetOrientation());
                i++;
            }else break;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if(!m_creature->isAlive())
            return;

        if (IronRoots_Timer < diff)
        {
            HandleRoots(m_bIsRegularMode ? 1 : 2);              //not sure about how many times roots should be summoned
            IronRoots_Timer = urand(23, 28)*IN_MILISECONDS;
        }else IronRoots_Timer -= diff;

        if (ThronSwarm_Timer < diff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,1), m_bIsRegularMode ? SPELL_THORN_SWARM : H_SPELL_THORN_SWARM);
            ThronSwarm_Timer = urand(9,11)*IN_MILISECONDS;
        }else ThronSwarm_Timer -= diff;

        if (Impale_Timer < diff)
        {
            DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_IMPALE : H_SPELL_IMPALE);
            Impale_Timer = urand(50,60)*IN_MILISECONDS;
        }else Impale_Timer -= diff;

         DoMeleeAttackIfReady();
    }
};

///////////////////////
/// Elder Stonebark ///
///////////////////////
struct MANGOS_DLL_DECL boss_elder_stonebarkAI : public ScriptedAI
{
    boss_elder_stonebarkAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }
    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 GroundTremor_Timer;
    uint32 FistOfStone_Timer;
    uint32 PetrifiedBark_Timer;
    void Reset()
    {
        GroundTremor_Timer = urand(7,10)*IN_MILISECONDS;
        FistOfStone_Timer = urand(13,16)*IN_MILISECONDS;
        PetrifiedBark_Timer = urand(30,40)*IN_MILISECONDS;

    }
    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_STONE_AGGRO, m_creature);
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(SAY_STONE_DEATH, m_creature);
    }

    void KilledUnit(Unit *victim)
    {
        DoScriptText(urand(0,1) ? SAY_STONE_SLAY_1 : SAY_STONE_SLAY_2, m_creature);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(GroundTremor_Timer < diff)
        {
            DoCast(m_creature, m_bIsRegularMode ? SPELL_GROUND_TREMOR : H_SPELL_GROUND_TREMOR);
            GroundTremor_Timer = urand(18,22)*IN_MILISECONDS;
        }else GroundTremor_Timer -= diff;

        if(FistOfStone_Timer < diff)
        {
            DoCast(m_creature, SPELL_FIST_OF_STONE);
            FistOfStone_Timer = urand(45,55)*IN_MILISECONDS;
        }else FistOfStone_Timer -= diff;

        if(PetrifiedBark_Timer < diff)
        {
            DoCast(m_creature, m_bIsRegularMode ? SPELL_PETRIFIED_BARK : H_SPELL_PETRIFIED_BARK);
            PetrifiedBark_Timer = urand(30,40)*IN_MILISECONDS;
        }else PetrifiedBark_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

///////////////////
/// spawned adds///
///////////////////
struct MANGOS_DLL_DECL mob_freya_spawnedAI : public ScriptedAI
{
    mob_freya_spawnedAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    bool AncientConservator;
    bool AncientWaterSpirit;
    bool StormLasher;
    bool Snaplasher;
    bool DetonatingLasher;
    bool Wave3;
    bool Wave3_FirstDeath;

    uint32 FlameLash_Timer;
    uint32 NaturesFury_Timer;
    uint32 Wave3_DeathCountdown;

    void Reset()
    {
        AttackStart(SelectUnit(SELECT_TARGET_RANDOM,0));
        AncientConservator = false;
        AncientWaterSpirit = false;
        StormLasher = false;
        Snaplasher = false;
        DetonatingLasher = false;
        Wave3 = false;
        Wave3_FirstDeath = false;
        FlameLash_Timer = urand(5,10)*IN_MILISECONDS;
        NaturesFury_Timer = urand(8,10)*IN_MILISECONDS;
        Wave3_DeathCountdown = 10*IN_MILISECONDS;
        switch(m_creature->GetEntry())
        {
            case NPC_WAVE_1:            AncientConservator = true; m_creature->CastSpell(m_creature, SPELL_CONSERVATORS_GRIP, true); break;
            case NPC_WAVE_3_WATER:      AncientWaterSpirit = true; Wave3 = true; break;
            case NPC_WAVE_3_SNAPLASHER: Snaplasher = true;         Wave3 = true; break;
            case NPC_WAVE_3_STORM:      StormLasher = true;        Wave3 = true; break;
            case NPC_WAVE_10:           DetonatingLasher = true; break;
        }

    }
    void JustDied(Unit* Killer)
    {
        if (AncientConservator)
            ReduceStack(30);
        if (Wave3)
        {
            ReduceStack(10);
            Wave3_FirstDeath = true;
        }
        if (DetonatingLasher)
            ReduceStack(2);
    }

    void ReduceStack(uint8 count)
    {
        if(Aura *pAura = Unit::GetUnit((*m_creature), m_pInstance->GetData64(DATA_FREYA))->GetAura(SPELL_ATTUNED_TO_NATURE, EFFECT_INDEX_0))
        {
            if(count > pAura->GetStackAmount())
            {
                pAura->SetStackAmount(1);
                pAura->DropAuraCharge();
            }else pAura->SetStackAmount(pAura->GetStackAmount()-count);
        }
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (damage > m_creature->GetHealth())
            m_creature->CastSpell(m_creature, m_bIsRegularMode ? SPELL_DETONATE : H_SPELL_DETONATE, true);
    }

    void UpdateAI(const uint32 diff)
    {
        if(Wave3_DeathCountdown < diff && Wave3_FirstDeath && Wave3)
        {
        
        }else Wave3_DeathCountdown -= diff;

        if(!m_creature->isAlive())
            return;
        
        if(DetonatingLasher && FlameLash_Timer < diff)
        {
            DoCast(m_creature->getVictim(), SPELL_FLAME_LASH);
            FlameLash_Timer = urand(5,10)*IN_MILISECONDS;
        }else FlameLash_Timer -= diff;

        if(AncientConservator && NaturesFury_Timer < diff)
        {
            DoCast(SelectUnit(SELECT_TARGET_RANDOM,0), m_bIsRegularMode ? SPELL_NATURES_FURY : H_SPELL_NATURES_FURY);
            NaturesFury_Timer = urand(5,6)*IN_MILISECONDS;
        }else NaturesFury_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_freya(Creature* pCreature)
{
    return new boss_freyaAI(pCreature);
}
CreatureAI* GetAI_mob_freya_ground(Creature* pCreature)
{
    return new mob_freya_groundAI(pCreature);
}
CreatureAI* GetAI_mob_iron_roots(Creature* pCreature)
{
    return new mob_iron_rootsAI(pCreature);
}
CreatureAI* GetAI_boss_elder_brightleaf(Creature* pCreature)
{
    return new boss_elder_brightleafAI(pCreature);
}
CreatureAI* GetAI_boss_elder_ironbranch(Creature* pCreature)
{
    return new boss_elder_ironbranchAI(pCreature);
}
CreatureAI* GetAI_boss_elder_stonebark(Creature* pCreature)
{
    return new boss_elder_stonebarkAI(pCreature);
}
CreatureAI* GetAI_mob_freya_spawned(Creature* pCreature)
{
    return new mob_freya_spawnedAI(pCreature);
}

void AddSC_boss_freya()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_freya";
    newscript->GetAI = &GetAI_boss_freya;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_freya_ground";
    newscript->GetAI = &GetAI_mob_freya_ground;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_iron_roots";
    newscript->GetAI = &GetAI_mob_iron_roots;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_elder_brightleaf";
    newscript->GetAI = &GetAI_boss_elder_brightleaf;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "boss_elder_ironbranch";
    newscript->GetAI = &GetAI_boss_elder_ironbranch;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "boss_elder_stonebark";
    newscript->GetAI = &GetAI_boss_elder_stonebark;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_freya_spawned";
    newscript->GetAI = &GetAI_mob_freya_spawned;
    newscript->RegisterSelf();
}

/*
UPDATE creature_template SET ScriptName = 'boss_freya' WHERE entry = 32906;
UPDATE creature_template SET ScriptName = 'boss_elder_stonebark' WHERE entry = 32914;
UPDATE creature_template SET ScriptName = 'boss_elder_ironbranch' WHERE entry = 32913;
UPDATE creature_template SET ScriptName = 'boss_elder_brightleaf' WHERE entry = 32915;
UPDATE creature_template SET ScriptName = 'mob_freya_ground' WHERE entry IN (34129,33228, 33215);
UPDATE creature_template SET ScriptName = 'mob_iron_roots' WHERE entry IN (33008,33168);
UPDATE creature_template SET ScriptName = 'mob_freya_spawned' WHERE entry IN (33203, 33202, 32916, 32919, 32918);
INSERT IGNORE INTO spell_script_target VALUES (62385, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62387, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62386, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62584, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62619, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (63294, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (63292, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (63295, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (63295, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (63292, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (62584, 1, 32906);
INSERT IGNORE INTO spell_script_target VALUES (63947, 1, 32906);
INSERT IGNORE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES('194324','3','8628','Freya\'s Gift','','','','0','0','1','0','0','0','0','0','0','1634','0','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','');
INSERT IGNORE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES('194325','3','8628','Freya\'s Gift','','','','0','0','1','0','0','0','0','0','0','1634','0','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','');
INSERT IGNORE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES('194326','3','8628','Freya\'s Gift','','','','0','0','1','0','0','0','0','0','0','1634','0','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','');
INSERT IGNORE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES('194327','3','8628','Freya\'s Gift','','','','0','0','1','0','0','0','0','0','0','1634','0','0','1','0','0','0','0','0','0','0','1','0','1','0','1','0','0','0','0','0','0','0','0','');
UPDATE creature_template SET scale = 0.1 WHERE entry = 33228;
// 194324 - normal, 194325 - normal hard, 194326 - hc, 194327 - hc hard

-- Ulduar: Freya yells
(-1700152,'The Conservatory must be protected!',15526,1,0,'freya - aggro'),
(-1700153,'Elders, grant me your strength!',15527,1,0,'freya - hardmode aggro'),
(-1700154,'Eonar, your servant requires aid!',15528,1,0,'freya - summon conservator'),
(-1700155,'Children, assist me!',15533,1,0,'freya - summon elementals'),
(-1700156,'The swarm of the elements shall overtake you!',15534,1,0,'freya - summon lashers'),
(-1700157,'Forgive me.',15529,1,0,'freya - slay 01'),
(-1700158,'From your death springs life anew!',15530,1,0,'freya - slay 02'),
(-1700159,'You have strayed too far, wasted too much time!',15532,1,0,'freya - berserk'),
(-1700160,'His hold on me dissipates. I can see clearly once more. Thank you, heroes.',15531,1,0,'freya - defeated'),
(-1700161,'Eonar, your servant calls for your blessing!',15535,1,0,'freya - yoggsaron event'),


-- Ulduar: Elder Brightleaf yells
(-1700162,'Matron, the Conservatory has been breached!',15483,1,0,'brightleaf - aggro'),
(-1700163,'Fertilizer.',15485,1,0,'brightleaf - slay 01'),
(-1700164,'Your corpse will nourish the soil!',15486,1,0,'brightleaf - slay 0s2'),
(-1700165,'Matron, one has fallen!',15487,1,0,'brightleaf - death'),
-- Ulduar: Elder Stonebark yells
(-1700166,'This place will serve as your graveyard.',15500,1,0,'stonebark - aggro'),
(-1700167,'<Angry roar>',15501,3,0,'stonebark - slay 01'),
(-1700168,'Such a waste.',15502,1,0,'stonebark - slay 02'),
(-1700169,'Matron, flee! They are ruthless....',15503,1,0,'stonebark - death'),
-- Ulduar: Elder Ironbranch yells
(-1700170,'Mortals have no place here!',15493,1,0,'ironbranch - aggro'),
(-1700171,'I return you whence you came!',15494,1,0,'ironbranch - slay 01'),
(-1700172,'BEGONE!',15495,1,0,'ironbranch - slay 02'),
(-1700173,'Freya! They come for you.',15496,1,0,'ironbranch - death'),
*/