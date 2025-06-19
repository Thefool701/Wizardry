#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROM_SIZE (32 * 1024 * 1024) // 32MB max for GBA
#define GB_HEADER_START 0x100           // Header start offset
#define GB_TITLE_OFFSET 0x134           // Game title (16 bytes)
#define GB_CART_TYPE_OFFSET 0x147       // Cartridge type
#define GB_ROM_SIZE_OFFSET 0x148        // ROM size code
#define GB_RAM_SIZE_OFFSET 0x149        // RAM size code
#define GB_CHECKSUM_OFFSET 0x14D        // Header checksum

// Game Boy emulator memory structure (simplified)
typedef struct {
  uint8_t *rom_data;       // ROM data
  size_t rom_size;         // ROM size in bytes
  char title[17];          // Game title (null-terminated)
  uint8_t cart_type;       // Cartridge type (MBC)
  uint32_t rom_bank_count; // Number of ROM banks
  uint32_t ram_size;       // RAM size in bytes
} GameBoy;

// Map ROM size code to bytes
uint32_t get_rom_size(uint8_t code) {
  if (code <= 0x08) {
    return 32 * 1024 << code; // 32KB * 2^code
  }
  return 0; // Invalid
}

// Map RAM size code to bytes
uint32_t get_ram_size(uint8_t code) {
  switch (code) {
  case 0x00:
    return 0;
  case 0x01:
    return 2 * 1024; // 2KB (unused)
  case 0x02:
    return 8 * 1024; // 8KB
  case 0x03:
    return 32 * 1024; // 32KB
  case 0x04:
    return 128 * 1024; // 128KB
  case 0x05:
    return 64 * 1024; // 64KB
  default:
    return 0;
  }
}

// Read and validate ROM file
int load_rom(GameBoy *gb, const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    fprintf(stderr, "Error: Could not open file %s\n", filename);
    return 0;
  }

  // Get file size
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  // Validate size
  if (size <= GB_HEADER_START || size > MAX_ROM_SIZE) {
    fprintf(stderr, "Error: Invalid ROM size (%ld bytes)\n", size);
    fclose(file);
    return 0;
  }

  // Allocate memory
  gb->rom_data = malloc(size);
  if (!gb->rom_data) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    fclose(file);
    return 0;
  }

  // Read ROM
  size_t bytes_read = fread(gb->rom_data, 1, size, file);
  if (bytes_read != size) {
    fprintf(stderr, "Error: Failed to read ROM (%zu/%ld bytes)\n", bytes_read,
            size);
    free(gb->rom_data);
    fclose(file);
    return 0;
  }
  fclose(file);
  gb->rom_size = size;

  // Extract header info
  memcpy(gb->title, gb->rom_data + GB_TITLE_OFFSET, 16);
  gb->title[16] = '\0'; // Null-terminate
  gb->cart_type = gb->rom_data[GB_CART_TYPE_OFFSET];
  gb->rom_bank_count = get_rom_size(gb->rom_data[GB_ROM_SIZE_OFFSET]) /
                       (16 * 1024); // 16KB banks
  gb->ram_size = get_ram_size(gb->rom_data[GB_RAM_SIZE_OFFSET]);

  // Validate checksum
  uint8_t checksum = 0;
  for (int i = 0x134; i <= 0x14C; i++) {
    checksum = checksum - gb->rom_data[i] - 1;
  }
  if (checksum != gb->rom_data[GB_CHECKSUM_OFFSET]) {
    fprintf(stderr,
            "Warning: Header checksum mismatch (expected 0x%02X, got 0x%02X)\n",
            gb->rom_data[GB_CHECKSUM_OFFSET], checksum);
  }

  return 1;
}

// Print ROM info
void print_rom_info(const GameBoy *gb) {
  printf("ROM Info:\n");
  printf("  Title: %s\n", gb->title);
  printf("  Cartridge Type: 0x%02X ", gb->cart_type);
  switch (gb->cart_type) {
  case 0x00:
    printf("(ROM Only)\n");
    break;
  case 0x01:
    printf("(MBC1)\n");
    break;
  case 0x03:
    printf("(MBC1+RAM+Battery)\n");
    break;
  case 0x13:
    printf("(MBC3+RAM+Battery)\n");
    break;
  case 0x19:
    printf("(MBC5)\n");
    break;
  default:
    printf("(Unknown)\n");
    break;
  }
  printf("  ROM Size: %zu bytes (%u banks)\n", gb->rom_size,
         gb->rom_bank_count);
  printf("  RAM Size: %u bytes\n", gb->ram_size);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <rom_file>\n", argv[0]);
    fprintf(stderr, "Example: %s pokemon_red.gb\n", argv[0]);
    return 1;
  }

  GameBoy gb = {0};
  if (!load_rom(&gb, argv[1])) {
    return 1;
  }

  print_rom_info(&gb);

  // Example: Pass to emulator (simplified)
  printf("ROM loaded into memory at 0x%p, ready for emulator...\n",
         (void *)gb.rom_data);
  // Emulator loop would go here (e.g., initialize SDL2, emulate CPU)

  // Cleanup
  free(gb.rom_data);
  return 0;
}
