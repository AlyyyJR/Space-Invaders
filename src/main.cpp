/**
 * ============================================================
 * FICHIER : main.cpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Point d'entrée du programme.
 *
 * Instancie la classe Game et appelle game.run() pour démarrer
 * la boucle principale SFML.
 *
 * Compilation (avec Makefile) :
 *   make
 *
 * Compilation manuelle :
 *   g++ src/*.cpp -Iinclude -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -o space_invaders
 *
 * Lancement :
 *   ./space_invaders
 * ============================================================
 */

#include "../include/Game.hpp"

using namespace std;

/**
 * @brief Fonction principale : instancie et lance le jeu Space Invaders.
 * @return 0 à la fermeture normale de la fenêtre
 */
int main() {
    Game game;
    game.run();
    return 0;
}
