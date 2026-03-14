/**
 * ============================================================
 * FICHIER : Game.cpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Game — orchestrateur principal du jeu.
 *
 * Gère l'ensemble du cycle de vie du jeu :
 *   - Initialisation des assets (textures, sons, musique de fond)
 *   - Boucle principale SFML : processEvents → update → render
 *   - Spawn des ennemis (6 en ligne) et des blocs (initiaux + descendants)
 *   - Tirs ennemis aléatoires
 *   - Détection et résolution de toutes les collisions :
 *       * Balle → Bloc    : détruit le bloc, +10 pts, son blockDestroy
 *       * Balle → Ennemi  : détruit l'ennemi, son explosion
 *       * Balle → Joueur  : game over (fenêtre fermée)
 *       * Bloc  → Joueur  : game over (fenêtre fermée)
 *   - Purge des entités hors écran (blocs y>600, ennemis y>600)
 *
 * Fenêtre : 800×600 px. Musique de fond : canary.ogg (volume 15%).
 *
 * Dépendances :
 *   - Game.hpp, Player.hpp, Enemy.hpp, Bullet.hpp, Block.hpp
 *   - SFML/Graphics.hpp, SFML/Audio.hpp
 *   - <algorithm> (std::all_of, std::remove_if)
 * ============================================================
 */

#include "../include/Game.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * @brief Constructeur : initialise la fenêtre, les assets audio/visuels et les entités.
 *
 * Séquence d'initialisation :
 *   1. Ouvre la fenêtre SFML 800×600.
 *   2. Charge l'image de fond (background.png).
 *   3. Charge les sons (shoot.ogg, explosion.ogg, sfx_lose.ogg).
 *   4. Lance la musique de fond en boucle (canary.ogg, volume 15%).
 *   5. Initialise le score à 0 et allBlocksDestroyed à false.
 *   6. Spawne 6 ennemis en ligne et 6 blocs initiaux.
 */
Game::Game() : window(sf::VideoMode(800, 600), "Space Invaders"), rowCounter(0) {
    // Chargement de l'arrière-plan
    if (!backgroundTexture.loadFromFile("assets/images/background.png")) {
        cerr << "Erreur chargement background.png\n";
    }
    background.setTexture(backgroundTexture);

    // Chargement des sons
    if (!shootBuffer.loadFromFile("assets/sounds/shoot.ogg") ||
        !explosionBuffer.loadFromFile("assets/sounds/explosion.ogg") ||
        !blockDestroyBuffer.loadFromFile("assets/sounds/sfx_lose.ogg")) {
        cerr << "Erreur chargement des sons\n";
    }

    shootSound.setBuffer(shootBuffer);
    explosionSound.setBuffer(explosionBuffer);
    blockDestroySound.setBuffer(blockDestroyBuffer);

    // Chargement et lancement de la musique de fond
    if (!backgroundMusic.openFromFile("assets/sounds/canary.ogg")) {
        cerr << "Erreur chargement musique de fond\n";
    } else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(15);  // Volume discret (15%)
        backgroundMusic.play();
    }

    // Initialisation du score et des flags
    score = 0;
    allBlocksDestroyed = false;

    // Spawn initial des entités
    spawnEnemies();
    spawnInitialBlocks();
    lastBlockY = 500;
}

/**
 * @brief Lance la boucle principale du jeu jusqu'à fermeture de la fenêtre.
 *
 * Exécute en boucle : processEvents() → update() → render()
 * tant que la fenêtre est ouverte.
 */
void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

/**
 * @brief Traite les événements SFML de la file d'attente.
 *
 * Événements gérés :
 *   - sf::Event::Closed : ferme la fenêtre (fin du jeu)
 *   - sf::Keyboard::Space (maintenu) : tire un projectile depuis le joueur
 *     et joue shootSound si le son n'est pas déjà en cours.
 */
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    // Tir du joueur : touche Espace maintenue
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        bullets.push_back(player.shoot());
        if (shootSound.getStatus() != sf::Sound::Playing) {
            shootSound.play();
        }
    }
}

/**
 * @brief Met à jour toutes les entités du jeu et gère la logique globale.
 *
 * Séquence d'update :
 *   1. Mettre à jour le joueur (mouvement clavier).
 *   2. Mettre à jour chaque ennemi (descente).
 *   3. Mettre à jour chaque projectile (montée).
 *   4. Mettre à jour chaque bloc (descente si non détruit).
 *   5. Purger les blocs et ennemis hors écran.
 *   6. Détecter et résoudre les collisions.
 *   7. Vérifier si tous les blocs sont détruits (allBlocksDestroyed).
 *   8. Si oui : spawner un nouveau bloc descendant aléatoire.
 *   9. Tirs ennemis aléatoires.
 */
void Game::update() {
    player.update();

    for (auto &enemy : enemies)
        enemy.update();

    for (auto &bullet : bullets)
        bullet.update();

    for (auto &block : blocks)
        block.update();

    // Purge des entités hors écran
    removeOffscreenBlocks();
    removeOffscreenEnemies();

    // Gestion des collisions
    handleCollisions();

    // Vérification si tous les blocs initiaux sont détruits
    if (!allBlocksDestroyed) {
        allBlocksDestroyed = all_of(blocks.begin(), blocks.end(),
            [](const Block &b) { return b.isDestroyed(); });
    }

    // Spawn de blocs descendants si tous les blocs initiaux sont détruits
    if (allBlocksDestroyed) {
        spawnDescendingBlocks();
    }

    // Tirs ennemis aléatoires
    enemyShoot();
}

