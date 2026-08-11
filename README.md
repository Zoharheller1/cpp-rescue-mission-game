# 🎮 C++ Rescue Mission Game

A 2D action game developed in **C++** with a strong focus on **Object-Oriented Programming, design patterns, enemy behavior, collision handling, animations, and modular game architecture**.

The player controls a vehicle that must infiltrate a hostile military base, rescue three prisoners, and safely reach the extraction point before time or health runs out.

## 🚀 Gameplay

The player begins outside an enemy military base and must fight through several types of enemies in order to enter the compound.

To access the base, the player must obtain and use a grenade to destroy the entrance gate.

Once inside, the player must:

- Fight different enemy types
- Search buildings for prisoners
- Rescue three prisoners
- Manage health and remaining time
- Collect useful power-ups
- Navigate using the mini-map
- Reach the helicopter extraction point to complete the mission

The prisoners are randomly distributed among different buildings, making each playthrough less predictable.

## 🎯 Main Features

- 🚗 Player movement in multiple directions
- 🔫 Shooting mechanics
- 💣 Grenade system with multi-directional explosions
- 🪖 Multiple enemy types
- 🚜 Tanks and heavy artillery
- 🎯 Snipers and guards
- 💥 Suicide bomber enemies
- ❤️ Health system
- ⏱️ Time-limited gameplay
- 🛡️ Temporary shield power-up
- 🎁 Random power-ups
- 🗺️ Mini-map system
- 🏠 Destructible buildings
- 🚪 Destructible base gate
- 🚁 Extraction point and victory system
- 🔊 Sound and music management
- 🎞️ Character and object animations
- ⏸️ Pause, restart, menu, help, and end screens

## 🛠️ Technologies

- **C++**
- **SFML**
- **CMake**
- Object-Oriented Programming
- STL Containers
- Design Patterns
- Event-driven game logic

## 🧠 Architecture

The project was designed using a modular object-oriented architecture.

The game contains a large inheritance hierarchy built around a common base `Object` class, with separate hierarchies for static and active game objects.

The `Board` class manages the game's static and dynamic objects, while the `Controller` handles the different game screens and overall game flow.

The architecture was designed to make it easier to extend the game with additional enemies, weapons, projectiles, screens, and gameplay mechanics.

## 🧩 Design Patterns

Several software design patterns are used throughout the project.

### Factory Pattern

A generic factory system is used to create game objects dynamically according to their type.

### Strategy Pattern

Different movement, shooting, and direction algorithms are implemented independently and assigned to game objects according to their behavior.

This allows different enemies to use different strategies without tightly coupling the behavior to the object itself.

### Observer Pattern

Used for communication between game objects.

For example:

- Enemies can track the player's location
- The mini-map is updated when relevant game objects change
- Buildings can notify other components when they are destroyed

### State Pattern

The game controller manages multiple application states, including:

- Main Menu
- Gameplay
- Help
- Volume Settings
- End Screen
- Exit

Each screen has its own behavior while sharing a common interface.

### Singleton Pattern

The `Resources` class uses the Singleton pattern to provide centralized access to shared game resources such as:

- Textures
- Fonts
- Sounds
- Music
- Animations

### Multimethod Collision Handling

Collision behavior is handled according to the types of the two objects involved, allowing different collision responses between players, enemies, bullets, buildings, power-ups, and other game objects.

## 🤖 Enemy Behavior

Enemies use different movement and attack strategies depending on their type.

Some enemies actively follow the player's position, while others use different movement or shooting behaviors.

The game also includes direction-handling logic designed to prevent enemies from becoming stuck when encountering static objects.

## 💥 Weapons

The player has access to multiple attack types.

### Standard Weapon

The player's default weapon can be used continuously against enemies.

### Grenades

Grenades are obtained through collectible power-ups.

When activated, grenades are launched in multiple directions and deal significantly more damage than the standard weapon.

They are also required to destroy the military base entrance.

Different enemies use different projectile types and damage levels.

## 🎁 Power-Ups

The game includes several collectible bonuses:

- 💣 Grenades
- ❤️ Additional health
- ⏱️ Additional time
- 🛡️ Temporary shield

Power-up values and durations may vary during gameplay.

## 🗺️ Mini-Map

The game includes a mini-map that helps the player navigate the environment.

It displays important locations such as:

- Player position
- Buildings
- Mission objectives
- Extraction point

The mini-map is dynamically updated during gameplay.

## 📁 Project Structure

```text
.
├── cmake/
├── include/
├── resources/
├── src/
├── CMakeLists.txt
└── CMakePresets.json
