#ifndef EXCHANGESTRUCT_H
#define EXCHANGESTRUCT_H

namespace DriverExchange
{
    #pragma pack(push,1)

    struct DataFromBINS
    {
        float   phi             = 0,
                lyambda         = 0,
                heading         = 0,
                pitch           = 0,
                roll            = 0,
                speedNorth      = 0,
                speedEast       = 0;

        int     COMStatusWord   = 0,
                ethStatusWord   = 16;

        bool    ComConnection   = false;

    };

    #pragma pack(pop)

    #pragma pack(push, 1)
        struct DataFromSNS
        {
            double       latitude        = 0;
            double       longitude       = 0;
            float        absSpeed        = 0;
            double       northSpeed      = 0;
            double       eastSpeed       = 0;
            unsigned int status          = 2;   // 0 - есть соединение
                                                // 1 - ошибка
                                                // 2 - нет соединения

        };

    #pragma pack(pop)

    enum ConnectionQuality {Good, Norm, Bad, NoConnection};

    struct FlagsFromLag {
        bool
            is_velocity_valid : 1,  //Признак валидности скорости
            is_altitude_valid : 1,  //Признак валидности высоты
            is_volume_solve   : 1,  //Признак решения по объёмной реверберации (1 - расчёт по ОР)
            is_pwm_global     : 1,  //Признак глобального разрешения излучения
            is_pwm_shoot      : 1,  //Признак разрешения излучения для текущего выстрела
            is_salinity       : 1,  //Признак расчёта скорости звука по солёности и температуре
            is_temp_alert     : 1;  //Признак превышения рабочей температуры

    };

    #pragma pack(push, 1)
        struct DataFromLag
        {
            float   speed[3] = {0};
            float   altitude_m = 0;
            float   t_env_deg = 0,
                    t_dev_deg = 0;
            float   soundvel_ms = 0;

            ConnectionQuality connectionQuality = ConnectionQuality::NoConnection;

            uint32_t count_tx = 0;
            FlagsFromLag flags;

        };

    #pragma pack(pop)

}

#endif // EXCHANGESTRUCT_H