/**
 * @brief Dessine tous les éléments visuels dans la fenêtre SFML.
 *
 * Ordre de rendu :
 *   1. Effacer la fenêtre.
 *   2. Dessiner l'arrière-plan.
 *   3. Dessiner le joueur.
 *   4. Dessiner les ennemis, projectiles et blocs.
 *   5. Afficher le framebuffer (display).
 */
void Game::render() {
    window.clear();
    window.draw(background);
    player.draw(window);

    for (const auto &enemy : enemies)
        enemy.draw(window);

    for (const auto &bullet : bullets)
        bullet.draw(window);

    for (const auto &block : blocks)
        block.draw(window);

    window.display();
}

/**
 * @brief Spawne 6 ennemis en ligne horizontale en haut de l'écran.
 *
 * Position : y=50, x espacé de 120 px à partir de x=50.
 * Les ennemis sont ajoutés au vecteur enemies par emplace_back.
 */
void Game::spawnEnemies() {
    for (int i = 0; i < 6; i++) {
        float x = 50 + i * 120;  // 6 ennemis espacés de 120 px
        enemies.emplace_back(x, 50);
    }
}

/**
 * @brief Spawne 6 blocs initiaux en ligne horizontale.
 *
 * Position : y=100, x espacé de 120 px à partir de x=50.
 * Ces blocs sont présents dès le début de la partie.
 */
void Game::spawnInitialBlocks() {
    for (int i = 0; i < 6; i++) {
        float x = 50 + i * 120;
        blocks.emplace_back(x, 100);
    }
}

/**
 * @brief Spawne aléatoirement un bloc descendant depuis le haut de l'écran.
 *
 * Probabilité : 1/50 à chaque appel (rand() % 50 == 0).
 * Position X aléatoire entre 50 et 750. Position Y initiale : -50 (hors écran).
 * Appelé à chaque frame une fois allBlocksDestroyed == true.
 */
void Game::spawnDescendingBlocks() {
    if (rand() % 50 == 0) {
        float x = rand() % 700 + 50;
        blocks.emplace_back(x, -50);  // Spawn au-dessus de l'écran
    }
}

/**
 * @brief Chaque ennemi a une probabilité de tirer un projectile à chaque frame.
 *
 * Probabilité : 3/200 par ennemi par frame (rand() % 200 < 3).
 * Le projectile est créé à (x+10, y+20) — en bas du sprite ennemi.
 */
void Game::enemyShoot() {
    for (auto &enemy : enemies) {
        if (rand() % 200 < 3) {  // ~1.5% de probabilité par frame
            bullets.emplace_back(enemy.getPosition().x + 10, enemy.getPosition().y + 20);
        }
    }
}

/**
 * @brief Vérifie et résout toutes les collisions entre entités.
 *
 * Collisions vérifiées :
 *   1. Balle → Bloc    : détruit les deux, joue blockDestroySound, +10 pts.
 *   2. Balle → Ennemi  : détruit les deux, joue explosionSound.
 *   3. Balle → Joueur  : game over immédiat (window.close()).
 *   4. Bloc  → Joueur  : game over immédiat (window.close()) si bloc non détruit.
 *
 * Note : utilise sf::FloatRect::intersects() pour la détection AABB.
 */
void Game::handleCollisions() {
    for (auto &bullet : bullets) {
        // Collision balle → bloc
        for (auto &block : blocks) {
            if (!block.isDestroyed() && bullet.getBounds().intersects(block.getBounds())) {
                block.destroy();
                bullet.destroy();
                if (blockDestroySound.getStatus() != sf::Sound::Playing) {
                    blockDestroySound.play();
                }
                updateScore(10);  // +10 points par bloc détruit
            }
        }

        // Collision balle → ennemi
        for (const auto &enemy : enemies) {
            if (bullet.getBounds().intersects(enemy.getBounds())) {
                enemy.destroy();
                bullet.destroy();
                if (explosionSound.getStatus() != sf::Sound::Playing) {
                    explosionSound.play();
                }
            }
        }

        // Collision balle → joueur (game over)
        if (player.getBounds().intersects(bullet.getBounds())) {
            cout << "GAME OVER - Touché par un tir ennemi !" << endl;
            window.close();
        }
    }

    // Collision bloc → joueur (game over)
    for (const auto &block : blocks) {
        if (!block.isDestroyed() && player.getBounds().intersects(block.getBounds())) {
            cout << "GAME OVER - Collision avec un bloc !" << endl;
            window.close();
        }
    }
}

/**
 * @brief Ajoute des points au score et affiche le total dans la console.
 * @param points Nombre de points à ajouter
 */
void Game::updateScore(int points) {
    score += points;
    cout << "Score: " << score << endl;
}

/**
 * @brief Supprime du vecteur les blocs dont la position Y dépasse 600 px.
 *
 * Utilise std::remove_if + erase (idiome erase-remove).
 * Appelé à chaque frame dans update().
 */
void Game::removeOffscreenBlocks() {
    blocks.erase(remove_if(blocks.begin(), blocks.end(),
        [](const Block &b) { return b.getY() > 600; }), blocks.end());
}

/**
 * @brief Supprime du vecteur les ennemis dont la position Y dépasse 600 px.
 *
 * Utilise std::remove_if + erase (idiome erase-remove).
 * Appelé à chaque frame dans update().
 */
void Game::removeOffscreenEnemies() {
    enemies.erase(remove_if(enemies.begin(), enemies.end(),
        [](const Enemy &e) { return e.getPosition().y > 600; }), enemies.end());
}
