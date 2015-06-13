//
//  main.cpp
//  hackit
//
//  Created by Vansh Pahwa on 6/13/15.
//  Copyright (c) 2015 Vansh Pahwa. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;



struct position
{
    int x,y;
    position operator+(position& a)
    {
        position ans;
        ans.x = a.x+this->x;
        ans.y = a.y+this->y;
        return ans;
    }

    bool operator==(position& b)
    {
        return (x==b.x && y==b.y);
    }
};

bool sortpostion(position p1,position p2)
{
    //todo
    return true;
}
int GetDistance(position pos1,position pos2)
{
    //return abs(pos1.x-pos2.x)+abs(pos1.y-pos2.y);
    return 0;
}

struct message
{
    int messageId;
    position opponent;
};
struct state
{
    position my_loc;
    position opponent_loc;
    vector<vector<bool> > *occupied;//(boardSize, vector<bool>(boardsize, false));
    int size;
    void setOccupied(position mypos)
    {
        occupied->at(mypos.x).at(mypos.y)=true;
    }
    
    int isIsolated()
    {
        //doFloodFill(occupied, my_loc);
        return 0;
    }
};
void printBoard(state board);
class processor
{
public:
    state board;
    void boardInitialise(position my_loc,position opponent_loc,int boardSize)
    {
        board.occupied = new std::vector<vector<bool> >(boardSize, vector<bool>(boardSize, false));
        board.my_loc=my_loc;
        board.opponent_loc=opponent_loc;
        board.setOccupied(my_loc);
        board.setOccupied(opponent_loc);
        board.size=boardSize;
        printBoard(board);
    }
    void processOpponentMove(position pos);
    position myMove();
    bool isValidMove(position pos);
    position getNextMove();
    bool isWithinBoard(position pos1);
    vector<position> getValidMoves();
    vector<position> getValidMoves(state board);
};

void printBoard(state board)
{
    for(int i=0;i<board.size;i++)
    {
        for(int j=0;j<board.size;j++)
        {
            cout<<((board.occupied->at(i)[j])?"#":".")<<" ";
        }
        cout<<endl;
    }
}

void processor::processOpponentMove(position opp_pos)
{
    board.occupied->at(opp_pos.x)[opp_pos.y]=true;
    board.opponent_loc=opp_pos;
    printBoard(board);
}

position processor::myMove()
{
    position next=getNextMove();
    board.setOccupied(next+board.my_loc);
    board.my_loc=next+board.my_loc;
    printBoard(board);
    return next;
}


position processor::getNextMove()
{
    vector<position> validmoves=getValidMoves();
    if (!validmoves.size())
    {
        position pos;
        for (int i=-1;i<=1;i++)
        {
            for (int j=-1;j<=1;j++)
            {
                pos.x=i;pos.y=j;
                if (i==0&&j==0) continue;
                position new_loc =pos+board.my_loc;
                if (isWithinBoard(new_loc)&&(!board.occupied->at(new_loc.x)[new_loc.y]))
                {
                    return pos;
                }
            }
        }
        return pos;
    }
    
    int offset = rand()%validmoves.size();
    
    return validmoves[offset];
}

vector<position> processor:: getValidMoves()
{
    vector<position> temp;
    for (int i=-1;i<=1;i++)
    {
        for (int j=-1;j<=1;j++)
        {
            if (i==0 && j==0) continue;
            position a;
            a.x=i;a.y=j;
            if (isValidMove(a))
            {
                temp.push_back(a);
            }
        }
    }
    return temp;
}

vector<position> processor:: getValidMoves(state board)
{
   vector<position> temp;
    return temp;
}

bool processor::isWithinBoard(position new_loc)
{
    
    if (new_loc.x>board.size-1 || new_loc.x < 0 || new_loc.y>board.size-1 || new_loc.y<0)
    {
        return false;
    }
    return true;
}



bool processor::isValidMove(position pos)
{
    if (abs(pos.x)>1 || abs(pos.y)>1)
    {
        return false;
    }
    else
    {
        position new_loc =pos+board.my_loc;
       if (!isWithinBoard(new_loc))
       {
           return false;
       }
        
        if (board.occupied->at(new_loc.x)[new_loc.y])
        {
            return false;
        }
        else
        {
            for (int i=-1;i<=1;i++)
            {
                for (int j=-1;j<=1;j++)
                {
                    if (i==0 && j==0) continue;
                    position a;
                    a.x=i;a.y=j;
                    position adj = new_loc+a;
                    
                    if (isWithinBoard(adj))
                    {
                        if (board.opponent_loc==adj)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        
    }
    return true;
}
int main(int argc, const char * argv[])
{
    processor proc;
    int msgtype;
    int myx,myy,opx,opy,size;
    position opp,my;
    bool debug = true;
    if(debug)
    {
        while(cin>>msgtype)
        {
            switch(msgtype)
            {
                case 0:
                    cin>>myx>>myy>>opx>>opy>>size;
                    my.x=myx; my.y=myy;
                    opp.x=opx;opp.y=opy;
                    proc.boardInitialise(my, opp, size);
                    break;
                case 1:
                    int opx,opy;
                    cin>>opx>>opy;
                    opp.x=opx; opp.y=opy;
                    proc.processOpponentMove(opp);
                    break;
                case 2:
                    proc.myMove();
                    break;
            }
        }
    }
    return 0;
}

