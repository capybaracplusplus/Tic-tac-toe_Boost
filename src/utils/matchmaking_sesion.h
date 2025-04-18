#ifndef TIC_TAC_TOE_BOOST_MATCHMAKING_SESION_H
#define TIC_TAC_TOE_BOOST_MATCHMAKING_SESION_H

#include <string>

struct MatchmakingSesion {
  // key to check that the player has access to this game by uuid
  std::string game_uuid;
  std::string creator_uuid;
  std::string creator_key;
  std::string joining_uuid;
  std::string joining_key;
};

#endif // TIC_TAC_TOE_BOOST_MATCHMAKING_SESION_H
