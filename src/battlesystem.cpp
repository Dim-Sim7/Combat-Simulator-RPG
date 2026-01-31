#include "battlesystem.h"

#include <iostream>


BattleSystem::BattleSystem()
    : gcdEndTime(0.f), running(false)
{
    startTime = std::chrono::steady_clock::now();
}

BattleSystem::~BattleSystem()
{
    running = false;
    if (inputThread.joinable())
        inputThread.join();
}

void BattleSystem::battleLoop(Player& player, NPC& enemy)
{
    running = true;

    inputThread = std::thread([&]() {
        inputLoop(player);
    });

    enemyAI = std::make_unique<NPC_AI>(&enemy, &player);

    while (running)
    {
        float now = getTime();

        if (player.cast.isCasting && now >= player.cast.castEnd)
            handleSpellCast(&player, now);

        if (enemy.cast.isCasting && now >= enemy.cast.castEnd)
            handleSpellCast(&enemy, now);

        if (!enemy.cast.isCasting && enemyAI)
            enemyAI->update(now);

        if (enemy.hasFledCombat()) {
            std::cout << enemy.getEntityName() << " fled from combat!\n";
            break;
        }

        Command cmd;
        while (popCommand(cmd)) {
            if (!player.cast.isCasting)
                handleCommand(player, enemy, cmd, now);
        }

        if (enemy.isDead()) {
            player.gainExp(enemy.expOnDeath());
            enemy.onDeath();
            break;
        }

        if (player.isDead()) {
            player.onDeath();
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    running = false;
    if (inputThread.joinable())
        inputThread.join();

    enemyAI.reset();
}

float BattleSystem::getTime()
{
    return std::chrono::duration<float>(
        std::chrono::steady_clock::now() - startTime
    ).count();
}


void BattleSystem::pushCommand(PlayerCommand command, float currentTime, const std::string& data)
{
    std::lock_guard<std::mutex> lock(commandMutex);
    commandQueue.push({command, data, currentTime});
}

bool BattleSystem::popCommand(Command& out)
{
    std::lock_guard<std::mutex> lock(commandMutex);
    if (commandQueue.empty()) return false;
    out = commandQueue.front();
    commandQueue.pop();
    return true;
}

void BattleSystem::inputLoop(Player& player)
{
    while (running)
    {
        if (!std::cin.good()) {
            std::cin.clear();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        std::cout << "\n" << player.getEntityName()
                  << " HP: " << player.getCurrentHP()
                  << "/" << player.getMaxHP() << "\n";

        std::cout << "\n===== ACTIONS =====\n";
        std::cout << "[1] Melee Attack\n";

        const auto& spells = player.getAbilities();
        const auto& items =
            player.inventory->getItemsByType(ITEMTYPE::CONSUMABLE);

        int optionIndex = 2;

        for (const auto& sp : spells)
            std::cout << "[" << optionIndex++ << "] Spell: " << sp.getName() << "\n";

        for (const auto& it : items)
            std::cout << "[" << optionIndex++ << "] Item: " << it->getName() << "\n";

        std::cout << "> ";
        int choice;
        if (!(std::cin >> choice)) {
            running = false;
            break;
        }

        float now = getTime();

        if (choice == 1) {
            pushCommand(PlayerCommand::Attack, now);
            continue;
        }

        int spellStart = 2;
        int spellEnd = spellStart + spells.size() - 1;

        if (choice >= spellStart && choice <= spellEnd) {
            pushCommand(PlayerCommand::Spell, now, spells[choice - spellStart].getName());
            continue;
        }

        int itemStart = spellEnd + 1;
        int itemEnd = itemStart + items.size() - 1;

        if (choice >= itemStart && choice <= itemEnd) {
            pushCommand(PlayerCommand::Consumable, now, items[choice - itemStart]->getName());
            continue;
        }

        std::cout << "[INVALID INPUT]\n";
    }
}

void BattleSystem::handleCommand(Player& player, NPC& enemy, const Command& cmd, float now)
{
    switch (cmd.type)
    {
        case PlayerCommand::Attack:
            tryAttack(player, enemy, now);
            break;

        case PlayerCommand::Spell:
            tryCastSpell(player, enemy, cmd.data, now);
            break;

        case PlayerCommand::Consumable:
            tryUseConsumable(player, cmd.data, now);
            break;

        default:
            break;
    }
}

void BattleSystem::handleSpellCast(Entity* caster, float now)
{
    if (!caster->cast.isCasting || caster->cast.spell == nullptr)
        return;

    Abilities* spell = caster->cast.spell;
    Entity* target = caster->cast.target;

    // finish spell cast
    spell->use(now);

    //Damage spell
    if (spell->isOffensive())
    {
        int dmg = spell->rollDamage();
        if (caster->isCrit()) dmg *= 2;

        target->takeDamage(dmg);

        std::cout << caster->getEntityName() << " casts "
                    << spell->getName()
                    << " for " << dmg << " damage!\n";
    }
    else if (!(spell->isOffensive()))
    {
        int heal = spell->rollDamage();
        if (caster->isCrit()) heal *= 2;

        caster->heal(heal);

        std::cout << caster->getEntityName() << " casts "
                    << spell->getName()
                    << " that heals themselves for " << heal << "\n";            
    }
    else
    {
        std::cout << caster->getEntityName()
                << " finishes casting " << spell->getName() << ".\n";
    }

    
    //trigger gcd
    gcdEndTime = now + 1.5f;

    //Clear cast state
    caster->cast.isCasting = false;
    caster->cast.spell = nullptr;
    caster->cast.target = nullptr;
}

// ============================================================
// COMBAT EXECUTION
// ============================================================
float gcdEndTime; //global  timer

void BattleSystem::tryAttack(Player& player, NPC& enemy, float now)
{
    if (now < gcdEndTime)
    {
        std::cout << "[Fail] Attack on Global Cooldown. " << gcdEndTime - now << "s remaining.\n";
        return;
    }

    std::cout << "[Attack]\n";
    player.attack(enemy, now);
    gcdEndTime = now + 1.5f; //1.5s GCD
}

void BattleSystem::tryCastSpell(Player& player, NPC& enemy, const std::string& spellName, float now)
{
    //Check GCD
    if (now < gcdEndTime)
    {
        std::cout << "[Fail] On Global Cooldown. " << gcdEndTime - now << "s remaining.\n";
        return;        
    }

    auto& spells = player.getAbilities();
    for (auto& sp: spells)
    {
        if (sp.getName() == spellName)
        {
            std::cout << "[Cast] " << spellName << "\n";
            player.castSpell(&enemy, sp, now);
            return;
        }
    }

    std::cout << "[Fail] Spell not found.\n";
}

void BattleSystem::tryUseConsumable(Player& player, const std::string& name, float now)
{
        // Check GCD first
    if (now < gcdEndTime)
    {
        std::cout << "[Fail] On Global .\n";
        return;
    }
    auto const& items = player.inventory->getItemsByType(ITEMTYPE::CONSUMABLE);

    for (auto& it : items)
    {
        if (it->getName() == name)
        {
            std::cout << "[Use] " << name << "\n";

            applyConsumableEffect(&player, it->getStatModifier());
            player.inventory->removeItem(it);

            gcdEndTime = now + 1.5f;
            return;
        }
    }
}
void BattleSystem::applyConsumableEffect(Player* player, const StatModifier& statMod)
{
    // Health buff
    if (statMod.health.has_value()) {
        player->heal(statMod.health.value());
        std::cout << player->getEntityName() << " heals for " << statMod.health.value() << " HP!\n";
        std::cout << player->getEntityName() << " HP: [" << player->getCurrentHP() << "/" << player->getMaxHP() << "]\n";
    }

    // Armor buff
    if (statMod.armor.has_value()) {
        player->getStats().increaseArmor(statMod.armor.value());
        std::cout << player->getEntityName() << " gains " << statMod.armor.value() << " armor!\n";
    }

    // Crit buff
    if (statMod.crit.has_value()) {
        player->getStats().increaseCritChance(statMod.crit.value());
        std::cout << player->getEntityName() << " gains " << statMod.crit.value() << " crit chance!\n";
    }

    // Damage buff
    if (statMod.damage.has_value()) {
        player->getStats().increaseDamage(statMod.damage.value());
        std::cout << player->getEntityName() << " gains +" 
                << statMod.damage.value().first << "-" << statMod.damage.value().second 
                << " damage!\n";
    }
}

