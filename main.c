/*
    hex-lexer
    Copyright (C) 2024 Gabriel Jickells

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>

int main(int argc, char** argv) {

	if(argc != 3) {
		fprintf(stderr, "Usage: %s <INPUT FILE> <OUTPUT FILE>\n", argv[0]);
		return -1;
	}

	#define SOURCE_FILE_INDEX 1
	#define OUT_FILE_INDEX 2

	FILE* source_file = fopen(argv[SOURCE_FILE_INDEX], "r");
	if(!source_file) {
		fprintf(stderr, "Error: Could not open source file \"%s\"\n", argv[SOURCE_FILE_INDEX]);
		return -1;
	}

	FILE* output_file = fopen(argv[OUT_FILE_INDEX], "w");
	if(!output_file) {
		fprintf(stderr, "Error: Could not open output file \"%s\"\n", argv[OUT_FILE_INDEX]);
		return -1;
	}

	#define SRC_CHARS_PER_BYTE 2
	char source_buffer[SRC_CHARS_PER_BYTE] = {0};
	int current_char; // needed to check for EOF
	int shift_amount;

	unsigned char output_byte;

	#define STATE_STOPPED 0
	#define STATE_READ 1
	#define STATE_WORK 2	
	int state = STATE_READ;

	while(state != STATE_STOPPED) {

		switch(state) {

			case STATE_READ:

				state = STATE_WORK;

				for(int i = 0; i < SRC_CHARS_PER_BYTE; i++) {

					current_char = fgetc(source_file);
					if(current_char == EOF) {
						state = STATE_STOPPED;
						break;
					}

					if((current_char >= '0' && current_char <= '9') ||
					   (current_char >= 'a' && current_char <= 'f') ||
					   (current_char >= 'A' && current_char <= 'F'))
						source_buffer[i] = (char)current_char;
					else i--;
					// decrementing i prevents the premature termination of the
					// loop in the event of an invalid character

				}

				break;

			case STATE_WORK:

				state = STATE_READ;
				output_byte = 0;

				for(int i = 0; i < SRC_CHARS_PER_BYTE; i++) {

					#define BITS_PER_HEX_DIGIT 4
					// an extra one is taken away to account for the SRC_CHARS_PER_BYTE
					// having a minimum count of 1 and i starting at 0
					shift_amount = (SRC_CHARS_PER_BYTE - 1 - i) * BITS_PER_HEX_DIGIT;

					if(source_buffer[i] >= '0' && source_buffer[i] <= '9')
						// in ASCII, a number added to the character to 0 gives
						// the character for that number
						output_byte |= (source_buffer[i] - '0') << shift_amount;
					if(source_buffer[i] >= 'A' && source_buffer[i] <= 'F')
						// same logic as for the numbers except 10 is added because
						// A in hexadecimal means 10
						output_byte |= (source_buffer[i] + 10 - 'A') << shift_amount;
					if(source_buffer[i] >= 'a' && source_buffer[i] <= 'f')
						output_byte |= (source_buffer[i] + 10 - 'a') << shift_amount;

				}

				if(fputc(output_byte, output_file) == EOF) {
					fprintf(stderr, "Error: Could not write to output file\n");
					return -1;
				}

				break;

			default:
				break;

		}
	}

	return 0;

}
