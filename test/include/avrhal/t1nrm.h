#ifndef _LIBAVRHAL_T1NRM_MOCK
#define _LIBAVRHAL_T1NRM_MOCK

typedef enum
{
  HAL_T1NRM_PRESC_NONE,
  HAL_T1NRM_PRESC_1,
  HAL_T1NRM_PRESC_8,
  HAL_T1NRM_PRESC_64,
  HAL_T1NRM_PRESC_256,
  HAL_T1NRM_PRESC_1024,
} hal_t1nrm_prescaller_t;

void hal_t1nrm_run(hal_t1nrm_prescaller_t presc);
void hal_t1nrm_set(uint16_t value);
void hal_t1nrm_stop(void);

#endif