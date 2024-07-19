#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
    Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool gameOver;
    int score;

private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool Blockfits();
    void reset();
    void UpdateScore(int linesCleared, int moveDownPOints);
    std::vector<Block> GetAllBlocks();
    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;

};