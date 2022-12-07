#define NM_YAMAHA_DD5_CLASS 1
#include <lofaro_dynamixel_ach_client.h>
#include <unistd.h>
#include <string.h>




class NarrativeMachineYamahaDD5
{
  #define DD5_MOT_NUM 254
  #define DD5_HEADER "DD5: "
  #define MOT_ID_STICK_0          5
  #define MOT_ID_STICK_1          3 
  #define MOT_VEL                 100.0
  #define MOT_TOR                 0.4
  #define MOT_VEL_CALIBRATE       0.5
  #define MOT_TOR_CALIBRATE       0.15
  #define MOT_POS_UP_CALIBRATE   -0.2
  #define MOT_POS_DOWN_CALIBRATE  0.2
  #define MOT_HIT_OFFSET_UP       0.05
  #define MOT_HIT_OFFSET_DOWN     0.05
  #define MOT_HIT_TIME            0.04
  #define DEFAULT_RATE            250.0

  enum{
    DD5_OK   = 0,
    DD5_FAIL = 1,
    DD5_STICK_UP = 2,
    DD5_STICK_DOWN = 3,
    DD5_ENUM_COUNT
  }__attribute__((packed)) dd5_enum_t;

  typedef struct mot_info_def {
    double pos_down;
    double pos_up;
    double tor;
    double vel;
    double dir;
    double offset_down;
    double offset_up;
  }__attribute__((packed)) mot_info_def_t;

  typedef struct mot_def {
    mot_info_def_t mot[DD5_MOT_NUM];
  }__attribute__((packed)) mot_def_t;

  typedef struct midi_def {
    int16_t message;
    int16_t status;
    int16_t data0;
    int16_t data1;
  }__attribute__((packed)) midi_def_t;

  typedef struct stick_def {
    int16_t stick;
    double dt;
    double velocity;
    double force;
  }__attribute__((packed)) stick_def_t;

  typedef struct hit_def {
    midi_def_t midi;
    stick_def_t stick;
  }__attribute__((packed)) hit_def_t;

  typedef struct hit_tracking_stick_def {
    bool do_hit;
    bool in_hit;
    bool in_hit_previous;
    double dt;
    double t;
  }__attribute__((packed)) hit_tracking_stick_def_t;

  typedef struct hit_tracking_def {
    hit_tracking_stick_def_t stick[DD5_MOT_NUM];
  }__attribute__((packed)) hit_tracking_def_t;

  public:
    NarrativeMachineYamahaDD5();

    /* Turn System On */
    int on();
    int on( int mot );

    /* Turn System Off */
    int off();

    /* Calibrate Motor */
    int calibrate(int mot);

    /* Hit */
    int hit(int mot);
    int hit_loop(int mot);
    int hit_blocking(int mot);

    /* Sleep */
    int sleep(double val);

    /* Add motor */
    int add(int mot);

    /* Update Loop */
    int loop();

  private:
    mot_def_t mot_calibrate;
    hit_def_t stick_hit;
    hit_tracking_def_t stick_hit_tracking;
    DynamixelAchClient dac = DynamixelAchClient();
    
    int addMotor(int mot);

    bool do_debug = true;

    /* Calibrate Motor */
    // int calibrate(mot_def_t *data, int mot);
};
