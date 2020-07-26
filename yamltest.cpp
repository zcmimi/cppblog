#include<yaml.h>

yaml_parser_t parser;
yaml_event_t event;

int main(){

int done = 0;

/* Create the Parser object. */
yaml_parser_initialize(&parser);

/* Set a string input. */
char *input = "...";
size_t length = strlen(input);

yaml_parser_set_input_string(&parser, input, length);

/* Set a file input. */
FILE *input = fopen("...", "rb");

yaml_parser_set_input_file(&parser, input);

/* Set a generic reader. */
void *ext = ...;
int read_handler(void *ext, char *buffer, int size, int *length) {
    /* ... */
    *buffer = ...;
    *length = ...;
    /* ... */
    return error ? 0 : 1;
}

yaml_parser_set_input(&parser, read_handler, ext);

/* Read the event sequence. */
while (!done) {

    /* Get the next event. */
    if (!yaml_parser_parse(&parser, &event))
        goto error;

    /*
      ...
      Process the event.
      ...
    */

    /* Are we finished? */
    done = (event.type == YAML_STREAM_END_EVENT);

    /* The application is responsible for destroying the event object. */
    yaml_event_delete(&event);

}

/* Destroy the Parser object. */
yaml_parser_delete(&parser);

return 1;

/* On error. */
error:

/* Destroy the Parser object. */
yaml_parser_delete(&parser);

return 0;
Emitter API Synopsis
#include <yaml.h>

yaml_emitter_t emitter;
yaml_event_t event;

/* Create the Emitter object. */
yaml_emitter_initialize(&emitter);

/* Set a file output. */
FILE *output = fopen("...", "wb");

yaml_emitter_set_output_file(&emitter, output);

/* Set a generic writer. */
void *ext = ...;
int write_handler(void *ext, char *buffer, int size) {
    /*
       ...
       Write `size` bytes.
       ...
    */
    return error ? 0 : 1;
}

yaml_emitter_set_output(&emitter, write_handler, ext);

/* Create and emit the STREAM-START event. */
yaml_stream_start_event_initialize(&event, YAML_UTF8_ENCODING);
if (!yaml_emitter_emit(&emitter, &event))
    goto error;

/*
  ...
  Emit more events.
  ...
*/

/* Create and emit the STREAM-END event. */
yaml_stream_end_event_initialize(&event);
if (!yaml_emitter_emit(&emitter, &event))
    goto error;

/* Destroy the Emitter object. */
yaml_emitter_delete(&emitter);

return 1;

/* On error. */
error:

/* Destroy the Emitter object. */
yaml_emitter_delete(emitter);

return 0;
}