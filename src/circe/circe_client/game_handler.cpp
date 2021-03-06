#include "stdafx.h"
#include "game_handler.h"

LoginHandler        GameHandler::login;
RegisterHandler     GameHandler::reg;
CFGFightHandler     GameHandler::fightcard;
PlayerInfoHandler   GameHandler::player_info;

void GameHandler::user_login_handler( const NetworkMessage& message )
{
    Protocol::S2CLoginRsp msg;
    message.parse(msg);
    if (msg.login_result())
    {
        login.NotifyResult();
    }
    else
    {
        std::string strErr = msg.failed_reason();
        login.NotifyResult(strErr);
    }
}

void GameHandler::user_register_handler( const NetworkMessage& message )
{
    Protocol::S2CRegisterRsp msg;
    message.parse(msg);
    if (msg.register_result())
    {
        reg.NotifyResult();
    }
    else
    {
        std::string strErr = msg.failed_reason();
        reg.NotifyResult(strErr);
    }
}

void GameHandler::game_fight_handler(const NetworkMessage& message)
{

}

void GameHandler::player_info_rsp( const NetworkMessage& message )
{
    Protocol::S2CGetPlayerProfileRsp msg;
    message.parse(msg);
    player_info.NotifyResult(msg);
}
