/**
 * ============================================================
 * FICHIER : Game.hpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Déclaration de la classe Game — orchestrateur principal du jeu.
 *
 * Responsabilités :
 *   - Gérer la fenêtre SFML (800×600)
 *   - Contenir et coordonner toutes les entités (Player, Enemy, Bullet, Block)
 *   - Exécuter la boucle principale run() : events → update → render
 *   - Gérer les sons (tir, explosion, destruction de bloc) et la musique de fond
 *   - Calculer et afficher le score
 *   - Spawner les ennemis et les blocs descendants
 *   - Détecter et traiter toutes les collisions
 *
 * Attributs privés principaux :
 *   - window          : fenêtre de rendu SFML
 *   - player          : vaisseau du joueur
 *   - enemies         : vecteur d'ennemis actifs
 *   - bullets         : vecteur de projectiles actifs
 *   - blocks          : vecteur de blocs actifs
 *   - score           : score courant
 *   - allBlocksDestroyed : flag indiquant si tous les blocs initiaux sont détruits
 *   - rowCounter      : compteur de rangées de blocs descendantes spawnées
 *
 * Dépendances :
 *   - SFML/Graphics.hpp, SFML/Audio.hpp
 *   - Player.hpp, Enemy.hpp, Bullet.hpp, Block.hpp
 * ============================================================
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Block.hpp"

/**
 * @class Game
 * @brief Orchestrateur principal du jeu Space Invaders.
 *
 * Contient toutes les entités du jeu, gère la boucle principale SFML,
 * les événements, la physique, les collisions et le rendu.
 */
class Game {
private:
    sf::RenderWindow window;         ///< Fenêtre de rendu SFML (800×600)
    sf::Texture backgroundTexture;   ///< Texture de l'arrière-plan
    sf::Sprite background;           ///< Sprite de l'arrière-plan

    sf::SoundBuffer shootBuffer;        ///< Buffer son : tir joueur
    sf::SoundBuffer explosionBuffer;    ///< Buffer son : explosion ennemi
    sf::SoundBuffer blockDestroyBuffer; ///< Buffer son : destruction bloc
    sf::Sound shootSound;               ///< Son joué lors d'un tir
    sf::Sound explosionSound;           ///< Son joué lors d'une explosion
    sf::Sound blockDestroySound;        ///< Son joué lors de la destruction d'un bloc
    sf::Music backgroundMusic;          ///< Musique de fond en boucle

    Player player;                  ///< Vaisseau contrôlé par le joueur
    std::vector<Enemy> enemies;     ///< Liste des ennemis actifs
    std::vector<Bullet> bullets;    ///< Liste des projectiles actifs (joueur + ennemis)
    std::vector<Block> blocks;      ///< Liste des blocs actifs (obstacles descendants)

    int score;                      ///< Score courant du joueur
    bool allBlocksDestroyed;        ///< True quand tous les blocs initiaux sont détruits
    float lastBlockY;               ///< Position Y du dernier bloc spawné
    int rowCounter;                 ///< Compteur de rangées de blocs descendantes

    /** @brief Traite les événements SFML (fermeture, tir Espace). */
    void processEvents();

    /** @brief Met à jour toutes les entités et gère la logique de jeu. */
    void update();

    /** @brief Dessine tous les éléments dans la fenêtre. */
    void render();

    /** @brief Spawne 6 ennemis en ligne en haut de l'écran. */
    void spawnEnemies();

    /** @brief Spawne les blocs initiaux (6 en ligne). */
    void spawnInitialBlocks();

    /** @brief Spawne aléatoirement des blocs descendants. */
    void spawnDescendingBlocks();

    /** @brief Vérifie et résout toutes les collisions entre entités. */
    void handleCollisions();

    /** @brief Ajoute des points au score et l'affiche dans la console. */
    void updateScore(int points);

    /** @brief Chaque ennemi a une probabilité de tirer un projectile. */
    void enemyShoot();

    /** @brief Supprime les blocs sortis de l'écran (y > 600). */
    void removeOffscreenBlocks();

    /** @brief Supprime les ennemis sortis de l'écran (y > 600). */
    void removeOffscreenEnemies();

public:
    /**
     * @brief Constructeur : initialise la fenêtre, les assets, les sons et les entités.
     *
     * Charge les textures et sons depuis assets/, lance la musique de fond,
     * spawne les ennemis et les blocs initiaux.
     */
    Game();

    /**
     * @brief Lance la boucle principale du jeu jusqu'à fermeture de la fenêtre.
     */
    void run();
};

#endif
