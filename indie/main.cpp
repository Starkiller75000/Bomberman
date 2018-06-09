#include "inc/game.hpp"
#include <unistd.h>
#include "inc/player.hpp"
#include "inc/irrlicht.hpp"

irrlicht *motor;

int main()
{
        motor = new irrlicht(irr::video::EDT_OPENGL); // linux ? windows
        game oui(13, 11, 1080, 1920);
        std::pair<int, int> tmp;
        moveDir KeyOne = NOP;
        moveDir KeyTwo = NOP;
        moveDir KeyThree = NOP;
        moveDir KeyFour = NOP;
        int winner;

        oui.spawn(4); // prendre du menu
        while (motor->isOk()) {
                winner = oui.checkWin();
                std::cout << oui.getPlayersAlive(0) << oui.getPlayersAlive(1) << oui.getPlayersAlive(2) << oui.getPlayersAlive(3) << std::endl;
                if (winner != 0) {
                        printf("The winner is %d !!!\n", winner);
                        break;
                }
                oui.checkAllBomb();
                motor->loop(&oui);
                // touche joueur 1
                if (oui.getPlayersAlive(0)) {
                        KeyOne = motor->nextKeyOne();
                        if (KeyOne != NOP) {
                                auto p = oui.getBoard();
                                for (auto ob = p.begin(); ob != p.end(); ++ob) {
                                        tmp = ob->second->getPosition();
                                        if (ob->second->getStatus() == PLAYER && ob->second->getId() == 1)
                                                ob->second->movePlayer(KeyOne, &oui);
                                }
                                KeyOne = NOP;
                        }
                }
                // touche joueur 2
                if (oui.getPlayersAlive(1)) {
                        KeyTwo = motor->nextKeyTwo();
                        if (KeyTwo != NOP) {
                                auto p = oui.getBoard();
                                for (auto ob = p.begin(); ob != p.end(); ++ob) {
                                        tmp = ob->second->getPosition();
                                        if (ob->second->getStatus() == PLAYER && ob->second->getId() == 2)
                                                ob->second->movePlayer(KeyTwo, &oui);
                                }
                                KeyTwo = NOP;
                        }
                }
                // touche joueur 3
                if (oui.getPlayersAlive(2)) {
                        KeyThree = motor->nextKeyThree();
                        if (KeyThree != NOP) {
                                auto p = oui.getBoard();
                                for (auto ob = p.begin(); ob != p.end(); ++ob) {
                                        tmp = ob->second->getPosition();
                                        if (ob->second->getStatus() == PLAYER && ob->second->getId() == 3)
                                                ob->second->movePlayer(KeyThree, &oui);
                                }
                                KeyThree = NOP;
                        }
                }
                // touche joueur 4
                if (oui.getPlayersAlive(3)) {
                        KeyFour = motor->nextKeyFour();
                        if (KeyFour != NOP) {
                                auto p = oui.getBoard();
                                for (auto ob = p.begin(); ob != p.end(); ++ob) {
                                        tmp = ob->second->getPosition();
                                        if (ob->second->getStatus() == PLAYER && ob->second->getId() == 4)
                                                ob->second->movePlayer(KeyFour, &oui);
                                }
                                KeyFour = NOP;
                        }
                }

        }
        return 0;
}
