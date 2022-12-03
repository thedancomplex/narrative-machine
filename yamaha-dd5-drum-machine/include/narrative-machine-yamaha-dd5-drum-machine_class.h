#define NM_YAMAHA_DD5_CLASS 1

#define DD5_MOT_NUM 254
typedef struct mot_def {
    double pos_down[DD5_MOT_NUM];
    double pos_up[DD5_MOT_NUM];
    double tor[DD5_MOT_NUM];
    double vel[DD5_MOT_NUM];
    int    id_list[DD5_MOT_NUM];
}__attribute__((packed)) mot_def_t;


class NmYamahaDD5
{
  public:
    NmYamahaDD5();

  private:
}
