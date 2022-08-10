#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h> // PATH_MAX
#include <unistd.h>

#define INITIAL_STACK_SIZE 64
#define STACK_CHUNK_SIZE 64

/**
 * Implementacja stosu
 */
typedef struct v_stack {
  void** data;
  unsigned int size; // ilość zaalokowanych int'ów
  unsigned int count; // ilość elementów na stosie
} v_stack;

v_stack v_stack_init();
void v_stack_push(v_stack* stk, void* data);
void* v_stack_peek(v_stack* stk);
int v_stack_pop(v_stack* stk, bool release);
int v_stack_release(v_stack* stk, bool release_nested);
#define MAX_POSIX_FILENAME_LEN 256
#define TREE_LEVEL_SPACING_LEN 3
#define TREE_EDGE_CHARACTER "├"
#define TREE_LINE_CHARACTER "─"
#define TREE_ROW_CHARACTER "│"
#define TREE_EDGE_TERMINATOR_CHARACTER "└"

typedef struct tree_file {
  unsigned char type; // DT_DIR, DT_REG
  bool is_dir;
  bool is_symlink;
  char* name;
  char* path;

  // daty dostępu
  time_t last_access_time;
  time_t last_modificiation_time;

  off_t size; // w bajtach rozmiar

  // jeśli symlink
  struct tree_file* symlink_dest;
} tree_file;

// informacje podsumowujące drzewo
typedef struct tree_stats {
  unsigned int files_count;
  unsigned int dir_count;
} tree_stats;

// informacje używane do rysowania drzewa
typedef struct tree_print_flags {
  bool dir_only;
  bool follow_symlinks;
  bool print_full_path;
  int max_level;
} tree_print_flags;

/**
 * Łączy dwie ścieżki
 */
char* join_paths(const char* parent, const char* child);
v_stack tree_list_files(
    const char* path,
    struct tree_print_flags* flags);
void tree_free_file(tree_file* file);
void tree_release_files(v_stack* stk);
int tree_recursive_print(
    const char* path,
    struct v_stack* parents, // przechowuje flagi czy parent jest ostatnim elementem
    struct tree_print_flags* flags,
    struct tree_stats* stats);
void tree_print(
    const char* path,
    struct tree_print_flags* flags);
int tree_demo();
