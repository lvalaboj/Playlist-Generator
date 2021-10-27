#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
 * This functions add a particular song to the head of the list.
 * The first parameter, song_ptr, points to the head. The second
 * and third parameters describe a song that will be added after
 * being created to the head of the list.
 */

song_t *add_song_to_head(song_t* song_ptr, char * title, char * artist) {
  assert(title != NULL);
  assert(artist != NULL);

  song_t* new_song = malloc(sizeof(song_t));
  assert(new_song != NULL);

  new_song->title = malloc(strlen(title) + 1);
  assert(new_song->title != NULL);
  new_song->title = title;

  new_song->artist = malloc(strlen(artist) + 1);
  assert(new_song->artist != NULL);
  new_song->artist = artist;

  new_song->next_song = song_ptr;
  song_ptr = new_song;

  return song_ptr;
} /* add_song_to_head() */

/*
 * This function removes a song from the head.
 * The first parameter points to the head of the list.
 */

song_t *remove_song_from_head(song_t * song_ptr) {
  if (song_ptr == NULL) {
    return NULL;
  }
  song_t* temp_song = song_ptr;
  song_ptr = song_ptr->next_song;
  free(temp_song->artist);
  free(temp_song->title);
  free(temp_song);

  return song_ptr;
} /* remove_song_from_head() */

/*
 * This function adds a particular song to the tail of the list.
 * The first parameter, song_ptr, points to the head of the list.
 * the seconda and third parameters describe a song to be added
 * to the list.
 */

song_t *add_song_to_tail(song_t * song_ptr, char * title, char * artist) {
  assert(title != NULL);
  assert(artist != NULL);

  song_t* current_song = song_ptr;
  while ((current_song != NULL) && (current_song->next_song != NULL)) {
    current_song = current_song->next_song;
  }

  song_t* new_song = malloc(sizeof(song_t));
  assert(new_song != NULL);

  new_song->title = malloc(strlen(title) + 1);
  assert(new_song->title != NULL);
  new_song->title = title;

  new_song->artist = malloc(strlen(artist) + 1);
  assert(new_song->artist != NULL);
  new_song->artist = artist;

  new_song->next_song = NULL;

  if (current_song != NULL) {
    current_song->next_song = new_song;
  }
  else {
    song_ptr = new_song;
  }
  return song_ptr;
} /* add_song_to_tail() */

/*
 * This function removes a song from the tail given
 * the pointer that points to the head of the list,
 * the first parameter.
 */

song_t *remove_song_from_tail(song_t * song_ptr) {
  if (song_ptr == NULL) {
    return NULL;
  }

  if (song_ptr->next_song == NULL) {
    free(song_ptr->artist);
    free(song_ptr->title);
    free(song_ptr);
    song_ptr = NULL;
    return song_ptr;
  }
  song_t* current_song = song_ptr;
  while (current_song->next_song->next_song != NULL) {
    current_song = current_song->next_song;
  }

  free(current_song->next_song->artist);
  free(current_song->next_song->title);
  free(current_song->next_song);
  current_song->next_song = NULL;

  return song_ptr;
} /* remove_song_from_tail() */

/*
 * This functions counts the number of songs
 * that exist in the list pointed by the first parameter,
 * song_ptr.
 */

int count_songs(song_t* song_ptr) {
  if (song_ptr == NULL) {
    return 0;
  }
  song_t *current_song = song_ptr;
  int song_counter = 0;
  while ((current_song != NULL) && (current_song->next_song != NULL)) {
    current_song = current_song->next_song;
    song_counter++;
  }

  return song_counter + 1;
} /* count_songs() */

/*
 * This function will search for a song given the index of it
 * in a particular list pointed by the first parameter, song_ptr.
 * The second parameter is the index.
 */

song_t *search_by_index(song_t * song_ptr, int index) {
  assert(index > 0);
  int song_counter = 1;
  while (song_ptr != NULL) {
    if (index == song_counter) {
      return song_ptr;
    }
    song_ptr = song_ptr->next_song;
    song_counter++;
  }
  return NULL;
} /* search_by_index() */

