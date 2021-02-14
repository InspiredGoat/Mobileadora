#include "../include/library_internal.h"

// input definitions
const Input JOYSTICK = {
	INPUT_JOYSTICK,
	sizeof(short) * 2
};

// TODO: revise this, using clients_data right now so that new data is only accessed when l_poll occurs
bool l_input_get(unsigned int client_index, InputType type, unsigned char input_index, unsigned char* data) {
	unsigned long index = 0;
	unsigned int input_size_sum = 0;
	unsigned char inputs_of_type_count = 0;

	if(client_index > 0 && client_index < clients_size) {
		for(unsigned int i = 0; i < client_index; i++) {
			index += clients[i].frame->input_size;
		}

		for(unsigned char i = 0; i < clients[client_index].frame->input_count; i++) {
			if(clients[client_index].frame->inputs[i].type == type) {
				if(inputs_of_type_count == input_index) {
					for(unsigned int j = 0; j < clients[client_index].frame->inputs[i].size; j++)
						data[j] = (unsigned char) clients_data[index];

					return 1;
				}
				inputs_of_type_count++;
			}

			input_size_sum += clients[client_index].frame->inputs[i].size;
		}
	}

	return 0;
}


Input l_input_joystick_create() {
	return JOYSTICK;
}

bool l_input_joystick_get(unsigned int client_index, unsigned char input_index, float* x_value, float* y_value) {
	unsigned char data[JOYSTICK.size];
	bool res = l_input_get(client_index, INPUT_JOYSTICK, input_index, data);

	short x = data[0];
	short y = data[2];
	*x_value = (float) x;
	*y_value = (float) y;

	return res;
}
