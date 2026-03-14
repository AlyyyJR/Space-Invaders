# Space Invaders

> Jeu Space Invaders développé en **C++ avec SFML**, avec ennemis descendants, tirs, blocs obstacles, sons et musique de fond.

---

## Présentation

Space Invaders est une réinterprétation du jeu arcade classique. Le joueur pilote un vaisseau en bas de l'écran et doit détruire les ennemis et les blocs qui descendent vers lui. Le jeu se termine si le joueur est touché par un tir ennemi ou percuté par un bloc.

---

## Objectifs

- Maîtriser la **boucle de jeu SFML** (events → update → render)
- Implémenter la **détection de collision AABB** avec `sf::FloatRect::intersects()`
- Gérer des **entités multiples** avec des vecteurs (enemies, bullets, blocks)
- Appliquer les **design patterns orientés objet** en C++ (encapsulation, séparation des responsabilités)
- Intégrer l'**audio SFML** (sons ponctuels + musique de fond en boucle)
- Utiliser les **algorithmes STL** (`std::remove_if`, `std::all_of`)

---

## Stack technique

| Composant         | Technologie          | Rôle                                              |
|-------------------|----------------------|---------------------------------------------------|
| Langage           | C++17                | Langage principal                                 |
| Moteur graphique  | SFML 2.x (Graphics)  | Rendu 2D, fenêtre, sprites, textures              |
| Audio             | SFML 2.x (Audio)     | Sons ponctuels (Sound) et musique (Music)         |
| Build             | Makefile / CMake     | Compilation multi-fichiers                        |
| Gestion mémoire   | std::vector          | Conteneur dynamique pour entités (enemies, etc.)  |

---

## Structure du projet

```
Space-Invaders/
├── include/
│   ├── Game.hpp        # Déclaration de l'orchestrateur principal
│   ├── Player.hpp      # Déclaration du vaisseau joueur
│   ├── Enemy.hpp       # Déclaration de l'ennemi descendant
│   ├── Bullet.hpp      # Déclaration du projectile
│   └── Block.hpp       # Déclaration du bloc obstacle
├── src/
│   ├── main.cpp        # Point d'entrée
│   ├── Game.cpp        # Implémentation de la boucle principale
│   ├── Player.cpp      # Déplacement, tir du joueur
│   ├── Enemy.cpp       # Descente et destruction des ennemis
│   ├── Bullet.cpp      # Déplacement et destruction des projectiles
│   └── Block.cpp       # Descente, destruction et état des blocs
├── assets/
│   ├── images/
│   │   ├── background.png   # Image de fond
│   │   ├── player.png       # Sprite du vaisseau
│   │   └── enemy.png        # Sprite des ennemis et blocs
│   └── sounds/
│       ├── shoot.ogg        # Son de tir joueur
│       ├── explosion.ogg    # Son d'explosion ennemi
│       ├── sfx_lose.ogg     # Son de destruction de bloc
│       └── canary.ogg       # Musique de fond
├── Makefile
└── CMakeLists.txt
```

---

## Architecture

```
main()
  └── Game
        ├── Player         ← déplacement ←/→, tir (Espace)
        ├── vector<Enemy>  ← descente 0.2 px/frame, tir aléatoire
        ├── vector<Bullet> ← montée 5 px/frame (joueur + ennemis)
        └── vector<Block>  ← descente 0.1 px/frame, destructible
```

### Boucle principale (run)

```
run()
  ├── processEvents()
  │     ├── Closed → window.close()
  │     └── Space  → bullets.push_back(player.shoot())
  │
  ├── update()
  │     ├── player.update()          → déplace le joueur
  │     ├── enemy.update()           → descend chaque ennemi
  │     ├── bullet.update()          → monte chaque projectile
  │     ├── block.update()           → descend chaque bloc actif
  │     ├── removeOffscreenBlocks()  → purge blocs y > 600
  │     ├── removeOffscreenEnemies() → purge ennemis y > 600
  │     ├── handleCollisions()       → résout toutes les collisions
  │     ├── allBlocksDestroyed ?     → spawnDescendingBlocks()
  │     └── enemyShoot()             → tirs ennemis aléatoires
  │
  └── render()
        ├── window.clear()
        ├── background, player, enemies, bullets, blocks
        └── window.display()
```