/*
 * This function searches for a particular song given the song
 * details. The second two parameter are these details, artist and title.
 * The first parameter is the pointer that points to the head of the list.
 */

song_t *search_by_title_and_artist(song_t * song_ptr, char * title,
  char * artist) {
  assert(title != NULL);
  assert(artist != NULL);

  while (song_ptr != NULL) {
    if (strcmp(song_ptr->title, title) == 0) {
      if (strcmp(song_ptr->artist, artist) == 0) {
        return song_ptr;
      }
    }
    song_ptr = song_ptr->next_song;
  }

  return NULL;
} /* search_by_title_and_artist() */

/*
 * Given the index, the function first locates a song from the list
 * pointed by the first parameter, song_ptr. Then, this song is modified
 * using the information of title and artist given as the third and fourth
 * parameters.
 */

song_t *modify_song_by_index(song_t * song_ptr, int index,
  char * title, char * artist) {
  assert(index > 0);
  assert(title != NULL);
  assert(artist != NULL);

  int song_counter = 1;
  while (song_ptr != NULL) {
    if (song_counter == index) {
      free(song_ptr->artist);
      free(song_ptr->title);
      song_ptr->artist = (char*) malloc(strlen(artist) + 1);
      assert(song_ptr->artist != NULL);
      song_ptr->title = (char*) malloc(strlen(title) + 1);
      assert(song_ptr->title != NULL);
      song_ptr->artist = artist;
      song_ptr->title = title;
      return song_ptr;
    }
    song_ptr = song_ptr->next_song;
    song_counter++;
  }
  return NULL;
} /* modify_song_by_index() */

/*
 * This function takes a particular song given the index, the second
 * parameter, and moves it to the tail. The first parameter, song_ptr,
 * points to the head of a list. The second parameter, song_counter, is
 * used to locate a particular song.
 */

song_t *move_to_tail(song_t * song_ptr, int song_counter) {
  assert(song_counter >= 0);
  assert(song_counter <= count_songs(song_ptr));

  int index_counter = 1;
  song_t* current_song = song_ptr;
  while ((index_counter < song_counter) && (current_song != NULL)) {
    current_song = current_song->next_song;
    index_counter++;
  }

  song_t* nth_song = current_song;

  while (current_song->next_song != NULL) {
    current_song = current_song->next_song;
  }

  current_song->next_song = song_ptr;

  song_t* head_song = nth_song->next_song;
  nth_song->next_song = NULL;
  return head_song;
} /* move_to_tail() */

/*
 * This function will combine two lists by alternating the
 * the song elements.The fist parameter points to the head of
 * the first list, while the second parameter points to the head
 * of the second list.
 */

song_t *interleave_songs(song_t * song_ptr1, song_t * song_ptr2) {
  assert(song_ptr1 != NULL);
  assert(song_ptr2 != NULL);

  if ((count_songs(song_ptr2)) > (count_songs(song_ptr1))) {
    while ((song_ptr1 != NULL) && (song_ptr2 != NULL)) {
      song_t* current_song2 = song_ptr2->next_song;
      song_ptr2->next_song = song_ptr1;
      song_ptr1 = current_song2;
      song_ptr2 = song_ptr2->next_song;
    }
    return song_ptr2;
  }

  song_t *current_song1 = song_ptr1;
  while ((song_ptr1 != NULL) && (song_ptr2 != NULL)) {
    current_song1 = song_ptr1->next_song;
    song_ptr1->next_song = song_ptr2;
    song_ptr2 = current_song1;
    song_ptr1 = song_ptr1->next_song;
  }
  return song_ptr1;

} /* interleave_songs() */

/*
 * This function takes a list and frees all of the
 * songs in the list. The first parameter, song_ptr,
 * points to the head of the list.
 */

void free_song_list(song_t * song_ptr) {
  song_t *temp_song = song_ptr;
  while (song_ptr != NULL) {
    temp_song = song_ptr;
    song_ptr = song_ptr->next_song;
    free(temp_song->artist);
    free(temp_song->title);
    free(temp_song);
  }
} /* free_song_list() */
