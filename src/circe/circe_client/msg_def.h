#pragma once

enum emUserMsg
{
    msg_login_result        = WM_USER + 100,
    msg_register_result,
    msg_goto_world,
    msg_player_info,
};

enum emGameMsg
{
    msg_game_update        = WM_USER + 1000,
    msg_game_out_card,
};