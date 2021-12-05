/*
 * my_accessory.c
 * Define the accessory in C language using the Macro in characteristics.h
 *
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 *      
 *  Modified on: 2021-11-26
 *      Author: Rohaizan Roosley
 *
 */

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
	printf("accessory identify\n");
}

homekit_characteristic_t cha_current_position_x = HOMEKIT_CHARACTERISTIC_(CURRENT_POSITION, 0);
homekit_characteristic_t cha_target_position_x = HOMEKIT_CHARACTERISTIC_(TARGET_POSITION, 0);
homekit_characteristic_t cha_position_state_x = HOMEKIT_CHARACTERISTIC_(POSITION_STATE, 0);
homekit_characteristic_t cha_name_x = HOMEKIT_CHARACTERISTIC_(NAME, "Left Blinds");

homekit_characteristic_t cha_current_position_y = HOMEKIT_CHARACTERISTIC_(CURRENT_POSITION, 0);
homekit_characteristic_t cha_target_position_y = HOMEKIT_CHARACTERISTIC_(TARGET_POSITION, 0);
homekit_characteristic_t cha_position_state_y = HOMEKIT_CHARACTERISTIC_(POSITION_STATE, 0);
homekit_characteristic_t cha_name_y = HOMEKIT_CHARACTERISTIC_(NAME, "Right Blinds");

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_bridge, .services=(homekit_service_t*[]) {
      HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Multiple Ikea Blinds"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Rohaizan Technology"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "26112012"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
        NULL
    }),
    HOMEKIT_ACCESSORY(.id=2, .category=homekit_accessory_category_window, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Left Blinds"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Rohaizan Technology"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "26112012"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
    		HOMEKIT_SERVICE(WINDOW, .primary=true, .characteristics=(homekit_characteristic_t*[]){
    			&cha_current_position_x,
    			&cha_target_position_x,
    			&cha_position_state_x,  
    			&cha_name_x,
    			NULL
    		}),
        NULL
    }),
	 HOMEKIT_ACCESSORY(.id=3, .category=homekit_accessory_category_window, .services=(homekit_service_t*[]) {
         HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
             HOMEKIT_CHARACTERISTIC(NAME, "Right Blinds"),
             HOMEKIT_CHARACTERISTIC(MANUFACTURER, "Rohaizan Technology"),
             HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "26112012"),
             HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266"),
             HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
             HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
             NULL
         }),
    	 	HOMEKIT_SERVICE(WINDOW, .primary=true, .characteristics=(homekit_characteristic_t*[]){
    	 		&cha_current_position_y,
    	 		&cha_target_position_y,
    	 		&cha_position_state_y,  
    	 		&cha_name_y,
    	 		NULL
  	 	  }),
        NULL
     }),
    NULL
};

homekit_server_config_t config = {
		.accessories = accessories,
		.password = "111-11-111"
};
