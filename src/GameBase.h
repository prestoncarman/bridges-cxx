#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <SocketConnection.h>



namespace bridges {
  class GameBase {
  private:
    Bridges bridges;

    GameGrid gg;

    bool firsttime = true;


    std::unique_ptr<SocketConnection> sockcon;

  protected:
    bool debug = true;
    
  
    ///Having a protected constructor prevent the object from being
    ///directly created. Since GameBase is meant to be a purely internal
    ///class, that seems appropriate.
    GameBase(int assignmentID, std::string username, std::string apikey, int nbRow=10, int nbColumn=10)
      :bridges(assignmentID, username, apikey), gg(nbRow, nbColumn) {
      bridges.setServer("games");

      sockcon = std::make_unique<SocketConnection>(bridges);

      if (debug)
	std::cerr<<"nbRow: "<<nbRow<<" nbCol: "<<nbColumn<<std::endl;
    }

    /// @brief This function is called once when the game starts.
    ///
    /// Students write this function.
    /// It will be called once at the begining of the game.
    virtual void initialize () = 0;

    /// @brief This function is called once per frame of the game.
    ///
    /// Students write this function.
    /// It will be called at each frame of the game.
    virtual void GameLoop () = 0;

    
  protected:
    /// @brief register a new KeypressListener
    ///
    /// Students should not have to call this function directly.  The
    /// KeypressListener listener will get notified of all keypresses
    /// (up and down) that happens in the game.
    ///
    /// @param kl a KeypressListener to register
    void registerKeyListener(KeypressListener* p) {
      sockcon->registerKeyListener(p);
    }

    /// @brief Renders the game
    ///
    /// Student should not have to call this function directly. It is
    /// called automatically by Bridges.
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
    /// @brief Change the background color of a cell
    ///
    /// @param x row of the cell to set
    /// @param y column of the cell to set
    /// @param c NamedColor to set
    void setBGColor(int row, int col, NamedColor nc) {
      gg.setBGColor(row, col, nc);
    }
    
    /// @brief Draw an object on the game
    ///
    /// @param x row of the cell to draw the object on
    /// @param y column of the cell to draw the object on
    /// @param s symbol representing the object
    /// @param c color of the object
    void drawObject(int row, int col, NamedSymbol symb, NamedColor nc) {
      gg.drawObject(row, col, symb, nc);
    }


  };
}

#endif
