#ifndef DEFINITION_H
#define DEFINITION_H
#include <QString>
#include <QMap>
#include <QStringList>

namespace AppDefinition
{

    namespace BINS
    {
        const QString   PHI                 = "phi",
                        LYAMBDA             = "lyambda",
                        HEADING             = "heading",
                        PITCH               = "pitch",
                        ROLL                = "roll",
                        SPEEDNORTH          = "speedNorth",
                        SPEEDEAST           = "speedEast",
                        CONNWITHBINS        = "ConnWithBINS",
                        INITCOORDINATE      = "InitCoordinate",
                        READYSTATUS         = "ReadyStatus",
                        BINSREGIM           = "BINSRegim",
                        LAGDATASTATUS       = "LagDataStatus",
                        SNSDATASTATUS       = "SNSDataStatus",
                        COMCONNECTSTATUS    = "COMConnectStatus";

        enum
        {
            phi = 0,
            lyambda,
            heading,
            pitch,
            roll,
            speedNorth,
            speedEast,
            ConnWithBINS,
            InitCoordinate,
            ReadyStatus,
            BINSRegim,
            LagDataStatus,
            SNSDataStatus,
            ComConnectionStatus
        };

        /*!
          \brief - Ассоциативная карта - LABELS
          \details Служит для того, чтобы записывать данные в модель
          BINSDataModel в том порядке, в котором мне нужно
        */
        const QMap<int, QString>    LABELS
        {
            { phi,                  PHI},
            { lyambda,              LYAMBDA},
            { heading,              HEADING},
            { pitch,                PITCH},
            { roll,                 ROLL},
            { speedNorth,           SPEEDNORTH},
            { speedEast,            SPEEDEAST},
            { ConnWithBINS,         CONNWITHBINS},
            { InitCoordinate,       INITCOORDINATE},
            { ReadyStatus,          READYSTATUS},
            { BINSRegim,            BINSREGIM},
            { LagDataStatus,        LAGDATASTATUS},
            { SNSDataStatus,        SNSDATASTATUS},
            { ComConnectionStatus,  COMCONNECTSTATUS}
        };

        const QStringList TableLabels
        {
            PHI,
            LYAMBDA,
            HEADING,
            PITCH,
            ROLL,
            SPEEDNORTH,
            SPEEDEAST,
            CONNWITHBINS,
            INITCOORDINATE,
            READYSTATUS,
            BINSREGIM,
            LAGDATASTATUS,
            SNSDATASTATUS,
            COMCONNECTSTATUS
        };


    }

    namespace controlBINS
    {
        enum class BitDescr
        {
            INITIAL_HEAD = 0,
            SNS_PRIORITY,
            CHANGE_SNS_PR,
            REGIM,
            SPEED_PRIORITY,
            CHANGE_LAG_PR,
            INIT_RESET,
            GIRO_RGM,
            HARD_RESET,
            RS_PRIORITY,
            USE_HEIGHT
        };

        #pragma pack(push,1)

        // Эту структуру отправляем в драйвер БИНСа
        struct OperateData
        {
            float   initLatitude    = 0,
                    initLongitude   = 0,
                    initHead        = 0,
                    height          = 69,
                    controlWord     = 0;

        };
        #pragma pack(pop)

    }

    namespace recFolderParam
    {
        const QString   FOLDERNAME = "Data";
    }

    namespace JSONFileNames
    {
        const QString   CONNECTION = "./config.json";
        const QString   REPERDATA = "./ReperData.json";
    }

    namespace SNS
    {
        const QString   LATITUDE    = "latitude",
                        LONGITUDE   = "longitude",
                        ABS_SPEED   = "absSpeed",
                        NORTH_SPEED = "northSpeed",
                        EAST_SPEED  = "eastSpeed",
                        STATUS      = "status";

        enum
        {
            latitude = 0,
            longitude,
            absSpeed,
            northSpeed,
            eastSpeed,
            status
        };

        const QMap<int, QString>    LABELS
        {
            { latitude,     LATITUDE },
            { longitude,    LONGITUDE },
            { absSpeed,     ABS_SPEED },
            { northSpeed,   NORTH_SPEED },
            { eastSpeed,    EAST_SPEED },
            { status,       STATUS }
        };

        const QStringList TableLabels
        {
            "Широта, град.",
            "Долгота, град.",
            "Абсолютная скорость, м/с",
            "Северная скорость, м/с",
            "Восточная скорость, м/с",
            "Признак достоверности:"
        };
    }

    namespace LAG
    {
        const QString   SPEED_VX            = "speedVx",
                        SPEED_VZ            = "speedVz",
                        SPEED_VY            = "speedVy",
                        SPEED_VALID         = "speedValid",
                        HEIGHT_VALID        = "heightValid",
                        REVERBERATION_SOLID = "reverberationSolid",
                        PWM_ENABLE          = "pwmEnable";

        enum
        {
            speedVx = 0,
            speedVz,
            speedVy,
            speedValid,
            heightValid,
            reverberationSolid,
            pwmEnable
        };

        const QMap<int, QString>    LABELS
        {
            { speedVx,              SPEED_VX },
            { speedVz,              SPEED_VZ },
            { speedVy,              SPEED_VY },
            { speedValid,           SPEED_VALID},
            { heightValid,          HEIGHT_VALID},
            { reverberationSolid,   REVERBERATION_SOLID},
            { pwmEnable,            PWM_ENABLE}
        };

        const QStringList TableLabels
        {
            "Скорость Vx, м/с",
            "Скорость Vy, м/с",
            "Скорость Vz, м/с",
            "Признак валидности скорости:",
            "Признак валидности высоты:",
            "Признак решения по объемное реверберации:",
            "Признак глобального разрешения излучения"
        };
    }

}

#endif // DEFINITION_H