---

## Système de collisions

Toutes les collisions utilisent la méthode **AABB** (Axis-Aligned Bounding Box) via `sf::FloatRect::intersects()`.

| Collision         | Résultat                                    | Son déclenché     |
|-------------------|---------------------------------------------|-------------------|
| Balle → Bloc      | Bloc détruit + Balle détruite + +10 pts     | sfx_lose.ogg      |
| Balle → Ennemi    | Ennemi détruit + Balle détruite             | explosion.ogg     |
| Balle → Joueur    | **GAME OVER** (window.close())              | —                 |
| Bloc  → Joueur    | **GAME OVER** (window.close())              | —                 |

### Destruction des entités

La destruction est simulée par déplacement hors écran (-100, -100) plutôt que par suppression immédiate du vecteur. La purge réelle s'effectue par l'idiome **erase-remove** :

```cpp
blocks.erase(remove_if(blocks.begin(), blocks.end(),
    [](const Block &b) { return b.getY() > 600; }), blocks.end());
```

---

## Contrôles

| Touche              | Action                        |
|---------------------|-------------------------------|
| `←` Flèche gauche   | Déplacer le vaisseau à gauche |
| `→` Flèche droite   | Déplacer le vaisseau à droite |
| `Espace`            | Tirer un projectile           |
| Fermer la fenêtre   | Quitter le jeu                |

---

## Progression du jeu

```
Phase 1 : 6 ennemis + 6 blocs initiaux
  ↓ tous les blocs détruits ?
Phase 2 : blocs descendants aléatoires (1/50 chance par frame)
  ↓ ennemis sortis de l'écran → supprimés automatiquement (y > 600)
```

---

## Installation & compilation

### Prérequis

- Compilateur C++17 (g++ ou clang++)
- SFML 2.5+ installé
- make (ou cmake)

### Installation SFML (Linux)

```bash
sudo apt-get install libsfml-dev
```

### Installation SFML (macOS)

```bash
brew install sfml
```

### Compilation avec Makefile

```bash
cd Space-Invaders
make
./space_invaders
```

### Compilation manuelle

```bash
g++ src/*.cpp -Iinclude -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -o space_invaders
./space_invaders
```

> Le jeu doit être lancé depuis le répertoire `Space-Invaders/` pour que les chemins `assets/` soient résolus correctement.

---

## Paramètres configurables

| Paramètre               | Valeur    | Description                                 |
|-------------------------|-----------|---------------------------------------------|
| Fenêtre                 | 800×600   | Résolution de la fenêtre SFML               |
| `Player::speed`         | 2.0f      | Vitesse de déplacement du joueur (px/frame) |
| `Enemy::update()`       | 0.2f      | Vitesse de descente des ennemis (px/frame)  |
| `Bullet::speed`         | 5.0f      | Vitesse des projectiles (px/frame)          |
| `Block::update()`       | 0.1f      | Vitesse de descente des blocs (px/frame)    |
| `spawnDescendingBlocks` | 1/50      | Probabilité de spawn par frame              |
| `enemyShoot()`          | 3/200     | Probabilité de tir ennemi par frame         |
| Musique de fond         | 15%       | Volume de canary.ogg                        |
| Score par bloc          | +10 pts   | Points gagnés par bloc détruit              |

---

## Classes et responsabilités

| Classe   | Fichiers               | Responsabilité principale                                |
|----------|------------------------|----------------------------------------------------------|
| `Game`   | Game.hpp / Game.cpp    | Boucle SFML, orchestration, collisions, score, spawn     |
| `Player` | Player.hpp / Player.cpp| Déplacement ←/→, tir de projectiles                     |
| `Enemy`  | Enemy.hpp / Enemy.cpp  | Descente automatique, tir aléatoire, destruction         |
| `Bullet` | Bullet.hpp / Bullet.cpp| Projectile (joueur + ennemi), déplacement vers le haut   |
| `Block`  | Block.hpp / Block.cpp  | Obstacle descendant, état destroyed, purge hors écran    |

---

## Auteur

**Aly KONATE** - Projet personnel
