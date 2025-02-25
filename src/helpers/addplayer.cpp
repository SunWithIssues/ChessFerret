#include "headers/addplayer.h"

AddPlayer::AddPlayer(QList<QString> sectionNames) {
    this->sectionNames = sectionNames;
}


QList<PlayerInfo> AddPlayer::getPlayers()
{
    return players;
}

void AddPlayer::addPlayerToList(PlayerInfo pi)
{
    players.append(pi);
}
