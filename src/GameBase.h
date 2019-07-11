#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <SocketConnection.h>



namespace bridges {
  class GameBase {
    Bridges bridges;

    GameGrid gg;

    bool firsttime = true;

  protected:
    std::unique_ptr<SocketConnection> sockcon;
  
    ///Having a protected constructor prevent the object from being
    ///directly created. Since GameBase is meant to be a purely internal
    ///class, that seems appropriate.
  GameBase(int assignmentID, std::string username, std::string apikey)
    :bridges(assignmentID, username, apikey) {
      bridges.setServer("games");

      sockcon = std::make_unique<SocketConnection>(bridges);
    }

  
  protected:


    void render() {
      if (firsttime) {
	bridges.setVisualizeJSONFlag(true);
    
	bridges.setDataStructure(&gg);

	bridges.visualize();

	firsttime = false;
      
      }

      sockcon->sendGameGrid(gg);
    }

  protected:
    void SetBGColor(int row, int col, NamedColor nc) {
      gg.setBGColor(row, col, nc);
    }

    void DrawObject(int row, int col, NamedSymbol symb, NamedColor nc) {
      gg.drawObject(row, col, symb, nc);
    }


  };
}

#endif
