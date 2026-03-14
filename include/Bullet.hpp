/**
 * ============================================================
 * FICHIER : Bullet.hpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Déclaration de la classe Bullet — projectile tiré par le joueur ou les ennemis.
 *
 * Le projectile est représenté par un RectangleShape SFML (5×10 px, rouge).
 * Il se déplace vers le haut à vitesse constante (5.0f px/frame).
 * La destruction est simulée en déplaçant le shape hors de l'écran (-100, -100).
 *
 * Attributs privés :
 *   - shape : rectangle SFML représentant la balle
 *   - speed : vitesse de déplacement vertical (5.0f px/frame vers le haut)
 *
 * Méthodes publiques :
 *   - update()    : déplace le projectile de -speed vers le haut
 *   - draw()      : dessine le projectile dans la fenêtre
 *   - destroy()   : déplace le shape hors écran (-100, -100)
 *   - getBounds() : retourne la hitbox pour la détection de collision
 *
 * Dépendances :
 *   - SFML/Graphics.hpp
 * ============================================================
 */

#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

/**
 * @class Bullet
 * @brief Projectile tiré par le joueur ou les ennemis.
 *
 * Rectangle rouge (5×10 px) se déplaçant vers le haut à 5 px/frame.
 * Utilisé à la fois pour les tirs joueur et les tirs ennemis.
 */
class Bullet {
private:
    sf::RectangleShape shape;  ///< Forme rectangulaire représentant le projectile
    float speed;               ///< Vitesse de déplacement vers le haut (px/frame)

public:
    /**
     * @brief Constructeur : initialise le projectile à la position donnée.
     * @param x Position horizontale initiale (px)
     * @param y Position verticale initiale (px)
     *
     * Taille : 5×10 px. Couleur : rouge. Vitesse : 5.0f px/frame.
     */
    Bullet(float x, float y);

    /**
     * @brief Déplace le projectile de -speed px vers le haut à chaque frame.
     */
    void update();

    /**
     * @brief Dessine le projectile dans la fenêtre SFML.
     * @param window Référence constante à la fenêtre de rendu
     */
    void draw(sf::RenderWindow &window) const;

    /**
     * @brief Simule la destruction en déplaçant le shape à (-100, -100).
     *
     * Le projectile reste dans le vecteur mais est hors écran et hors hitbox active.
     */
    void destroy();

    /**
     * @brief Retourne la hitbox globale du shape pour les collisions.
     * @return sf::FloatRect rectangle englobant le projectile
     */
    sf::FloatRect getBounds() const;
};

#endif
