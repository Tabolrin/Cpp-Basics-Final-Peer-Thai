#include "CombatSystem.h"
#include "HitResult.h"
#include "Items.h"
#include "Ui.h"
#include "PlayerChoice.h"
#include <iostream>
#include <cstdlib>
#include <limits> 
#include <vector>      

float GetElementMultiplier(Elements attacker, Elements defender)
{
    if (attacker == Elements::WATER && defender == Elements::FIRE)
        return 2.0f;
    if (attacker == Elements::WATER && defender == Elements::GRASS)
        return 0.5f;

    if (attacker == Elements::FIRE && defender == Elements::GRASS)
        return 2.0f;
    if (attacker == Elements::FIRE && defender == Elements::WATER)
        return 0.5f;

    if (attacker == Elements::GRASS && defender == Elements::WATER)
        return 2.0f;
    if (attacker == Elements::GRASS && defender == Elements::FIRE)
        return 0.5f;

    return 1.0f;
}

void CombatSystem::Combat(PlayerParty& party, Enemy& enemy, Inventory& inventory)
{
    std::cout << "\n  Combat started between your party and " << enemy.GetName() << "!\n\n";
    Ui::PrintCombatVisual(enemy.GetElement());

    //  Choose who goes first
    std::cout << "Choose your starting unit:\n";
    Unit* currentUnit = ChoosePartyUnit(party);

    //  Main loop
    while (!party.IsDefeated() && enemy.GetHp() > 0)
    {
        system("cls");
        Ui::PrintCombatVisual(enemy.GetElement());

        // -- Player's turn --
        if (currentUnit->GetHp() <= 0)
        {
            std::cout << currentUnit->GetName() << " is down. Please switch to another unit.\n";
            currentUnit = ChoosePartyUnit(party);
            continue;
        }

        std::cout << "\n " << currentUnit->GetName() << "'s turn:\n"
            << "Choose action:\n"
            << "1. Attack\n"
            << "2. Use Item\n"
            << "3. Switch Unit\n"
            << "Choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        // todo: delete  Discard everything in the input buffer up to (and including) the next newline.
        // Wrapping max in parentheses prevents the Windows max macro from interfering.

        switch (static_cast<PlayerChoice>(choice))
        {
        case PlayerChoice::ATTACK:
        {
            std::cout << "Choose attack type:\n"
                << "1. Normal Attack\n"
                << "2. Elemental Attack\n"
                << "Choice: ";

            int attackType;
            std::cin >> attackType;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

            HitResult result = currentUnit->HitOrMiss();
            int        baseDmg = (attackType == 1)
                ? currentUnit->GetNormalDmg()
                : static_cast<int>(currentUnit->GetElementalDmg()
                    * GetElementMultiplier(currentUnit->GetElement(), enemy.GetElement()));
            int        damage = 0;

            // print and apply damage
            switch (result)
            {
                case HitResult::CRIT:
                    damage = baseDmg * 2;
                    std::cout << "[CRIT] Dealt " << damage << " damage!\n";
                    enemy.TakeDamage(damage);
                    break;

                case HitResult::HIT:
                    damage = baseDmg;
                    std::cout << "[HIT] Dealt " << damage << " damage!\n";
                    enemy.TakeDamage(damage);
                    break;

                case HitResult::MISS:
                    std::cout << "[MISS] Attack missed!\n";
                    break;
            }
            std::cout << "Enemy HP: " << enemy.GetHp() << "\n";

            // check for victory
            if (enemy.GetHp() <= 0)
            {
                std::cout << "\n Enemy defeated!\n";
                int expReward = 10 + enemy.GetLevel() * 5;
                std::cout << currentUnit->GetName() << " gains " << expReward << " EXP!\n";
                currentUnit->AddExp(expReward);

                if (currentUnit->GetLevel() * 10 <= currentUnit->GetExp())
                {
                    currentUnit->PlayerLevelUp();
                    std::cout << currentUnit->GetName()
                        << " leveled up to level "
                        << currentUnit->GetLevel() << "!\n";
                }
                return;
            }
            break;
        }

        case PlayerChoice::USE_ITEM:
            UseItemMenu(inventory, currentUnit);
            break;

        case PlayerChoice::SWITCH_UNIT:
            currentUnit = ChoosePartyUnit(party);
            break;

        default:
            std::cout << "Invalid choice, turn skipped.\n";
            break;
        }

        // -- Enemy's turn --
        std::cout << "\nEnemy's turn:\n";
        if (currentUnit->GetHp() > 0)
        {
            HitResult result = enemy.HitOrMiss();
            int damage = 0;
            std::cout << enemy.GetName() << " attacks " << currentUnit->GetName() << "! ";

            damage = enemy.GetNormalDmg()
                + static_cast<int>(enemy.GetElementalDmg()
                    * GetElementMultiplier(enemy.GetElement(), currentUnit->GetElement()));

            switch (result)
            {
            case HitResult::CRIT:
                damage *= 2;
                std::cout << "[CRIT] ";
                break;
            case HitResult::HIT:
                std::cout << "[HIT] ";
                break;
            case HitResult::MISS:
                std::cout << "[MISS] Attack missed!\n";
                damage = 0;
                break;
            }
            if (damage > 0)
            {
                currentUnit->TakeDamage(damage);
                std::cout << "Dealt " << damage << " damage! ";
            }
            std::cout << currentUnit->GetName()
                << " HP: " << currentUnit->GetHp() << "\n";

            if (currentUnit->GetHp() <= 0)
            {
                std::cout << currentUnit->GetName() << " has fallen! Choose another unit.\n";
                currentUnit = ChoosePartyUnit(party);
            }

            if (party.IsDefeated())
            {
                std::cout << "\nYour party was defeated!\n";
                return;
            }
        }
        else
        {
            std::cout << currentUnit->GetName()
                << " is down, skipping enemy attack.\n";
        }
    }
}


