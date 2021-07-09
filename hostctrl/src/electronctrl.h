#ifndef __is_included__d3cf826b_df20_11eb_ba7e_b499badf00a1
#define __is_included__d3cf826b_df20_11eb_ba7e_b499badf00a1 1

#ifndef __cplusplus
    #ifndef true
        typedef unsigned char bool;
        #define true 1
        #define false 0
    #endif
#endif

#ifdef __cplusplus
    extern "C" {
#endif

enum egunError {
    egunE_Ok                        = 0,

    egunE_Failed,
    egunE_OutOfMemory,
    egunE_ConnectionError,
    egunE_InvalidParam,
};

enum egunPolarity {
    egunPolarity_Pos,
    egunPolarity_Neg
};

struct electronGun;
struct electronGun_VTBL;

typedef enum egunError (*electronGun_Release)(
    struct electronGun* lpSelf
);
typedef enum egunError (*electronGun_RequestID)(
    struct electronGun* lpSelf
);
typedef enum egunError (*electronGun_GetCurrentVoltage)(
    struct electronGun* lpSelf,
    unsigned long int dwPSUIndex
);
typedef enum egunError (*electronGun_GetCurrentCurrent)(
    struct electronGun* lpSelf,
    unsigned long int dwPSUIndex
);
typedef enum egunError (*electronGun_SetPSUPolarity)(
    struct electronGun* lpSelf,
    unsigned long int dwPSUIndex,
    enum egunPolarity polPolarity
);
typedef enum egunError (*electronGun_SetPSUEnabled)(
    struct electronGun* lpSelf,
    unsigned long int dwPSUIndex,
    bool bEnable
);


struct electronGun_VTBL {
    electronGun_Release             release;
    electronGun_RequestID           requestId;
    electronGun_GetCurrentVoltage   getCurrentVoltage;
    electronGun_GetCurrentCurrent   getCurrentCurrent;
    electronGun_SetPSUPolarity      setPSUPolarity;
    electronGun_SetPSUEnabled       setPSUEnabled;
};

struct electronGun {
    struct electronGun_VTBL*        vtbl;
    void*                           lpReserved;
};

enum egunError egunConnect_Serial(
    struct electronGun** lpOut,
    char* lpPort
);

#ifdef __cplusplus
    } /* extern "C" { */
#endif

#endif /* #ifndef __is_included__d3cf826b_df20_11eb_ba7e_b499badf00a1 */
