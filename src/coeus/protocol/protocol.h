// Generate by the sword of core(核心之刃). DO NOT EDIT!
// Source : protocol.h
// Comment : 通信消息协议文件。

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <venus_net/venus_net.h>

namespace Protocol
{
    static uint32 getStrListSize(const std::vector<std::string>& strList) 
    {
        uint32 size = 0; 
        for (uint32 i = 0; i < strList.size(); i++) 
        { 
            size += strList[i].length() + 2; 
        }

        return size + 2;
    }

    template<class T> 
    static uint32 getStructArrBytesSize(const std::vector<T>& vt)
    {
        uint32 size = 0; 
        for (uint32 i = 0; i < vt.size(); i++) 
        { 
            size += vt[i].byteSize(); 
        }

        return 2 + size;
    }

    //角色基本数据
    struct CharacterBaseInfo 
    {
        std::string nickname;                   //角色昵称
        uint8 character_type;             //角色类型（职业）

        int byteSize()
        {
            return (nickname.length() + 2) + sizeof(character_type);
        }

    };

    static StreamReader& operator >> (StreamReader& r, CharacterBaseInfo& st)
    {
        r >> st.nickname;
        r >> st.character_type;

        return r;
    }

    static StreamWriter& operator << (StreamWriter& w, CharacterBaseInfo& st)
    {
        w << st.nickname;
        w << st.character_type;

        return w;
    }

    /**
    * ● 登录&注册(4 message)
    */

    //登录请求
    struct CSLoginReq : public NetworkMessage
    {
        //登录帐号（邮箱地址）
        std::string account;
        //密码
        std::string password;

        int byteSize()
        {
            return (account.length() + 2) + (password.length() + 2);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << account;
            w << password;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> account;
            r >> password;
        }
    };

    //登录返回
    struct SCLoginRsp : public NetworkMessage
    {
        //登录结果
        uint8 login_result;
        //角色ID
        uint64 player_id;
        //是否需要创建角色
        uint8 character_create_require;

        int byteSize()
        {
            return sizeof(login_result) + sizeof(player_id) + sizeof(character_create_require);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << login_result;
            w << player_id;
            w << character_create_require;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> login_result;
            r >> player_id;
            r >> character_create_require;
        }
    };

    //用户注册请求
    struct CSRegisterReq : public NetworkMessage
    {
        //要注册的用户名
        std::string username;
        //密码
        std::string password;

        int byteSize()
        {
            return (username.length() + 2) + (password.length() + 2);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << username;
            w << password;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> username;
            r >> password;
        }
    };

    //用户注册返回
    struct SCRegisterRsp : public NetworkMessage
    {
        //注册结果（true-成功， false-失败）
        uint8 register_result;

        int byteSize()
        {
            return sizeof(register_result);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << register_result;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> register_result;
        }
    };

    /**
    * ● 角色创号系统(6 message)
    */

    //请求获取一个随机名字
    struct CSGetRandomNameReq : public NetworkMessage
    {
        //获取的性别
        uint8 gender;
        //获取的类别
        uint8 type;

        int byteSize()
        {
            return sizeof(gender) + sizeof(type);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << gender;
            w << type;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> gender;
            r >> type;
        }
    };

    //返回一个随机名字
    struct SCGetRandomNameRsp : public NetworkMessage
    {
        //随机名字
        std::string random_name;

        int byteSize()
        {
            return (random_name.length() + 2);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << random_name;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> random_name;
        }
    };

    //发送创建角色的请求
    struct CSCreateCharacterReq : public NetworkMessage
    {
        //昵称
        std::string nickname;
        //性别
        uint8 gender;
        //信仰
        uint8 belief;
        //角色类型（职业）
        uint8 character_type;

        int byteSize()
        {
            return (nickname.length() + 2) + sizeof(gender) + sizeof(belief) + sizeof(character_type);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << nickname;
            w << gender;
            w << belief;
            w << character_type;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> nickname;
            r >> gender;
            r >> belief;
            r >> character_type;
        }
    };

    //创建角色返回
    struct SCCreateCharacterRsp : public NetworkMessage
    {
        //结果
        uint8 result;

        int byteSize()
        {
            return sizeof(result);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << result;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> result;
        }
    };

    //请求检查昵称是否存在
    struct CSCheckNicknameExistReq : public NetworkMessage
    {
        //昵称
        std::string nickname;

        int byteSize()
        {
            return (nickname.length() + 2);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << nickname;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> nickname;
        }
    };

    //返回昵称检查结果
    struct SCCheckNicknameExistRsp : public NetworkMessage
    {
        //结果
        uint8 result;

        int byteSize()
        {
            return sizeof(result);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << result;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> result;
        }
    };

    /**
    * ● PHP后台(0 message)
    */

    /**
    * ● 系统(2 message)
    */

    //错误通知
    struct SCErrorNotify : public NetworkMessage
    {
        //错误码
        uint32 error_code;

        int byteSize()
        {
            return sizeof(error_code);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << error_code;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> error_code;
        }
    };

    //扩展的错误通知
    struct SCErrorExNotify : public NetworkMessage
    {
        //错误码
        uint32 error_code;
        //错误原因
        std::string reason;

        int byteSize()
        {
            return sizeof(error_code) + (reason.length() + 2);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << error_code;
            w << reason;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> error_code;
            r >> reason;
        }
    };

    /**
    * ● 角色属性(2 message)
    */

    //请求玩家属性
    struct CSPropertiesReq : public NetworkMessage
    {

        int byteSize()
        {
            return 0;
        }

        void encode(byte* buffer, size_t size)
        {
        }

        void decode(const byte* buffer, size_t size)
        {
        }
    };

    //玩家属性返回
    struct SCPropertiesRsp : public NetworkMessage
    {
        //宇宙币
        uint64 coins;
        //等级
        uint32 level;
        //宇宙气（经验值）
        uint32 exp;

        int byteSize()
        {
            return sizeof(coins) + sizeof(level) + sizeof(exp);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << coins;
            w << level;
            w << exp;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> coins;
            r >> level;
            r >> exp;
        }
    };

}

#endif    //__PROTOCOL_H__