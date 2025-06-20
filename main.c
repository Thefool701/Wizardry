#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
// Offset Definitions
#define GB_MAX_SIZE (32 * 1024 * 1024)
#define GB_HEADER_START 0x100
#define GB_TITLE_OFFSET 0x134
#define GB_MANUFACTURER_CODE_OFFSET 0x13F
#define GB_CGB_FLAG_OFFSET 0x143
#define GB_NEW_LICENSE_CODE_OFFSET 0x144
#define GB_SGB_FLAG_OFFSET 0x146
#define GB_CARTRIDGE_TYPE_OFFSET 0x147
#define GB_ROM_SIZE_OFFSET 0x148
#define GB_RAM_SIZE_OFFSET 0x149
#define GB_DESTINATION_CODE 0x14A
#define GB_OLD_LICENSE_CODE_OFFSET 0x14B
#define GB_MASK_ROM_VERSION_NUMBER 0x14C
#define GB_CHECKSUM_OFFSET 0x14D

#define MID_SIZE 7
// Game Boy emulator memory structure (simplified)
typedef struct {
  uint8_t *rom_data;         // ROM data
  char title[17];            // Game Title
  char manufacturer_code[5]; // Manufacturer Code(Purpose Unknown)
  uint32_t cgb_flag;
  uint32_t licensee_code;
  uint32_t sgb_flag;
  uint8_t cart_type;
  size_t rom_size;         // ROM size
  uint32_t rom_bank_count; // Number of ROM banks
  size_t ram_size;         // RAM size
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
  switch (code) {
  case 0x00:
    return 0;
  case 0x01:
    return 0;
  case 0x02:
    return 8 * 1024;
  case 0x03:
    return 32 * 1024;
  case 0x04:
    return 128 * 1024;
  case 0x05:
    return 64 * 1024;
  }
  return 0;
}

