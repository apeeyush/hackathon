#include<bits/stdc++.h>

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
#include "mongoose.h"
// #include <iostream>
// #include <algorithm>
// #include <math.h>
// #include <vector>

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
        board.occupied = new vector<vector<bool> >(boardSize, vector<bool>(boardSize, false));
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
    return board.my_loc;
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



processor proc;



static const char *s_no_cache_header =
  "Cache-Control: max-age=0, post-check=0, "
  "pre-check=0, no-store, no-cache, must-revalidate\r\n";

// static void handle_restful_call(struct mg_connection *conn) {
//   char n1[100], n2[100];
//   mg_get_var(conn, "n1", n1, sizeof(n1));
//   mg_get_var(conn, "n2", n2, sizeof(n2));

//   mg_printf_data(conn, "{ \"result\": %lf }", strtod(n1, NULL) + strtod(n2, NULL));
// }

static void handle_ping_call(struct mg_connection *conn) {
  mg_printf_data(conn, "{ \"ok\": \"true\" }");
}

position getPosition(char* s)
{
  std::vector<char*> v;
  char* chars_array = strtok(s, "|");
  while(chars_array)
  {
      v.push_back(chars_array);
      chars_array = strtok(NULL, "|");
  }
  position ans;
  ans.x = strtod(v[0], NULL)-1;
  ans.y = strtod(v[1], NULL)-1;
  return ans;
}

static void handle_start_call(struct mg_connection *conn) {
  char y[100], o[100], g[100];
  mg_get_var(conn, "y", y, sizeof(y));
  mg_get_var(conn, "o", o, sizeof(o));
  mg_get_var(conn, "g", g, sizeof(g));

  position myp = getPosition(y);
  position opp = getPosition(o);
  proc.boardInitialise(myp, opp, strtod(g,NULL));
  // TODO : initGame(strtod(y, NULL), strtod(o, NULL), strtod(g, NULL))

  mg_printf_data(conn, "{ \"ok\": \"true\" }");
}

static void handle_play_call(struct mg_connection *conn) {
  char m[100];
  mg_get_var(conn, "m", m, sizeof(m));
  cout<<string(m)<<endl;
  position opp = getPosition(m);
  proc.processOpponentMove(opp);
  position myMove = proc.myMove();
  // TODO : Send move and ask ou
  char s1[15];
  sprintf(s1, "%d", myMove.x+1);
  char s2[15];
  sprintf(s2, "%d", myMove.y+1);
  // string s1 = to_string(myMove.x+1);
  // string s2 = to_string(myMove.y+1);
  string s3 = "{ \"m\": \"" + string(s1) + "|" + string(s2) + "\" }";
  // char * s3 = new char[100];
  // s3 = strcat("{ \"m\": \"" , s1);
  // s3 = strcat(s3, "|");
  // s3 = strcat(s3, s2);
  // s3 = strcat(s3, "\" }");
  char const *pchar = s3.c_str(); 
  mg_printf_data(conn, pchar);
  cout<<s3<<endl;
}


static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_AUTH: return MG_TRUE;
    case MG_REQUEST:

      if (!strcmp(conn->uri, "/ping")) {
        handle_ping_call(conn);
        return MG_TRUE;
      }
      if (!strcmp(conn->uri, "/start")) {
        handle_start_call(conn);
        return MG_TRUE;
      }
      if (!strcmp(conn->uri, "/play")) {
        handle_play_call(conn);
        return MG_TRUE;
      }
      return MG_FALSE;
      // if (!strcmp(conn->uri, "/api/sum")) {
      //   handle_restful_call(conn);
      //   return MG_TRUE;
      // }
      // mg_send_file(conn, "index.html", s_no_cache_header);
      // return MG_MORE;
    default: return MG_FALSE;
  }
}

int main(void) {
  struct mg_server *server;
  // Create and configure the server
  server = mg_create_server(NULL, ev_handler);
  mg_set_option(server, "listening_port", "8080");
  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) {
    mg_poll_server(server, 1000);
  }
  // Cleanup, and free server instance
  mg_destroy_server(&server);
  return 0;
}
