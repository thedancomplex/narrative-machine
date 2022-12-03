#define NM_YAMAHA_DD5_CLASS 1
#include <lofaro_dynamixel_ach_client.h>
#include <unistd.h>
#include <string.h>


#define DD5_MOT_NUM 254
#define DD5_HEADER "DD5: "

#define STICK_0 4

enum{
  DD5_OK   = 0,
  DD5_FAIL = 1
}

typedef struct mot_info_def {
    double pos_down;
    double pos_up;
    double tor;
    double vel;
    double dir;
}__attribute__((packed)) mot_info_def_t;

typedef struct mot_def {
    mot_info_def_t mot[DD5_MOT_NUM];
}__attribute__((packed)) mot_def_t;


class NarrativeMachineYamahaDD5
{
  public:
    NarrativeMachineYamahaDD5();

    /* Turn System On */
    int on();
    int on( bool low-latency );

    /* Calibrate Motor */
    int calibrate(mot_def_t *data, int mot);

  private:
    mot_def_t mot_calibrate;
    DynamixelAchClient dac;
    int addMotor(int mot);

    bool do_debug = true;
}
