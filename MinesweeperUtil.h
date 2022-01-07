#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array>
#include <iostream>
#include <map>
using namespace std;

class Tile {
public:
  sf::Sprite sprite;

  unsigned int adjMineCount;
  bool flagged;
  bool hidden;
  bool mine;

  Tile(bool mine);
};

class TextureManager {
  static map<string, sf::Texture> textures;

public:
  static void LoadTexture(string textureName);
  static sf::Texture &GetTexture(string textureName);
};
void LoadAssets();
void LoadBoard(int board, int myArray[400], vector<Tile> &tiles, int reLoadCode,
               int &availFlags);
void unhideAdjacent(vector<Tile> &tiles, unsigned int indexCleared);
bool GameStatus(vector<Tile> &tiles);
