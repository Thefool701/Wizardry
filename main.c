#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Offset Definitions
#define GB_MAX_SIZE (32 * 1024 * 1024)
#define GB_HEADER_START 0x100
#define GB_TITLE_OFFSET 0x134
#define GB_MANUFACTURER_CODE_OFFSET 0x13F
#define GB_CGB_FLAG_OFFSET 0x143
#define GB_NEW_LICENSE_CODE_OFFSET 0x144
#define GB_SGB_FLAG_OFFSET 0x146
#define GB_CARTRIDGE_TYPE_OFFSET 0x147
#define GB_ROM_SIZE 0x148
#define GB_RAM_SIZE 0x149
#define GB_DESTINATION_CODE 0x14A
#define GB_OLD_LICENSE_CODE_OFFSET 0x14B
#define GB_MASK_ROM_VERSION_NUMBER 0x14C
#define GB_CHECKSUM_OFFSET 0x14D

// Game Boy emulator memory structure (simplified)
typedef struct {
  uint8_t *rom_data;         // ROM data
  char title[17];            // Game Title
  char manufacturer_code[5]; // Manufacturer Code(Purpose Unknown)
  uint32_t cgb_flag;
  char licensee_code[3];
  uint32_t sgb_flag;
  uint8_t cart_type;
  size_t rom_size; // ROM size
  size_t ram_size; // RAM size
  uint8_t dest_code;
  uint64_t mask_rom_version_number;
} GameBoy;

// Map ROM size code to bytes
uint32_t get_rom_size(uint8_t code) {
  if (code <= 0x08) {
    return 32 * (1 << code);
  }
  return 0; // Invalid
}

// Map RAM size code to bytes
uint32_t get_ram_size(uint8_t code) {
  // Check cartridge type

  // Then Specify RAM Size
  return 0; // Invalid
}

// Read and validate ROM file

// Read file

// Get file size

// Validate File Size

// Allocate memory

// Read ROM
// Extract header info
// Validate checksum
// Print ROM info

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Usage: %s <gamefile>\n", argv[0]);
    printf("Example: %s  pokemon_red.gb", argv[0]);
  }
}