void get_new_licensee_code(uint8_t code) {
  switch (code) {
  case 0x00:
    printf("Publisher: None\n");
    break;
  case 0x01:
    printf("Publisher: Nintendo Research & Development 1\n");
    break;
  case 0x08:
    printf("Publisher: Capcom\n");
    break;
  case 0x13:
    printf("Publisher: EA (Electronic Arts)\n");
    break;
  case 0x18:
    printf("Publisher: Hudson Soft\n");
    break;
  case 0x19:
    printf("Publisher: B-AI\n");
    break;
  case 0x20:
    printf("Publisher: KSS\n");
    break;
  case 0x22:
    printf("Publisher: Planning Office WADA\n");
    break;
  case 0x24:
    printf("Publisher: PCM Complete\n");
    break;
  case 0x25:
    printf("Publisher: San-X\n");
    break;
  case 0x28:
    printf("Publisher: Kemco\n");
    break;
  case 0x29:
    printf("Publisher: SETA Corporation\n");
    break;
  case 0x30:
    printf("Publisher: Viacom\n");
    break;
  case 0x31:
    printf("Publisher: Nintendo\n");
    break;
  case 0x32:
    printf("Publisher: Bandai\n");
    break;
  case 0x33:
    printf("Publisher: Ocean Software/Acclaim Entertainment\n");
    break;
  case 0x34:
    printf("Publisher: Konami\n");
    break;
  case 0x35:
    printf("Publisher: HectorSoft\n");
    break;
  case 0x37:
    printf("Publisher: Taito\n");
    break;
  case 0x38:
    printf("Publisher: Hudson Soft\n");
    break;
  case 0x39:
    printf("Publisher: Banpresto\n");
    break;
  case 0x41:
    printf("Publisher: Ubi Soft\n");
    break;
  case 0x42:
    printf("Publisher: Atlus\n");
    break;
  case 0x44:
    printf("Publisher: Malibu Interactive\n");
    break;
  case 0x46:
    printf("Publisher: Angel\n");
    break;
  case 0x47:
    printf("Publisher: Bullet-Proof Software\n");
    break;
  case 0x49:
    printf("Publisher: Irem\n");
    break;
  case 0x50:
    printf("Publisher: Absolute\n");
    break;
  case 0x51:
    printf("Publisher: Acclaim Entertainment\n");
    break;
  case 0x52:
    printf("Publisher: Activision\n");
    break;
  case 0x53:
    printf("Publisher: Sammy USA Corporation\n");
    break;
  case 0x54:
    printf("Publisher: Konami\n");
    break;
  case 0x55:
    printf("Publisher: Hi Tech Expressions\n");
    break;
  case 0x56:
    printf("Publisher: LJN\n");
    break;
  case 0x57:
    printf("Publisher: Matchbox\n");
    break;
  case 0x58:
    printf("Publisher: Mattel\n");
    break;
  case 0x59:
    printf("Publisher: Milton Bradley Company\n");
    break;
  case 0x60:
    printf("Publisher: Titus Interactive\n");
    break;
  case 0x61:
    printf("Publisher: Virgin Games Ltd.\n");
    break;
  case 0x64:
    printf("Publisher: Lucasfilm Games\n");
    break;
  case 0x67:
    printf("Publisher: Ocean Software\n");
    break;
  case 0x69:
    printf("Publisher: EA (Electronic Arts)\n");
    break;
  case 0x70:
    printf("Publisher: Infogrames\n");
    break;
  case 0x71:
    printf("Publisher: Interplay Entertainment\n");
    break;
  case 0x72:
    printf("Publisher: Broderbund\n");
    break;
  case 0x73:
    printf("Publisher: Sculptured Software\n");
    break;
  case 0x75:
    printf("Publisher: The Sales Curve Limited\n");
    break;
  case 0x78:
    printf("Publisher: THQ\n");
    break;
  case 0x79:
    printf("Publisher: Accolade\n");
    break;
  case 0x80:
    printf("Publisher: Misawa Entertainment\n");
    break;
  case 0x83:
    printf("Publisher: lozc\n");
    break;
  case 0x86:
    printf("Publisher: Tokuma Shoten\n");
    break;
  case 0x87:
    printf("Publisher: Tsukuda Original\n");
    break;
  case 0x91:
    printf("Publisher: Chunsoft Co.\n");
    break;
  case 0x92:
    printf("Publisher: Video System\n");
    break;
  case 0x93:
    printf("Publisher: Ocean Software/Acclaim Entertainment\n");
    break;
  case 0x95:
    printf("Publisher: Varie\n");
    break;
  case 0x96:
    printf("Publisher: Yonezawa/s’pal\n");
    break;
  case 0x97:
    printf("Publisher: Kaneko\n");
    break;
  case 0x99:
    printf("Publisher: Pack-In-Video\n");
    break;
  case 0x9A:
    printf("Publisher: Bottom Up\n");
    break; // Assuming 9H is 0x9A
  case 0xA4:
    printf("Publisher: Konami (Yu-Gi-Oh!)\n");
    break;
  case 0xBL:
    printf("Publisher: MTO\n");
    break; // Non-standard code
  default:
    printf("Publisher: Unknown (Code 0x%02X)\n", code);
    break;
  }
}
void get_old_licensee_code(uint8_t code) {
  switch (code) {
  case 0x00:
    printf("Publisher: None\n");
    break;
  case 0x01:
    printf("Publisher: Nintendo\n");
    break;
  case 0x08:
    printf("Publisher: Capcom\n");
    break;
  case 0x09:
    printf("Publisher: HOT-B\n");
    break;
  case 0x0A:
    printf("Publisher: Jaleco\n");
    break;
  case 0x0B:
    printf("Publisher: Coconuts Japan\n");
    break;
  case 0x0C:
    printf("Publisher: Elite Systems\n");
    break;
  case 0x13:
    printf("Publisher: EA (Electronic Arts)\n");
    break;
  case 0x18:
    printf("Publisher: Hudson Soft\n");
    break;
  case 0x19:
    printf("Publisher: ITC Entertainment\n");
    break;
  case 0x1A:
    printf("Publisher: Yanoman\n");
    break;
  case 0x1D:
    printf("Publisher: Japan Clary\n");
    break;
  case 0x1F:
    printf("Publisher: Virgin Games Ltd.\n");
    break;
  case 0x24:
    printf("Publisher: PCM Complete\n");
    break;
  case 0x25:
    printf("Publisher: San-X\n");
    break;
  case 0x28:
    printf("Publisher: Kemco\n");
    break;
  case 0x29:
    printf("Publisher: SETA Corporation\n");
    break;
  case 0x30:
    printf("Publisher: Infogrames\n");
    break;
  case 0x31:
    printf("Publisher: Nintendo\n");
    break;
  case 0x32:
    printf("Publisher: Bandai\n");
    break;
  case 0x33:
    get_new_licensee_code(code);
    break;
  case 0x34:
    printf("Publisher: Konami\n");
    break;
  case 0x35:
    printf("Publisher: HectorSoft\n");
    break;
  case 0x38:
    printf("Publisher: Capcom\n");
    break;
  case 0x39:
    printf("Publisher: Banpresto\n");
    break;
  case 0x3C:
    printf("Publisher: Entertainment Interactive (stub)\n");
    break;
  case 0x3E:
    printf("Publisher: Gremlin\n");
    break;
  case 0x41:
    printf("Publisher: Ubi Soft\n");
    break;
  case 0x42:
    printf("Publisher: Atlus\n");
    break;
  case 0x44:
    printf("Publisher: Malibu Interactive\n");
    break;
  case 0x46:
    printf("Publisher: Angel\n");
    break;
  case 0x47:
    printf("Publisher: Spectrum HoloByte\n");
    break;
  case 0x49:
    printf("Publisher: Irem\n");
    break;
  case 0x4A:
    printf("Publisher: Virgin Games Ltd.\n");
    break;
  case 0x4D:
    printf("Publisher: Malibu Interactive\n");
    break;
  case 0x4F:
    printf("Publisher: U.S. Gold\n");
    break;
  case 0x50:
    printf("Publisher: Absolute\n");
    break;
  case 0x51:
    printf("Publisher: Acclaim Entertainment\n");
    break;
  case 0x52:
    printf("Publisher: Activision\n");
    break;
  case 0x53:
    printf("Publisher: Sammy USA Corporation\n");
    break;
  case 0x54:
    printf("Publisher: GameTek\n");
    break;
  case 0x55:
    printf("Publisher: Park Place\n");
    break;
  case 0x56:
    printf("Publisher: LJN\n");
    break;
  case 0x57:
    printf("Publisher: Matchbox\n");
    break;
  case 0x59:
    printf("Publisher: Milton Bradley Company\n");
    break;
  case 0x5A:
    printf("Publisher: Mindscape\n");
    break;
  case 0x5B:
    printf("Publisher: Romstar\n");
    break;
  case 0x5C:
    printf("Publisher: Naxat Soft\n");
    break;
  case 0x5D:
    printf("Publisher: Tradewest\n");
    break;
  case 0x60:
    printf("Publisher: Titus Interactive\n");
    break;
  case 0x61:
    printf("Publisher: Virgin Games Ltd.\n");
    break;
  case 0x67:
    printf("Publisher: Ocean Software\n");
    break;
  case 0x69:
    printf("Publisher: EA (Electronic Arts)\n");
    break;
  case 0x6E:
    printf("Publisher: Elite Systems\n");
    break;
  case 0x6F:
    printf("Publisher: Electro Brain\n");
    break;
  case 0x70:
    printf("Publisher: Infogrames\n");
    break;
  case 0x71:
    printf("Publisher: Interplay Entertainment\n");
    break;
  case 0x72:
    printf("Publisher: Broderbund\n");
    break;
  case 0x73:
    printf("Publisher: Sculptured Software\n");
    break;
  case 0x75:
    printf("Publisher: The Sales Curve Limited\n");
    break;
  case 0x78:
    printf("Publisher: THQ\n");
    break;
  case 0x79:
    printf("Publisher: Accolade\n");
    break;
  case 0x7A:
    printf("Publisher: Triffix Entertainment\n");
    break;
  case 0x7C:
    printf("Publisher: MicroProse\n");
    break;
  case 0x7F:
    printf("Publisher: Kemco\n");
    break;
  case 0x80:
    printf("Publisher: Misawa Entertainment\n");
    break;
  case 0x83:
    printf("Publisher: LOZC G.\n");
    break;
  case 0x86:
    printf("Publisher: Tokuma Shoten\n");
    break;
  case 0x8B:
    printf("Publisher: Bullet-Proof Software\n");
    break;
  case 0x8C:
    printf("Publisher: Vic Tokai Corp.\n");
    break;
  case 0x8E:
    printf("Publisher: Ape Inc.\n");
    break;
  case 0x8F:
    printf("Publisher: I’Max\n");
    break;
  case 0x91:
    printf("Publisher: Chunsoft Co.\n");
    break;
  case 0x92:
    printf("Publisher: Video System\n");
    break;
  case 0x93:
    printf("Publisher: Tsubaraya Productions\n");
    break;
  case 0x95:
    printf("Publisher: Varie\n");
    break;
  case 0x96:
    printf("Publisher: Yonezawa/S’Pal\n");
    break;
  case 0x97:
    printf("Publisher: Kemco\n");
    break;
  case 0x99:
    printf("Publisher: Arc\n");
    break;
  case 0x9A:
    printf("Publisher: Nihon Bussan\n");
    break;
  case 0x9B:
    printf("Publisher: Tecmo\n");
    break;
  case 0x9C:
    printf("Publisher: Imagineer\n");
    break;
  case 0x9D:
    printf("Publisher: Banpresto\n");
    break;
  case 0x9F:
    printf("Publisher: Nova\n");
    break;
  case 0xA1:
    printf("Publisher: Hori Electric\n");
    break;
  case 0xA2:
    printf("Publisher: Bandai\n");
    break;
  case 0xA4:
    printf("Publisher: Konami\n");
    break;
  case 0xA6:
    printf("Publisher: Kawada\n");
    break;
  case 0xA7:
    printf("Publisher: Takara\n");
    break;
  case 0xA9:
    printf("Publisher: Technos Japan\n");
    break;
  case 0xAA:
    printf("Publisher: Broderbund\n");
    break;
  case 0xAC:
    printf("Publisher: Toei Animation\n");
    break;
  case 0xAD:
    printf("Publisher: Toho\n");
    break;
  case 0xAF:
    printf("Publisher: Namco\n");
    break;
  case 0xB0:
    printf("Publisher: Acclaim Entertainment\n");
    break;
  case 0xB1:
    printf("Publisher: ASCII Corporation or Nexsoft\n");
    break;
  case 0xB2:
    printf("Publisher: Bandai\n");
    break;
  case 0xB4:
    printf("Publisher: Square Enix\n");
    break;
  case 0xB6:
    printf("Publisher: HAL Laboratory\n");
    break;
  case 0xB7:
    printf("Publisher: SNK\n");
    break;
  case 0xB9:
    printf("Publisher: Pony Canyon\n");
    break;
  case 0xBA:
    printf("Publisher: Culture Brain\n");
    break;
  case 0xBB:
    printf("Publisher: Sunsoft\n");
    break;
  case 0xBD:
    printf("Publisher: Sony Imagesoft\n");
    break;
  case 0xBF:
    printf("Publisher: Sammy Corporation\n");
    break;
  case 0xC0:
    printf("Publisher: Taito\n");
    break;
  case 0xC2:
    printf("Publisher: Kemco\n");
    break;
  case 0xC3:
    printf("Publisher: Square\n");
    break;
  case 0xC4:
    printf("Publisher: Tokuma Shoten\n");
    break;
  case 0xC5:
    printf("Publisher: Data East\n");
    break;
  case 0xC6:
    printf("Publisher: Tonkin House\n");
    break;
  case 0xC8:
    printf("Publisher: Koei\n");
    break;
  case 0xC9:
    printf("Publisher: UFL\n");
    break;
  case 0xCA:
    printf("Publisher: Ultra Games\n");
    break;
  case 0xCB:
    printf("Publisher: VAP, Inc.\n");
    break;
  case 0xCC:
    printf("Publisher: Use Corporation\n");
    break;
  case 0xCD:
    printf("Publisher: Meldac\n");
    break;
  case 0xCE:
    printf("Publisher: Pony Canyon\n");
    break;
  case 0xCF:
    printf("Publisher: Angel\n");
    break;
  case 0xD0:
    printf("Publisher: Taito\n");
    break;
  case 0xD1:
    printf("Publisher: SOFEL\n");
    break;
  case 0xD2:
    printf("Publisher: Quest\n");
    break;
  case 0xD3:
    printf("Publisher: Sigma Enterprises\n");
    break;
  case 0xD4:
    printf("Publisher: ASK Kodansha Co.\n");
    break;
  case 0xD6:
    printf("Publisher: Naxat Soft\n");
    break;
  case 0xD7:
    printf("Publisher: Copya System\n");
    break;
  case 0xD9:
    printf("Publisher: Banpresto\n");
    break;
  case 0xDA:
    printf("Publisher: Tomy\n");
    break;
  case 0xDB:
    printf("Publisher: LJN\n");
    break;
  case 0xDD:
    printf("Publisher: Nippon Computer Systems\n");
    break;
  case 0xDE:
    printf("Publisher: Human Ent.\n");
    break;
  case 0xDF:
    printf("Publisher: Altron\n");
    break;
  case 0xE0:
    printf("Publisher: Jaleco\n");
    break;
  case 0xE1:
    printf("Publisher: Towa Chiki\n");
    break;
  case 0xE2:
    printf("Publisher: Yutaka\n");
    break;
  case 0xE3:
    printf("Publisher: Varie\n");
    break;
  case 0xE5:
    printf("Publisher: Epoch\n");
    break;
  case 0xE7:
    printf("Publisher: Athena\n");
    break;
  case 0xE8:
    printf("Publisher: Asmik Ace Entertainment\n");
    break;
  case 0xE9:
    printf("Publisher: Natsume\n");
    break;
  case 0xEA:
    printf("Publisher: King Records\n");
    break;
  case 0xEB:
    printf("Publisher: Atlus\n");
    break;
  case 0xEC:
    printf("Publisher: Epic/Sony Records\n");
    break;
  case 0xEE:
    printf("Publisher: IGS\n");
    break;
  case 0xF0:
    printf("Publisher: A Wave\n");
    break;
  case 0xF3:
    printf("Publisher: Extreme Entertainment\n");
    break;
  case 0xFF:
    printf("Publisher: LJN\n");
    break;
  default:
    printf("Publisher: Unknown (Code 0x%02X)\n", code);
    break;
  }
}
void get_cartridge_type(uint8_t code) {
  switch (code) {
  case 0x00:
    printf("Cartridge Type: ROM ONLY\n");
    break;
  case 0x01:
    printf("Cartridge Type: MBC1\n");
    break;
  case 0x02:
    printf("Cartridge Type: MBC1+RAM\n");
    break;
  case 0x03:
    printf("Cartridge Type: MBC1+RAM+BATTERY\n");
    break;
  case 0x05:
    printf("Cartridge Type: MBC2\n");
    break;
  case 0x06:
    printf("Cartridge Type: MBC2+BATTERY\n");
    break;
  case 0x08:
    printf("Cartridge Type: ROM+RAM\n");
    break;
  case 0x09:
    printf("Cartridge Type: ROM+RAM+BATTERY\n");
    break;
  case 0x0B:
    printf("Cartridge Type: MMM01\n");
    break;
  case 0x0C:
    printf("Cartridge Type: MMM01+RAM\n");
    break;
  case 0x0D:
    printf("Cartridge Type: MMM01+RAM+BATTERY\n");
    break;
  case 0x0F:
    printf("Cartridge Type: MBC3+TIMER+BATTERY\n");
    break;
  case 0x10:
    printf("Cartridge Type: MBC3+TIMER+RAM+BATTERY\n");
    break;
  case 0x11:
    printf("Cartridge Type: MBC3\n");
    break;
  case 0x12:
    printf("Cartridge Type: MBC3+RAM\n");
    break;
  case 0x13:
    printf("Cartridge Type: MBC3+RAM+BATTERY\n");
    break;
  case 0x19:
    printf("Cartridge Type: MBC5\n");
    break;
  case 0x1A:
    printf("Cartridge Type: MBC5+RAM\n");
    break;
  case 0x1B:
    printf("Cartridge Type: MBC5+RAM+BATTERY\n");
    break;
  case 0x1C:
    printf("Cartridge Type: MBC5+RUMBLE\n");
    break;
  case 0x1D:
    printf("Cartridge Type: MBC5+RUMBLE+RAM\n");
    break;
  case 0x1E:
    printf("Cartridge Type: MBC5+RUMBLE+RAM+BATTERY\n");
    break;
  case 0x20:
    printf("Cartridge Type: MBC6\n");
    break;
  case 0x22:
    printf("Cartridge Type: MBC7+SENSOR+RUMBLE+RAM+BATTERY\n");
    break;
  case 0xFC:
    printf("Cartridge Type: POCKET CAMERA\n");
    break;
  case 0xFD:
    printf("Cartridge Type: BANDAI TAMA5\n");
    break;
  case 0xFE:
    printf("Cartridge Type: HuC3\n");
    break;
  case 0xFF:
    printf("Cartridge Type: HuC1+RAM+BATTERY\n");
    break;
  default:
    printf("Cartridge Type: Unknown (Code 0x%02X)\n", code);
    break;
  }
}

