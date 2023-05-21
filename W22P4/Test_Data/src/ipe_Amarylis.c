/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 21/05/2023
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <button.h>
#include <buzzer.h>
#include <display.h>
#include <led.h>
#include <potentio.h>

#include <stdlib.h>
#include <string.h>
#include <usart.h>
#include <util/delay.h>

#define NOTE1 261.630
#define NOTE2 293.660
#define NOTE3 329.630

#define DURATION1 500

int MULTIPLE;
int level = 0;
int button_pushed = 0;
int counterTime = 0;
int line = 0;
int i = 0;
int segment;

void initTimer() {
  TCCR2A |= (1 << WGM21);  // Set Timer2 to Clear Timer on Compare Mode.
  OCR2A = MULTIPLE;        // Set the compare match value to 249 (OCR2A = 249).
  TIMSK2 |= (1 << OCIE2A);  // Enable OCRA interrupt.
  sei();                    // Enable global interrupts.
}

void startTimer() { TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); } // Schalingsfactor = 256. (startTimer)

void stopTimer() { TCCR2B = (0 << (CS22)) | (0 << (CS21)) | (0 << (CS20)); }  // Schalingsfactor = 0.

ISR(PCINT1_vect) { if (buttonPushed(0)) button_pushed = !button_pushed; }

typedef struct {
  float frequency;
  uint16_t duration;
} NOTE;

typedef struct {
  char* name;
  NOTE** notes;
  uint16_t length;
} SONG;

typedef struct {
  char* name;
  int level;
} HIGHSCORE;

HIGHSCORE* createHighscore(char* name, int level) {
  HIGHSCORE* highscore = malloc(sizeof(HIGHSCORE));
  highscore->name = malloc(strlen(name) + 1);
  strcpy(highscore->name, name);
  highscore->level = level;
  return highscore;
}

void insertHighscore(HIGHSCORE* highscores[], int numHighscores, HIGHSCORE* newHighscore) {
  int j;
  for (j = 0; j < numHighscores; j++) if (newHighscore->level > highscores[j]->level) break;
  if (j < numHighscores) {
    for (int f = numHighscores - 1; f > i; f--) highscores[f] = highscores[f - 1];
    highscores[j] = newHighscore;
  }
}

void displayHighscores(HIGHSCORE* highscores[], int numHighscores) {
  printf("Highscores:\n");
  for (int j = 0; j < numHighscores; j++) printf("%d. Name: %s, level: %d\n", j + 1, highscores[j]->name, highscores[j]->level);
}

SONG* currentSong = NULL;
void choseLevel() {
  switch (level) {
    case 0:
      MULTIPLE = 300;
      break;
    case 1:
      MULTIPLE = 275;
      break;
    case 2:
      MULTIPLE = 250;
      break;
    case 3:
      MULTIPLE = 225;
      break;
    case 4:
      MULTIPLE = 200;
      break;
    case 5:
      MULTIPLE = 175;
      break;
    case 6:
      MULTIPLE = 150;
      break;
    case 7:
      MULTIPLE = 125;
      break;
    case 8:
      MULTIPLE = 100;
      break;
    case 9:
      MULTIPLE = 75;
      break;
    case 10:
      MULTIPLE = 50;
      break;
  }
}

NOTE* createNote(float frequency, uint16_t duration) {
  NOTE* note = malloc(sizeof(NOTE));
  note->frequency = frequency;
  note->duration = duration;
  return note;
}

SONG* createSong(char* name, NOTE** notes, uint16_t length) {
  SONG* song = malloc(sizeof(SONG));
  song->name = name;
  song->notes = notes;
  song->length = length;
  return song;
}

