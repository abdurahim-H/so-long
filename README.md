<h1 align="center">🎮 So Long Game Project</h1>

<div align="center">

![Languages](https://img.shields.io/github/languages/top/abdurahim-H/so-long) ![Repo Size](https://img.shields.io/github/repo-size/abdurahim-H/so-long) ![Last Commit](https://img.shields.io/github/last-commit/abdurahim-H/so-long)

</div>

<p align="center">
  <img src="https://i.imgur.com/lTlUmcC.pnghttps://i.imgur.com/lTlUmcC.png" alt="So Long Game Demo">
</p>

---

## 🕹️ **Game Overview**

**So Long** is an exciting 2D retro puzzle game built with **C** and **MiniLibX**. Your mission: navigate through tricky mazes, collect all the hidden treasures, and escape through the exit—but only after collecting everything! 

Prepare to challenge your wits and reflexes in this pixelated adventure. Created as part of the 42 School curriculum, **So Long** is a great mix of fun and learning about graphics programming.

---

## 🚀 **Key Features**  
![Features](https://img.shields.io/badge/Features-Dynamic-blue?style=for-the-badge)

- 🏞️ **Dynamic Tile Maps:** Every map presents a new puzzle with varying complexity.
- 💎 **Collectible System:** Collect all items before unlocking the exit!
- 🎮 **Simple, Intuitive Controls:** Use `W`, `A`, `S`, `D` or arrow keys to move.
- 💡 **Error Handling:** Robust map validation ensures smooth gameplay.
- 🕹️ **Real-Time Updates:** Visual feedback on collected items and exit readiness.

---

## ⚙️ **Installation**  
![Install](https://img.shields.io/badge/Installation-Easy-green?style=for-the-badge)

### Prerequisites
- **GCC** or compatible C compiler.
- **MiniLibX** library.
- **Make** to build the project.

### Build the Game
To build the game, clone the repository and run `make`:

```bash
git clone https://github.com/abdurahim-H/so-long.git
cd so-long
make
```

This will generate the `so_long` executable, and you're ready to play!

---

## 🎮 **How to Play**  
![Gameplay](https://img.shields.io/badge/Gameplay-Exciting-purple?style=for-the-badge)

Start the game by running the executable with a map file:

```bash
./so_long path/to/map_file.ber
```

**Controls:**
- **W** or ⬆️ - Move Up
- **S** or ⬇️ - Move Down
- **A** or ⬅️ - Move Left
- **D** or ➡️ - Move Right

---

## 🗺️ **Create Your Own Maps**  
![Map Creation](https://img.shields.io/badge/Create%20Maps-Fun-yellow?style=for-the-badge)

Customize your game experience by creating your own maps! Maps are text files where each character represents part of the game:

- `1` - Wall
- `0` - Floor
- `P` - Player starting position
- `C` - Collectible item
- `E` - Exit

**Example Map:**

```
111111
1P0C01
100001
1C00E1
111111
```

---

## 🧩 **Error Handling**  
![Error Handling](https://img.shields.io/badge/Error%20Management-Essential-red?style=flat-square)

The game gracefully handles errors and logs them to a file `error_log.txt` for easier debugging. Invalid inputs, like incorrect map characters, duplicates, or non-integer values, are caught before starting the game.

---

## 📈 **Performance Optimization**  
![Performance](https://img.shields.io/badge/Performance-Optimized-blue?style=flat-square)

The game’s performance is optimized to handle different map sizes and configurations efficiently. It dynamically loads and validates maps, ensuring smooth gameplay.

---

## 📸 **Screenshots**  
![Gameplay Screenshot](https://i.imgur.com/SoXEJJg.png)

---

## 🛡 **License**  
![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for more details.

---

## 🧑‍💻 **Contributions**  
![Contributions](https://img.shields.io/badge/Contributions-Welcome-brightgreen?style=flat-square)

Contributions are welcome! Feel free to open issues or submit pull requests. Together, we can make **So Long** even better!

Steps to contribute:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit (`git commit -am 'Add some feature'`).
4. Push the branch (`git push origin feature-branch`).
5. Submit a pull request.

---

## 👨‍💻 **Author**  
![Author](https://img.shields.io/badge/Author-Abdurahim-blue?style=flat-square)

Developed by **Abdurahim** | [GitHub](https://github.com/abdurahim-H)

---

## 💡 **Inspiration**  
![Inspiration](https://img.shields.io/badge/Inspiration-42%20School-orange?style=flat-square)

This project was inspired by the curriculum at [42 School](https://www.42heilbronn.de/), blending learning with a hands-on approach to graphical programming and C-based game development.

