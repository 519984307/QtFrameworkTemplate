﻿//
//  EventTrack-C-Interface.h
//  Billfish
//
//  Created by luqi on 2021/1/16.
//

#ifndef EventTrackCInterface_h
#define EventTrackCInterface_h
#include <QString>
#include <QMap>
#include <QVariantMap>

const char RSA_PUB_KEY[] = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEArfJ20CDphWthi2GYA93qJL5vpOqk1/HQ0Qo3ZfV61aQ66KGoiPtCkjsoZJXQBN25tq/H1tvN31JTgAT7LxePBBP6//E9nmDEDdCynV0XDuTdJCkTUC+dfw13b5TQOCN/Vr43iRB8d21Lrt4HtW/0sVY11jLThYnEadZ95Hv3Q9ehvk60zumaav+lskG8Dv1/V5tZCSfcRV4c5Se+3LuIrPKlE09yUokpBlsjqMfM7zH51R599PaIdL7FKPXNVeY0D/jfyxKN5VZlfC1UzTOno6j5/Iv28aD18OBRdq/vaO7LL/acMQShg1lfcXcE9OQIUOSKK+vBBIkdfAFyTyjxFQIDAQAB";

const char RSA_PRI_KEY[] = "MIIEowIBAAKCAQEAz2ai9FJQXt3wVFN+O5CGu4zfSqiDw5mZj56mIDrnp7j9nklYDvmIbULRibiMUVotASCEZqMJVQipvanFB9rkU6t2DM99xWCiU5ajgv/NQed0lnMF/CeGLv8HPUvONweI8QLCcQuFAXGY++nW3vaTlWJf7ROoWZhB8K1IDHnBIBU31SqcSWTQLvsqVe3ZabWwaBoI7s8CwgsEivuulF+aSucD6jomXmuIIaCp/BaryWgHlbtTBaT7nQzESL2gX77rRIB1/HjwWKmigor/CBFo+jbquVJyZniP2XDHB6Rm/rd5U4MkoLPGBkkQjrJlQ7chdMSb+6sWf56hbkI5JDcUKwIDAQABAoIBAF7Mx0duKJZ0U9n3oAeR9EPeDGKPzEqn9u0S01SAGEst359uXvXZUWa/2A9fb6Pv2Apf1qUjeKyJnSy4YPtKLnugMAGDBjYmCYyzmmHSkvvA1CXAxceQOWFZ6PE3qTa2Fv4zCLWrUkxqpEbhh/m6M5NguAAhsB3j3qAoVHp/XKtQtAgXFLMOyK/Fyv6mSifjQ868gQFyGz8zzkDO6n1tAvkEBHocFiJMtDywA8NQRLFY5Ob7+VZf/bOFAVDpJQsHxOgvpTFCvhmDHc5+Sj6Sn0UH3iq3uMVBwUYkuW6BOGCn/HtJ0cnFYTIpy/udNCEyjRMpdp/0qfPNngATCyeeSsECgYEA/B0v2tQlQbjZr3YbATP/uUZ0UVbSf5TYRV7sSaPV7sbUez2CmTu51eVuGu7yc2GZZgtawmyE54mKNasBkCAfE55tx9xPR7ReRWynWt/UhTEEbtndb0xjL/bYAXOuAysNJOcnXbMN315E256DchVAjPuMMly7NmPpYty3Rjx54aMCgYEA0pkEUgBp4LgeLLokd8J3WAZDgqB4se2oxRSibGOARCC1rcedVJwfrU0De/uSJ4FLYacVdgR79oL+S0rjFZRkd1qxllxCALr7WI89XdWb53JPaPKD66THRyMeOkl0OpXkiNUt9kaifdHMF+eGW/etqhAVofotw+/jce6MDJ9k+9kCgYATFZ6GwSJk3DpWRul6aNZFzyiE876Re9H3Rl06odVS8ugowBo/wT6rC2gPT+E4jL3Q9LEVIKPa5xV4RI6ku1m+4XJL+8hglC3CsZvljCYJQxGj1oglobGsctIdIgWdJcgj7/+R3zkAnKE3wsMOgr9VLMGLGmvtjRigrDaPcYqEYwKBgCF5Yv9pw2qNuXYgjEVg6rlaHYb43NZjUU0qL3sNAclSba5WqUJWoo5YTHJ7lUqkOYgnF7kvk0imn6b2G0xFzwZNqyacOX2GOwdjlTyCBIrwV4D181QUV/yNr3NSU6AwTSgWwnx/07ouC8PM8EVUBA2hCt85NecMDVoBsc8b0uBZAoGBAKQncZCk5tF0q1BCn7foa6o9bEDv8NkJLtNmGPC1gw+3SuXGw1fHpCVa7+ZJCQ+mY55A7bsnpSMpwK52MWm0ygo39wVAJhDEJu5KF+AyTPDD97sj16XWAWVBcriCntlMTYilXkLeihfQf49GA2Q0BQ1xIWuzN6KA2swu7AkDm5lo";

void setupTracker();
void trackKeyValueEvent(const char* event_id);
void trackKeyValueEventWithProps(const char* event_id ,const QVariantMap&);
void flush();

void trackInstallEvent();
void trackLaunchEvent();
void trackTerminateEvent();
void clearSubprocessCrash();

const char* getMid();
const char Event_Soft_Resolution[] = "BSoftResolution";


#endif /* EventTrack_C_Interface_h */
