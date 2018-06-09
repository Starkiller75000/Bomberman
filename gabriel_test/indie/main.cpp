#include "inc/game.hpp"
#include <unistd.h>
#include "inc/player.hpp"
#include "inc/irrlicht.hpp"

irrlicht *motor;

int main()
{
        motor = new irrlicht(irr::video::EDT_OPENGL); // linux ? windows
        game oui(13, 11);
	oui.spawn(1);
        std::pair<int, int> tmp;
        moveDir KeyOne = NOP;

        while (motor->isOk()) {
                motor->loop(&oui);
                oui.checkAllBomb();
                // touche joueur 1
                if (oui.getNbPlayer() >= 1) {
                        KeyOne = motor->nextKeyOne();
                        if (KeyOne != NOP) {
                                auto p = oui.getBoard();
                                for (auto ob = p.begin(); ob != p.end(); ++ob) {
                                        tmp = ob->second->getPosition();
                                        if (ob->second->getStatus() == PLAYER )
                                                ob->second->movePlayer(KeyOne,
                                                        &oui);
                                }
                                KeyOne = NOP;
                        }
                }
        }
        return 0;
}
