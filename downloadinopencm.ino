#include <DynamixelWorkbench.h>

#define DEVICE_NAME "3" 
#define BAUDRATE 1000000
#define DXL_ID_1 1
#define DXL_ID_2 2
#define DXL_ID_3 3
#define DXL_ID_4 4
#define DXL_ID_5 5

DynamixelWorkbench dxl_wb;

int id_1 = 2048;
int id_2 = 2048;
int id_3 = 2048;
int id_4 = 512;
int id_5 = 512;

const uint8_t handler_index_speed = 0;
int32_t goal_speed[5] = {16, 12, 12, 16 ,60}; //Массив скоростей

const uint8_t handler_index_pos = 1;
int32_t goal_position[5] = {id_1, id_2, id_3, id_4, id_5}; //Массив положения 


int32_t data_packet[5] = {0, 0, 0 ,0 ,0};
 
void setup() {
  Serial.begin(115200);
  //while(!Serial);

  const char *log;
  bool result = false;
  uint16_t model_number = 0;
  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  
for (int i = 1; i <= 5; i++) {
  uint8_t dxl_id = i;
  result = dxl_wb.ping(dxl_id,&model_number, &log);
}

for (int i = 1; i <= 5; i++) {
  uint8_t dxl_id = i;
  result = dxl_wb.jointMode(i, 0, 0, &log);
}

result = dxl_wb.addSyncWriteHandler(1, "Moving_Speed", &log); //Обработчик скоростей
result = dxl_wb.syncWrite(handler_index_speed, goal_speed, &log); // метод отправки скоростей 
result = dxl_wb.addSyncWriteHandler(1, "Goal_Position", &log); //Обработчик положений (синхронный)


}

void loop() {
 Set_Pos();
 delay(6000);
 goal_position[0] = 1900;
 Set_Pos();
 delay(6000);
 goal_position[0] = id_1;
 Set_Pos();
 delay(6000);
}

void Set_Pos() {
  const char *log;
  bool result = false;
  result = dxl_wb.syncWrite(handler_index_pos, goal_position, &log);
}

void get_data_load(int32_t* data_array, char* table_pos)
{
  for(int cnt = 0; cnt < 5; cnt++) {
    int32_t get_present_load = 0;
    dxl_wb.itemRead(cnt++, "Present_Load", &get_present_load);
    data_array[cnt] = get_present_load;
    
  }
}
