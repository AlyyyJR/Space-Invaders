/**
 * ============================================================
 * FICHIER : Player.cpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Player — vaisseau contrôlé par le joueur.
 *
 * Le joueur se déplace horizontalement avec les flèches ←/→.
 * Il est limité entre x=0 (bord gauche) et x=750 (bord droit).
 * La fonction shoot() génère un projectile centré sur le vaisseau.
 *
 * Dépendances :
 *   - Player.hpp, Bullet.hpp, SFML/Graphics.hpp
 * ============================================================
 */

#include "../include/Player.hpp"

using namespace std;

/**
 * @brief Constructeur : charge la texture depuis assets/ et positionne le vaisseau.
 *
 * Position initiale : (400, 500) — centré en bas de l'écran 800×600.
 * Vitesse de déplacement : 2.0f px/frame.
 */
Player::Player() : speed(2.0f) {
    texture.loadFromFile("assets/images/player.png");
    sprite.setTexture(texture);
    sprite.setPosition(400, 500);  // Position initiale : centre-bas de l'écran
}

/**
 * @brief Lit les touches clavier et déplace le vaisseau horizontalement.
 *
 * - Flèche gauche : décale de -speed px si x > 0 (évite de sortir à gauche)
 * - Flèche droite : décale de +speed px si x < 750 (évite de sortir à droite)
 */
void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sprite.getPosition().x > 0)
        sprite.move(-speed, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sprite.getPosition().x < 750)
        sprite.move(speed, 0);
}

/**
 * @brief Dessine le sprite du joueur dans la fenêtre SFML.
 * @param window Référence à la fenêtre de rendu
 */
void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

/**
 * @brief Crée et retourne un projectile tiré depuis la position du vaisseau.
 *
 * Le projectile est créé à (x+22, y-10) pour partir du centre-haut du sprite.
 * @return Bullet initialisé à la position de tir
 */
Bullet Player::shoot() {
    return Bullet(sprite.getPosition().x + 22, sprite.getPosition().y - 10);
}

/**
 * @brief Retourne la position courante du sprite.
 * @return sf::Vector2f position (x, y) en pixels
 */
sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

/**
 * @brief Retourne la hitbox globale du sprite pour la détection de collision.
 * @return sf::FloatRect rectangle englobant le sprite dans l'espace monde
 */
sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}