Unit* CombatSystem::ChoosePartyUnit(PlayerParty& party)
{
    int choice;
    bool validChoice = false;
    auto& members = party.GetAll();

    std::cout << "\nAvailable Units:\n";

    auto partyUnits = party.GetAll();

    for (int i = 0; i < partyUnits.size(); ++i)
    {
        if (partyUnits[i].GetHp() > 0)
        {
            std::cout << i + 1 << ". " << partyUnits[i].GetName() << ", Element: ";

            switch (partyUnits[i].GetElement())
            {
            case Elements::FIRE:
                std::cout << "FIRE";
                break;
            case Elements::WATER:
                std::cout << "WATER";
                break;
            case Elements::GRASS:
                std::cout << "GRASS";
                break;
            default:
                std::cout << "UNKNOWN";
                break;
            }

            std::cout << " (HP: " << partyUnits[i].GetHp() << ")\n";
        }
    }

    do
    {
        char ch;
        std::cout << "Choose unit index: ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > static_cast<int>(members.size()))
        {
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            std::cout << "Invalid choice. Please try again.\n";
        }
        else if (members[choice - 1].GetHp() <= 0)
        {
            std::cout << "This unit is down. Please choose another unit.\n";
        }
        else
        {
            validChoice = true;
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    } while (!validChoice);

    return &members[choice - 1];
}

void CombatSystem::UseItemMenu(Inventory& inventory, Unit* target)
{
    std::cout << "\nChoose item to use:\n";
    std::cout << static_cast<int>(Items::HP_POTION) << ". Heal (HP_POTION)\n"
        << static_cast<int>(Items::NORMAL_ATTACK_POTION) << ". Power Boost (NORMAL_ATTACK_POTION)\n"
        << static_cast<int>(Items::SMOKE_BOMB) << ". Smoke Bomb (SMOKE_BOMB)\n"
        << "Choice: ";

    int itemChoiceInt;
    std::cin >> itemChoiceInt;
    Items itemChoice = static_cast<Items>(itemChoiceInt);
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    switch (itemChoice)
    {
    case Items::HP_POTION:
        if (inventory.IsInInventory(Items::HP_POTION))
        {
            target->Heal(25);
            inventory.UseItem(Items::HP_POTION);
            std::cout << "Healed 25 HP. Current HP: " << target->GetHp() << "\n";
        }
        else
            std::cout << "No health potions left!\n";
        break;

    case Items::NORMAL_ATTACK_POTION:
        if (inventory.IsInInventory(Items::NORMAL_ATTACK_POTION))
        {
            target->IncreaseNormalDmg(5);
            inventory.UseItem(Items::NORMAL_ATTACK_POTION);
            std::cout << "Increased normal damage by 5.\n";
        }
        else
            std::cout << "No power potions left!\n";
        break;

    case Items::ELEMENTAL_ATTACK_POTION:
        if (inventory.IsInInventory(Items::ELEMENTAL_ATTACK_POTION))
        {
            target->IncreaseElementalDmg(5);
            inventory.UseItem(Items::ELEMENTAL_ATTACK_POTION);
            std::cout << "Increased elemental damage by 5.\n";
        }
        else
            std::cout << "No power potions left!\n";
        break;

    case Items::SMOKE_BOMB:
        if (inventory.IsInInventory(Items::SMOKE_BOMB))
        {
            inventory.UseItem(Items::SMOKE_BOMB);
            std::cout << "You escaped using a smoke bomb!\n";
            std::exit(0);
        }
        else
            std::cout << "No smoke bombs left!\n";
        break;

    default:
        std::cout << "Invalid item choice.\n";
        break;
    }
}
