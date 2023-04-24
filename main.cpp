#include "Util.h"
#include "Dice.h"
#include "Entity.h"

class Game{
public:
    Game(){
        player.setName("player");
        enemy.randomizeName();

        Util::clearScreen();
        Util::alert("Welcome to hak21");

        getPlayerName();
        playMatch();
    }
private:
    void getPlayerName(){
        player.name = Util::readLine("What is your name? ");
        Util::clearScreen();
    }
    void roll(Entity * entity){
        if(entity->holding == true){
            Util::echo(entity->name + " is holding at: "+std::to_string(entity->sum));
            return;
        }
        Util::echo(entity->name + " is rolling...");
        int res = dice.roll();
        entity->sum += res;
        Util::echo("+" + std::to_string(res)); 
        Util::echo("-------");
        Util::echo(entityRatioString(entity));
        Util::echo(" ");
    }
    void combatStatus(){
        entityStatus(&player);
        Util::echo("");
        entityStatus(&enemy);
    }
    void entityStatus(Entity * entity){
        Util::echo(entity->name + ":");
        Util::echo("--EP:      "+std::to_string(entity->ep));
        Util::echo("--Sum:     "+entityRatioString(entity));
        Util::echo("--Holding: "+(std::string)(entity->holding ? "yes" : "no"));
    }
    std::string entityRatioString(Entity * entity){
        return std::to_string(entity->sum) + "/" + std::to_string(entity->burst);
    }
    std::string readCmd(){
        if(player.holding == false){
            Util::echo("r - roll again");
            Util::echo("h - hold");
        }
        else{
            Util::echo("r - continue");
            Util::echo("h - continue");
        }
        Util::echo("x - hax");
        Util::echo("s - status");
        std::string cmd = Util::readLine();
        Util::clearScreen();
        return cmd;
    }
    void playMatch(){
        player.initMatch();
        enemy.initMatch();
        while(true){
            if(player.sum >= player.burst){break;}
            if(enemy.sum >= enemy.burst){break;}
            if(player.holding && enemy.holding){break;}

            if(player.sum < 1){
                roll(&player);
                roll(&enemy);
            }
            std::string input = readCmd();
            if(input == "r"){
                roll(&player);
                // Enemy will roll again
                // if less than player
                if(enemy.sum <= player.sum){
                    roll(&enemy);
                }
                else{
                    Util::echo("Enemy holds");
                    enemy.holding = true;
                }
            }
            else if(input == "x"){
                // Hax
                Util::echo("1 - add 1 for you");
                Util::echo("2 - minus 1 for enemy");
                Util::echo("0 - go back");
                std::string hinput = Util::readLine();
                if(hinput == "1"){
                    Util::echo("added 1");
                }
                else if(hinput == "2"){
                    Util::echo("minused 1");
                }
                else if(hinput == "0"){
                    Util::echo("going back");
                    continue;
                }
            }
            else if(input == "h"){
                player.holding = true;
                // Roll again for UI reasons
                roll(&player);
                roll(&enemy);
                //break;
            }
            else if(input == "s"){
                combatStatus();
            }
            else{
                Util::echo("Unknown CMD: "+input);
            }
        }
        Util::alert("Round End");
        Util::readLine("Any key to continue...");
        Util::clearScreen();
        Util::echo("Final Score");
        Util::echo("You: "+entityRatioString(&player));
        Util::echo(enemy.name+": "+entityRatioString(&enemy));
        if(player.sum > player.burst){
            Util::alert("YOU BURST!");
            player.sum = 0;
        }
        else if(enemy.sum > enemy.burst){
            Util::alert("ENEMY BURSTS!"); 
            enemy.sum = 0;
        }
        else if(player.sum == enemy.sum){
            Util::alert("DRAW!");
        }
        if(player.sum > enemy.sum){
            Util::alert("YOU ATTACK!");
            int dmg = enemy.defend(player.sum);
            Util::alert("You do "+std::to_string(dmg)+" damage!");
        }
        else{
            Util::alert("YOU DEFEND!");
            int dmg = player.defend(enemy.sum);
            Util::alert("You take "+std::to_string(dmg)+" damage!");
        }
        combatStatus();
        Util::readLine("Any key to continue...");
        Util::clearScreen();
        playMatch();
    }
    Dice dice;
    Entity player;
    Entity enemy;
};

int main(){
    Game game;
    return 0;
}