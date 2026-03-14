/**
 * ============================================================
 * FICHIER : Block.hpp
 * Projet  : Space Invaders
 * Auteur  : Aly KONATE
 * ============================================================
 * Déclaration de la classe Block — obstacle descendant vers le joueur.
 *
 * Les blocs descendent lentement (0.1f px/frame) depuis le haut de l'écran.
 * Ils peuvent être détruits par les tirs du joueur (+10 pts) ou provoquer
 * un game over s'ils touchent le vaisseau. Un flag "destroyed" contrôle
 * leur visibilité et leur participation aux collisions.
 *
 * Attributs privés :
 *   - texture   : texture chargée depuis assets/images/enemy.png
 *   - sprite    : sprite affiché à l'écran
 *   - destroyed : true si le bloc a été détruit
 *
 * Méthodes publiques :
 *   - update()       : descend le sprite de 0.1f px/frame si non détruit
 *   - draw()         : dessine le sprite si non détruit
 *   - destroy()      : marque le bloc comme détruit (destroyed = true)
 *   - isDestroyed()  : retourne l'état de destruction
 *   - getBounds()    : retourne la hitbox pour la détection de collision
 *   - getY()         : retourne la position Y pour la purge hors-écran
 *
 * Dépendances :
 *   - SFML/Graphics.hpp
 * ============================================================
 */

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>

/**
 * @class Block
 * @brief Obstacle descendant détruit par les tirs ou provoquant un game over.
 *
 * Descend à 0.1f px/frame. Reste dans le vecteur mais cesse d'être dessiné
 * et de participer aux collisions une fois destroyed = true.
 */
class Block {
private:
    sf::Texture texture;  ///< Texture du sprite bloc
    sf::Sprite sprite;    ///< Sprite affiché à l'écran
    bool destroyed;       ///< True si le bloc est détruit

public:
    /**
     * @brief Constructeur : charge la texture et positionne le bloc.
     * @param x Position horizontale initiale (px)
     * @param y Position verticale initiale (px)
     */
    Block(float x, float y);

    /**
     * @brief Descend le sprite de 0.1f px vers le bas à chaque frame (si non détruit).
     */
    void update();

    /**
     * @brief Dessine le sprite dans la fenêtre si le bloc n'est pas détruit.
     * @param window Référence constante à la fenêtre de rendu
     */
    void draw(sf::RenderWindow &window) const;

    /**
     * @brief Marque le bloc comme détruit (destroyed = true).
     *
     * Une fois détruit, le bloc n'est plus dessiné et n'est plus
     * pris en compte dans les collisions.
     */
    void destroy();

    /**
     * @brief Indique si le bloc est détruit.
     * @return true si destroyed == true
     */
    bool isDestroyed() const;

    /**
     * @brief Retourne la hitbox globale du sprite pour les collisions.
     * @return sf::FloatRect rectangle englobant le sprite
     */
    sf::FloatRect getBounds() const;

    /**
     * @brief Retourne la position verticale du sprite.
     * @return float position Y en pixels (utilisée pour la purge hors-écran)
     */
    float getY() const;
};

#endif
