#ifndef ADDPLAYER_H
#define ADDPLAYER_H

#include "info.h"
#include <QComboBox>

class AddPlayer
{

public:
    AddPlayer(QList<QString> sectionNames);

    QList<PlayerInfo> getPlayers();
    void addPlayerToList(PlayerInfo pi);

private:

    QList<QString> sectionNames;
    QList<PlayerInfo> players;



};

#endif // ADDPLAYER_H
