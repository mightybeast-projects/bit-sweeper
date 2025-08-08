# 💣️ **Bit-sweeper** 💥

<img src="ui/examples/demo-1.gif" height="250">
<img src="ui/examples/demo-3.gif" height="250">

<img src="ui/examples/demo-4.gif" height="250">
<img src="ui/examples/demo-2.gif" height="250">

## 📃 Description

Minesweeper game clone. Written in C (btw) (and I'm very proud of it). Valgrind said no memory leaks.

## 🔧 Developed using

[![C](https://img.shields.io/badge/C-black?style=for-the-badge&logo=c&logoColor=black&labelColor=orange)](#)
[![Raylib](https://img.shields.io/badge/raylib-black?style=for-the-badge&logo=raylib&logoColor=black&labelColor=orange)](#)

## 🖥️ Platforms

[![Linux](https://img.shields.io/badge/Linux-black?style=for-the-badge&logo=Linux&logoColor=black&labelColor=orange)](#)
[![Windows](https://img.shields.io/badge/Windows-black?style=for-the-badge&logo=Windows&logoColor=black&labelColor=orange)](#)

## 🎮 **How to play**

Clone this repo, pull github submodules for raylib and unity (no, not Unity, the testing framework), build with CMake and run:

```
$ git submodule update --recursive
$ cmake -B build -S .
$ cd build && make
$ cd ui && ./bitsweeper-game
```
