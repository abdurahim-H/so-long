# **So Long Game Project**

<p align="center">
  <img src="https://i.imgur.com/Nb6IAUz.gif">
</p>

## **Overview**

**So Long** is a 2D puzzle game built with the MiniLibX library, designed to challenge players to collect all items on a map before exiting through the designated exit point. This project was created as part of a learning exercise to understand graphical applications using C programming and MiniLibX library functionalities.

## **Features**

- **Dynamic Tile Maps:** Load and play on different maps with varying complexities.
- **Collectible Tracking:** Players must collect all items on the map before they can exit.
- **Simple Controls:** Use keyboard arrows to navigate through the map.
- **Error Handling:** Comprehensive error management for map validation and gameplay integrity.
- **Visual Feedback:** Real-time updates on game status with collectibles count and exit readiness.

## **Installation**

### Prerequisites

- GCC or another C compiler
- MiniLibX library
- Make (for building)

### Building the Game

Clone the repository and build the game using `make`:

```bash
git clone https://github.com/abdurahim-H/so-long.git
cd so_long
make
```

This will compile all necessary files and produce an executable named `so_long`.

## **Usage**

To start the game, run the executable with a map file:

```bash
./so_long path/to/map_file.ber
```

Control the player using the following keyboard keys:

- **W** - Move up
- **S** - Move down
- **A** - Move left
- **D** - Move right

### Maps

Maps are text files where each character represents a piece of the game:
- `1` - Wall
- `0` - Floor
- `P` - Player start position
- `C` - Collectible item
- `E` - Exit point

An example map looks like this:

```
111111
1P0C01
100001
1C00E1
111111
```

## **Screenshots**

![Gameplay Screenshot](https://i.imgur.com/SoXEJJg.png)

## **Contributing**

Contributions to the project are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit them (`git commit -am 'Add some feature'`).
4. Push the branch (`git push origin feature-branch`).
5. Submit a pull request.

## **Contact**

Abdurahim - abul.hudul@gmail.com

---
