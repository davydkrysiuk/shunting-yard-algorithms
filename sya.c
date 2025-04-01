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

void str_append(char* str, char value) {
  str[strlen(str)] = value;
  str[strlen(str) + 1] = '\0';
}

Tokens tokenize(char* input) {
  Tokens tk_arr = init_tk_arr();

  char* buffer = malloc(sizeof(char));

  for (int i = 0; i < strlen(input); ++i) {
	if (input[i] == ' ') continue;
	if (isdigit(input[i])) {
	  str_append(buffer, input[i]);
	} else {
	  if (buffer[0] != '\0') {
		push_tk_arr(&tk_arr, buffer, NUMBER);

		push_tk_arr(&tk_arr, ch_to_str(input[i]), tktp_by_char(input[i]));
		buffer[0] = '\0';
	  } else {
		push_tk_arr(&tk_arr, ch_to_str(input[i]), tktp_by_char(input[i]));
		buffer[0] = '\0';
	  }
	}
  }

  if (buffer[0] != '\0') {
	if (is_number(buffer) == 1) push_tk_arr(&tk_arr, buffer, NUMBER);
	if (is_number(buffer) == 0) push_tk_arr(&tk_arr, ch_to_str(buffer[0]), tktp_by_char(buffer[0]));
  }


  return tk_arr;
}

int main() {
  char *input = "(2 + 2) * 3";
  Tokens tk_arr = tokenize(input);

  for (int i = 0; i < tk_arr.count; i++) {
	printf("%d - %s [%d]\n", i, tk_arr.array[i].value, tk_arr.array[i].type);
  }
}
