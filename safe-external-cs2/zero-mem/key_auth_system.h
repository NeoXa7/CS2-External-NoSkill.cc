#pragma once
#include <libs/lazy.h>
#include <libs/keyauth.cc/auth.hpp>
#include <libs/keyauth.cc/skStr.h>
#include <libs/keyauth.cc//utils.hpp>
#include <libs/xorstr.h>
#include <utils/console.h>

std::string name = xorstr_("NoSkill.cc");
std::string ownerid = xorstr_("bv6UWJfoiz");
std::string secret = xorstr_("9e06931b982d57acf48d8f92dd86d1687e4f78cc3a4d1097ce99e9fa601e5b1d");
std::string version = xorstr_("1.0");
std::string url = xorstr_("https://keyauth.win/api/1.3/");
std::string path = xorstr_("");

KeyAuth::api KAA(name, ownerid, version, url, path);

std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10); // long

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}

void sessionStatus() {
    KAA.check(true); // do NOT specify true usually, it is slower and will get you blocked from API
    if (!KAA.response.success) {
        LI_FN(printf).get()(KAA.response.message.c_str());
    }

    if (KAA.response.isPaid) {
        while (true) {
            Sleep(20000); // this MUST be included or else you get blocked from API
            KAA.check();
            if (!KAA.response.success) {
                LI_FN(printf).get()(KAA.response.message.c_str());
            }
        }
    }
}


const std::string compilation_date = (std::string)xorstr_(__DATE__);
const std::string compilation_time = (std::string)xorstr_(__TIME__);