/**
 * ============================================================
 * FICHIER : Player.hpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Déclaration de la classe Player — vaisseau contrôlé par le joueur.
 *
 * Le joueur se déplace horizontalement (←/→) à vitesse fixe et peut
 * tirer des projectiles vers le haut (Espace). Il est positionné en bas
 * de l'écran (x=400, y=500) au démarrage.
 *
 * Attributs privés :
 *   - texture : texture chargée depuis assets/images/player.png
 *   - sprite  : sprite affiché à l'écran
 *   - speed   : vitesse de déplacement horizontal (2.0f px/frame)
 *
 * Méthodes publiques :
 *   - update()     : déplace le sprite selon les touches ←/→ pressées
 *   - draw()       : dessine le sprite dans la fenêtre
 *   - shoot()      : crée et retourne un projectile positionné sur le vaisseau
 *   - getPosition(): retourne la position courante du sprite
 *   - getBounds()  : retourne la hitbox pour la détection de collision
 *
 * Dépendances :
 *   - SFML/Graphics.hpp, Bullet.hpp
 * ============================================================
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Bullet.hpp"

/**
 * @class Player
 * @brief Vaisseau spatial contrôlé par le joueur.
 *
 * Se déplace horizontalement entre 0 et 750 px.
 * Génère des projectiles (Bullet) depuis sa position courante.
 */
class Player {
private:
    sf::Texture texture;  ///< Texture du sprite joueur
    sf::Sprite sprite;    ///< Sprite affiché à l'écran
    float speed;          ///< Vitesse de déplacement horizontal (px/frame)

public:
    /**
     * @brief Constructeur : charge la texture et positionne le vaisseau.
     *
     * Position initiale : (400, 500). Vitesse : 2.0f.
     */
    Player();

    /**
     * @brief Met à jour la position du joueur selon les touches pressées.
     *
     * - Flèche gauche : déplace de -speed si x > 0
     * - Flèche droite : déplace de +speed si x < 750
     */
    void update();

    /**
     * @brief Dessine le sprite du joueur dans la fenêtre SFML.
     * @param window Référence à la fenêtre de rendu
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Crée un projectile centré sur le vaisseau.
     * @return Bullet positionné à (x+22, y-10) par rapport au sprite
     */
    Bullet shoot();

    /**
     * @brief Retourne la position courante du sprite.
     * @return sf::Vector2f position (x, y) en pixels
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Retourne la hitbox globale du sprite pour les collisions.
     * @return sf::FloatRect rectangle englobant le sprite
     */
    sf::FloatRect getBounds() const;
};

#endif
