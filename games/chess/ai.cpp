// AI
// This is where you build your AI

#include "ai.hpp"
#include "userfiles/utility.h"
#include "userfiles/state.h"
#include "userfiles/minmax.h"
#include <ctime>
#include <thread>
#include <exception>
static state currentState;
static std::thread pthread;
// You can add #includes here for your AI.

namespace cpp_client
{

namespace chess
{

/// <summary>
/// This returns your AI's name to the game server.
/// Replace the string name.
/// </summary>
/// <returns>The name of your AI.</returns>
std::string AI::get_name() const
{
    // REPLACE WITH YOUR TEAM NAME!
    return "Brave Boysenberry";
}

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
  std::cout << "Iinitializing game...." << std::endl;
  currentState.m_id = player->id;
  currentState = game;
  srand(time(NULL));
  std::cout << "done" << std::endl;
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
    // If a function you call triggers an update this will be called before it returns.
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
  // You can do any cleanup of your AI here.  The program ends when this function returns.
}

/// <summary>
/// This is called every time it is this AI.player's turn.
/// </summary>
/// <returns>Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.</returns>
bool AI::run_turn()
{
  std::cout << "MyTurn" << std::endl;
  MYTURN = true;
  if(pthread.joinable())
  {
    pthread.join();
  }
  if(game->moves.size() > 0)
  {
    std::cout << "Opponent's Last Move: '" << game->moves[game->moves.size() - 1]->san << "'" << std::endl;
  }
  print_current_board();
  std::cout << std::endl;
  if(game->moves.size() > 0)
  {
    action lastMove(game->moves[game->moves.size() - 1]);
    currentState.applyAction(lastMove);
  }
  currentState.m_board.print();
  std::cout << std::endl;
  auto theAction = IDTLMMS(currentState, 1);
  currentState.applyAction(theAction);
  modifyGame(player, theAction);
  std::cout << "Time Remaining: " << player->time_remaining << " ns" << std::endl;
  MYTURN = false;
  pthread = std::thread(pondering, currentState);
  return true; // to signify we are done with our turn.
}

/// <summary>
///  Prints the current board using pretty ASCII art
/// </summary>
/// <remarks>
/// Note: you can delete this function if you wish
/// </remarks>
void AI::print_current_board()
{
    for(int rank = 9; rank >= -1; rank--)
    {
        std::string str = "";
        if(rank == 9 || rank == 0) // then the top or bottom of the board
        {
            str = "   +------------------------+";
        }
        else if(rank == -1) // then show the ranks
        {
            str = "     a  b  c  d  e  f  g  h";
        }
        else // board
        {
            str += " ";
            str += std::to_string(rank);
            str += " |";
            // fill in all the files with pieces at the current rank
            for(int file_offset = 0; file_offset < 8; file_offset++)
            {
                std::string file(1, 'a' + file_offset); // start at a, with with file offset increasing the char;
                chess::Piece current_piece = nullptr;
                for(const auto& piece : game->pieces)
                {
                    if(piece->file == file && piece->rank == rank) // then we found the piece at (file, rank)
                    {
                        current_piece = piece;
                        break;
                    }
                }

                char code = '.'; // default "no piece";
                if(current_piece != nullptr)
                {
                    code = current_piece->type[0];

                    if(current_piece->type == "Knight") // 'K' is for "King", we use 'N' for "Knights"
                    {
                        code = 'N';
                    }

                    if(current_piece->owner->id == "1") // the second player (black) is lower case. Otherwise it's upppercase already
                    {
                        code = tolower(code);
                    }
                }

                str += " ";
                str += code;
                str += " ";
            }

            str += "|";
        }

        std::cout << str << std::endl;
    }
}

// You can add additional methods here for your AI to call

} // chess

} // cpp_client
