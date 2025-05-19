#ifndef TIC_TAC_TOE_BOOST_MATCHMAKING_SESION_H
#define TIC_TAC_TOE_BOOST_MATCHMAKING_SESION_H

#include <string>

struct MatchmakingSesion {
  std::string game_uuid;
  std::string creator_uuid;
  std::string joining_uuid;
};

#endif // TIC_TAC_TOE_BOOST_MATCHMAKING_SESION_H
