/**
 * ============================================================
 * FICHIER : Enemy.cpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Implémentation de la classe Enemy — ennemi descendant vers le joueur.
 *
 * Les ennemis spawnent en ligne de 6 en haut de l'écran (y=50, espacés de 120 px).
 * Ils descendent à 0.2f px/frame. Lorsqu'un ennemi est touché par un projectile,
 * destroy() déplace son sprite à (-100, -100) pour le rendre inactif sans le
 * supprimer immédiatement du vecteur.
 *
 * Note : destroy() utilise const_cast car la méthode est déclarée const
 * mais doit modifier le sprite. Ce pattern est un compromis de conception.
 *
 * Dépendances :
 *   - Enemy.hpp, SFML/Graphics.hpp
 * ============================================================
 */

#include "../include/Enemy.hpp"

/**
 * @brief Constructeur : charge la texture et positionne l'ennemi.
 *
 * @param x Position horizontale initiale (px)
 * @param y Position verticale initiale (px), généralement 50
 */
Enemy::Enemy(float x, float y) {
    texture.loadFromFile("assets/images/enemy.png");
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

/**
 * @brief Descend le sprite de 0.2f px vers le bas à chaque frame.
 *
 * Les ennemis descendent continuellement sans s'arrêter.
 * Ils sont supprimés du vecteur par removeOffscreenEnemies() quand y > 600.
 */
void Enemy::update() {
    sprite.move(0, 0.2f);  // Descente continue à vitesse constante
}

/**
 * @brief Dessine le sprite de l'ennemi dans la fenêtre SFML.
 * @param window Référence constante à la fenêtre de rendu
 */
void Enemy::draw(sf::RenderWindow &window) const {
    window.draw(sprite);
}

/**
 * @brief Simule la destruction de l'ennemi en déplaçant son sprite hors écran.
 *
 * Déplace le sprite à (-100, -100) pour l'extraire des hitboxes actives.
 * Utilise const_cast car la méthode est const mais modifie le sprite.
 * L'ennemi sera ensuite supprimé par removeOffscreenEnemies().
 */
void Enemy::destroy() const {
    const_cast<Enemy*>(this)->sprite.setPosition(-100, -100);
}

/**
 * @brief Retourne la hitbox globale du sprite pour les collisions.
 * @return sf::FloatRect rectangle englobant le sprite dans l'espace monde
 */
sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}

/**
 * @brief Retourne la position courante du sprite.
 * @return sf::Vector2f position (x, y) en pixels
 */
sf::Vector2f Enemy::getPosition() const {
    return sprite.getPosition();
}
