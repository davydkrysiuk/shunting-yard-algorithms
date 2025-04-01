#include "ctype.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

typedef enum {
  NUMBER,
  OP,
  OPEN_P,
  CLOSE_P
} TokenType;

typedef struct {
  char *value;
  TokenType type;
} Token;

typedef struct {
  Token *array;
  int count;
} Tokens;

Token create_tk(char *value, TokenType type) {
  Token tk;
  tk.value = malloc(strlen(value) * sizeof(char));
  strcpy(tk.value, value);
  tk.type = type;
  return tk;
}

char* ch_to_str(char value) {
  char* str = malloc(2 * sizeof(char));
  str[0] = value;
  str[1] = '\0';
  return str;
}

int is_number(char *input) {
  for (int i = 0; i < strlen(input); ++i) {
	if (!isdigit(input[i])) return 0;
  }
  return 1;
}

TokenType tktp_by_char(char input) {
  if (input == '(') return OPEN_P;
  if (input == ')') return CLOSE_P;
  return OP;
}

Tokens init_tk_arr() {
  Tokens tk_arr;
  tk_arr.array = malloc(sizeof(Token));
  tk_arr.count = 0;
  return tk_arr;
};

void push_tk_arr(Tokens *tk_arr, char *value, TokenType type) {
  tk_arr->array = realloc(tk_arr->array, (tk_arr->count + 1) * sizeof(Token));
  Token tk = create_tk(value, type);
  tk_arr->array[tk_arr->count] = tk;
  tk_arr->count++;
}

Tokens tokenize(char* input) {
  Tokens tk_arr = init_tk_arr();

  char* buffer = malloc(sizeof(char));
  buffer[0] = '\0';
  
  for (int i = 0; i < strlen(input); ++i) {

	if (input[i] == ' ') continue;
	
	if (isdigit(input[i])) {
	  size_t len = strlen(buffer);
	  buffer = realloc(buffer, (len + 2) * sizeof(char));
	  buffer[len] = input[i];
	  buffer[len + 1] = '\0';
	} else {
	  if (buffer[0] != '\0') {
		push_tk_arr(&tk_arr, buffer, NUMBER);
		buffer[0] = '\0';
		push_tk_arr(&tk_arr, ch_to_str(input[i]), tktp_by_char(input[i]));
	  } else {
		push_tk_arr(&tk_arr, ch_to_str(input[i]), tktp_by_char(input[i]));
	  }
	}
  }

  if (buffer[0] != '\0') {
	if (is_number(buffer) == 1) push_tk_arr(&tk_arr, buffer, NUMBER);
  }

  free(buffer);
  return tk_arr;
}

int main() {
  char *input = "(1234567892 + 345) * 6789";
  Tokens tk_arr = tokenize(input);

  for (int i = 0; i < tk_arr.count; i++) {
	printf("%d - %s [%d]\n", i, tk_arr.array[i].value, tk_arr.array[i].type);
  }
}