SONG** songsArray() {
  NOTE* song1Notes[] = {
      createNote(NOTE1, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE3, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE3, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE3, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1)};
  NOTE* song2Notes[] = {
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE3, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE3, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1)};
  NOTE* song3Notes[] = {
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE3, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE2, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE3, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE2, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE3, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1), createNote(NOTE1, DURATION1),
      createNote(NOTE1, DURATION1)};

  SONG* song1 = createSong("Song1", song1Notes, 36);
  SONG* song2 = createSong("Song2", song2Notes, 36);
  SONG* song3 = createSong("Song3", song3Notes, 36);

  SONG** songList = malloc(sizeof(SONG*) * 3);
  songList[0] = song1;
  songList[1] = song2;
  songList[2] = song3;

  return songList;
}

void start() {
  uint16_t seed = 0;
  printf("Draai aan de potentiometer, Als u klaar bent druk op knop 1\n");

  while (!button_pushed) { /* wacht */
    seed = ((double)readPotentio() / 100);
    writeNumber(seed);
  }
  level = seed;
  printf("level : %d\n", seed);
  srand(seed);
}

void songStart(SONG* song) {
  printf("Willekeurig liedje gekozen: %s!\n", song->name);
  for (int i = 0; i < song->length; i++) playTone(song->notes[i]->frequency, song->notes[i]->duration);
}

SONG* randomSong(SONG** songs) {
  SONG* song = songs[rand() % 3];
  return song;
}

void writeLineOnDislpay(uint8_t line) {
  SONG* song = currentSong;

  if (song->notes[i]->frequency == NOTE1) {
    segment = 0;
    writeStripe(segment, line);

  } else if (song->notes[i]->frequency == NOTE2) {
    segment = 1;
    writeStripe(segment, line);

  } else if (song->notes[i]->frequency == NOTE3) {
    segment = 2;
    writeStripe(segment, line);
  }
}

ISR(TIMER2_COMPA_vect) {
  // Verhoog counter met 1.
  counterTime++;
  // Als counter + 1 deelbaar is door VEELVOUD tel één seconde.
  if (counterTime % MULTIPLE == 0) {
    writeLineOnDislpay(line);
    line++;
    if (line > 2) {
      line = 0;
      i++;
    }
  };
}

int main() {
  int counterHits = 0;
  initDisplay();
  initUSART();

  enableAllButtons();
  enablePotentio();
  enableBuzzer();
  buzzerOff();
  enableAllLeds();
  lightDownAllLeds();
  enableAllButtonInterrupts();
  SONG** songs = songsArray();
  currentSong = randomSong(songs);

  start();
  choseLevel();
  songStart(currentSong);
  initTimer();
  startTimer();

  HIGHSCORE** highscores = malloc(3 * sizeof(HIGHSCORE*));
  char* name[50];

  while (level <= 10) {
  if (counterHits >= 9) lightUpLed(0);
  if (counterHits >= 18) lightUpLed(1);
  if (counterHits >= 27) lightUpLed(2);
  if (counterHits == 35) {
    currentSong = randomSong(songs);
    lightUpLed(3);
    level++;
    printf("level: %d\n", level);
    playTone(NOTE1, 500);
    playTone(NOTE3, 500);
    playTone(NOTE2, 500);
    counterHits = 0;
    lightDownAllLeds();
    choseLevel();
    startTimer();
  }
  if (level > 10) break;

  if (buttonPushed(0) && segment == 0 && line == 0) {
    counterHits++;
    playTone(currentSong->notes[0]->frequency, currentSong->notes[0]->duration);
    } else if (buttonPushed(1) && segment == 1 && line == 0) {
    counterHits++;
    playTone(currentSong->notes[1]->frequency, currentSong->notes[1]->duration);
    } else if (buttonPushed(2) && segment == 2 && line == 0) {
      counterHits++;
      playTone(currentSong->notes[2]->frequency, currentSong->notes[2]->duration);
    } else if ((buttonPushed(0) || buttonPushed(1) || buttonPushed(2)) && line > 0) {
      counterHits = 0;
      lightDownAllLeds();
    }
  }

  for (int i = 0; i < 5; i++) free(songs[i]);
  free(songs);
  return 0;
}