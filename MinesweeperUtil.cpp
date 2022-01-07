#include "MinesweeperUtil.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <stack>
#include <vector>
using namespace std;

void TextureManager::LoadTexture(string textureName) {
  string path = "images/";
  path += textureName + ".png";
  textures[textureName].loadFromFile(path);
}

sf::Texture &TextureManager::GetTexture(string textureName) {

  return textures[textureName];
}
void LoadAssets() {
  TextureManager::LoadTexture("mine");
  TextureManager::LoadTexture("tile_hidden");
  TextureManager::LoadTexture("tile_revealed");
  TextureManager::LoadTexture("number_1");
  TextureManager::LoadTexture("number_2");
  TextureManager::LoadTexture("number_3");
  TextureManager::LoadTexture("number_4");
  TextureManager::LoadTexture("number_5");
  TextureManager::LoadTexture("number_6");
  TextureManager::LoadTexture("number_7");
  TextureManager::LoadTexture("number_8");
  TextureManager::LoadTexture("flag");
  TextureManager::LoadTexture("face_happy");
  TextureManager::LoadTexture("face_win");
  TextureManager::LoadTexture("face_lose");
  TextureManager::LoadTexture("digits");
  TextureManager::LoadTexture("debug");
  TextureManager::LoadTexture("test_1");
  TextureManager::LoadTexture("test_2");
  TextureManager::LoadTexture("test_3");
}
void LoadBoard(int board, int myArray[400], vector<Tile> &tiles, int reLoadCode,
               int &availFlags) {
  for (int i = 0; i < 400; i++) {
    myArray[i] = 0;
  }
  if (board == 0) {
    unsigned seed = static_cast<unsigned int>(
        chrono::steady_clock::now().time_since_epoch().count());
    mt19937 mt(seed);
    uniform_int_distribution<int> dist(0, 399);
    int numMines = 0;
    unsigned int index = 0;
    while (numMines < 50) {
      index = static_cast<unsigned int>(dist(mt));
      if (myArray[index] == 0) {
        myArray[index] = 1;
        numMines++;
      }
    }

  } else if (board == 1) {
    ifstream in("boards/testBoard1.brd");
    char c;
    int j = 0;
    while (in >> c) {
      myArray[j] = (c - 48);
      j++;
    }

  } else if (board == 2) {
    ifstream in("boards/testBoard2.brd");
    char c;
    int j = 0;
    while (in >> c) {
      myArray[j] = (c - 48);
      j++;
    }

  } else if (board == 3) {
    ifstream in("boards/testBoard3.brd");
    char c;
    int j = 0;
    while (in >> c) {
      myArray[j] = (c - 48);
      j++;
    }
  }
  if (reLoadCode == 0) {
    availFlags = 0;
    for (unsigned int i = 0; i < 400; i++) {
      if (myArray[i] == 1) {
        Tile t(true);
        tiles.push_back(t);
        availFlags++;
      } else {
        Tile t(false);
        tiles.push_back(t);
      }
    }
  }
  if (reLoadCode == 1) {
    availFlags = 0;
    for (unsigned int i = 0; i < 400; i++) {
      if (myArray[i] == 1) {
        tiles[i].mine = true;
        tiles[i].hidden = true;
        tiles[i].flagged = false;
        tiles[i].adjMineCount = 0;
        availFlags++;
      } else {
        tiles[i].mine = false;
        tiles[i].hidden = true;
        tiles[i].flagged = false;
        tiles[i].adjMineCount = 0;
      }
    }
  }
  unsigned int index = 0;
  unsigned int mineCount = 0;
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 25; j++) {

      if (tiles[index].mine == false) {
        mineCount = 0;

        if (j - 1 >= 0 && i - 1 >= 0) {
          mineCount +=
              static_cast<unsigned int>(myArray[(i - 1) * (25) + j - 1]);
        }
        if (i - 1 >= 0) {
          mineCount += static_cast<unsigned int>(myArray[(i - 1) * (25) + j]);
        }
        if (j + 1 <= 24 && i - 1 >= 0) {
          mineCount +=
              static_cast<unsigned int>(myArray[(i - 1) * (25) + j + 1]);
        }
        if (j - 1 >= 0) {
          mineCount += static_cast<unsigned int>(myArray[(i) * (25) + j - 1]);
        }

        if (j + 1 <= 24) {
          mineCount += static_cast<unsigned int>(myArray[(i) * (25) + j + 1]);
        }
        if (j - 1 >= 0 && i + 1 <= 15) {
          mineCount +=
              static_cast<unsigned int>(myArray[(i + 1) * (25) + j - 1]);
        }
        if (i + 1 <= 15) {
          mineCount += static_cast<unsigned int>(myArray[(i + 1) * (25) + j]);
        }
        if (i + 1 <= 15 && j + 1 <= 24) {
          mineCount +=
              static_cast<unsigned int>(myArray[(i + 1) * (25) + j + 1]);
        }
        tiles[index].adjMineCount = mineCount;
      }
      index++;
    }
  }
}
Tile::Tile(bool mine) {
  sf::Sprite sprite;
  this->mine = mine;

  this->sprite.setTexture(TextureManager::GetTexture("tile_hidden"));
  this->adjMineCount = 0;
  this->flagged = false;
  this->hidden = true;
}
void unhideAdjacent(vector<Tile> &tiles, unsigned int indexCleared) {
  stack<unsigned int> cleared;
  cleared.push(indexCleared);
  int j = 0;
  int i = 0;
  unsigned int index = 0;
  while (cleared.size() != 0) {
    index = cleared.top();
    cleared.pop();
    i = static_cast<int>(floor(index / 25.0));
    j = static_cast<int>(floor(index - 25.0 * i));
    if (tiles[index].adjMineCount == 0 && tiles[index].flagged == false &&
        tiles[index].mine == false) {

      if (j - 1 >= 0 && i - 1 >= 0 && tiles[index - 26].hidden == true &&
          tiles[index - 26].flagged == false &&
          tiles[index - 26].mine == false) {
        cleared.push(index - 26);
        tiles[index - 26].hidden = false;
      }
      if (i - 1 >= 0 && tiles[index - 25].hidden == true &&
          tiles[index - 25].flagged == false &&
          tiles[index - 25].mine == false) {
        cleared.push(index - 25);
        tiles[index - 25].hidden = false;
      }
      if (j + 1 <= 24 && i - 1 >= 0 && tiles[index - 24].hidden == true &&
          tiles[index - 24].flagged == false &&
          tiles[index - 24].mine == false) {
        cleared.push(index - 24);
        tiles[index - 24].hidden = false;
      }
      if (j - 1 >= 0 && tiles[index - 1].hidden == true &&
          tiles[index - 1].flagged == false && tiles[index - 1].mine == false) {
        cleared.push(index - 1);
        tiles[index - 1].hidden = false;
      }

      if (j + 1 <= 24 && tiles[index + 1].hidden == true &&
          tiles[index + 1].flagged == false && tiles[index + 1].mine == false) {
        cleared.push(index + 1);
        tiles[index + 1].hidden = false;
      }
      if (j - 1 >= 0 && i + 1 <= 15 && tiles[index + 24].hidden == true &&
          tiles[index + 24].flagged == false &&
          tiles[index + 24].mine == false) {
        cleared.push(index + 24);
        tiles[index + 24].hidden = false;
      }
      if (i + 1 <= 15 && tiles[index + 25].hidden == true &&
          tiles[index + 25].flagged == false &&
          tiles[index + 25].mine == false) {
        cleared.push(index + 25);
        tiles[index + 25].hidden = false;
      }
      if (i + 1 <= 15 && j + 1 <= 24 && tiles[index + 26].hidden == true &&
          tiles[index + 26].flagged == false &&
          tiles[index + 26].mine == false) {
        cleared.push(index + 26);
        tiles[index + 26].hidden = false;
      }
    }
  }
}
bool GameStatus(vector<Tile> &tiles) {
  unsigned int tileCount = 0;
  bool winner = false;
  for (unsigned int i = 0; i < 400; i++) {
    if (tiles[i].mine && tiles[i].hidden) {
      tileCount++;
    }
    if (tiles[i].hidden == false) {
      tileCount++;
    }
  }
  if (tileCount == 400) {
    winner = true;
  }
  return winner;
}
