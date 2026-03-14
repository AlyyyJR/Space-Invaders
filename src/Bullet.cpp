/**
 * ============================================================
 * FICHIER : Bullet.cpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Bullet — projectile tiré par le joueur ou les ennemis.
 *
 * Le projectile est un RectangleShape SFML de 5×10 px, rouge, qui monte
 * verticalement à 5.0f px/frame. La destruction est simulée en déplaçant
 * le shape à (-100, -100), le rendant inactif sans suppression immédiate du vecteur.
 *
 * Utilisé pour :
 *   - Les tirs du joueur (Espace) : créés par Player::shoot()
 *   - Les tirs ennemis : créés par Game::enemyShoot()
 *
 * Dépendances :
 *   - Bullet.hpp, SFML/Graphics.hpp
 * ============================================================
 */

#include "../include/Bullet.hpp"

using namespace std;

/**
 * @brief Constructeur : initialise le projectile à la position donnée.
 *
 * @param x Position horizontale initiale (px)
 * @param y Position verticale initiale (px)
 *
 * Crée un rectangle rouge de 5×10 px avec une vitesse de 5.0f px/frame.
 */
Bullet::Bullet(float x, float y) : speed(5.0f) {
    shape.setSize(sf::Vector2f(5, 10));     // Dimensions : 5px large, 10px haut
    shape.setFillColor(sf::Color::Red);     // Couleur rouge
    shape.setPosition(x, y);               // Position initiale
}

/**
 * @brief Déplace le projectile de -speed px vers le haut à chaque frame.
 *
 * Le projectile monte à vitesse constante (5.0f px/frame).
 * Les projectiles hors écran sont supprimés par la logique de collision de Game.
 */
void Bullet::update() {
    shape.move(0, -speed);  // Mouvement vers le haut
}

/**
 * @brief Dessine le projectile dans la fenêtre SFML.
 * @param window Référence constante à la fenêtre de rendu
 */
void Bullet::draw(sf::RenderWindow &window) const {
    window.draw(shape);
}

/**
 * @brief Simule la destruction en déplaçant le shape hors de l'écran.
 *
 * Déplace le shape à (-100, -100) pour sortir de toutes les hitboxes actives.
 * Le Bullet reste dans le vecteur mais n'est plus visible ni en collision.
 */
void Bullet::destroy() {
    shape.setPosition(-100, -100);
}

/**
 * @brief Retourne la hitbox globale du shape pour les collisions.
 * @return sf::FloatRect rectangle englobant le projectile dans l'espace monde
 */
sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}
