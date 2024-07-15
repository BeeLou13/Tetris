#include "game.h"
#include <random>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock()
{
    if(blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
};
std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
};

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw();   
}

void Game::HandleInput()
{
    int keyPressed =  GetKeyPressed();
    switch(keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    currentBlock.Move(0,-1);
    if(IsBlockOutside())
    {
        currentBlock.Move(0,1);
    }
}
void Game::MoveBlockRight()
{
    currentBlock.Move(0,1);
    if(IsBlockOutside() || Blockfits() == false)
    {
        currentBlock.Move(0,-1);
    }
}
void Game::MoveBlockDown()
{
    currentBlock.Move(1,0);
    if(IsBlockOutside())
    {
        currentBlock.Move(-1,0);
        LockBlock();
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        if(grid.isCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    currentBlock.Rotate();
    if(IsBlockOutside())
    {
        currentBlock.UndoRotation();
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();
}

bool Game::Blockfits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        if(grid.isCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
     return true;
}