// Load Gamefile
int load_gamefile(GameBoy *gb, const char *filename) {
  // Read and validate ROM file
  FILE *gamefile = fopen(filename, "rb");
  if (!gamefile) {
    printf("Error in Reading Gamefile!\n");
    return 1;
  }

  // Get file size
  fseek(gamefile, 0, SEEK_END);
  long size = ftell(gamefile);
  rewind(gamefile);

  // Validate File Size
  if (size < GB_HEADER_START || size > GB_MAX_SIZE) {
    printf("Gamefile is to Large!");
    fclose(gamefile);
    return 1;
  }

  // Read file
  gb->rom_data = malloc(size);
  if (!gb->rom_data) {
    printf("Memory Allocation Failed!\n");
  }
  // Read ROM
  size_t bytes_read = fread(gb->rom_data, 1, size, gamefile);
  if (bytes_read != size) {
    printf("Failed in reading ROM File!\n");
    fprintf(stderr, "Error: Failed to read ROM (%zu/%ld bytes)\n", bytes_read,
            size);
    free(gb->rom_data);
    fclose(gamefile);
    return 0;
  }
  fclose(gamefile);
  gb->rom_size = size;

  // Extract header info
  memcpy(gb->title, gb->rom_data + GB_TITLE_OFFSET, 16);
  memcpy(gb->manufacturer_code, gb->rom_data + GB_TITLE_OFFSET, 4);
  gb->cgb_flag = gb->rom_data[GB_CGB_FLAG_OFFSET];
  gb->sgb_flag = gb->rom_data[GB_SGB_FLAG_OFFSET];
  gb->rom_size = get_rom_size(gb->rom_data[GB_ROM_SIZE_OFFSET]);
  gb->ram_size = get_ram_size(gb->rom_data[GB_RAM_SIZE_OFFSET]);
  gb->rom_bank_count = get_rom_size(gb->rom_data[GB_ROM_SIZE_OFFSET]) /
                       (16 * 1024); // 16KB banks
  gb->licensee_code = gb->rom_data[GB_OLD_LICENSE_CODE_OFFSET];
  gb->cart_type = gb->rom_data[GB_CARTRIDGE_TYPE_OFFSET];
  // Validate checksum
  uint8_t checksum = 0;
  for (uint16_t address = 0x0134; address <= 0x014C; address++) {
    checksum = checksum - gb->rom_data[address] - 1;
  }
  if (checksum != gb->rom_data[GB_CHECKSUM_OFFSET]) {
    printf("Error Occured. Aborting Game!");
    return 1;
  }
  free(gb->rom_data);
  return 1;
}

