// Generate by the sword of core(核心之刃). DO NOT EDIT!
// Source : Protocol.h
// Comment : 在此处输入注释...

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <venus_net/venus_net.h>

namespace GameEncoder
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
    * ● 登录/注册(4 message)
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

        int byteSize()
        {
            return sizeof(login_result) + sizeof(player_id);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << login_result;
            w << player_id;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> login_result;
            r >> player_id;
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
    struct SCCeateCharacterRsp : public NetworkMessage
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

}

#endif    //__PROTOCOL_H__