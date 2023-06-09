#include "hangman.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int get_word(char secret[]) {
  // check if file exists first and is readable
  FILE *fp = fopen(WORDLIST_FILENAME, "rb");
  if (fp == NULL) {
    fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
    return 1;
  }

  // get the filesize first
  struct stat st;
  stat(WORDLIST_FILENAME, &st);
  long int size = st.st_size;

  do {
    // generate random number between 0 and filesize
    long int random = (rand() % size) + 1;
    // seek to the random position of file
    fseek(fp, random, SEEK_SET);
    // get next word in row ;)
    int result = fscanf(fp, "%*s %20s", secret);
    if (result != EOF)
      break;
  } while (1);

  fclose(fp);

  return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]) {
  int uhadnute = 0;

  for (int i = 0; i < strlen(secret); i++) {
    for (int j = 0; j < strlen(letters_guessed); j++) {
      if (secret[i] == letters_guessed[j]) {
        uhadnute++;
      }
    }
  }

  return uhadnute == strlen(secret);
}

void get_guessed_word(const char secret[], const char letters_guessed[],
                      char guessed_word[]) {

  for (int i = 0; i < strlen(secret); i++) {
    guessed_word[i] = '_';

    for (int j = 0; j < strlen(letters_guessed); j++) {
      if (secret[i] == letters_guessed[j]) {
        guessed_word[i] = secret[i];
      }
    }
  }

  printf("%s\n\n", guessed_word);
}

void get_available_letters(const char letters_guessed[],
                           char available_letters[]) {

  available_letters = "abcdefghijklmnoprtquvwxyz";

  for (int i = 0; i < strlen(available_letters); i++) {
    int cislo = 0;

    for (int j = 0; j < strlen(letters_guessed); j++) {
      if (letters_guessed[j] == available_letters[i]) {
        cislo = 1;
      }
    }
    if (cislo == 0) {
      printf("%c ", available_letters[i]);
    }
  }
  printf("\n");
}

void hangman(const char secret[]) {
  char letters_guessed[26];
  int cislo = 0;
  int uhadnute = 0, neviem = 0;
  int gues = 8;
  char avaliable_letters[26];
  char result[30];

  printf("Welcome to the game, Hangman!\n");
  printf("I am thinking of a word that is %ld letters long.\n", strlen(secret));

  do {
    printf("-------------\n");
    printf("You have %d guesses left.\n", gues);

    printf("Please guess a letter: ");
    scanf(" %c", &letters_guessed[cislo]);
    cislo++;
    printf("\n");

    get_guessed_word(secret, letters_guessed, result);
    printf("\n");
    get_available_letters(letters_guessed, avaliable_letters);
    uhadnute = 0;
    for (int i = 0; i < strlen(secret); i++) {
      if (letters_guessed[cislo - 1] == secret[i]) {
        uhadnute++;
      }
    }
    if (uhadnute == neviem) {
      printf("\nNeuhadol si.\n");
      uhadnute = neviem;
      gues--;
    } else {
      printf("\nUhadol si.\n");
      uhadnute = neviem;
    }
  } while (is_word_guessed(secret, letters_guessed) == 0 && gues > 0);
  printf("-------------\n");
  if (gues < 1) {
    printf("prehral si\n");
  } else if (is_word_guessed(secret, letters_guessed) == 1) {
    printf("Congratulations, you won!\n");
  } else {
    printf("nieco zle");
  }
}

int main() {
  char result[30];

  get_word(result);
  hangman(result);

  return 0;
}