void print_rom_info(const GameBoy *gb) {
  printf("Game Title: %s\n", gb->title);
  printf("Manufacturer Code: %s\n", gb->manufacturer_code);
  if (gb->cgb_flag == 0x80) {
    printf("CGB Mode\n");
  } else {
    printf("Non-CGB Mode\n");
  }
  get_old_licensee_code(gb->licensee_code);
  printf("Supports SGB functions: %s\n", gb->sgb_flag == 0x33 ? "Yes" : "No");
  get_cartridge_type(gb->cart_type);
  printf("ROM Size: %zu bytes (%u banks)\n", gb->rom_size, gb->rom_bank_count);
  printf("RAM Size: %zu bytes\n", gb->ram_size);
  switch (gb->dest_code) {
  case 0x00:
    printf("Sold in Japan(and possibly overseas)\n");
    break;
  case 0x01:
    printf("Overseas only\n");
    break;
  }
  printf("Mask ROM Version Number: %zu\n", gb->mask_rom_version_number);
}

// Print ROM info
int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <gamefile>\n", argv[0]);
    printf("Example: %s  pokemon_red.gb", argv[0]);
  }

  GameBoy gb = {0};
  if (!load_gamefile(&gb, argv[1])) {
    printf("Error Loading Gamefile!");
    return 1;
  }

  print_rom_info(&gb);

  return 0;
}
