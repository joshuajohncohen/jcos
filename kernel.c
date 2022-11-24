static char* const VGA_MEMORY = (char*)0x0b8000;
static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;

static const char textstyle = 0x3e;

void kernel_early(void) {
  const int screensize = VGA_WIDTH * VGA_HEIGHT;
  unsigned int position = 0;
  while (position < screensize) {
    VGA_MEMORY[(2*position) + 1] = textstyle;
  }
}

int main(void) {
  const char *str = "╒═════════╤══════╕\n│Joshua   │Cohen's│\n╞═════════╪═══════╡\n│Operating│System  │\n├┼────────┴──────┼┤\n╘╛               ╘╛";
  
  unsigned int i = 0; //placeholder for index in text string
  unsigned int j = 0; //placeholder for position in video buffer
  
  while (str[i] != '\0') {
    if (str[i] == '\n') {
      j = 2 * VGA_WIDTH * ((int) (j / VGA_WIDTH / 2));
      i++;
    }
    
    VGA_MEMORY[j] = str[i];
    VGA_MEMORY[j+1] = textstyle;
    i++;
    j = j+2;
  }

  return 0;
}

