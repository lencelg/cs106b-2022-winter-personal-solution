#include "Labyrinth.h"
#include <string>
using namespace std;

bool isPathToFreedomhelper(MazeCell* start, const string& moves, int cnt[]) {
    if(start->whatsHere==Item::SPELLBOOK) cnt[0]=1;
    if(start->whatsHere==Item::POTION) cnt[1]=1;
    if(start->whatsHere==Item::WAND) cnt[2]=1;
    if(cnt[0]==1&&cnt[1]==1&&cnt[2]==1)return true;
    if(moves!=""){
        auto curstring=moves.substr(0,1);
        if(curstring=="N"&&start->north)return isPathToFreedomhelper(start->north,moves.substr(1,moves.size()-1),cnt);
        if(curstring=="S"&&start->south)return isPathToFreedomhelper(start->south,moves.substr(1,moves.size()-1),cnt);
        if(curstring=="W"&&start->west)return isPathToFreedomhelper(start->west,moves.substr(1,moves.size()-1),cnt);
        if(curstring=="E"&&start->east)return isPathToFreedomhelper(start->east,moves.substr(1,moves.size()-1),cnt);
        return false;
    }
    return false;
}
bool isPathToFreedom(MazeCell* start, const string& moves) {
    /* TODO: Delete this comment and the next few lines, then implement
     * this function.
     */
    int a[3]={0};
    return isPathToFreedomhelper(start,moves,a);
}


/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"
#include "Demos/MazeGenerator.h"

/* Optional: Add your own custom tests here! */














/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we write 'delete maze;'
     * rather than what's shown above?
     */
}

PROVIDED_TEST("Checks paths in the sample maze.") {
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);
}

PROVIDED_TEST("Can't walk through walls.") {
    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);
}

PROVIDED_TEST("Works when starting on an item.") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);
}

