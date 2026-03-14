/**
 * ============================================================
 * FICHIER : Enemy.hpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Déclaration de la classe Enemy — ennemi descendant vers le joueur.
 *
 * Les ennemis sont spawnés en ligne de 6 en haut de l'écran (y=50)
 * et descendent automatiquement à 0.2 px par frame. Ils peuvent tirer
 * des projectiles aléatoirement. Lorsqu'ils sont détruits, leur sprite
 * est déplacé hors écran (-100, -100).
 *
 * Attributs privés :
 *   - texture : texture chargée depuis assets/images/enemy.png
 *   - sprite  : sprite affiché à l'écran
 *
 * Méthodes publiques :
 *   - update()     : descend le sprite de 0.2f px vers le bas
 *   - draw()       : dessine le sprite dans la fenêtre
 *   - destroy()    : déplace le sprite hors écran (simule la destruction)
 *   - getBounds()  : retourne la hitbox pour la détection de collision
 *   - getPosition(): retourne la position courante du sprite
 *
 * Dépendances :
 *   - SFML/Graphics.hpp
 * ============================================================
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

/**
 * @class Enemy
 * @brief Ennemi spatial qui descend vers le bas de l'écran.
 *
 * Se déplace verticalement à vitesse constante (0.2f px/frame).
 * La destruction est simulée en déplaçant le sprite hors de l'écran.
 */
class Enemy {
private:
    sf::Texture texture;  ///< Texture du sprite ennemi
    sf::Sprite sprite;    ///< Sprite affiché à l'écran

public:
    /**
     * @brief Constructeur : charge la texture et positionne l'ennemi.
     * @param x Position horizontale initiale (px)
     * @param y Position verticale initiale (px)
     */
    Enemy(float x, float y);

    /**
     * @brief Déplace l'ennemi de 0.2f px vers le bas à chaque frame.
     */
    void update();

    /**
     * @brief Dessine le sprite de l'ennemi dans la fenêtre SFML.
     * @param window Référence constante à la fenêtre de rendu
     */
    void draw(sf::RenderWindow &window) const;

    /**
     * @brief Simule la destruction en déplaçant le sprite à (-100, -100).
     *
     * Utilise const_cast pour modifier le sprite depuis une méthode const.
     * L'ennemi reste dans le vecteur mais est invisible et hors hitbox.
     */
    void destroy() const;

    /**
     * @brief Retourne la hitbox globale du sprite pour les collisions.
     * @return sf::FloatRect rectangle englobant le sprite
     */
    sf::FloatRect getBounds() const;

    /**
     * @brief Retourne la position courante du sprite.
     * @return sf::Vector2f position (x, y) en pixels
     */
    sf::Vector2f getPosition() const;
};

#endif
